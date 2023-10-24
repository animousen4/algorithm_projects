# CMakeList.txt : CMake project for 69_2_WayOfJaba, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (69_2_WayOfJaba "69_2_WayOfJaba.cpp" "69_2_WayOfJaba.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 69_2_WayOfJaba PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
