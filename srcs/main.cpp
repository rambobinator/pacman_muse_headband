#include "../includes/LibSFML.hpp"
#include "map.hpp"

int		main(int ac, char **av)
{
	sf::RenderWindow	window(sf::VideoMode(WIN_SZ, WIN_SZ), av[0]);
	sf::RectangleShape	rectangle(sf::Vector2f(0, 0));
	rectangle.setFillColor(sf::Color(100, 250, 50));
	sf::Vector2f position = rectangle.getPosition();

	if (ac != 2)
		return (-1);
	Map map(av[1]);
	rectangle.setSize(sf::Vector2f(map, 10));

	map.display();
	while (1)
	{
		window.clear();
		window.draw(rectangle);
		rectangle.setPosition(10, 50);
		window.draw(rectangle);
		rectangle.setPosition(position);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return (0);
			}
		}
		window.display();
	}
	return (0);
}
