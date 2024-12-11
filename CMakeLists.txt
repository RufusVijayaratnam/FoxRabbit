cmake_minimum_required(VERSION 3.30)
enable_testing()

# Get the project directory name
get_filename_component(ProjectDirName ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${ProjectDirName} VERSION 2.0.0 LANGUAGES CXX)

# Enable generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(OpenCV REQUIRED)

# Add the library target
add_library(FRComponents STATIC 
    src/Animal.cpp
    src/Map.cpp
    src/ProgramOptions.cpp
)

# Include directories for FRComponents
target_include_directories(FRComponents PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    includes
)

# Link OpenCV libraries to FRComponents
target_link_libraries(FRComponents PUBLIC 
    ${Boost_LIBRARIES}
    ${OpenCV_LIBS}
)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Include directories for the executable (only Boost)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${Boost_INCLUDE_DIRS}
    includes
)

# Link the library and Boost to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE 
    FRComponents 
)

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

# Set link options
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

# Check if verbose build
option(VERBOSE "Enable verbose output" OFF)
if(VERBOSE)
    add_definitions(-DVERBOSE)
endif()
