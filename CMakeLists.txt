cmake_minimum_required(VERSION 3.16)

project(bomberman)

include(FindIrrlicht.cmake)
#ADD .CPP HERE
set(SRCS 
	./src/main.cpp
	)

#ADD .HPP HERE
set(HEADER
	./src/test/test.hpp
	)

add_executable(bomberman ${SRCS} ${HEADER})