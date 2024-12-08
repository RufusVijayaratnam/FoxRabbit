cmake_minimum_required(VERSION 3.30)
enable_testing()
get_filename_component(ProjectDirName ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${ProjectDirName} VERSION 2.0.0 LANGUAGES CXX)
# Enable generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set C++ standard and CUDA standard
set(CMAKE_CXX_STANDARD 23)
find_package(Boost REQUIRED COMPONENTS program_options)
# Add the executable with the name of the current directory
add_executable(${PROJECT_NAME} main.cpp)
# Add library target for the components, including any CUDA files
add_library(FRComponents STATIC 
    src/Animal.cpp
    )
# Include directories for our project
target_include_directories(FRComponents PUBLIC includes)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
# Link the library with our executable
target_link_libraries(${PROJECT_NAME} PRIVATE FRComponents ${Boost_LIBRARIES})
# Set custom compile options for different build types
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Sanitize>:-fsanitize=address>
    $<$<CONFIG:Release>:-O3>
)
target_compile_options(FRComponents PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Sanitize>:-fsanitize=address>
    $<$<CONFIG:Release>:-O3>
)
target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Sanitize>:-fsanitize=address>
)
target_link_options(FRComponents PRIVATE
    $<$<CONFIG:Sanitize>:-fsanitize=address>
)
# Define DEBUG macro for Debug configuration
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)
target_compile_definitions(FRComponents PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

# check if verbose build
option(VERBOSE "Enable verbose output" OFF)
if(VERBOSE)
    add_definitions(-DVERBOSE)
endif()
