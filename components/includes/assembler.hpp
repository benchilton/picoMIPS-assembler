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
    void                                    write_output_footer();

    std::tuple<std::size_t, ssize_t>        assembler_process_token( std::string token , size_t iterations );
    std::tuple<std::string, std::size_t>    convert_machine_code( std::string line );

    void                                    fill_field_widths(void);

    void                                    JSON_neat_print( std::ostream& stream , std::string field , std::string line_start );

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

    size_t register_size;
    size_t opcode_size;
    size_t immediate_size;
    size_t address_size;
    size_t instruction_size;
    bool   relative_branches;

};

/**************************** - Function Prototypes - ******************************/
/****************************** - Global Variables - *******************************/

#endif //COMPONENTS_ASSEMBLER_H
