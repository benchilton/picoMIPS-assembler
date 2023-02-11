cmake_minimum_required(VERSION 3.21)

set(PROJECT builtProject)

project(${PROJECT})

#Conan
add_definitions("-std=c++2a")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(components)

set(HEADER_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/includes/main.hpp
    )

set(HEADER_LOCATIONS
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

#Add .c files to the project
add_executable(${PROJECT}
  ${HEADER_FILES}
  ${COMPONENT_HEADERS}
  main.cpp
)

target_include_directories( ${PROJECT} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  ${CMAKE_CURRENT_SOURCE_DIR}/components/includes
  )

target_link_libraries( ${PROJECT} PUBLIC COMPONENTS)
target_link_libraries( ${PROJECT} ${CONAN_LIBS})
