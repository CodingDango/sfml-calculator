cmake_minimum_required(VERSION 3.10)

project(SFMLCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics) # Add audio network if needed

add_executable(
  calculator 
  ./src/main.cpp 
  ./src/application.cpp
  ./src/core.cpp 
  ./src/calc.cpp 
  ./src/clipboard.cpp
  ./src/ui_elements.cpp 
  ./src/utils.cpp 
  ./src/input.cpp
) 

target_include_directories(calculator PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_compile_options(calculator PRIVATE "-O3" "-DNDEBUG")

if(SFML_FOUND)
  target_link_libraries(calculator PRIVATE sfml-system sfml-window sfml-graphics)

endif()