set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.29)
project("soundwich")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g")

include_directories(
        src
        include
)

set(HEADER_FILES
        include/audio_output/audio_output.hpp
        include/audio_output/IAudioOutput.hpp
        include/decoder_manager.hpp
        include/player_controller.hpp
        include/playlist_manager.hpp
        include/common.hpp
)

set(SRC_FILES
        src/main.cpp
        src/audio_output/PipeWireCore.cpp
        src/audio_output/PipeWireOutput.cpp
        src/audio_output/process.cpp
)

add_executable(soundwich
        ${SRC_FILES}
        ${HEADER_FILES}
)


find_package(PkgConfig REQUIRED)
pkg_check_modules(PIPEWIRE REQUIRED libpipewire-0.3)

target_include_directories(soundwich PRIVATE ${PIPEWIRE_INCLUDE_DIRS})
target_link_libraries(soundwich PRIVATE m ${PIPEWIRE_LIBRARIES})
