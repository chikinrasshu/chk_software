# CMakeList.txt : CMake project for chk_software, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project("chk_software")

add_subdirectory("ext")

# Add source to this project's executable.
add_executable(
  chk_software
  "src/chk_common.cpp"
  "src/chk_common.h"
  "src/chk_dbg.cpp"
  "src/chk_dbg.h"
  "src/chk_math.h"
  "src/chk_software.cpp"
  "src/chk_software.h"
  "src/chk_window.cpp"
  "src/chk_window.h")

target_link_libraries(chk_software glm::glm fmt::fmt glfw)
target_compile_features(chk_software PUBLIC cxx_std_17)

# TODO: Add tests and install targets if needed.
