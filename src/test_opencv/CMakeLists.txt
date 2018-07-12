cmake_minimum_required(VERSION 2.8.3)
project(test_opencv)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
  message_generation
)

add_message_files(
  FILES
  Num.msg
  Nineaxes.msg
  coordinate.msg
  key.msg
  now_num.msg
  path.msg
)

#generate_messages(
#  DEPENDENCIES
#  #std_msgs
#)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES test_opencv
  CATKIN_DEPENDS roscpp std_msgs
)
include_directories(include)
include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})


#add_executable(image_converter src/image_converter.cpp)
#target_link_libraries(image_converter ${catkin_LIBRARIES})

add_executable(img_publisher src/img_publisher.cpp)
target_link_libraries(img_publisher ${catkin_LIBRARIES})

add_executable(img_subscriber src/img_subscriber.cpp)
target_link_libraries(img_subscriber ${catkin_LIBRARIES})

add_executable(img_topview_publisher src/img_topview_publisher.cpp)
target_link_libraries(img_topview_publisher ${catkin_LIBRARIES})

add_executable(img_topview_subscriber src/img_topview_subscriber.cpp)
target_link_libraries(img_topview_subscriber ${catkin_LIBRARIES})

add_executable(test_write_path_coordinate src/test_write_path_coordinate.cpp)
target_link_libraries(test_write_path_coordinate ${catkin_LIBRARIES})

add_executable(write_path_coordinate src/write_path_coordinate.cpp)
target_link_libraries(write_path_coordinate ${catkin_LIBRARIES})

add_executable(key src/key.cpp)
target_link_libraries(key ${catkin_LIBRARIES})

add_executable(read_path_pub src/read_path_pub.cpp)
target_link_libraries(read_path_pub ${catkin_LIBRARIES})

add_executable(matching src/matching.cpp)
target_link_libraries(matching ${catkin_LIBRARIES})

add_executable(serial src/serial.cpp)
target_link_libraries(serial ${catkin_LIBRARIES})


add_executable(urg_judge src/urg_judge.cpp)
target_link_libraries(urg_judge ${catkin_LIBRARIES})

add_executable(top_image src/top_image.cpp)
target_link_libraries(top_image ${catkin_LIBRARIES})

add_executable(AroundSearch src/AroundSearch.cpp)
target_link_libraries(AroundSearch ${catkin_LIBRARIES})


