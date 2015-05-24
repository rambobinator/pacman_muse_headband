#ifndef ENEMY_HPP
# define ENEMY_HPP

#include <iostream>
#include "map.hpp"
#include "player.hpp"

class Enemy : public Player
{
	public:
		Enemy(int y, int x, Map *map, Player *p, int sprite);
		~Enemy();
		Enemy &		operator=( Enemy const & rhs );
		void		ia();
		int			getDir();
		int			Astar();
		int			AstarDeath(void);
		void		move(void);
		int			sprite;
		bool		state;
		int			home_x;
		int			home_y;
		bool		dead;

	private:
		Player	*p;

};

std::ostream & 		operator<<(std::ostream &o, Player const &rhs);

#endif