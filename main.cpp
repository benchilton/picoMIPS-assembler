/*
 *  @name   main.cpp
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

/****************************** - Library Includes - *******************************/

#include <string>

/******************************** - User Includes - ********************************/

#include "input_handler.hpp"
#include "components/includes/assembler.hpp"

/*********************************** - Defines - ***********************************/
/************************************ - Enums - ************************************/
/*********************************** - Classes - ***********************************/
/**************************** - Function Prototypes - ******************************/
/********************************* - Constants - ***********************************/
/********************************* - Variables - ***********************************/
/***************************** - Public Functions - ********************************/

int main( int argc, char *argv[] )
{
  input_handler handler(argc , argv);

  std::string instruction_set_path = handler.get_instruction_path();
  std::string assembly_file        = handler.get_source_path();
  std::string output_dir_path      = handler.get_output_path();

  if( true == handler.successful() )
  {
    assembler a( instruction_set_path , assembly_file , output_dir_path );
  }
  return 0;
}

/***************************** - Private Functions - *******************************/
