#ifndef MAP_HPP
# define MAP_HPP

# define WIN_SZ 500

#include <iostream>
#include <vector>

class Map
{
	public:
		Map(std::string const filename);
		Map( Map const & src );
		~Map();
		Map &		operator=( Map const & rhs );
		void		display(void);

	private:
		std::vector< std::string >	_raw_map;
		int							_tile_sz_x;
		int							_tile_sz_y;						
};

std::ostream & 		operator<<(std::ostream &o, Map const &rhs);

#endif