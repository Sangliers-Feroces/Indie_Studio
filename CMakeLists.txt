cmake_minimum_required(VERSION 3.11)


project(bomberman)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX /wd4244 /wd4267 /wd4305)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -g -Wno-unused-parameter -Wno-deprecated-copy)
endif()

set(CMAKE_MODULE_PATH "./cmake_modules")

include(${CMAKE_MODULE_PATH}/FindIrrlicht.cmake)
include(${CMAKE_MODULE_PATH}/FindSFMLAudio.cmake)

#ADD .CPP HERE
set(SRCS 
	./src/Engine/Session.cpp
	./src/Engine/World.cpp
	./src/Engine/Entity.cpp
	./src/Engine/Camera.cpp
	./src/Engine/Mesh.cpp
	./src/Engine/AnimatedMesh.cpp
	./src/Engine/IrrReceiver.cpp
	./src/Engine/EntityGui.cpp
	./src/Engine/EntityGuiWorld.cpp
	./src/Engine/ui/GuiButton.cpp

	./src/Bomberman/Game.cpp
	./src/Bomberman/Gui.cpp
	./src/Bomberman/Field.cpp
	./src/Bomberman/Player.cpp
	./src/Bomberman/Camera.cpp
	./src/Bomberman/Model.cpp
	./src/Bomberman/Tile.cpp
	./src/Bomberman/Mob.cpp
	./src/Bomberman/Bomb.cpp
	./src/Bomberman/Sparks.cpp
	./src/Bomberman/PowerUp/Base.cpp
	./src/Bomberman/PowerUp/PassUp.cpp
	./src/Bomberman/PowerUp/SpeedUp.cpp
	./src/Bomberman/PowerUp/FireUp.cpp
	./src/Bomberman/PowerUp/BombUp.cpp

	./src/main.cpp
)

include_directories(src)
include_directories(${CMAKE_MODULE_PATH}/include)

add_executable(bomberman ${SRCS})

target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
target_link_libraries(bomberman ${SFMLAudio_LIBRARIES})
target_compile_features(bomberman PRIVATE cxx_std_17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set_property(TARGET bomberman PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif ()