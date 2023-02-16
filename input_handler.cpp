/*
 *  @name   input_handler.cpp
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

/****************************** - Library Includes - *******************************/

#include <iostream>
#include <fstream>

/******************************** - User Includes - ********************************/

#include "input_handler.hpp"

/*********************************** - Defines - ***********************************/

#define ARGUMENT_LONG_INSTRUCTIONS  "--defines"
#define ARGUMENT_SHORT_INSTRUCTIONS "-d"

#define ARGUMENT_LONG_SOURCE        "--source"
#define ARGUMENT_SHORT_SOURCE       "-s"

#define ARGUMENT_LONG_OUTPUT        "--output"
#define ARGUMENT_SHORT_OUTPUT       "-o"

/************************************ - Enums - ************************************/
/*********************************** - Classes - ***********************************/
/**************************** - Function Prototypes - ******************************/
/********************************* - Constants - ***********************************/
/********************************* - Variables - ***********************************/
/******************************* - Public Methods - ********************************/
input_handler::input_handler()
{

}

input_handler::input_handler(int argc , char** argv)
{
  //The command to call the programs seems to count in this
  this->argc = argc - 1;
  this->argv = &argv[1];

  assemble_arguments();

}

std::string input_handler::get_instruction_path()
{
  std::string ret_string;
  if( false == instructions.empty() )
  {
    ret_string = this->instructions;
  }
  else
  {
    std::ifstream source_file;
    std::cout << "No architecutre data file provided in arguments, provide file here:" << std::endl;

    std::cin >> ret_string;
    source_file.open(ret_string);
    if( true == source_file.fail() )
    {
      std::cout << "❌ Failed to find file: " << ret_string << std::endl;
    }

  }

  return ret_string;
}

std::string input_handler::get_source_path()
{
  std::string ret_string;
  if( false == source_assembly.empty() )
  {
    ret_string = this->source_assembly;
  }
  else
  {
    std::ifstream source_file;
    std::cout << "No source file provided in arguments, provide file here:" << std::endl;

    std::cin >> ret_string;
    source_file.open(ret_string);
    if( false == source_file.fail() )
    {
      std::cout << "❌ Failed to find file: " << ret_string << std::endl;
    }

  }

  return ret_string;
}

std::string input_handler::get_output_path()
{
  std::string ret_string;
  if( false == this->output.empty() )
  {
    ret_string = this->output;
  }
  else
  {

    std::cout << "No output file provided in arguments, provide file here:" << std::endl;
    std::cin >> ret_string;

  }

  return ret_string;
}

bool input_handler::successful()
{
  return !(this->instructions.empty() && this->source_assembly.empty() && this->output.empty());
}

/******************************* - Private Methods - *******************************/

void input_handler::assemble_arguments()
{
  for (int idx = 0; !(this->argc % 2) && (idx < this->argc); idx+=2)
  {

    this->map_arguments( this->argv[idx] , this->argv[idx + 1] );

  }

}

void input_handler::map_arguments( char* arg_opt , char* arg_val )
{

  if ( (std::string(arg_opt) == ARGUMENT_LONG_INSTRUCTIONS) || (std::string(arg_opt) == ARGUMENT_SHORT_INSTRUCTIONS) )
  {
    this->instructions = std::string(arg_val);

    std::ifstream source_file;
    source_file.open(this->instructions);
    std::cout << "Checking " << this->instructions << " exists" << std::endl;
    if( true == source_file.fail() )
    {
      std::cout << "❌ Failed to find file: " << this->instructions << std::endl;
      this->instructions.clear();
    }
    else
    {
      std::cout << "Found " << this->instructions << std::endl;
    }

  }
  else if ( (std::string(arg_opt) == ARGUMENT_LONG_SOURCE) || (std::string(arg_opt) == ARGUMENT_SHORT_SOURCE) )
  {
    this->source_assembly = std::string(arg_val);

    std::ifstream source_file;
    source_file.open(this->source_assembly);
    std::cout << "Checking " << this->source_assembly << " exists" << std::endl;
    if( true == source_file.fail() )
    {
      std::cout << "❌ Failed to find file: " << this->source_assembly << std::endl;
      this->source_assembly.clear();
    }
    else
    {
      std::cout << "Found " << this->source_assembly << std::endl;
    }

  }
  else if ( (std::string(arg_opt) == ARGUMENT_LONG_OUTPUT) || (std::string(arg_opt) == ARGUMENT_SHORT_OUTPUT) )
  {
    this->output = std::string(arg_val);
  }
}

/***************************** - Public Functions - ********************************/
/***************************** - Private Functions - *******************************/
