/*(2017/12/21) 终于完成了第一版满是bug的贪吃蛇…累死啦(；′⌒`)*/
/*version 1.0 思路：
	获取蛇头、蛇尾的位置，每次移动时，实际只有蛇头、蛇尾在改变 ；通过改变参数传递给移动函数，改变蛇头、蛇尾的字符；跨行的一个字符也根据规律改变 */	
/*此种思路的bug：
	蛇尾的位置直接通过四周只有一个‘X’判断；事实上，这种判断是错误的 
  下一版的改进思路：
  	参照我哥的思路，考虑蛇的初始位置，建立传递所有'X''H'位置的数组结构体（注意要规定蛇的最大长度），每次字符输入之后，每个蛇身字符的位置它前边字符的位置;
	除此以外 可以考虑Linux下非阻塞地检测键盘输入的方法*/

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
	system("pause");
	exit(0);
}

//定义一个结构，使可以返回两个值 
struct coord {
	int coordinate[2];
};

//随机产生食物的坐标 
struct coord food() {
	struct coord food;
	srand((unsigned)time(NULL));
	food.coordinate[0] = (rand() % 10) + 1;
	food.coordinate[1] = (rand() % 10) + 1;
	return food; 
}

//放置食物 
void putfood() {
	struct coord food1 = food();
	int i = food1.coordinate[0], j = food1.coordinate[1];
	if (map[i][j] == ' ') map[i][j] = '$';
	else putfood();
}

//检验是否有食物存在 
bool testfood() {
	for (int i = 1; i < 11; ++ i) {
		for (int j = 1; j < 11; ++ j) {
			if (map[i][j] == '$') return 0; 
		}
	}
	return 1;
}

/*用循环获得head的位置*/
struct coord getHead() {
	struct coord position;
	for (int i = 1; i < 11; ++ i) {
		for (int j = 1; j < 11; ++ j) {
			if (map[i][j] == 'H'){
				position.coordinate[0] = i;
				position.coordinate[1] = j;
				return position;
			} 
		}
	}
}

/*获得尾部的位置：此处只考虑最简单的情况：尾部四周只有一个X。*/
struct coord getTail() {
	struct coord position;
	for (int i = 1; i < 11; ++ i) {
		for (int j = 1; j < 11; ++ j) {
			if (map[i][j] == 'X'){
				int count = 0;
				if (map[i+1][j] != 'X' && map[i+1][j] != 'H') count ++;
				if (map[i-1][j] != 'X' && map[i-1][j] != 'H') count ++;
				if (map[i][j+1] != 'X' && map[i][j+1] != 'H') count ++;
				if (map[i][j-1] != 'X' && map[i][j-1] != 'H') count ++;
				if (count == 3) {
					position.coordinate[0] = i;
					position.coordinate[1] = j;
					return position;
				}
			} 
		}
	}
}

/*蛇的移动函数。这里有上下左右四种情况，使四种情况传递不同参数，寻找规律*/
void snakemove(int m, int n) {
	struct coord headPosition, tailPosition;
	headPosition = getHead();
	tailPosition = getTail();
	int x1 = headPosition.coordinate[0], y1 = headPosition.coordinate[1];
	int x2 = tailPosition.coordinate[0], y2 = tailPosition.coordinate[1];
	/*无法移动的情况*/
	if (map[x1+m][y1+n] == 'X' || map[x1+m][y1+n] == '*') gameover();
	/*可移动的情况*/
	else {
		map[x2][y2] = ' ';
		if (map[x1+m][y1+n] == '$') map[x2][y2] = 'X';
		map[x1+m][y1+n] = 'H';
		map[x1][y1] = 'X';
	}	
}

int main() {
	while (1) {
		if (testfood()) putfood();
		printMap();
		char direction = getchar();
		switch (direction) {
			case 'A': snakemove(left); break;
			case 'S': snakemove(down); break;
			case 'D': snakemove(right); break;
			case 'W': snakemove(up); break; 
		}
	}
}
