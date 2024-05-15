cmake_minimum_required(VERSION 3.27)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR "C:\\Users\\Komputer\\Desktop\\SDL2-2.30.1\\include")
set(SDL2_LIB_DIR "C:\\Users\\Komputer\\Desktop\\SDL2-2.30.1\\lib\\x64")

include_directories(${SDL2_INCLUDE_DIR})
add_executable(GameProject main.cpp
        src/engine/PhysicsEngine.h
        src/engine/PhysicsEngine.cpp
        src/game/GameObject.h
        src/game/GameObject.cpp
        src/game/TireObject.h
        src/game/Player.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib ${SDL2_LIB_DIR}/SDL2main.lib)