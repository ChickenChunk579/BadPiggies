cmake_minimum_required(VERSION 3.0)
project(BadPiggies)

message( STATUS "Targeting iOS" )

    if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Override this platform and tell CMake to cross compile to iOS.
    SET( CMAKE_CROSSCOMPILING TRUE )
    SET( CMAKE_SYSTEM_NAME "Darwin" )
    SET( CMAKE_SYSTEM_PROCESSOR "arm" )

    # Setup the valid architectures.
    set( CMAKE_OSX_ARCHITECTURES "${ARCHS_STANDARD_32_BIT}" )
    # SET( CMAKE_OSX_ARCHITECTURES "${ARCHS_UNIVERSAL_IPHONE_OS}" )

    # Allow simulator and deploy.
    SET( CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator" )

    set( SDKVER "18.0.1" )
    set( DEVROOT "/Applications/Developer/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer" )
    set( SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk" )



endif()

if ( CMAKE_GENERATOR STREQUAL "Xcode" )
    set ( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11" )
    set ( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++" )
endif ( CMAKE_GENERATOR STREQUAL "Xcode" )

set( MACOSX_BUNDLE_GUI_IDENTIFIER "com.chickenchunk.${PROJECT_NAME}" )

set ( FRAMEWORKS
        Foundation
        AudioToolbox
        CoreGraphics
        QuartzCore
        UIKit
        OpenGLES
        OpenAL # nomlib dep
        # SDL2_image
        ImageIO
        MobileCoreServices
    )




add_subdirectory(vendor/SDL)
add_subdirectory(vendor/spdlog)

add_executable(BadPiggies MACOSX_BUNDLE main.cpp)
target_link_libraries(BadPiggies PRIVATE SDL2::SDL2 spdlog)