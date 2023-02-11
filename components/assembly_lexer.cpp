/*
 *  @name   lexer.cpp
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

/****************************** - Library Includes - *******************************/

#include <fstream>
#include <filesystem>
#include <list>

/******************************** - User Includes - ********************************/

#include "includes/assembly_lexer.hpp"

/*********************************** - Defines - ***********************************/

#define STATE_MULTILINE_COMMENT  (1U << 0)
#define STATE_SINGLELINE_COMMENT (1U << 1)

/************************************ - Enums - ************************************/
/*********************************** - Classes - ***********************************/
/**************************** - Function Prototypes - ******************************/
std::size_t stringToSSize_t(std::string str);
inline std::string string_remove_repeats(std::string blk , std::string rep_delim);
/********************************* - Constants - ***********************************/
/********************************* - Variables - ***********************************/
/******************************* - Public Methods - ********************************/

assembly_lexer::assembly_lexer()
{
  lexed_source_path = "./.lexed_source.asm";
  this->current_line = 0;
}

assembly_lexer::assembly_lexer( std::string file_to_process )
{
  //This contains the path to the source assembly file
  this->current_line = 0;
  this->source_file_path = file_to_process;
  this->source_file.open(source_file_path);
  if( true == this->source_file.is_open() )
  {
    //This contains the path to the temporary source file for lexing
    this->source_file.close();
    this->lexed_source_path = "./.lexed_source.asm";

    this->lexing_thread = std::thread( &assembly_lexer::format_source_file , this );
    this->lexing_thread.join();
  }

}

std::string assembly_lexer::get_temp_file()
{
  return this->lexed_source_path;
}

nlohmann::json assembly_lexer::get_subroutine_data()
{
  return this->subroutine_data;
}

/******************************* - Private Methods - *******************************/

void assembly_lexer::format_source_file()
{
  this->source_file.open(this->source_file_path);
  this->lexed_source_file.open(this->lexed_source_path);
  this->state_in_multi_line_comment = false;
  while( false == this->source_file.eof() )
  {
    this->file_read_block();
    this->process_line();
    if( this->read_line.empty() == false )
    {
        this->lexed_source_file << this->read_line << std::endl;
    }
  }
  this->source_file.close();
  this->lexed_source_file.close();
}

void assembly_lexer::file_read_block()
{
  std::getline( this->source_file , this->read_line );
}

void assembly_lexer::process_line()
{
  this->remove_comments();
  this->read_line = string_remove_repeats( this->read_line , " ");
  this->line_collect_subroutines();

//This code replaces the space after the instruction to a comma
  size_t first_pos = this->read_line.find_first_not_of( " " , 0);
  if ( this->read_line.find( " " , (first_pos == std::string::npos) ? std::string::npos : first_pos ) != std::string::npos )
  {
      this->read_line.replace( this->read_line.find( " " , first_pos ) , 1 , "," );
  }
  this->read_line.erase(std::remove(this->read_line.begin(), this->read_line.end(), ' '), this->read_line.end());
}

void assembly_lexer::line_collect_subroutines()
{

  if( this->read_line.empty() == false )
  {
    size_t subroutine_pos = this->read_line.find( ":" , 0 );
    if( subroutine_pos != std::string::npos )
    {
      std::string subroutine_name( this->read_line , 0 , subroutine_pos );
      this->read_line.erase( 0 , subroutine_pos + 1);

      if( this->read_line.empty() == true )
      {
          this->subroutine_data[subroutine_name] = this->current_line + 1;
      }
      else
      {
          this->subroutine_data[subroutine_name] = this->current_line;
      }

    }
    else
    {
      this->current_line++;
    }

  }
}

void assembly_lexer::remove_comments()
{
  size_t comment_start_delim_pos = this->read_line.find( "/*" , 0 );
  size_t comment_end_delim_pos = this->read_line.find( "*/" , (comment_start_delim_pos == std::string::npos) ? 0 : comment_start_delim_pos + 2);
  if( comment_start_delim_pos != std::string::npos )
  {
      this->state_in_multi_line_comment = true;
  }
  if( this->state_in_multi_line_comment == true )
  {
      if( comment_end_delim_pos != std::string::npos )
      {
        this->state_in_multi_line_comment = false;
        comment_end_delim_pos += 3;
      }
      comment_start_delim_pos = (comment_start_delim_pos == std::string::npos) ? 0 : comment_start_delim_pos ;
      this->read_line.erase( comment_start_delim_pos , comment_end_delim_pos );
  }
  comment_start_delim_pos = this->read_line.find( ";" , 0 );
  if( comment_start_delim_pos != std::string::npos )
  {
      this->read_line = this->read_line.erase( comment_start_delim_pos , this->read_line.length() );
  }
}

/***************************** - Public Functions - ********************************/
/***************************** - Private Functions - *******************************/

inline std::string string_remove_repeats(std::string blk , std::string rep_delim)
{
  size_t rep_pos = 0;
  while ( 1 )
  {
    rep_pos = blk.find( rep_delim + rep_delim , 0 );
    if( rep_pos != std::string::npos )
    {
      blk = blk.replace( rep_pos , std::string(rep_delim + rep_delim).length() , rep_delim );
    }
    else
    {
      break;
    }
  }
  return blk;
}
