cmake_minimum_required(VERSION 3.27)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR "D:\\WORK\\s25770\\SDL2-2.30.1\\include")
set(SDL2_LIB_DIR "D:\\WORK\\s25770\\SDL2-2.30.1\\lib\\x64")

include_directories(${SDL2_INCLUDE_DIR})
add_executable(GameProject main.cpp
        src/game/GameObject.h
        src/game/GameObject.cpp
        src/game/CarObject.h
        src/game/Player.cpp
        src/game/WallObject.h
        src/game/TruckObject.h
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib ${SDL2_LIB_DIR}/SDL2main.lib)