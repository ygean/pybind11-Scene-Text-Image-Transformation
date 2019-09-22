cmake_minimum_required (VERSION 2.6.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D CUDA_USE_STATIC_CUDA_RUNTIME=OFF -g -Wall -std=c++11 -O3 -I/usr/include/python3.5m -I/usr/include/python3.5m  -Wno-unused-result -Wsign-compare -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv")
# CXXFLAGS = "-g -Wall -std=c++11 -O3 $(shell python3-config --cflags)"
# Head and source
include_directories(include)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

# Find necessary packages

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIR} )

# Define the wrapper library
add_library(MLSTransformer SHARED ${DIR_SRCS})
# add_executable(ImageTransformer ${DIR_SRCS})
# target_link_libraries(ImageTransformer ${OpenCV_LIBRARIES})
target_link_libraries(MLSTransformer ${OpenCV_LIBRARIES} MLSTransformer)

# Don't prepend wrapper library name with lib
# set_target_properties(ImageTransformer PROPERTIES PREFIX "" )
set_target_properties(MLSTransformer PROPERTIES PREFIX "" )
