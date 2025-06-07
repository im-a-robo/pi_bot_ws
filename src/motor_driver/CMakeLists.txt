cmake_minimum_required(VERSION 3.8)
project(motor_driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Include directories
include_directories(include)

# Add the library from .cpp files (if any) in src/
file(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} ${SOURCES})

# Link against ROS 2 libraries
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
)

# Install the library
install(TARGETS
  ${PROJECT_NAME}
  DESTINATION lib
)

# Install header files
install(DIRECTORY include/
  DESTINATION include/
)

# Testing (optional)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
