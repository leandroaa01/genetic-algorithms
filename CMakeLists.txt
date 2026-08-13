cmake_minimum_required(VERSION 3.28.3)
project(Mahl VERSION 1.0 DESCRIPTION "Memetic Algorithm project." LANGUAGES CXX)

# Set the C++ language standard.
#
# Using C++23.
set(CMAKE_CXX_STANDARD 23)
# Require the compiler to support exactly this standard.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flag to set the binaries output directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Flag to generate compile_commands.json (Useful for clangd).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release) # for fastier math calcs
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto -ffast-math")
find_package(OpenMP REQUIRED) # lib to divide the evolve's loop into threads

# Adds the includes directory.
include_directories(include libs)

# Recursively searches for all .cpp files in src/ and subdirectories.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    libs/*.cpp
)

# Create the executable called 'Mahl' using the source files found.
add_executable(Mahl ${SOURCES}
                    )

# Adds the include directories to the 'Mahl' target.
target_include_directories(Mahl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX) # lib to divide the evolve's loop into threads

# Set compilation flags.
target_compile_options(Mahl PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wno-deprecated
    -O3
)

# option(RT3_DEBUG "Enables debug logs." OFF)

# if(RT3_DEBUG)
#     target_compile_definitions(Mahl PRIVATE RT3_DEBUG_MODE=1)
# endif()
