cmake_minimum_required(VERSION 3.0.2)
project(ball_chaser)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  sensor_msgs
)

add_service_files(
  FILES
  DriveToTarget.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime roscpp std_msgs sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(drive_bot src/drive_bot.cpp)
target_link_libraries(drive_bot ${catkin_LIBRARIES})
add_dependencies(drive_bot ball_chaser_generate_messages_cpp)

add_executable(process_image src/process_image.cpp)
target_link_libraries(process_image ${catkin_LIBRARIES})
add_dependencies(process_image ball_chaser_generate_messages_cpp)
