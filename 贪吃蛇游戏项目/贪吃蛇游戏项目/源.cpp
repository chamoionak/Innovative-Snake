#include<easyx.h>
#include<iostream>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#define wide 40
using namespace std;
struct node//�ṹ��ȷ������x,y
{
	int x;
	int y;
};
void print()//��ӡ����������
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

	settextstyle(40, 0, "΢���ź�");
	setbkmode(TRANSPARENT);
	const char* p = "���֣�";
	outtextxy(0, 600, p);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	int n = c;
	TCHAR s[5];
	sprintf_s(s, _T("%d"), n);		// �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(100, 600, s);

	settextstyle(40, 0, "΢���ź�");
	setbkmode(TRANSPARENT);
	const char* d = "��ɫ+10  ��ɫ+50  ��ɫ+100  �Ծ�����ɫƻ��";
	outtextxy(150, 600, d);

	settextstyle(40, 0, "΢���ź�");
	setbkmode(TRANSPARENT);
	const char* w = "�ۼƳ�3����ɫƻ��������������Ϸ��ʽ����";
	outtextxy(150, 640, w);
}
void printsnack(node*snack,int length,int p)//�˺������ڻ��ߣ�����ṹ���������ͷָ�뵱������ʹ�ã����������С
{
	if (p == 0)
	{
		setfillcolor(WHITE);//������Ϊ��ɫ
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
		setfillcolor(WHITE);//������Ϊ��ɫ
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
enum direction//ö�ٷ���Ϊ�������ң�ö�����������ڽṹ���﷨
{
	eup,
	edown,
	eleft,
	eright
};
node snackmove(node* snack, int length, int direction)//��NODE�ṹ�����ͺ��������ܴ�����β���껹�ܶԽ������˶��ĺ�����������
{
	node lasttail = snack[length - 1];//���������һ������Ϊ��β������ѭ������β���긲�ǹ���Ҫ��ǰ���棩
	for (int i = length -1; i>0; --i)//���δӵ����ڶ�������ʼ�������긳�����һ����������
	{
		snack[i].x = snack[i - 1].x;
		snack[i].y = snack[i - 1].y;
	}
	node newhead;//NODEһ���µ�ͷ��������ͷ����δ�����¸�ֵ����ڶ�������������ͬ��
	newhead = snack[0];
	if (direction == eup)
	{
		newhead.y--;//������ϱ���y--
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
	return lasttail;//������β�����꣬�����߳Ե�ʳ������ԭ��β�Ļ���
}
void control(direction* p)//��direction��ָ�봫�룬Ĭ��ָ��ָ�����ҵĲ������ú������м����д
{
	if (_kbhit() != 0)
	{
		char c = _getch();
		switch (c)
		{
		case'a':
			if (*p != eright)//������ǰ�������෴
			{
				*p = eleft;//�ı�ָ�뷽��
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
node creat(node*snack, int length)//Ϊʳ��������ɵ�����ʹ�ýṹ��node����
{
	node food;
	while (1)
	{
		food.x = rand() % (800 / wide);
		food.y = rand() % (600 / wide);
		int i;
		for (i = 0; i < length; ++i)//����Ƿ�������������
		{
			if (snack[i].x == food.x && snack[i].y == food.y)//���������������
			{
				break;//�˳�forѭ�������õ���i��ֵ���±ȶ�
			}//���û�������������ϣ���ôѭ����������LENGTH�Σ�i����������
		}
		if (i < length)//����õ���i��ֵС�������ȣ�˵���������ϣ�����ѭ��
		{
			continue;
		}
		else
		{
			break;//��������whileѭ��������ʳ������
		}
	}
	return food;
}
void printfood(node food,int m)//�����Ϸ����꺯����ӡʳ��
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

bool purple(node* snack, int length)//�ж����Ƿ���ǽ���Ծ��Ļ���
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
void reset(node* snack, int* length, direction* d,int *a,int *p)//��Ϸ���������»����ߺ�ʳ��
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

