cmake_minimum_required(VERSION 3.11)


project(bomberman)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -O2 -Wno-unused-parameter -Wno-deprecated-copy)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

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
	./src/Engine/Light.cpp
	./src/Engine/IrrReceiver.cpp
	./src/Engine/EntityGui.cpp
	./src/Engine/EntityGuiWorld.cpp
	./src/Engine/ui/GuiButton.cpp
	./src/Engine/ui/ComboBox.cpp
	./src/Engine/ui/EditBox.cpp
	./src/Engine/ui/GuiScrollBar.cpp
	./src/Engine/ui/GuiCheckBox.cpp
	./src/Engine/ui/GuiStaticText.cpp
	./src/Engine/ui/GuiImage.cpp

	./src/Bomberman/Game.cpp
	./src/Bomberman/Gui.cpp
	./src/Bomberman/Menu.cpp
	./src/Bomberman/PreGame.cpp
	./src/Bomberman/Pause.cpp
	./src/Bomberman/IGOptions.cpp
	./src/Bomberman/WinScreen.cpp
	./src/Bomberman/Intro.cpp
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
	./src/Bomberman/ui/Button.cpp
	./src/Bomberman/ui/EditBox.cpp
	./src/Bomberman/ui/ComboBox.cpp
	./src/Bomberman/ui/ScrollBar.cpp
	./src/Bomberman/ui/CheckBox.cpp
	./src/Bomberman/ui/StaticText.cpp
	./src/Bomberman/ui/Image.cpp
	
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