cmake_minimum_required(VERSION 3.16)

project(bomberman)

set(CMAKE_MODULE_PATH "./cmake_modules")

include(FindIrrlicht)

#ADD .CPP HERE
set(SRCS 
	./src/Engine/Session.cpp
	./src/Engine/World.cpp
	./src/Engine/Entity.cpp

	./src/Bomberman/Game.cpp
	./src/Bomberman/Field.cpp

	./src/main.cpp
)

#ADD .HPP HERE
set(HEADER
)

include_directories(src)

add_executable(bomberman ${SRCS} ${HEADER})

target_link_libraries(bomberman ${Irrlicht_LIBRARIES})