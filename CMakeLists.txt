cmake_minimum_required(VERSION 3.14)
project(rd_reborn_c C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

# Fetch GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(glad)

# Fetch stb (single-header)
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(stb)

# Sources
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/c/*.c"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/c)
include_directories(${glad_SOURCE_DIR}/include)
include_directories(${stb_SOURCE_DIR})

add_executable(rd_c_app ${SRC_FILES})

# Link against glfw and glad
target_link_libraries(rd_c_app PRIVATE glfw glad)

# On Windows link opengl32
if (WIN32)
  target_link_libraries(rd_c_app PRIVATE opengl32)
elseif(APPLE)
  find_library(COCOA Cocoa)
  find_library(IOKIT IOKit)
  find_library(COREFOUNDATION CoreFoundation)
  find_library(OPENGL OpenGL)
  target_link_libraries(rd_c_app PRIVATE ${COCOA} ${IOKIT} ${COREFOUNDATION} ${OPENGL})
else()
  find_package(OpenGL REQUIRED)
  target_link_libraries(rd_c_app PRIVATE ${OPENGL_gl_LIBRARY} dl)
endif()

# Copy resources (terrain.png) to build directory for runtime
add_custom_command(TARGET rd_c_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:rd_c_app>/resources
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/src/main/resources/terrain.png $<TARGET_FILE_DIR:rd_c_app>/resources/terrain.png
)
