#include "Enemy.hpp"

Enemy::Enemy(int y, int x, Map *map) : Player(y, x, map)
{
}

Enemy::~Enemy(){
}

// int		getDir(std::vector<std::string> map){
// 	int	zone[3][3];
// }

void	Enemy::ia(void)
{
	dir = 1;
	move();
}
