cmake_minimum_required(VERSION 3.0.2)
project(gzpluginz)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  gazebo_plugins
  std_srvs
  std_msgs
  message_generation
)

find_package(gazebo REQUIRED)



add_service_files(
  FILES
  lift.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES gzpluginz
  CATKIN_DEPENDS roscpp
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(hello_world src/hello_world.cc)
target_link_libraries(hello_world ${GAZEBO_LIBRARIES})

add_library(CustElevatorPlugin src/CustElevatorPlugin.cc)
target_link_libraries(CustElevatorPlugin ${GAZEBO_LIBRARIES})

add_library(RosLed src/RosLed.cc)
target_link_libraries(RosLed ${GAZEBO_LIBRARIES} LedPlugin)

add_library(RosElevator src/RosElevator.cc)
target_link_libraries(RosElevator ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES} CustElevatorPlugin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
