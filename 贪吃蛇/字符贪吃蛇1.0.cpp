/*(2017/12/21) ��������˵�һ������bug��̰���ߡ�������(�����`)*/
/*version 1.0 ˼·��
	��ȡ��ͷ����β��λ�ã�ÿ���ƶ�ʱ��ʵ��ֻ����ͷ����β�ڸı� ��ͨ���ı�������ݸ��ƶ��������ı���ͷ����β���ַ������е�һ���ַ�Ҳ���ݹ��ɸı� */	
/*����˼·��bug��
	��β��λ��ֱ��ͨ������ֻ��һ����X���жϣ���ʵ�ϣ������ж��Ǵ���� 
  ��һ��ĸĽ�˼·��
  	�����Ҹ��˼·�������ߵĳ�ʼλ�ã�������������'X''H'λ�õ�����ṹ�壨ע��Ҫ�涨�ߵ���󳤶ȣ���ÿ���ַ�����֮��ÿ�������ַ���λ����ǰ���ַ���λ��;
	�������� ���Կ���Linux�·������ؼ���������ķ���*/

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
	system("pause");
	exit(0);
}

//����һ���ṹ��ʹ���Է�������ֵ 
struct coord {
	int coordinate[2];
};

//�������ʳ������� 
struct coord food() {
	struct coord food;
	srand((unsigned)time(NULL));
	food.coordinate[0] = (rand() % 10) + 1;
	food.coordinate[1] = (rand() % 10) + 1;
	return food; 
}

//����ʳ�� 
void putfood() {
	struct coord food1 = food();
	int i = food1.coordinate[0], j = food1.coordinate[1];
	if (map[i][j] == ' ') map[i][j] = '$';
	else putfood();
}

//�����Ƿ���ʳ����� 
bool testfood() {
	for (int i = 1; i < 11; ++ i) {
		for (int j = 1; j < 11; ++ j) {
			if (map[i][j] == '$') return 0; 
		}
	}
	return 1;
}

/*��ѭ�����head��λ��*/
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

/*���β����λ�ã��˴�ֻ������򵥵������β������ֻ��һ��X��*/
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

/*�ߵ��ƶ������������������������������ʹ����������ݲ�ͬ������Ѱ�ҹ���*/
void snakemove(int m, int n) {
	struct coord headPosition, tailPosition;
	headPosition = getHead();
	tailPosition = getTail();
	int x1 = headPosition.coordinate[0], y1 = headPosition.coordinate[1];
	int x2 = tailPosition.coordinate[0], y2 = tailPosition.coordinate[1];
	/*�޷��ƶ������*/
	if (map[x1+m][y1+n] == 'X' || map[x1+m][y1+n] == '*') gameover();
	/*���ƶ������*/
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
