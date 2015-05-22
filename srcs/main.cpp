#include "../includes/LibSFML.hpp"
#include "map.hpp"
#include "Player.hpp"

int		main(int ac, char **av)
{
	sf::RenderWindow			window(sf::VideoMode(WIN_SZ, WIN_SZ), av[0]);
	sf::RectangleShape			rectangle(sf::Vector2f(0, 0));
	std::vector<std::string>	raw_map;
	int							x;
	int							y;

	if (ac != 2)
		return (-1);
	Map 						map(av[1]);
	Player						p(1,1, &map);

	raw_map = map.getRawMap();
	sf::Vector2f position = rectangle.getPosition();
	rectangle.setSize(sf::Vector2f(map.getX(), map.getY()));
	while (1)
	{
		rectangle.setPosition(position);
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
					window.draw(rectangle);
				}
				if (y == p.y && x == p.x)
				{
					rectangle.setFillColor(sf::Color(100, 250, 50));
					window.draw(rectangle);
				}
				rectangle.move(map.getX(), 0);
			}
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
				return (0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				p.setDir(3);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				p.setDir(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				p.setDir(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				p.setDir(2);
		}
		p.move();
		window.display();
		sf::sleep(sf::milliseconds(100));
	}
	return (0);
}
