/*
 *  @name   main.cpp
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

/****************************** - Library Includes - *******************************/

#include <iostream>
#include <fstream>
#include <string>

/******************************** - User Includes - ********************************/

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

  std::string   instruction_set_path;
  std::string   output_dir_path;
  std::string   assembly_file;

  std::ifstream file_check;

  std::cout << "Provide path to Assembly instruction set\n";
  std::cin >> instruction_set_path;
  std::cout << "Going to " << instruction_set_path << std::endl;

  file_check.open(instruction_set_path);

  if( true == file_check.fail() )
  {
    std::cout << "❌ Failed to find file: " << instruction_set_path << std::endl;
  }
  else
  {
    file_check.close();
    std::cout << "✅ Found pointed file" << std::endl;
    std::cout << "Specify Input file:" << std::endl;
    std::cin >> assembly_file;

    file_check.open(assembly_file);
    if( true == file_check.fail() )
    {
      std::cout << "❌ Failed to find file: " << assembly_file << std::endl;
    }
    else
    {
      std::cout << "Specify Output file (Will be produced in cwd):";
      std::cin >> output_dir_path;
      assembler a( instruction_set_path , assembly_file , output_dir_path );
    }
  }
}

/***************************** - Private Functions - *******************************/
