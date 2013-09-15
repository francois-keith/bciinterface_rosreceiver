cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include(FindPkgConfig)

pkg_check_modules(BCIINTERFACE bci-interface )
include_directories( ${BCIINTERFACE_INCLUDE_DIRS} )
link_directories( "${BCIINTERFACE_LIBRARY_DIRS}")

rosbuild_genmsg()

rosbuild_add_library(rosreceiver src/ROSReceiver.cpp)
target_link_libraries(rosreceiver bci-interface sfml-graphics sfml-window sfml-system)

rosbuild_add_executable(testROSReceiver src/testROSReceiver.cpp)
target_link_libraries(testROSReceiver rosreceiver bci-interface)
rosbuild_link_boost(testROSReceiver filesystem system thread)

install(TARGETS rosreceiver DESTINATION ${BCIINTERFACE_LIBRARY_DIRS})
install(FILES src/ROSReceiver.h DESTINATION ${BCIINTERFACE_INCLUDE_DIRS}/bci-interface/CommandReceiver)
