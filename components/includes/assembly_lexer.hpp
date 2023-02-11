/*
 *  @name   lexer.h
 *  @date   05/02/2023
 *  @author bdc1g19
 *
 *
 */

#ifndef COMPONENTS_LEXER_H
#define COMPONENTS_LEXER_H

/****************************** - Library Includes - *******************************/

#include <iostream>
#include <string>
#include <thread>

#include <nlohmann/json.hpp>

/******************************** - User Includes - ********************************/
/*********************************** - Defines - ***********************************/
/************************************ - Enums - ************************************/
/********************************** - Typedefs - ***********************************/
/********************************** - Classes - ************************************/

class assembly_lexer
{
  public:
    assembly_lexer();
    assembly_lexer( std::string file_to_process );

    std::string    get_temp_file();
    nlohmann::json get_subroutine_data();

  private:

    void        format_source_file();

    void        file_read_block();
    void        process_line();
    void        remove_comments();
    void        line_collect_subroutines();

    std::string string_remove_delim( std::string line , std::string delim , size_t offset );


    std::thread    lexing_thread;

    std::string    source_file_path;
    std::ifstream  source_file;

    std::string    lexed_source_path;
    std::ofstream  lexed_source_file;

    std::string    read_line;
    size_t         current_line;
    bool           state_in_multi_line_comment;

    nlohmann::json subroutine_data;

};

/**************************** - Function Prototypes - ******************************/
/****************************** - Global Variables - *******************************/

#endif //COMPONENTS_ASSEMBLER_H
