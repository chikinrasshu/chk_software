# CMakeList.txt : CMake project for chk_software, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory("ext/glfw")
add_subdirectory("ext/glm")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("chk_software")

# Add source to this project's executable.
add_executable (chk_software "src/chk_software.cpp" "src/chk_software.h" "src/chk_common.h" "src/chk_common.cpp")
target_link_libraries (chk_software glm::glm glfw)

# Enable the new preprocessor so we are std20 compliant
if(MSVC)
	target_compile_options(chk_software PRIVATE "/Zc:preprocessor" "/std:c++20" "/permissive-" "/Zc:ternary" "/Zc:char8_t")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chk_software PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
