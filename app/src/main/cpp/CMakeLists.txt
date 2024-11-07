cmake_minimum_required(VERSION 3.4.1)
message("========================================================================+++")

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -fexceptions -frtti")
##定义 动态库路径变量
#set(jnilibs "${CMAKE_SOURCE_DIR}/../jniLibs")

#添加全部头文件目录
include_directories(
        component
        component/handler
        glm
        include
        include/assimp
        jnibridge
        model
        polyline
        nativeCode/common
        nativeCode/modelAssimp
        render
        opencv
        util
        eric
)

#添加cpp下的子目录所有cpp源码路径
file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/eric/*.cpp

)

#命名最终非三方源码打包的动态库名称system.load加载
add_library( # Sets the name of the library.
        native-render

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${src-files}
        )

#设置android系统依赖库版本
set(ATLAS_ENGINE_SYSTEM_LIBS android EGL GLESv2 GLESv3 m)

find_library(
        log-lib
        log)
#导入依赖动态库assimp
#add_library(assimp SHARED IMPORTED)
#set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libassimp.so)

#导入依赖动态库opencv_java03
#add_library(opencv_java3 SHARED IMPORTED)
#set_target_properties(opencv_java3 PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libopencv_java3.so)



set(JNI_LIBS_DIR "${CMAKE_SOURCE_DIR}/../jniLibs")
add_library(avutil
        SHARED
        IMPORTED )
set_target_properties(avutil
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavutil.so )

add_library(avresample
        SHARED
        IMPORTED )
set_target_properties(avresample
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavresample.so )

add_library(swresample
        SHARED
        IMPORTED )
set_target_properties(swresample
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libswresample.so )

add_library(swscale
        SHARED
        IMPORTED )
set_target_properties(swscale
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libswscale.so )

add_library(avcodec
        SHARED
        IMPORTED )
set_target_properties(avcodec
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavcodec.so )

add_library(avformat
        SHARED
        IMPORTED )
set_target_properties(avformat
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavformat.so )

add_library(avfilter
        SHARED
        IMPORTED )
set_target_properties(avfilter
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavfilter.so )

add_library(avdevice
        SHARED
        IMPORTED )
set_target_properties(avdevice
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavdevice.so )

include_directories(${JNI_LIBS_DIR}/includes)



#设置三方so别名
set(third-party-libs
#        assimp
#        opencv_java3
        avutil avresample swresample swscale avcodec avformat avfilter avdevice
)

#链接动态库打包armv8a
target_link_libraries( # Specifies the target library.
        native-render
        ${third-party-libs}
        # Links the target library to the log library
        # included in the NDK.
        ${ATLAS_ENGINE_SYSTEM_LIBS}
        ${log-lib}
        )