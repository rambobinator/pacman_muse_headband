#include "Enemy.hpp"
#include <time.h>
#define RANGE 7

Enemy::Enemy(int y, int x, Map *map, Player *new_p) : Player(y, x, map){
	p = new_p;
}

Enemy::~Enemy(){
}

int		getOpposite(int i)
{
	int	op[4] = { 2, 3, 0, 1};
	return (op[i]);
}

void	astar(int zone[RANGE][RANGE], int y, int x, int val)
{
	if (y >= 0 && y < RANGE && x >= 0 && x < RANGE)
	{
		if (zone[y - 1][x] == 0)
			zone[y - 1][x] = val + 1;
		if (zone[y + 1][x] == 0)
			zone[y + 1][x] = val + 1;
		if (zone[y][x - 1] == 0)
			zone[y][x - 1] = val + 1;
		if (zone[y][x + 1] == 0)
			zone[y][x + 1] = val + 1;
	}
}

int		Enemy::Astar(void)
{
	int	zone[RANGE][RANGE];
	int	y;
	int	x;
	int zx, zy ;

	for (x = this->x - (RANGE/2), zx=0 ; x <= this->x + (RANGE/2) ; x++, zx++) {
		for (y = this->y - (RANGE/2) , zy=0 ; y <= this->y + (RANGE/2) ; y++, zy++) {
			if ((x > 0 && x < map->x && y >= 0 && y < map->y)
				&& map->colision(y, x) == '0') {
				if (x == this->x && y == this->y) {
					zone[zx][zy] = 2 ;
				}
				else if (x == p->x && y == p->y) {
					zone[zx][zy] = 1 ;
				}
				else {
					zone[zx][zy] = 0 ;
				}
			}
			else {
				zone[zx][zy] = -1 ;
			}
		}
	}
	y = RANGE;
	while (y--)
	{
		x = RANGE;
		std::cout << y << ((y > 9) ? " " : "  ");
		while (x--)
		{
			if (zone[y][x] >= 0)
				std::cout << zone[y][x];
			else
				std::cout << '_';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return (-1);
}

int		Enemy::getDir(void)
{
	int	dirs[4][3] = 
	{
		{-1, 0, 0},
		{0, 1, 0},
		{1, 0, 0},
		{0, -1, 0}
	};
	int	i = -1;
	int	count = 0;
	int	choice;

	srand (clock());
	while (++i < 4)
	{
		if (map->colision((y + dirs[i][0]), (x + dirs[i][1])) == '0' && i != getOpposite(dir))
		{
			dirs[i][2] = 1;
			count++;
		}
	}
	choice = rand() % count;
	i = -1;
	while (++i < 4)
	{
		if (dirs[i][2] == 1)
		{
			choice--;
		}
		if (choice)
			return (i);
	}
	return (-1);
}

void	Enemy::ia(void)
{
	int	new_dir = Astar();

	dir = (new_dir != -1) ? new_dir : getDir();
	if (dir != -1)
		move();
}
