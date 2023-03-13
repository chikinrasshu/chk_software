# CMakeList.txt : CMake project for chk_software, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project("chk_software")

add_subdirectory("ext")

# Visual Studio Specific stuff
if(MSVC)
  # Enable Hot Reload for MSVC compilers if supported.
  if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
    )
  endif()

  if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL
                                          "RelWithDebInfo")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Ob0 /Od /RTC1")
  endif()
endif()

# Add source to this project's executable.
add_executable(
  chk_software
  "cpp.hint"
  "src/chk_software.cpp"
  "src/chk_software.h"
  "src/common/chk_colors.cpp"
  "src/common/chk_colors.h"
  "src/common/chk_common.cpp"
  "src/common/chk_common.h"
  "src/common/chk_dbg.cpp"
  "src/common/chk_dbg.h"
  "src/common/chk_math.h"
  "src/common/chk_path.cpp"
  "src/common/chk_path.h"
  "src/renderer/chk_bitmap.cpp"
  "src/renderer/chk_bitmap.h"
  "src/renderer/chk_command_list.h"
  "src/renderer/chk_renderer.h"
  "src/soft/chk_soft_renderer.h"
  "src/window/chk_window.cpp"
  "src/window/chk_window.h"
  "src/soft/chk_soft_renderer.cpp"
  "src/soft/chk_opengl.h"
  "src/soft/chk_opengl.cpp")

target_link_libraries(chk_software glm::glm fmt::fmt glfw glad_gl_core_41 whereami)
target_compile_features(chk_software PUBLIC cxx_std_17)

# TODO: Add tests and install targets if needed.
