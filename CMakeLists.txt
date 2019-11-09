cmake_minimum_required(VERSION 2.8.3)
project(godot_ros_pcviz)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED
COMPONENTS
  geometry_msgs
  pcl_ros
  roscpp
  sensor_msgs
  std_msgs
  tf2
  tf2_eigen
  tf2_geometry_msgs
  tf2_ros
  tf2_sensor_msgs)

catkin_package()

find_package(OpenCV REQUIRED)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  thirdparty/godot-cpp/include
  thirdparty/godot-cpp/include/core
  thirdparty/godot-cpp/include/gen
  thirdparty/godot-cpp/godot_headers)

add_library(${PROJECT_NAME}
  src/godot_ros_pcviz.cpp
  src/gdlibrary.cpp)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
  ${PROJECT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.linux.debug.64.a)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}
  POSITION_INDEPENDENT_CODE ON)

configure_file(godot_project/godot_ros_pcviz.gdnlib  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/godot_ros_pcviz.gdnlib COPYONLY)
configure_file(godot_project/godot_ros_pcviz.gdns  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/godot_ros_pcviz.gdns COPYONLY)
configure_file(godot_project/project.godot  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/project.godot COPYONLY)
configure_file(godot_project/default_env.tres  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/default_env.tres COPYONLY)
configure_file(godot_project/Main.tscn  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/Main.tscn COPYONLY)
configure_file(godot_project/ImmediateGeometry.tscn  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/ImmediateGeometry.tscn COPYONLY)
configure_file(godot_project/PointCloud.tscn  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/PointCloud.tscn COPYONLY)
