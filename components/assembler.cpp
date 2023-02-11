/*
 *  @name   assembler.h
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

/****************************** - Library Includes - *******************************/

#include <fstream>
#include <sstream>
#include <bitset>

/******************************** - User Includes - ********************************/

#include "includes/assembler.hpp"

/*********************************** - Defines - ***********************************/

#define ASSEMBLER_OPCODE_LENGTH             (6U)
#define ASSEMBLER_REGISTER_ADDRESS_LENGTH   (5U)
#define ASSEMBLER_IMMEDIANT_LENGTH          (8U)
#define ASSEMBLER_ADDRESS_LENGTH            (ASSEMBLER_INSTRUCTION_LEN - ASSEMBLER_OPCODE_LENGTH)
#define ASSEMBLER_SHAMT_LENGTH              (ASSEMBLER_IMMEDIANT_LENGTH - 4U)
#define ASSEMBLER_FUNCT_LENGTH              (ASSEMBLER_IMMEDIANT_LENGTH - 4U)

#define ASSEMBLER_INSTRUCTION_LEN           (ASSEMBLER_OPCODE_LENGTH + 2*ASSEMBLER_REGISTER_ADDRESS_LENGTH + ASSEMBLER_IMMEDIANT_LENGTH)

/************************************ - Enums - ************************************/
/*********************************** - Classes - ***********************************/

typedef struct
{
  std::bitset<ASSEMBLER_OPCODE_LENGTH> opcode;
  std::bitset<ASSEMBLER_REGISTER_ADDRESS_LENGTH> rs;
  std::bitset<ASSEMBLER_REGISTER_ADDRESS_LENGTH> rt;
  std::bitset<ASSEMBLER_SHAMT_LENGTH> shamt;
  std::bitset<ASSEMBLER_FUNCT_LENGTH> func;
  std::bitset<ASSEMBLER_IMMEDIANT_LENGTH> immediant;
  std::bitset<ASSEMBLER_ADDRESS_LENGTH> address;
}instruction_t;

/**************************** - Function Prototypes - ******************************/

std::size_t stringToSize_t(std::string str);
bool        is_number(const std::string& s);

/********************************* - Constants - ***********************************/
/********************************* - Variables - ***********************************/
/******************************* - Public Methods - ********************************/

assembler::assembler( std::string input_arch_info_loc , std::string source_assembly_loc , std::string in_output_dir )
          : lexer( source_assembly_loc )
{
  this->file_path_architecture_info = input_arch_info_loc;
  this->file_path_assembly_source   = source_assembly_loc;
  this->file_path_output            = in_output_dir;

  this->file_architecture_info.open(file_path_architecture_info);
  this->file_assembly_source.open(file_path_assembly_source);
  //this->file_output_verilog.open(file_path_output);
  try
  {
    this->architecture_data = nlohmann::json::parse(file_architecture_info);
  }
  catch (nlohmann::json::parse_error& e)
  {
    std::cout << "❌ JSON Parse error ❌" << std::endl;
    std::cout << " - Cause: " << e.what() << std::endl;
  }

  this->file_architecture_info.close();
  if( this->architecture_data.end() == this->architecture_data.find("registers") )
  {
    std::cout << "❌Failed to find register information❌" << std::endl;
  }
  else
  {
    this->json_processing_thread = std::thread( &assembler::process_arch_json , this );
    this->json_processing_thread.join();
    this->file_assembly_source.close();
    assemble_code();

    std::filesystem::remove(".lexed_source.asm");

  }

}

/******************************* - Private Methods - *******************************/

void assembler::write_output_header()
{
  this->file_output_verilog << "//This file was generated by the picoMIPs assembler" << "\n";
  this->file_output_verilog << "//Instruction field lengths are as follows:" << "\n";
  this->file_output_verilog << "//  - Opcode " << ASSEMBLER_OPCODE_LENGTH << "\n";
  this->file_output_verilog << "//  - Registers Address " << ASSEMBLER_REGISTER_ADDRESS_LENGTH << "\n";
  this->file_output_verilog << "//  - Jump Address " << ASSEMBLER_ADDRESS_LENGTH << "\n";
  this->file_output_verilog << "//  - Total length: " << ASSEMBLER_INSTRUCTION_LEN << "\n";
  this->file_output_verilog << "// HEX              BINARY           Instruction in Assembly" << std::endl;
}

void assembler::assemble_code()
{
    std::string line;
    std::string machine_code;
    this->file_assembly_source.open( ".lexed_source.asm" );
    this->file_output_verilog.open(file_path_output);
    this->current_line = 0;

    std::string machine_code_out;

    if( this->file_assembly_source.is_open() == true )
    {
      write_output_header();
      while ( this->file_assembly_source.eof() == false )
      {
        std::getline( this->file_assembly_source , this->line_contents );
        if( false == this->line_contents.empty() )
        {
          line = this->line_contents;
          machine_code_out = this->convert_machine_code( line );
          this->file_output_verilog << std::setw(ASSEMBLER_INSTRUCTION_LEN/4) <<
                  std::setfill('0') << std::hex << std::stoll( machine_code_out , nullptr , 2);

          this->file_output_verilog << "\t\t\t//" << machine_code_out << "\t\t\t" << this->line_contents << std::endl;
          this->current_line++;
        }
      }
    }
    this->current_line = 0;
    this->file_output_verilog.close();
}


std::string assembler::convert_machine_code( std::string line )
{
  size_t      pos = 0;
  size_t      iterations = 0;
  std::string token;
  std::string output;

  while( (pos != std::string::npos) && (line.empty() == false) )
  {
    pos = line.find(",",0);
    token = std::string(line , 0 , pos);
    line = line.erase(0 , pos + 1);

    output = output + assembler_process_token( token , iterations );

    iterations++;
  }

  while ( output.length() < (ASSEMBLER_INSTRUCTION_LEN  - 1) )
  {
    output = output + '0';
  }

  return output;
}

std::string assembler::assembler_process_token( std::string token , size_t iterations )
{
  std::string return_string;
  std::string sub_name;
  if( nullptr != this->architecture_data["registers"][token] )
  {
    std::bitset<ASSEMBLER_REGISTER_ADDRESS_LENGTH> bits( this->architecture_data["registers"][token] );
    return_string = bits.to_string();
  }
  if( nullptr != this->architecture_data["instructions"][token] )
  {
    std::bitset<ASSEMBLER_REGISTER_ADDRESS_LENGTH> bits( this->architecture_data["instructions"][token] );
    return_string = bits.to_string();
  }
  if( true == return_string.empty() )
  {
    nlohmann::json subroutines = this->lexer.get_subroutine_data();
    if( nullptr != subroutines[token] )
    {
      if(iterations > 2)
      {
        ssize_t value = subroutines[token].get<ssize_t>() - current_line;
        std::bitset<ASSEMBLER_IMMEDIANT_LENGTH> bits( value );
        this->line_contents.insert( this->line_contents.find(token,0) , std::to_string(value) + " [" );
        this->line_contents.push_back(']');
        return_string = bits.to_string();
      }
      else
      {
        std::bitset<ASSEMBLER_ADDRESS_LENGTH> bits( subroutines[token] );
        this->line_contents.insert( this->line_contents.find(token,0) , std::to_string( subroutines[token].get<ssize_t>()) + " [" );
        this->line_contents.push_back(']');
        return_string = bits.to_string();
      }
    }
    else if( true == is_number(token) )
    {
      //Jumps are just <Instruction> <ADDRESS>
      //Branches are <instruction> <reg> <reg> <offset>
      if(iterations > 2)
      {
        std::bitset<ASSEMBLER_IMMEDIANT_LENGTH> bits( stringToSize_t(token) );
        return_string = bits.to_string();
      }
      else
      {
        std::bitset<ASSEMBLER_ADDRESS_LENGTH> bits( stringToSize_t(token) );
        return_string = bits.to_string();
      }
    }
    else
    {
      std::cout << "❌Unknown Token '" << token << "' in file❌" << std::endl;
    }
  }

  return return_string;
}

void assembler::process_arch_json()
{
  nlohmann::json architecture_info;
  auto register_data = process_field("registers");
  auto instruction_data = process_field("instructions");

  if( (std::get<0>(register_data) == true) && (std::get<0>(instruction_data) == true) )
  {
      std::get<1>(register_data).update(std::get<1>(instruction_data));
      this->architecture_data = std::get<1>(register_data);
  }
}

std::tuple<bool, nlohmann::json> assembler::process_field(std::string field )
{
  nlohmann::json processed_json;
  std::string current_key;
  std::string current_value;

  //Iterate through the field assembling the table of values
  for (auto& iter : architecture_data[field].items())
  {
      current_key   = iter.key();
      current_value = to_string(iter.value());

      /*Search in the key field for a -, this indicates a range*/
      if( std::string::npos == current_key.find("-") )
      {
        processed_json[field][ current_key ] = stringToSize_t(current_value);
      }
      else
      {
          //Remove whitespace and [] of the values
          current_value = assembler::remove_whitespace(current_value);
          current_value = current_value.erase( current_value.find("[") , 1  );
          current_value = current_value.erase( current_value.find("]") , 1  );
          current_key   = assembler::remove_whitespace(current_key);

          auto key_range   = json_extract_tokens( current_key , "-" );
          auto value_range = json_extract_tokens( current_value , "," );

          for (size_t idx = std::get<0>(key_range); idx <= std::get<1>(key_range); idx++)
          {
            processed_json[field][ std::get<2>(key_range) + std::to_string(idx) ] = std::get<0>(value_range) + idx;
          }
      }

  }
  return std::make_tuple(true , processed_json );
}

std::string assembler::remove_whitespace(std::string to_rm)
{
  while( std::string::npos != to_rm.find(" ") )
  {
    to_rm.erase(to_rm.find(" ") , 1);
  }
  return to_rm;
}

std::tuple<size_t, size_t, std::string> assembler::json_extract_tokens( std::string to_conv , std::string delim )
{
  size_t      lower_val = 10;
  size_t      upper_val = 10;
  std::string temp_string = to_conv.substr( to_conv.find(delim) + 1, to_conv.back() );
  temp_string = temp_string.substr( temp_string.find_first_of( "0123456789" ) , to_conv.find(delim) + 1 );
  upper_val = stringToSize_t( temp_string );

  temp_string = to_conv.substr( 0 , to_conv.find(delim) );
  temp_string = temp_string.substr( temp_string.find_first_of( "0123456789" , 0 ) , temp_string.find(delim) );
  lower_val = stringToSize_t( temp_string );

  std::string token_name = to_conv.substr( 0 , to_conv.find_first_of( "0123456789" ) );

  return std::make_tuple(lower_val , upper_val , token_name );
}

/***************************** - Public Functions - ********************************/
/***************************** - Private Functions - *******************************/

std::size_t stringToSize_t(std::string str)
{
	std::stringstream sstream(str);
	size_t result;
	sstream >> result;
	return result;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
