/*(2017/12/28) �ڶ���̰���ߣ�����������������Ҫ���ѵö࡭�����ۻ� ���Լ���struct����orz*/
/*version 2.0 ˼·��
	�����ߵĳ�ʼλ�ã�������������'X''H'λ�õ�����ṹ�壨ע��Ҫ�涨�ߵ���󳤶ȣ���ÿ���ַ�����֮��ÿ�������ַ���λ����ǰ���ַ���λ�á� */	

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
	
/*��ӡ��ͼ����*/ 
void printMap() {
	for (int i = 0; i < 12; ++ i) {
		for (int j = 0; j < 12; ++ j) printf("%c", map[i][j]);
		putchar('\n');
	}
}

//��Ϸ�������� 
void gameover() {
	printf("Game Over!!");
	system("pause");//�˴�ʹ�����ܹ���ʾ���ַ������˳� 
	exit(0);
}

//�������ʳ������� 
struct coord food() {
	struct coord food;
	srand((unsigned)time(NULL));
	food.coordX = (rand() % 10) + 1;
	food.coordY = (rand() % 10) + 1;
	return food; 
}

//����ʳ�� 
void putfood() {
	struct coord food1 = food();
	int i = food1.coordX, j = food1.coordY;
	if (map[i][j] == ' ') map[i][j] = '$';
	else putfood();
}

//�����Ƿ���ʳ����� 
int testfood() {
	for (int i = 1; i < 11; ++ i) {
		for (int j = 1; j < 11; ++ j) {
			if (map[i][j] == '$') return 0; 
		}
	}
	return 1;
}

//�����߳��ȵĺ���
int snakelength(struct coord snakecoord[]) {
	for (int i = 1; i <= 100; ++i) {
		if (snakecoord[i-1].coordX == 0) return i-1;
	}
} 

/*�ߵ��ƶ������������������������������ʹ����������ݲ�ͬ������Ѱ�ҹ���*/
struct coord snakemove(int m, int n, struct coord snakecoord[]) {
	int newX, newY, tailX, tailY;
	int length = snakelength(snakecoord);//����ߵĳ��� 
	newX = snakecoord[0].coordX + m;//ִ�в������ͷ����λ�� 
	newY = snakecoord[0].coordY + n;
	tailX = snakecoord[length-1].coordX;//β��λ�� 
	tailY = snakecoord[length-1].coordY;
	if (map[newX][newY] != ' ' && map[newX][newY] != '$') gameover();//��ײǽ��ײ���Լ� ����Ϸ���� 
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
	//��ʼ���ߵĳ�ʼλ�� 
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
