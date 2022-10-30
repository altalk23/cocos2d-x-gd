cmake_minimum_required(VERSION 3.21)

project(cocos2d VERSION 2.2.3.1 LANGUAGES CXX C)

set(COCOS_SRC ${COCOS_ROOT}/cocos2dx)

file(GLOB COCOS_SOURCES
	${COCOS_SRC}/actions/*.cpp
	${COCOS_SRC}/base_nodes/*.cpp
	${COCOS_SRC}/cocoa/*.cpp
	${COCOS_SRC}/draw_nodes/*.cpp
	${COCOS_SRC}/effects/*.cpp
	${COCOS_SRC}/keypad_dispatcher/*.cpp
	${COCOS_SRC}/label_nodes/*.cpp
	${COCOS_SRC}/layers_scenes_transitions_nodes/*.cpp
	${COCOS_SRC}/menu_nodes/*.cpp
	${COCOS_SRC}/misc_nodes/*.cpp
	${COCOS_SRC}/particle_nodes/*.cpp
	${COCOS_SRC}/platform/*.cpp
	${COCOS_SRC}/platform/mac/*.m
	${COCOS_SRC}/platform/mac/*.mm
	${COCOS_SRC}/script_support/*.cpp
	${COCOS_SRC}/sprite_nodes/*.cpp
	${COCOS_SRC}/support/*.cpp
	${COCOS_SRC}/support/image_support/*.cpp
	${COCOS_SRC}/support/user_default/*.mm
	${COCOS_SRC}/support/tinyxml2/*.cpp
	${COCOS_SRC}/support/zip_support/*.cpp
	${COCOS_SRC}/support/data_support/*.cpp
	${COCOS_SRC}/support/component/*.cpp
	${COCOS_SRC}/text_input_node/*.cpp
	${COCOS_SRC}/textures/*.cpp
	${COCOS_SRC}/tilemap_parallax_nodes/*.cpp
	${COCOS_SRC}/touch_dispatcher/*.cpp
	${COCOS_SRC}/shaders/*.cpp
	${COCOS_SRC}/kazmath/src/*.c
	${COCOS_SRC}/kazmath/src/GL/*.c
	${COCOS_SRC}/*.c
	${COCOS_SRC}/*.cpp
	${COCOS_SRC}/extensions/CCControlExtension/*.cpp
	${COCOS_SRC}/extensions/network/*.cpp
)

add_library(cocos2d SHARED ${COCOS_SOURCES})

target_compile_options(cocos2d PUBLIC
	-DCC_TARGET_OS_MAC
	-Wno-sequence-point
	-Wno-deprecated
	$<$<CONFIG:DEBUG>:-O0;-g3;-D_DEBUG;-DDEBUG=1;-DCOCOS2D_DEBUG=1>
	$<$<CONFIG:RELEASE>:-O3;-DNDEBUG>
)

target_include_directories(cocos2d PUBLIC
	$<BUILD_INTERFACE:${COCOS_SRC}>
	$<BUILD_INTERFACE:${COCOS_SRC}/cocoa>
	$<BUILD_INTERFACE:${COCOS_SRC}/include>
	$<BUILD_INTERFACE:${COCOS_SRC}/kazmath/include>
	$<BUILD_INTERFACE:${COCOS_SRC}/platform>
	$<BUILD_INTERFACE:${COCOS_SRC}/platform/mac>
	$<BUILD_INTERFACE:${COCOS_SRC}/platform/third_party/mac/webp>
)

target_include_directories(cocos2d PRIVATE
	$<BUILD_INTERFACE:${COCOS_SRC}/touch_dispatcher>
	$<BUILD_INTERFACE:${COCOS_SRC}/text_input_node>
	$<BUILD_INTERFACE:${COCOS_SRC}/textures>
)

find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${COCOS_ROOT}/cmake)
find_package(WebP REQUIRED)

target_link_libraries(cocos2d PUBLIC
	"-framework Cocoa"
	"-framework Foundation"
	"-framework CoreVideo"
	CURL
	z
	${OPENGL_LIBRARIES}
	${WebP_LIBRARIES}
)
set_target_properties(cocos2d PROPERTIES 
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug
)