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



#include "main.h"
#include "our_option.h"


double x_histogram[100];
double interval;
static int preLocation[100];
int movingTimer=100; 
int moving_finished=0;


static void initialization(void)
{
	int i;
	if (firstEnterRanking==1)
	{
		for(i=0;i<count;i++)
			preLocation[i]=location[i];
		firstEnterRanking=0;
	}
	

//	char location_char[20];
//	char num_char[20];
//	
//	for(i=0;i<count;i++)
//	{
//		sprintf(location_char, "%d", location[i]);
//		drawLabel(0.4*i,6.2,location_char);	
//		sprintf(num_char, "%d", preLocation[i]);
//		drawLabel(0.4*i,6,num_char);	
//	}
	
//	for(i=0;i<count;i++)
//	{
//		int j=0;
//		while(location[j]!=i+1)
//			j++;
//		sprintf(location_char, "%d", location[j]);
//		drawLabel(0.4*i,5.8,location_char);	
//		sprintf(num_char, "%d", preLocation[j]);
//		drawLabel(0.4*i,5.6,num_char);
//	}
}


static void drawHider(void)
{
	double w = 1.0;
	double h = GetFontHeight() * 2;
	
	SetPenColor("buttonBackground");
	drawBox(0, winheight-2.8, winwidth, 2.8, 1, "数据处理中...", 'C', "wordBlack");
	
	
	setButtonColors ("Red", "wordBlack", "Red", "White", 1); 
	if( button(GenUIID(0), 5, winheight-1.6, w, h, "停止")) 
	{
		bubble_flag=0;//实现自动执行状态下的暂停
		Select_flag=0;
		Merge_flag=0;
		movingTimer==100; 
	}
	setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
	
}

static void moveHistogram(void)
{	
	int flag=0;
	int i;
	int j=0; 
	interval= winwidth/(count+2-modelID);
	
	if (movingTimer<100)
	{
		for (i=0;i<count;i++)
			x_histogram[i]=(preLocation[i]*(100.0-movingTimer)/100.0+location[i]*movingTimer/100.0)*interval;
		drawHider();//画遮罩 
	}
	else 
	{
		if (moving_finished==1)
		{
			for (i=0;i<count;i++)
			{
				preLocation[i]=location[i];
				x_histogram[i]=location[i]*interval;
			}
			moving_finished=0;	
		}
		else
		{
			for (i=0;i<count;i++)
			{
				x_histogram[i]=location[i]*interval;
			}
			for (i=0;i<count;i++)
			{
				
				if (location[i]!=preLocation[i])
				{
					movingTimer=0;
				}
			}
			
		}
	}
}

static void setLocation(void)
{
	
	if(modelID==0)
	{
		int i;
		interval= winwidth/(count+2-modelID);
		for (i=0;i<count;i++)
			x_histogram[i]=location[i]*interval;	
	}
	else if(modelID==1)
	{
		initialization();
		moveHistogram();
	}

}




static void AddNumButton(void)
{
	double r=0.18;
	double h=0.6;
	MovePen(interval*(count+1)+r,h+r);

	SetPenSize(5);
	SetPenColor("Cyan");
	DrawArc(r,0,360);
	
	SetPenSize(5);
	SetPenColor("Dark Gray");
	MovePen(interval*(count+1)-0.45*r,h+r);
	DrawLine(0.9*r,0);
	MovePen(interval*(count+1),h+r-0.45*r);
	DrawLine(0,0.9*r);
	
	SetPenSize(1);
	SetPenColor("Black");
}

static double maxnum(void)
{
	int i;
	double max;
	max=0;
	for(i=0;i<count;i++)
	{
		if(max<num[i])
			max=num[i];
	}
	return max;
}

void drawHistogram(void)
{
	int i;
	double histogram_width=interval*0.4;
	double hh=5.3;//柱形图高度比例系数 
	double lowheight=0.25;//柱形图基准线的高度 
	char* color[]={"Orange","Blue","Dark Gray","Magenta","Red","Yellow", "Cyan","Green"};
//	int colorID;
	setLocation();
	for(i=0;i<count;i++)
	{
		char num_display[100];
		
//		colorID=rand()%8;
//		MovePen(x_histogram[i]-histogram_width/2,0.5);
//		SetPenSize(10);
		SetPenColor(color[i%8]);
		drawRectangle(x_histogram[i]-histogram_width/2,lowheight,histogram_width,num[i]/maxnum()*hh,1);
		SetPenColor("Black");
		
//		DrawLine(0,num[i]*0.05);
//		SetPenSize(1);

		sprintf(num_display,"%.1f",num[i]);
		
		drawLabel(x_histogram[i]-TextStringWidth(num_display)/2,lowheight+num[i]/maxnum()*hh+0.1,num_display);
	}
	if(modelID==0)
		AddNumButton();
	
	SetPenSize(5);
	SetPenColor("Gray");
	MovePen(0.2,lowheight);
	DrawLine(winwidth-0.4,0);
	MovePen(0.2,winheight-2.8);
	DrawLine(winwidth-0.4,0);
	SetPenSize(1);
	
}

