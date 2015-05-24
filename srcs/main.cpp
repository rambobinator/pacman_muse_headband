#include "../includes/LibSFML.hpp"
#include "../osc/tests/OscReceiveTest.h"
#include "map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <csignal>
#include <thread>

#define CHAR_PATH "assets/pac_sprite.png"
#define ELEM_PATH "assets/pac_elem_sprite.png"
enum	chararacters_code
{
	RED,
	PINK,
	CYAN,
	ORANGE,
	SICK,
	OL,
	OU,
	OD,
	OR,
	DEAD1,
	CL,
	CU,
	CD,
	CR,
	DEAD2,
	CHAR_NBR
};

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
	sf::Font					font;
	std::string					score = "score :";
	std::string					life = "life :";
	sf::Text 					text;
	sf::Text 					text2;
	font.loadFromFile("/Library/Fonts/Arial Black.ttf");
	text.setFont(font);
	text.setColor(sf::Color::Yellow);
	text2.setFont(font);
	text2.setColor(sf::Color::Yellow);
	sf::RectangleShape 			filter(sf::Vector2f(WIN_SZ, WIN_SZ));
	std::vector<std::string>	raw_map;
	int							x;
	int							y;
	int							sp = 0;
	int							i = -1;

	if (ac != 2)
		return (-1);
	std::thread 				first(thread);
	Map 						map(av[1]);
	sf::Sprite					*characters = get_sprites(CHAR_PATH, 5, 3, map.getX(), map.getY());
	sf::Sprite					*elements = get_sprites(ELEM_PATH, 5, 3, map.getX(), map.getY());
	Player						p(1,1, &map);
	Enemy						e1(6, 8, &map, &p, RED);
	Enemy						e2(7, 8, &map, &p, PINK);

	raw_map = map.getRawMap();
	sf::Vector2f position(0, 0);
	text.setPosition(0, 460);
	text2.setPosition(300, 460);
	while (1)
	{
		text.setString(score);
		text2.setString(life);
		elements[7].setPosition(position);
		i = -1;
		while (++i < CHAR_NBR)
			characters[i].setPosition(position);
		window.clear();
		/*DRAW MAP*/
		y = 0;
		for (std::vector<std::string>::iterator it = raw_map.begin() ; it != raw_map.end(); ++it, y++)
		{
			x = 0;
			for ( std::string::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2, x++)
			{
				if (*it2 != '0')
				{
					window.draw(elements[7]);
				}
				if (y == p.y && x == p.x)
				{
					sp = (sp) ? 0 : 5;
					if (p.dir == 3)
					{
						characters[OL + sp].move(map.getX() * x, map.getY() * y);
						window.draw(characters[OL + sp]);
					}
					else if (p.dir == 0)
					{
						characters[OU + sp].move(map.getX() * x, map.getY() * y);
						window.draw(characters[OU + sp]);
					}
					else if (p.dir == 2)
					{
						characters[OD + sp].move(map.getX() * x, map.getY() * y);
						window.draw(characters[OD + sp]);
					}
					else
					{
						characters[OR + sp].move(map.getX() * x, map.getY() * y);
						window.draw(characters[OR + sp]);
					}
				}
				if (y == e1.y && x == e1.x)
				{
					if (e1.dead && (e1.dir == 0 || e1.dir == 2)){
						characters[DEAD1].move(map.getX() * x, map.getY() * y);
						window.draw(characters[DEAD1]);
					}
					else if (e1.dead && (e1.dir == 1 || e1.dir == 3)){
						characters[DEAD2].move(map.getX() * x, map.getY() * y);
						window.draw(characters[DEAD2]);
					}
					else if (g_berserk){
						characters[SICK].move(map.getX() * x, map.getY() * y);
						window.draw(characters[SICK]);
					}
					else{
						characters[e1.sprite].move(map.getX() * x, map.getY() * y);
						window.draw(characters[e1.sprite]);
					}
				}
				if (y == e2.y && x == e2.x)
				{
					if (e2.dead && (e2.dir == 0 || e2.dir == 2)){
						characters[DEAD1].move(map.getX() * x, map.getY() * y);
						window.draw(characters[DEAD1]);
					}
					else if (e2.dead && (e2.dir == 1 || e2.dir == 3)){
						characters[DEAD2].move(map.getX() * x, map.getY() * y);
						window.draw(characters[DEAD2]);
					}
					else if (g_berserk){
						characters[SICK].move(map.getX() * x, map.getY() * y);
						window.draw(characters[SICK]);
					}
					else{
						characters[e2.sprite].move(map.getX() * x, map.getY() * y);
						window.draw(characters[e2.sprite]);
					}
				}
				elements[7].move(map.getX(), 0);
			}
			elements[7].move(-(map.getX() * x), map.getY());
		}
		filter.setFillColor(sf::Color(0, 0, 250, 0));
		if (g_berserk)
			filter.setFillColor(sf::Color(0, 0, 250, 80));
		/*SOUND*/
		
		
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				filter.setFillColor(sf::Color(0, 0, 0, 150));
				p.move();
			}
		}
		/*MUSE EVENT*/
		if (g_blink)
		{
			g_blink = 0;
			filter.setFillColor(sf::Color(0, 0, 0, 150));
			p.move();
		}
		p.move();
		e1.ia();
		e2.ia();
		window.draw(text);
		window.draw(text2);
		window.draw(filter);
		window.display();
		sf::sleep(sf::milliseconds(100));
	}
	return (0);
}
