#ifndef ENEMY_HPP
# define ENEMY_HPP

#include <iostream>
#include "map.hpp"
#include "player.hpp"

class Enemy : public Player
{
	public:
		Enemy(int y, int x, Map *map, Player *p);
		~Enemy();
		Enemy &		operator=( Enemy const & rhs );
		void		ia();
		int			getDir();
		int			Astar();

	private:
		Player	*p;

};

std::ostream & 		operator<<(std::ostream &o, Player const &rhs);

#endif