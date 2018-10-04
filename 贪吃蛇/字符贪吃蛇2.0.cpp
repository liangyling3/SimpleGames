/*(2017/12/28) 第二版贪吃蛇！！改起来比想象中要困难得多…累死累活 被自己的struct绕晕orz*/
/*version 2.0 思路：
	考虑蛇的初始位置，建立传递所有'X''H'位置的数组结构体（注意要规定蛇的最大长度），每次字符输入之后，每个蛇身字符的位置它前边字符的位置。 */	

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define up -1, 0
#define down 1, 0
#define left 0, -1
#define right 0, 1

char map[12][13] = 
	{"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"};
	
struct coord{
	int coordX;
	int coordY;
}; 
	
/*打印地图函数*/ 
void printMap() {
	for (int i = 0; i < 12; ++ i) {
		for (int j = 0; j < 12; ++ j) printf("%c", map[i][j]);
		putchar('\n');
	}
}

//游戏结束函数 
void gameover() {
	printf("Game Over!!");
	system("pause");//此处使界面能够显示完字符后再退出 
	exit(0);
}

//随机产生食物的坐标 
struct coord food() {
	struct coord food;
	srand((unsigned)time(NULL));
	food.coordX = (rand() % 10) + 1;
	food.coordY = (rand() % 10) + 1;
	return food; 
}

//放置食物 
void putfood() {
	struct coord food1 = food();
	int i = food1.coordX, j = food1.coordY;
	if (map[i][j] == ' ') map[i][j] = '$';
	else putfood();
}

//检验是否有食物存在 
int testfood() {
	for (int i = 1; i < 11; ++ i) {
		for (int j = 1; j < 11; ++ j) {
			if (map[i][j] == '$') return 0; 
		}
	}
	return 1;
}

//计算蛇长度的函数
int snakelength(struct coord snakecoord[]) {
	for (int i = 1; i <= 100; ++i) {
		if (snakecoord[i-1].coordX == 0) return i-1;
	}
} 

/*蛇的移动函数。这里有上下左右四种情况，使四种情况传递不同参数，寻找规律*/
struct coord snakemove(int m, int n, struct coord snakecoord[]) {
	int newX, newY, tailX, tailY;
	int length = snakelength(snakecoord);//获得蛇的长度 
	newX = snakecoord[0].coordX + m;//执行操作后的头部新位置 
	newY = snakecoord[0].coordY + n;
	tailX = snakecoord[length-1].coordX;//尾部位置 
	tailY = snakecoord[length-1].coordY;
	if (map[newX][newY] != ' ' && map[newX][newY] != '$') gameover();//若撞墙、撞到自己 则游戏结束 
	for (int i = length - 1; i > 0; -- i) {
		snakecoord[i] = snakecoord[i-1];
		map[snakecoord[i].coordX][snakecoord[i].coordY] = 'X';
	}
	if (map[newX][newY] == '$') {
		snakecoord[length].coordX = tailX;
		snakecoord[length].coordY = tailY;		
		map[tailX][tailY] = 'X';
	}
	else map[tailX][tailY] = ' ';
	map[newX][newY] = 'H';
	snakecoord[0].coordX = newX;
	snakecoord[0].coordY = newY; 
	return snakecoord[100]; 
}

int main() {
	//初始化蛇的初始位置 
	struct coord snakecoord[100];	
	for (int i = 0; i < 5; ++ i) {		
		snakecoord[i].coordX = 1;		
		snakecoord[i].coordY = 5 - i;	
	} 
	for (int i = 5; i < 100; ++ i) {
		snakecoord[i].coordX = snakecoord[i].coordY = 0;
	}
	while (1) {
		if (testfood()) putfood();
		printMap();
		char direction = getchar();
		switch (direction) {
			case 'A': snakecoord[100] = snakemove(left, snakecoord); break;
			case 'S': snakecoord[100] = snakemove(down, snakecoord); break;
			case 'D': snakecoord[100] = snakemove(right, snakecoord); break;
			case 'W': snakecoord[100] = snakemove(up, snakecoord); break; 
		}
	}
}
