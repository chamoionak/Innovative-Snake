#include<easyx.h>
#include<iostream>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#define wide 40
using namespace std;
struct node//结构体确定坐标x,y
{
	int x;
	int y;
};
void print()//打印横线与竖线
{
	for (int i = 1; i <=20; ++i)
	{
		line(i * wide, 0, i * wide, 600);
	}
	for (int i = 1; i <= 15; ++i)
	{
		line(0,i*wide,800,i*wide);
	}
}
void point(int c)
{
	setfillcolor(BLACK);
	solidrectangle(0, 600, 800, 680);
	settextcolor(WHITE);

	settextstyle(40, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	const char* p = "积分：";
	outtextxy(0, 600, p);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	int n = c;
	TCHAR s[5];
	sprintf_s(s, _T("%d"), n);		// 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(100, 600, s);

	settextstyle(40, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	const char* d = "青色+10  红色+50  金色+100  自尽赐紫色苹果";
	outtextxy(150, 600, d);

	settextstyle(40, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	const char* w = "累计吃3个紫色苹果，蛇死亡，游戏正式结束";
	outtextxy(150, 640, w);
}
void printsnack(node*snack,int length,int p)//此函数用于画蛇，传入结构体蛇数组的头指针当做数组使用，传入蛇身大小
{
	if (p == 0)
	{
		setfillcolor(WHITE);//设置蛇为白色
		for (int i = 0; i < length; ++i)
		{
			int x1 = (snack[i].x) * wide;
			int y1 = (snack[i].y) * wide;
			int x2 = (snack[i].x + 1) * wide;
			int y2 = (snack[i].y + 1) * wide;
			solidrectangle(x1, y1, x2, y2);
		}
	}
	else
	{
		setfillcolor(WHITE);//设置蛇为白色
		for (int i = p; i < length; ++i)
		{
			int x1 = (snack[i].x) * wide;
			int y1 = (snack[i].y) * wide;
			int x2 = (snack[i].x + 1) * wide;
			int y2 = (snack[i].y + 1) * wide;
			solidrectangle(x1, y1, x2, y2);
		}
		setfillcolor(RGB(150, 137, 255));
		for (int i = 0; i < p; ++i)
		{
			int x1 = (snack[i].x) * wide;
			int y1 = (snack[i].y) * wide;
			int x2 = (snack[i].x + 1) * wide;
			int y2 = (snack[i].y + 1) * wide;
			solidrectangle(x1, y1, x2, y2);
		}
	}
}
enum direction//枚举方向为上下左右，枚举类型类似于结构体语法
{
	eup,
	edown,
	eleft,
	eright
};
node snackmove(node* snack, int length, int direction)//以NODE结构体类型函数，既能传回蛇尾坐标还能对进行蛇运动的函数进行运行
{
	node lasttail = snack[length - 1];//设置蛇最后一个数组为蛇尾（下面循环将蛇尾坐标覆盖故需要提前储存）
	for (int i = length -1; i>0; --i)//依次从倒数第二节蛇身开始将其坐标赋于其后一节蛇身坐标
	{
		snack[i].x = snack[i - 1].x;
		snack[i].y = snack[i - 1].y;
	}
	node newhead;//NODE一个新的头（由于蛇头坐标未被重新赋值，与第二节蛇身坐标相同）
	newhead = snack[0];
	if (direction == eup)
	{
		newhead.y--;//如果向上边走y--
	}
	else if (direction == edown)
	{
		newhead.y++;
	}
	else if (direction == eleft)
	{
		newhead.x--;
	}
	else if (direction == eright)
	{
		newhead.x++;
	}
	snack[0] = newhead;
	return lasttail;//返回蛇尾的坐标，用于蛇吃掉食物增长原蛇尾的机制
}
void control(direction* p)//将direction的指针传入，默认指针指向向右的操作，该函数进行键入改写
{
	if (_kbhit() != 0)
	{
		char c = _getch();
		switch (c)
		{
		case'a':
			if (*p != eright)//不能以前进方向相反
			{
				*p = eleft;//改变指针方向
			}
			break;
		case'd':
			if (*p != eleft)
			{
				*p = eright;
			}
			break;
		case'w':
			if (*p != edown)
			{
				*p = eup;
			}
			break;
		case's':
			if (*p != eup)
			{
				*p = edown;
			}
			break;
		}
	}
}
node creat(node*snack, int length)//为食物随机生成的坐标使用结构体node返回
{
	node food;
	while (1)
	{
		food.x = rand() % (800 / wide);
		food.y = rand() % (600 / wide);
		int i;
		for (i = 0; i < length; ++i)//检测是否生成在蛇身上
		{
			if (snack[i].x == food.x && snack[i].y == food.y)//如果生成在蛇身上
			{
				break;//退出for循环，将得到的i的值向下比对
			}//如果没有生成在蛇身上，那么循环将会走完LENGTH次，i等于蛇身长度
		}
		if (i < length)//如果得到的i的值小于蛇身长度，说明在蛇身上，继续循环
		{
			continue;
		}
		else
		{
			break;//否则跳出while循环，返回食物坐标
		}
	}
	return food;
}
void printfood(node food,int m)//根据上方坐标函数打印食物
{
	int x1 = (food.x) * wide;
	int y1 = (food.y) * wide;
	int x2 = (food.x + 1) * wide;
	int y2 = (food.y + 1) * wide;

	if (m == 1)
	{
		setfillcolor(YELLOW);
	}
	else if (m == 2)
	{
		setfillcolor(GREEN);
	}
	else if (m == 3)
	{
		setfillcolor(RED);
	}
	else if (m == 4)
	{
		setfillcolor(RGB(145, 81, 255));
	}
	solidrectangle(x1, y1, x2, y2);
	setfillcolor(WHITE);
}

bool purple(node* snack, int length)//判断蛇是否碰墙或自尽的机制
{
	if (snack[0].x<0 || snack[0].x>(800 / wide))
	{
		return true;
	}
	else if (snack[0].y<0 || snack[0].y>(600 / wide))
	{
		return true;
	}
	for (int i = 1; i < length; ++i)
	{
		if (snack[0].x == snack[i].x && snack[0].y == snack[i].y)
		{
			return true;
		}
	}
	return false;
}
bool gameover(int p)
{
	if (p == 3)
	{
		return true;
	}
	return false;
}
void reset(node* snack, int* length, direction* d,int *a,int *p)//游戏结束后重新绘制蛇和食物
{
	snack[0] = { 5,7 };
	snack[1] = { 4,7 };
	snack[2] = { 3,7 };
	snack[3] = { 2,7 };
	snack[4] = { 1,7 };
	*length = 5;
	*d = eright;
	*a = 0;
	*p = 0;
}
void reset1(node* snack, int* length, direction* p)
{
	snack[0] = { 5,7 };
	snack[1] = { 4,7 };
	snack[2] = { 3,7 };
	snack[3] = { 2,7 };
	snack[4] = { 1,7 };
	*length = 5;
	*p = eright;
}
int main()
{
	initgraph(800, 680);
	setbkcolor(RGB(26, 226, 244));
	node snack[100] = { {5,7},{4,7},{3,7},{2,7},{1,7} };
	int n = 5;
	int a = 0;
	direction d = eright;
	srand(time(NULL));
	node food = creat(snack, n);
	srand(time(NULL));
	int m = 0;
	int p = 0;
	m = 1 + rand() % 3;
	while (1)
	{
		cleardevice();
		printfood(food,m);
		print();
		point(a);
		printsnack(snack, n,p);
		Sleep(500);
		control(&d);
		node lasttail=snackmove(snack, n, d);
		if (snack[0].x == food.x && snack[0].y == food.y)
		{
			if (n < 100)
			{
				snack[n] = lasttail;
				n++;
				if (m == 1)
				{
					a += 100;
				}
				else if (m == 2)
				{
					a += 10;
				}
				else if(m==3)
				{
					a += 50;
				}
				else
				{
					++p;
				}
				srand(time(NULL));
				m = 1 + rand() % 3;
			}
			food = creat(snack, n);
		}
		if (purple(snack,n) == true)
		{
			m = 4;
			reset1(snack,&n,&d);
		}
		if (gameover(p) == true)
		{
			srand((unsigned)time(NULL));
			m = 1 + rand() % 3;
			reset(snack, &n, &d, &a,&p);
			food = creat(snack, n);
		}
	}
	getchar();
	closegraph();
	return 0;
}

