# Minimum CMake version required. Choose a version you know is installed,
# or a reasonably recent one like 3.10 or higher.
cmake_minimum_required(VERSION 3.10)

# Define the project name and specify C++ as the language.
project(MySFMLApp LANGUAGES CXX)

# Set the C++ standard to use. C++17 is a good modern choice.
# CMAKE_CXX_STANDARD_REQUIRED ON ensures this standard is enforced.
# CMAKE_CXX_EXTENSIONS OFF prevents compiler-specific extensions (good practice).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_include_directories(./src/ PRIVATE includes)

# --- Finding SFML ---
# This is the core part for SFML.
# find_package attempts to locate the SFML library configuration files.
# VERSION 2.5 specifies we need at least SFML version 2.5 (adjust if needed).
# REQUIRED means CMake will stop with an error if SFML is not found.
# COMPONENTS lists the specific SFML modules your project needs.
# Common components: system, window, graphics, audio, network
# List only the ones you actually use!
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics) # Add audio network if needed

# --- Your Project Code ---
# Add your executable target.
# The first argument is the name of the executable file that will be built.
# The following arguments are your source code files (.cpp, .h if needed for IDEs).
add_executable(calculator ./src/main.cpp ./src/entities.cpp ./src/helpers.cpp) # Add other .cpp files here if you have them

# --- Linking SFML ---
# This links your executable (MySFMLApp) against the SFML libraries found earlier.
# Modern SFML (found via find_package) provides "imported targets" like SFML::system,
# SFML::window, etc. Linking against these automatically handles include directories
# and library paths for you. This is the preferred way.
if(SFML_FOUND)
  target_link_libraries(calculator PRIVATE sfml-system sfml-window sfml-graphics)
  # If the above line gives errors on your system (depends on how SFML provides targets),
  # try the modern target names instead:
  # target_link_libraries(MySFMLApp PRIVATE SFML::System SFML::Window SFML::Graphics) # Add SFML::Audio SFML::Network if needed

  # Note: You usually only need ONE of the target_link_libraries lines.
  # The `sfml-component` form is common, but `SFML::Component` is the more modern CMake way.
  # Use the one that works with your SFML installation.
endif()

# --- Optional: Include Directories (Usually not needed with modern SFML targets) ---
# If you link with SFML::system etc., CMake usually handles include paths automatically.
# If you encounter "header file not found" errors, you might need to uncomment
# the following line, but try without it first.
# if(SFML_FOUND)
#   target_include_directories(MySFMLApp PRIVATE ${SFML_INCLUDE_DIR})
# endif()

# --- Optional: Setting Build Type ---
# Allows you to easily switch between Debug and Release builds from the command line.
# Example: cmake .. -DCMAKE_BUILD_TYPE=Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Print a message upon configuration
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "CMake Generator: ${CMAKE_GENERATOR}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "SFML Found: ${SFML_FOUND}")
if(SFML_FOUND)
    message(STATUS "SFML Version: ${SFML_VERSION}")
    message(STATUS "SFML Include Dir: ${SFML_INCLUDE_DIR}") # From older SFML find modules
    message(STATUS "SFML Library Dir: ${SFML_LIBRARY_DIR}") # From older SFML find modules
    message(STATUS "SFML Libraries linked: sfml-system sfml-window sfml-graphics") # Adjust if you changed components or target style
endif()