#include "Map.hpp"

Map::Map( void )
{
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
