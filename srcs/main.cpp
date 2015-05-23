#include "../includes/LibSFML.hpp"
#include "../osc/tests/OscReceiveTest.h"
#include "map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <csignal>
#include <thread>

#define CHAR_PATH "assets/pac_sprite.png"
#define WALL 7
#define ME 9
#define BAD1 0
#define BAD2 1
#define BAD3 2
#define BAD4 3

void	thread(void)
{
	osc::RunReceiveTest(5002);
}

int		g_blink = 0;
int		g_berserk = 0;

static sf::Sprite	*get_sprites(char const *file, int x_max, int y_max, int s_x, int s_y)
{
	int				len = x_max * y_max;
	sf::Texture		*textures = new sf::Texture[len];
	sf::Sprite		*sprites = new sf::Sprite[len];
	int				i = -1;
	int				y = -1;
	int				x = -1;

	while (++y < y_max)
	{
		x = -1;
		while (++x < x_max)
		{
			i++;
			textures[i].loadFromFile(file, sf::IntRect(x * s_x, y * s_y, s_x, s_y));
			sprites[i].setTexture(textures[i]);
		}
	}
	return (sprites);
}

int		main(int ac, char **av)
{
	sf::RenderWindow			window(sf::VideoMode(WIN_SZ, WIN_SZ), av[0]);
	sf::RectangleShape			rectangle(sf::Vector2f(0, 0));
	std::vector<std::string>	raw_map;
	int							x;
	int							y;

	if (ac != 2)
		return (-1);
	std::thread 				first(thread);
	Map 						map(av[1]);
	sf::Sprite					*characters = get_sprites(CHAR_PATH, 5, 3, map.getX(), map.getY());
	(void)characters;
	Player						p(1,1, &map);
	Enemy						e1(1, 3, &map, &p);
	Enemy						e2(13, 1, &map, &p);
	// Enemy						e2(13, 1, &map);
	// Enemy						e2(13, 1, &map);


	raw_map = map.getRawMap();
	sf::Vector2f position = rectangle.getPosition();
	rectangle.setSize(sf::Vector2f(map.getX(), map.getY()));
	while (1)
	{
		rectangle.setPosition(position);
		characters[WALL].setPosition(position);
		characters[ME].setPosition(position);
		characters[ME].setRotation(0);
		characters[BAD1].setPosition(position);
		characters[BAD2].setPosition(position);
		characters[BAD3].setPosition(position);
		characters[BAD4].setPosition(position);

		window.clear();

		/*DRAW MAP*/
		y = 0;
		for (std::vector<std::string>::iterator it = raw_map.begin() ; it != raw_map.end(); ++it, y++)
		{
			x = 0;
			for ( std::string::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2, x++)
			{
				rectangle.setFillColor(sf::Color(250, 250, 250));
				if (*it2 != '0')
				{
					window.draw(characters[WALL]);
				}
				if (y == p.y && x == p.x)
				{
					characters[ME].move(map.getX() * x, map.getY() * y);
					window.draw(characters[ME]);
				}
				if (y == e1.y && x == e1.x)
				{
					characters[BAD1].move(map.getX() * x, map.getY() * y);
					window.draw(characters[BAD1]);
				}
				if (y == e2.y && x == e2.x)
				{
					characters[BAD2].move(map.getX() * x, map.getY() * y);
					window.draw(characters[BAD2]);
				}
				characters[WALL].move(map.getX(), 0);
				rectangle.move(map.getX(), 0);
			}
			characters[WALL].move(-(map.getX() * x), map.getY());
			rectangle.move(-(map.getX() * x), map.getY());
		}

		/*EVENT CATCH*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return (0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				std::raise(SIGINT);
				first.join();
				return (0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				p.setDir(3);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				p.setDir(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				p.setDir(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				p.setDir(2);
		}
		/*MUSE EVENT*/



		
		p.move();
		e1.ia();
		e2.ia();
		window.display();
		sf::sleep(sf::milliseconds(100));
	}
	return (0);
}
