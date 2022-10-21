cmake_minimum_required(VERSION 3.21)

project(cocos2d-root VERSION 2.2.3.1)

set(CMAKE_BUILD_TYPE Debug)

set(COCOS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cocos2dx/proj.mac)

# add_subdirectory(samples/Cpp/HelloCpp/proj.mac)