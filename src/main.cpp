/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Bomberman/Game.hpp"
#include <SFML/Audio.hpp>

int main(void)
{
	sf::Music music;

	music.openFromFile("music.ogg");
	music.play();
	Bomberman::Game();
	return 0;
}