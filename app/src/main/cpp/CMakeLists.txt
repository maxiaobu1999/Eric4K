cmake_minimum_required(VERSION 3.4.1)
message("========================================================================+++")
find_library(log-lib log)
find_library(android-lib android)

set(CMAKE_VERBOSE_MAKEFILE on)


#添加cpp下的子目录所有cpp源码路径
file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/eric/*.cpp
)

#命名最终非三方源码打包的动态库名称system.load加载
add_library(
        native-render
        SHARED
        ${src-files}
)

##定义 动态库路径变量
set(JNI_LIBS_DIR /Users/maqinglong/long/code/Eric4k/app/src/main/jniLibs)
message("========================================================================JNI_LIBS_DIR+++${JNI_LIBS_DIR}")


add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavutil.so)

add_library(avresample SHARED IMPORTED)
set_target_properties(avresample PROPERTIES IMPORTED_LOCATION ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavresample.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${JNI_LIBS_DIR}/${ANDROID_ABI}/libswresample.so)

add_library(swscale
        SHARED
        IMPORTED)
set_target_properties(swscale
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libswscale.so)

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavformat.so)

add_library(avfilter
        SHARED
        IMPORTED)
set_target_properties(avfilter
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavfilter.so)

add_library(avdevice
        SHARED
        IMPORTED)
set_target_properties(avdevice
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libavdevice.so)


#添加全部头文件目录
include_directories(
        util
        eric
        ${JNI_LIBS_DIR}/includes
)


#链接动态库打包armv8a
target_link_libraries(
        native-render
        avutil avresample swresample swscale avcodec avformat avfilter avdevice
        ${log-lib} ${android-lib}
)