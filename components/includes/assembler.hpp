/*
 *  @name   assembler.h
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

#ifndef COMPONENTS_ASSEMBLER_H
#define COMPONENTS_ASSEMBLER_H

/****************************** - Library Includes - *******************************/

#include <iostream>
#include <string>
#include <tuple>
#include <thread>

#include <nlohmann/json.hpp>

/******************************** - User Includes - ********************************/

#include "includes/assembly_lexer.hpp"

/*********************************** - Defines - ***********************************/
/************************************ - Enums - ************************************/
/********************************** - Typedefs - ***********************************/
/********************************** - Classes - ************************************/

class assembler
{
  public:
    assembler();
    assembler( std::string file_path_architecture_info , std::string assembly_file , std::string in_output_dir );

  private:
//Private Methods

    void                                    process_arch_json();
    std::tuple<bool, nlohmann::json>        process_field(std::string field );
    std::tuple<size_t, size_t, std::string> json_extract_tokens( std::string to_conv , std::string delim );
    std::string                             remove_whitespace(std::string to_rm);

    void                                    assemble_code();
    void                                    write_output_header();

    std::string  assembler_process_token( std::string token , size_t iterations );
    std::string convert_machine_code( std::string line );

//Private Data

    std::string    file_path_architecture_info;
    std::string    file_path_assembly_source;
    std::string    file_path_output;

    std::ifstream  file_architecture_info;
    std::ifstream  file_assembly_source;
    std::ofstream  file_output_verilog;

    nlohmann::json architecture_data;

    assembly_lexer lexer;

    std::thread    json_processing_thread;

    size_t         current_line;
    std::string    line_contents;

};

/**************************** - Function Prototypes - ******************************/
/****************************** - Global Variables - *******************************/

#endif //COMPONENTS_ASSEMBLER_H
