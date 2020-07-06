cmake_minimum_required(VERSION 3.16)
project(ffmpegD)


# 定义常量
set(CMAKE_C_STANDARD 99)
set(CUR_DIR .)
set(FFMPEG_ROOT_PATH /Users/zhishui/ffmpegPro/android)
#set(SOURCES src/Hello.cpp main.cpp)
# 开始
aux_source_directory(. source1)
aux_source_directory(./src source2)

#add_library(hello_lib STATIC ${source2} )
add_library(hello_lib SHARED ${source2})
# 看不懂
add_library(hello::library ALIAS hello_lib)

target_include_directories(hello_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

MESSAGE(源文件: ${source1} ${source2})

include_directories(./include ${FFMPEG_ROOT_PATH}/include )
link_directories(${FFMPEG_ROOT_PATH}/lib)

#aux_source_directory()

# 结束
add_executable(ffmpegD ${source1})
target_link_libraries(ffmpegD PRIVATE hello_lib libavcodec.dylib libavfilter.dylib libavformat.dylib libavutil.dylib libswresample.dylib libswscale.dylib)
