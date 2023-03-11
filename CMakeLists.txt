# CMakeList.txt : CMake project for chk_software, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project("chk_software")

add_subdirectory("ext")

# Add source to this project's executable.
add_executable(chk_software
  "src/chk_colors.cpp"
  "src/chk_colors.h" 
  "src/chk_command_list.h" 
  "src/chk_common.cpp"
  "src/chk_common.h"
  "src/chk_dbg.cpp"
  "src/chk_dbg.h"
  "src/chk_math.h"
  "src/chk_software.cpp"
  "src/chk_software.h"
  "src/chk_window.cpp"
  "src/chk_window.h" 
)

target_link_libraries(chk_software glm::glm fmt::fmt glfw)
target_compile_features(chk_software PUBLIC cxx_std_17)


if (MSVC)
	# Enable Hot Reload for MSVC compilers if supported.
	if (POLICY CMP0141)
	  cmake_policy(SET CMP0141 NEW)
	  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
	endif()
	
	if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd /Zi /Ob0 /Od /RTC1")
	endif()
endif()

# TODO: Add tests and install targets if needed.
