cmake_minimum_required(VERSION 3.16)
project(RoughCopy LANGUAGES CXX)

# Use C++17 (or 20 if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)


set(CMAKE_AUTOMOC ON)   
set(CMAKE_AUTOUIC ON)   
set(CMAKE_AUTORCC ON)

# Collect all source files recursively inside src/
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h

    # src/highlighters/*.cpp
    # src/highlighters/*.h
    # src/highlighters/language_highlighters/*.cpp
    # src/highlighters/language_highlighters/*.h
)

# Create the executable
add_executable(RoughCopy ${SOURCES})

# Link with Qt6
target_link_libraries(RoughCopy PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# (Optional) Ensure correct include paths for headers
target_include_directories(RoughCopy PRIVATE src)
