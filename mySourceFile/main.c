//===========================================================================
//
//  ��Ȩ�����ߣ� �������ⴴ�������裬�㽭��ѧ����ѧ԰ 
//
//	���ߣ�������	���䣺3200104898@zju.edu.cn	��ϵ�绰��15757168776
//	���ߣ��ⴴ		���䣺3200102123@zju.edu.cn	��ϵ�绰��19883143610
//	���ߣ�������	���䣺3200104748@zju.edu.cn	��ϵ�绰��17300989171
// 
//  ����޸ģ�2020��5��21�� 
//  ���δ�����2020��5��15�գ�����<<�������ר��>>�γ̴������
//	��Ŀ���ƣ�������ӻ� 
//
//===========================================================================
#include <windows.h>
#include <winuser.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "boolean.h"
//#include "exception.h"
#include "gcalloc.h"
#include "genlib.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

#include "our_option.h"
#include "our_histogram.h"
#include "our_option.h"


//�궨�壬���ڷ�ģ����� 
//#define DEMO_DISPLAY_RANK
#define DEMO_RANDOM20
//#define DEMO_BAR

/***************************************************************
 VisualStudio 2010 �û�ע�⣺
    ��Character Set����Ϊ Use Multibyte Character Set
	����������ʾ������
***************************************************************/
// ȫ�ֱ���
double winwidth, winheight;   // ���ڳߴ�

double num[100];//�洢��Ҫ��������ݣ����й�������ֵ��������
int location[100];//��Ӧ�洢���ݵ�ǰ���ڵ�λ�ã����й�������ֵ������
int count;//���ݸ�����
int enable_editing=1;//�ж��Ƿ�������������ڴ������ݡ�������

int modelID=0;//0-���ݱ༭ģʽ��1-����ģʽ�� 


// ����������provided in libgraphics
void DisplayClear(void);

// ��ʱ������������provided in libgraphics
void startTimer(int id,int timeinterval);

// �û�����ʾ����
void display(void); 

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

// ��ʱ��
#define MY_BUBBLE_TIMER  1
#define MY_SELECT_TIMER  2
#define MY_MERGE_TIMER  2
#define MOVE  0


// �û��ļ�ʱ��ʱ����Ӧ����
void TimerEventProcess(int timerID)
{
	if (timerID==MY_BUBBLE_TIMER && bubble_flag && movingTimer==100) //1500
	{
		rankBubble();
		display();// ˢ����ʾ
		
		if (finished==1)
			bubble_flag=0; 
		
	}
	
	if (timerID==MY_SELECT_TIMER && Select_flag && movingTimer==100) //1500
	{
		rankSelect();
		display();// ˢ����ʾ
		
		if (finished==1)
			Select_flag=0; 
		
	}
	
	if (timerID==MY_MERGE_TIMER && Merge_flag && movingTimer==100) //1500
	{
		rankMerge();
		display();// ˢ����ʾ
		
		if (finished==1)
			Merge_flag=0; 
		
	}

	if (timerID==MOVE && modelID==1) 
	{
		if (movingTimer<100)
		{
			movingTimer++;
			if(movingTimer==100)
				moving_finished=1;
		}
			
		display();// ˢ����ʾ
	}

	display();
}


// �û����������
// ����ʼ��ִ��һ��
void Main() 
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("������ӻ�");
	//SetWindowSize(10, 10); // ��λ - Ӣ��
	//SetWindowSize(15, 10);
	SetWindowSize(15, 9);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics();
    SetPenColor("Green");

	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��

	// ������ʱ��
	startTimer(MY_BUBBLE_TIMER, 100);
	startTimer(MY_SELECT_TIMER, 100);
	startTimer(MY_MERGE_TIMER, 100);
	startTimer(MOVE, 1);
	
	// �򿪿���̨��������printf/scanf���/�������Ϣ���������
//	InitConsole(); 

#if defined(DEMO_RANDOM20)
	int i;
	count=0;
	for(i=0;i<20;i++)
	{
		location[i]=i+1;
		num[i]=1+rand()%99;

		count++;
	}
#endif // #if defined(DEMO_RANDOM20)

}

#if defined(DEMO_DISPLAY_RANK)
void drawRank(void)
{
	int i;
	char location_char[20];
	char num_char[20];
	
	for(i=0;i<count;i++)
	{
		sprintf(location_char, "%d", location[i]);
		drawLabel(0.4*i,2.2,location_char);	
		sprintf(num_char, "%.1f", num[i]);
		drawLabel(0.4*i,2,num_char);	
	}
	
	for(i=0;i<count;i++)
	{
		int j=0;
		while(location[j]!=i+1)
			j++;
		sprintf(location_char, "%d", location[j]);
		drawLabel(0.4*i,1.8,location_char);	
		sprintf(num_char, "%.1f", num[j]);
		drawLabel(0.4*i,1.6,num_char);
	}
	
}

#endif // #if defined(DEMO_DISPLAY_RANK)

#if defined(DEMO_BAR)

#endif // #if defined(DEMO_BAR)

void drawBackground()
{
	DefineColor("Background_color",.95,.95,.95);
	DefineColor("Background_color2",.98,.98,.98);
	SetPenColor("Background_color");
	drawRectangle(0,0,winwidth,winheight,1);
	SetPenColor("Background_color2");
	drawRectangle(0,0.25,winwidth,winheight-2.8-0.25,1);
	SetPenColor("Black");
}

void display()
{
	DisplayClear();
//	SetPenColor("Green");
	drawBackground();
#if defined(DEMO_DISPLAY_RANK)
	
	drawRank();
#endif // #if defined(DEMO_DISPLAY_RANK)


//	if (modelID==0)
//		drawMenu();
	
	drawButtons();

	drawHistogram();
//	if(movingTimer==100)
//		drawLabel(8.5,6,"avalable!");
//	else
//	{
//		char timer[100];
//		sprintf(timer,"%d",movingTimer);
//		drawLabel(8.5,6,"inavalable!");
//		drawLabel(8.5,5.8,timer);
//	}
		
	
}




