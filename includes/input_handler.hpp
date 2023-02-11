/*
 *  @name   input_handler.hpp
 *  @date   04/02/2023
 *  @author bdc1g19
 *
 *
 */

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

/****************************** - Library Includes - *******************************/

#include <string>

/******************************** - User Includes - ********************************/
/*********************************** - Defines - ***********************************/
/************************************ - Enums - ************************************/
/********************************** - Typedefs - ***********************************/
/********************************* - Structures - **********************************/

class input_handler
{
public:
  input_handler();
  input_handler(int argc , char* argv[]);

  std::string get_instruction_path();
  std::string get_source_path();
  std::string get_output_path();

  bool        successful();

private:

  void        map_arguments( char* arg_opt , char* arg_val );
  std::string search_for_arg( char* arg_to_find );
  void        assemble_arguments();

  int    argc;
  char** argv;

  std::string   instructions;
  std::string   source_assembly;
  std::string   output;

};

/**************************** - Function Prototypes - ******************************/
/****************************** - Global Variables - *******************************/

#endif //INPUT_HANDLER_H
