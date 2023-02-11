#Define the headers
set(HEADER_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/includes/assembler.hpp
      ${CMAKE_CURRENT_SOURCE_DIR}/includes/assembly_lexer.hpp
    )
set(COMPONENT_HEADERS ${HEADER_FILES} PARENT_SCOPE)

#Create the component library
add_library(COMPONENTS
  ${HEADER_FILES}
  assembler.cpp
  assembly_lexer.cpp
)

target_include_directories( COMPONENTS PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  )

message(STATUS "AMOGUS")
