#include "Player.hpp"

Player::Player(int y, int x, Map *map) : x(x), y(y), map(map)
{
	dir = 0;
	life = 3;
}

Player::~Player( void )
{
}

Player & Player::operator=( Player const & rhs )
{
	(void)rhs;
	return *this;
}

std::ostream & 		operator<<(std::ostream &o, Player const &rhs)
{
	(void)rhs;
	o << "";
	return o;
}

void	Player::setDir(int new_dir)
{
	dir = new_dir;
}

void	Player::move(void)
{
	int	dirs[4][2] = 
	{
		{-1, 0},
		{0, 1},
		{1, 0},
		{0, -1}
	};
	if (map->colision(y, (x + dirs[dir][1])) == '0')
		x += dirs[dir][1];
	if (map->colision((y + dirs[dir][0]), x) == '0')
		y += dirs[dir][0];
}
