cmake_minimum_required(VERSION 3.16)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# Declare the project
project(sdl-min)

# Set the name of the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME})

target_include_directories(${EXECUTABLE_NAME} PRIVATE E:/libs/glm-1.0.1-light)

target_sources(${EXECUTABLE_NAME} 
PRIVATE 
    src/field.cpp
    src/fruit.cpp
    src/game.cpp
    src/main.cpp
    src/painter.cpp
    src/shader_program.cpp
    src/snake.cpp
)

# use C++11
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)

if(CMAKE_SYSTEM_NAME MATCHES Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

    target_link_options("${EXECUTABLE_NAME}" PRIVATE "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/color.vert@/assets/shaders/color.vert")
    set_property(TARGET "${EXECUTABLE_NAME}" APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/color.vert")

    target_link_options("${EXECUTABLE_NAME}" PRIVATE "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/color.frag@/assets/shaders/color.frag")
    set_property(TARGET "${EXECUTABLE_NAME}" APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/color.frag")
endif()

find_package(SDL3)

# Link SDL to our executable. This also makes its include directory available to us. 
target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL3::SDL3)
target_compile_definitions(${EXECUTABLE_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)
