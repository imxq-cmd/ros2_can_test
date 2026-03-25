cmake_minimum_required(VERSION 3.8)
project(can_test_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)
find_package(ros2_socketcan REQUIRED)

include_directories(include)

# 发送端节点
add_executable(can_sender_node src/can_sender_node.cpp)
target_include_directories(can_sender_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(
  can_sender_node 
  rclcpp 
  can_msgs 
  ros2_socketcan
)

# 接收端节点
add_executable(can_receiver_node src/can_receiver_node.cpp)
target_include_directories(can_receiver_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(
  can_receiver_node 
  rclcpp 
  can_msgs 
  ros2_socketcan
)

install(TARGETS
  can_sender_node
  can_receiver_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
