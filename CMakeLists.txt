cmake_minimum_required(VERSION 3.16)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -g)
endif()

project(bomberman)

set(CMAKE_MODULE_PATH "./cmake_modules")

include(${CMAKE_MODULE_PATH}/FindIrrlicht.cmake)

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
	./src/Bomberman/Field.cpp
	./src/Bomberman/Player.cpp
	./src/Bomberman/Camera.cpp
	./src/Bomberman/Model.cpp
	./src/Bomberman/Tile.cpp
	./src/Bomberman/Gui.cpp

	./src/main.cpp
)

include_directories(src)
include_directories(${CMAKE_MODULE_PATH}/include)

add_executable(bomberman ${SRCS})

target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
target_compile_features(bomberman PRIVATE cxx_std_17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set_property(TARGET bomberman PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif ()