#include "Map.hpp"
#include <fstream>

Map::Map(std::string const filename)
{
	std::ifstream	file;
	std::string		line;
	int				len = 0;

	file.open(filename);
	if (file.is_open())
	{
    	while (getline(file,line) )
    	{
    		_raw_map.push_back(line);
    		len = line.length();
    	}
    }
    file.close();
    x = len;
    y = _raw_map.size();
    _tile_sz_y = WIN_SZ / _raw_map.size();
    _tile_sz_x = WIN_SZ / len;
}

Map::Map( Map const & src )
{
	*this = src;
}

Map::~Map( void )
{
}

Map & Map::operator=( Map const & rhs )
{
	(void)rhs;
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Map const &rhs)
{
	(void)rhs;
	o << "";
	return o;
}

void		Map::display(void)
{
	std::cout << "X " << _tile_sz_x << " Y " << _tile_sz_y << std::endl;
	for (std::vector<std::string>::iterator it = _raw_map.begin() ; it != _raw_map.end(); ++it)
		std::cout << *it << std::endl;
}

char		Map::colision(int y, int x)
{
	return (_raw_map[y].at(x));
}

int			Map::getX(void) const {return(_tile_sz_x);}
int			Map::getY(void) const {return(_tile_sz_y);}
std::vector<std::string>	Map::getRawMap(void) const {return(_raw_map);}
