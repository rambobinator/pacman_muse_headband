#include "Enemy.hpp"
#include <time.h>
#define RANGE 13
#define HOME_X 10
#define HOME_Y 10

class Point {
public:
	int x;
	int y;
};

class Tab {
public:
	Point	tab[100];
	int		size;
};

Enemy::Enemy(int y, int x, Map *map, Player *new_p, int new_sprite) : Player(y, x, map){
	p = new_p;
	sprite = new_sprite;
	state = false;
	dead = false;
	home_x = x;
	home_y = y;
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

bool	is_in_tab(Tab tab, Point now)
{
	int 	i;

	i = 0;
	while (i < tab.size)
	{
		if (tab.tab[i].x == now.x && tab.tab[i].y == now.y)
			return (1);
		i++;
	}
	return (0);
}

Tab		min_tab(Tab tab0, Tab tab1, Tab tab2, Tab tab3)
{
	Tab		min1;
	Tab		min2;

	if (tab0.size == -1)
		min1 = tab1;
	else if (tab1.size == -1)
		min1 = tab0;
	else if (tab0.size <= tab1.size)
		min1 = tab0;
	else
		min1 = tab1;

	if (tab2.size == -1)
		min2 = tab3;
	else if (tab3.size == -1)
		min2 = tab2;
	else if (tab2.size <= tab3.size)
		min2 = tab2;
	else
		min2 = tab3;
	if (min1.size == -1){
		// std::cout << "size " <<min2.size << std::endl;
		return (min2);
	}
	else if (min2.size == -1){
		// std::cout << "size " <<min1.size << std::endl;
		return (min1);
	}
	else if (min1.size <= min2.size){
		// std::cout << "size " <<min1.size << std::endl;
		return (min1);
	}
	else{
		// std::cout << "size " <<min2.size << std::endl;
		return (min2);
	}
}

void	print_tab(Tab tab)
{
	int		i;

	i = 0;
	while (i < tab.size)
	{
		std::cout << tab.tab[i].x << "," << tab.tab[i].y << " ";
		i++;
	}
	std::cout << std::endl;
}

Tab		rec_dir(Tab tab, Point now, Point pac, int (*zone)[RANGE][RANGE])
{
	Tab		tab0, tab1, tab2, tab3, tab4;
	Point	tmp;

	tab0.size = tab1.size = tab2.size = tab3.size = tab4.size = -1;
	if (now.x == pac.x && now.y == pac.y)
		return (tab);
	if (((*zone)[now.x][now.y] == 0 || (*zone)[now.x][now.y] == 2) && is_in_tab(tab, now) == 0)
	{
		tab.tab[tab.size] = now;
		tab.size++;
		if (now.y > 0) {
			tmp.x = now.x;
			tmp.y = now.y - 1;
			tab0 = rec_dir(tab, tmp, pac, zone);
		}
		if (now.y < RANGE - 1) {
			tmp.x = now.x;
			tmp.y = now.y + 1;
			tab1 = rec_dir(tab, tmp, pac, zone);
		}
		if (now.x > 0) {
			tmp.x = now.x - 1;
			tmp.y = now.y;
			tab2 = rec_dir(tab, tmp, pac, zone);
		}
		if (now.x < RANGE - 1) {
			tmp.x = now.x + 1;
			tmp.y = now.y;
			tab3 = rec_dir(tab, tmp, pac, zone);
		}
		return (min_tab(tab0, tab1, tab2, tab3));
	}
		return (tab4);
}

int		Enemy::AstarDeath(void)
{
	int	zone[RANGE][RANGE];
	Point home;
	Tab	start;
	Tab	result;
	Point	tmp;
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
					zone[zx][zy] = 1;
				}
				else if (x == home_x && y == home_y)
				{
					home.x = zx;
					home.y = zy;
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
	start.size = 0;
	tmp.x = tmp.y = RANGE / 2;
	result = rec_dir(start, tmp, home, &zone);
	if (result.size == -1)
		return (-1);
	else if (result.tab[1].x - (RANGE / 2) > 0)
		return (1);
	else if (result.tab[1].x - (RANGE / 2) < 0)
		return (3);
	else if (result.tab[1].y - (RANGE / 2) > 0)
		return (2);
	else
		return (0);
	return (-1);
}

int		Enemy::Astar(void)
{
	extern int g_berserk;
	int	zone[RANGE][RANGE];
	int	is_pac;
	Point pac;
	Tab	start;
	Tab	result;
	Point	tmp;
	int	y;
	int	x;
	int zx, zy ;

//	g_berserk = 1;  FOR TEST AND DEMO
	
	is_pac = 0;
	for (x = this->x - (RANGE/2), zx=0 ; x <= this->x + (RANGE/2) ; x++, zx++) {
		for (y = this->y - (RANGE/2) , zy=0 ; y <= this->y + (RANGE/2) ; y++, zy++) {
			if ((x > 0 && x < map->x && y >= 0 && y < map->y)
				&& map->colision(y, x) == '0') {
				if (x == this->x && y == this->y) {
					zone[zx][zy] = 2 ;
				}
				else if (x == p->x && y == p->y) {
					zone[zx][zy] = 1 ;
					is_pac = 1;
					pac.x = zx;
					pac.y = zy;
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

	if (!is_pac)
		return (-1);
	start.size = 0;
	tmp.x = tmp.y = RANGE / 2;
	result = rec_dir(start, tmp, pac, &zone);
	if (result.size == -1)
		return (-1);
	else if (result.tab[1].x - (RANGE / 2) > 0)
	{
		if (!g_berserk)
			return (1);
		else if (map->colision(this->y, this->x - 1) == '0')
			return (3);
		else if (map->colision(this->y - 1, this->x) == '0')
			return (0);
		else if (map->colision(this->y + 1, this->x) == '0')
			return (2);
		else
			return (1);
	}
	else if (result.tab[1].x - (RANGE / 2) < 0)
	{
		if (!g_berserk)
			return (3);
		else if (map->colision(this->y, this->x + 1) == '0')
			return (1);
		else if (map->colision(this->y - 1, this->x) == '0')
			return (0);
		else if (map->colision(this->y + 1, this->x) == '0')
			return (2);
		else
			return (3);
	}
	else if (result.tab[1].y - (RANGE / 2) > 0)
	{
		if (!g_berserk)
			return (2);
		else if (map->colision(this->y - 1, this->x) == '0')
			return (0);
		else if (map->colision(this->y, this->x + 1) == '0')
			return (1);
		else if (map->colision(this->y, this->x - 1) == '0')
			return (3);
		else
			return (2);
	}
	else
	{		
		if (!g_berserk)
			return (0);
		else if (map->colision(this->y + 1, this->x) == '0')
			return (2);
		else if (map->colision(this->y, this->x + 1) == '0')
			return (1);
		else if (map->colision(this->y, this->x - 1) == '0')
			return (3);
		else
			return (0);
	}
	return (-1);
}


void	Enemy::move(void)
{
	float	dirs[4][2] = 
	{
		{-1, 0},
		{0, 1},
		{1, 0},
		{0, -1}
	};
	if (x == p->x && y == p->y)
	{
		dead = true;
		return;
	}
	state = (state) ? false : true;
	if (state)
		return ;
	if (map->colision(y, (x + dirs[dir][1])) == '0')
		x += dirs[dir][1];
	if (map->colision((y + dirs[dir][0]), x) == '0')
		y += dirs[dir][0];
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
	if (x >= 8 && x < 12 && y >= 6 && y < 10)
		dead = false;
	int	new_dir = (dead) ? AstarDeath() : Astar();

	dir = (new_dir != -1) ? new_dir : getDir();
	if (dir != -1)
		move();
}
