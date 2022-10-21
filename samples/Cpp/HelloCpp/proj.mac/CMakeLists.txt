cmake_minimum_required(VERSION 3.21)

project(cocos2d-HelloCpp LANGUAGES CXX C)

set(MAIN_NIBFILE "MainMenu")
set(PRINCIPAL_CLASS "NSApplication")

set(RESOURCE_FILES 
	../Resources/fonts/Nunito-Regular.ttf
	../Resources/HelloWorld.png
)

add_executable(cocos2d-HelloCpp MACOSX_BUNDLE
	main.mm
	AppController.mm
	../Classes/AppDelegate.cpp
	../Classes/HelloWorldScene.cpp
	en.lproj/MainMenu.xib
	en.lproj/InfoPlist.strings
	${RESOURCE_FILES}
)

target_include_directories(cocos2d-HelloCpp PRIVATE
	.
	../Classes
)

target_link_libraries(cocos2d-HelloCpp PRIVATE
	cocos2d
)

set_target_properties(cocos2d-HelloCpp PROPERTIES 
	MACOSX_BUNDLE TRUE
	MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
	RESOURCE "${RESOURCE_FILES}"
	MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
)

set_source_files_properties( "en.lproj/MainMenu.xib" PROPERTIES MACOSX_PACKAGE_LOCATION "en.lproj" )
