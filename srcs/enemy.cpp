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

int		Enemy::Astar(void)
{
	// int	zone[RANGE][RANGE];
	// int	y;
	// int	x;
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
