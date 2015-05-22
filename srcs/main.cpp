#include "../includes/LibSFML.hpp"
#define WIN_SZ 500

int		main(int ac, char **av)
{
	sf::RenderWindow	window(sf::VideoMode(WIN_SZ, WIN_SZ), av[0]);
	(void)ac;

	while (1)
	{
		window.clear();
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
