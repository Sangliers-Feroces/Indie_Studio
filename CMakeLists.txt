cmake_minimum_required(VERSION 3.16)

project(bomberman)

set(CMAKE_MODULE_PATH FindIrrlicht.cmake)

#ADD .CPP HERE
set(SRCS 
	./src/main.cpp
	)

#ADD .HPP HERE
set(HEADER
	./src/test/test.hpp
	)

add_executable(bomberman ${SRCS} ${HEADER})

target_link_libraries(bomberman ${Irrlicht_LIBRARIES})