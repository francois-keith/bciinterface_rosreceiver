cmake_minimum_required(VERSION 2.8.3)
project(bciinterface_rosreceiver)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    bciinterface_rosreceiver_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES rosreceiver
)

include(FindPkgConfig)

pkg_check_modules(BCIINTERFACE bci-interface )
include_directories( ${BCIINTERFACE_INCLUDE_DIRS} )
link_directories( "${BCIINTERFACE_LIBRARY_DIRS}")
if(NOT "${BCIINTERFACE_LIBRARY_DIRS}" STREQUAL "")
else()
set(BCIINTERFACE_INCLUDE_DIRS /usr/include)
set(BCIINTERFACE_LIBRARY_DIRS /usr/lib)
endif()

find_package(Boost REQUIRED COMPONENTS filesystem system thread)
include_directories(${Boost_INCLUDE_DIRS})

add_library(rosreceiver src/ROSReceiver.cpp)
add_dependencies(rosreceiver bciinterface_rosreceiver_msgs_generate_messages_cpp)
target_link_libraries(rosreceiver ${catkin_LIBRARIES} bci-interface sfml-graphics sfml-window sfml-system)

add_executable(testROSReceiver src/testROSReceiver.cpp)
target_link_libraries(testROSReceiver rosreceiver ${Boost_LIBRARIES})

install(TARGETS rosreceiver DESTINATION ${BCIINTERFACE_LIBRARY_DIRS})
install(FILES include/bci-interface/CommandReceiver/ROSReceiver.h DESTINATION ${BCIINTERFACE_INCLUDE_DIRS}/bci-interface/CommandReceiver)
