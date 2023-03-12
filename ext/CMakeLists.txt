# Add GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("glfw")

# Add OpenGL Math
add_subdirectory("glm")

# Add fmtlib
add_subdirectory("fmt")

# Add GLAD
set(GLAD_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glad/")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_41 REPRODUCIBLE API gl:core=4.1)
