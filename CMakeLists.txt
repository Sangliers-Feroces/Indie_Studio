cmake_minimum_required(VERSION 3.16)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -g)
endif()

project(bomberman)

set(CMAKE_MODULE_PATH "./cmake_modules")

include(FindIrrlicht)

#ADD .CPP HERE
set(SRCS 
	./src/Engine/Session.cpp
	./src/Engine/World.cpp
	./src/Engine/Entity.cpp
	./src/Engine/CameraFPS.cpp
	./src/Engine/Mesh.cpp
	./src/Engine/AnimatedMesh.cpp

	./src/Bomberman/Game.cpp
	./src/Bomberman/Field.cpp
	./src/Bomberman/Player.cpp

	./src/main.cpp
)

#ADD .HPP HERE
set(HEADER
)

include_directories(src)

add_executable(bomberman ${SRCS} ${HEADER})

target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
target_compile_features(bomberman PRIVATE cxx_std_17)