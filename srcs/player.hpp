#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <iostream>
#include "map.hpp"

class Player
{
	public:
		Player(int y, int x, Map *map);
		~Player();
		Player &		operator=( Player const & rhs );
		int				life;
		int				x;
		int				y;
		int				dir;
		bool			blink;
		bool			berseck;
		Map				*map;
		void			setDir(int new_dir);
		void			move(void);

	private:

};

std::ostream & 		operator<<(std::ostream &o, Player const &rhs);

#endif