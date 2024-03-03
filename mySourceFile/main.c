//===========================================================================
//
//  版权所有者： 刘逸洋、吴创、章仁翔，浙江大学蓝田学园 
//
//	作者：刘逸洋	邮箱：3200104898@zju.edu.cn	联系电话：15757168776
//	作者：吴创		邮箱：3200102123@zju.edu.cn	联系电话：19883143610
//	作者：章仁翔	邮箱：3200104748@zju.edu.cn	联系电话：17300989171
// 
//  最近修改：2020年5月21日 
//  初次创建：2020年5月15日，用于<<程序设计专题>>课程大程序编程
//	项目名称：排序可视化 
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


//宏定义，便于分模块调试 
//#define DEMO_DISPLAY_RANK
#define DEMO_RANDOM20
//#define DEMO_BAR

/***************************************************************
 VisualStudio 2010 用户注意：
    将Character Set设置为 Use Multibyte Character Set
	否则中文显示不正常
***************************************************************/
// 全局变量
double winwidth, winheight;   // 窗口尺寸

double num[100];//存储需要排序的数据，运行过程中数值不交换；
int location[100];//对应存储数据当前所在的位置，运行过程中数值交换；
int count;//数据个数；
int enable_editing=1;//判断是否允许操作（正在处理数据……）；

int modelID=0;//0-数据编辑模式；1-排序模式； 


// 清屏函数，provided in libgraphics
void DisplayClear(void);

// 计时器启动函数，provided in libgraphics
void startTimer(int id,int timeinterval);

// 用户的显示函数
void display(void); 

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}

// 计时器
#define MY_BUBBLE_TIMER  1
#define MY_SELECT_TIMER  2
#define MY_MERGE_TIMER  2
#define MOVE  0


// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{
	if (timerID==MY_BUBBLE_TIMER && bubble_flag && movingTimer==100) //1500
	{
		rankBubble();
		display();// 刷新显示
		
		if (finished==1)
			bubble_flag=0; 
		
	}
	
	if (timerID==MY_SELECT_TIMER && Select_flag && movingTimer==100) //1500
	{
		rankSelect();
		display();// 刷新显示
		
		if (finished==1)
			Select_flag=0; 
		
	}
	
	if (timerID==MY_MERGE_TIMER && Merge_flag && movingTimer==100) //1500
	{
		rankMerge();
		display();// 刷新显示
		
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
			
		display();// 刷新显示
	}

	display();
}


// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("排序可视化");
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(15, 10);
	SetWindowSize(15, 9);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();
    SetPenColor("Green");

	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器

	// 开启定时器
	startTimer(MY_BUBBLE_TIMER, 100);
	startTimer(MY_SELECT_TIMER, 100);
	startTimer(MY_MERGE_TIMER, 100);
	startTimer(MOVE, 1);
	
	// 打开控制台，方便用printf/scanf输出/入变量信息，方便调试
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




