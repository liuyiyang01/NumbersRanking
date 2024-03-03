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


#include "our_data.h" 
#include "main.h"
#include "our_histogram.h"

#define up_h   (2.1*h)


int i_rankBubble=0;
int j_rankBubble=0;//记录冒泡排序当前位置 
int restart_rankBubble=1;//判断冒泡排序是否需要重新开始 
int func=0; //标记目前正在使用何种排序方式 

int finished=0;//标记排序是否结束 

int bubble_flag;//是否开始自动排序 ，数据传递给main.c 

int restart_rankSelect=1;//判断选择排序是否需要重新开始 
int Select_locate=0;//记录选择排序当前位置
int Select_flag;
int Merge_flag;

int restart_rankMerge=1;
int n_Merge=1;
int iMax=1;

int firstEnterRanking;

void restart(void)
{
	finished=0;
	restart_rankBubble=1;
	restart_rankSelect=1;
	restart_rankMerge=1;
	bubble_flag=0;
}

void drawMenu()
{
	static char * menuListAbout[] = {"数据菜单",
		"生成快照",
		"恢复快照",
		"导入数据",
		"打开数据"
		};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 8; //fH/8;
	double y = winheight-1;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListAbout[2])*1.2; // 控件宽度    
	double wlist = TextStringWidth(menuListAbout[2])*1.2;
	double xindent = winheight/20; // 缩进
	int selection;
	
	// menu bar
//	drawMenuBar(0,y-h,winwidth,h);
	
	// 关于 菜单
	selection = menuList(GenUIID(0),10.4,  winheight-0.8, w, wlist,h, menuListAbout,sizeof(menuListAbout)/sizeof(menuListAbout[0]));
	if( selection==1 )
		saveData();
	if( selection==2 )
		restoreData();
	if( selection==3 )
		openData();
	if( selection==4 )
		system("database.txt");
}

void drawButtons(void)
{
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度
	double x = winwidth/2.5;  
	double y = winheight/2-h; 
	double w = winwidth/7; // 控件宽度
	DefineColor("buttonBackground",.88,.88,.88);
	DefineColor("wordBlack",.10,.10,.10);
	DefineColor("boxBackground",.90,.90,.90);
	DefineColor("DGreen",0,0.5,0); 
	
//	SetPenColor("newBlack");
	setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
	setMenuColors   ("Gray", "Black", "Dark Gray", "White", 1);
	setTextBoxColors("boxBackground", "wordBlack", "boxBackground", "wordBlack", 0);
	if(enable_editing==0)
	{
		if(func==1)
			setButtonColors ("Green", "wordBlack", "Magenta", "White", 1); 
		if( button(GenUIID(0), x-2.4*w, winheight-0*h-up_h, w, h, "冒泡排序") )
		{	
			func=1;
			display();
		}
		setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
		
		if(func==2)
			setButtonColors ("Green", "wordBlack", "Magenta", "White", 1); 
		if( button(GenUIID(0), x-1.2*w, winheight-0*h-up_h, w, h, "选择排序") )
		{	
			func=2;
			display();
		}
		setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
		
		if(func==3)
			setButtonColors ("Green", "wordBlack", "Magenta", "White", 1); 
		if( button(GenUIID(0), x-0*w, winheight-0*h-up_h, w, h, "归并排序") )
		{	
			func=3;
			display();
		}
		setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
		
		if(finished==1)
		{
			drawLabel(0.2,winheight-3.3,"排序已完成！");
		}
		if(func==1)
		{
			if( button(GenUIID(0), x-2.4*w, winheight-1.3*h-up_h, w, h, "单步执行")&&finished==0  && movingTimer==100) 
			{
				rankBubble();
				display();
				bubble_flag=0;//实现自动执行状态下的暂停 
			}
			
			if( button(GenUIID(0), x-1.2*w, winheight-1.3*h-up_h, w, h, "自动执行") &&finished==0 && movingTimer==100)
			{
				bubble_flag=1;
			}
			if( button(GenUIID(0), x, winheight-1.3*h-up_h, w, h, "全部执行")&&finished==0  && movingTimer==100)
			{
				bubble_flag=0;
				while(finished==0)
					rankBubble();
				display();
				
			}
		}
		
		if(func==2)//选择排序 
		{
			if( button(GenUIID(0), x-2.4*w, winheight-1.3*h-up_h, w, h, "单步执行")&&finished==0  && movingTimer==100) 
			{
				rankSelect();
				display();
				Select_flag=0;
			}
			 
			if( button(GenUIID(0), x-1.2*w, winheight-1.3*h-up_h, w, h, "自动执行") &&finished==0 && movingTimer==100)
			{
				Select_flag=1;
				
			}
			if( button(GenUIID(0), x, winheight-1.3*h-up_h, w, h, "全部执行")&&finished==0  && movingTimer==100)
			{
				Select_flag=0;
				while(finished==0)
					rankSelect();
				display();
				
			}
		}
		
		if(func==3)//归并排序 
		{
			if( button(GenUIID(0), x-2.4*w, winheight-1.3*h-up_h, w, h, "单步执行")&&finished==0 ) 
			{
				rankMerge();
				display();
				Merge_flag=0;
			}
			 
			if( button(GenUIID(0), x-1.2*w, winheight-1.3*h-up_h, w, h, "自动执行") &&finished==0)
			{
				Merge_flag=1;
				
			}
			if( button(GenUIID(0), x, winheight-1.3*h-up_h, w, h, "全部执行")&&finished==0 )
			{
				Merge_flag=0;
				while(finished==0)
					rankMerge();
				display();
			}
		}
		
		setButtonColors ("buttonBackground", "wordBlack", "Red", "White", 1);
		if( button(GenUIID(0), x+3*w, winheight-0*h-up_h, w, h, "退出排序") )
		{	
			
			enable_editing=1; 
			modelID=0;
			display();
		}
		setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);	
	}
	else
	{
		static char input1[80] = "";
		static char input2[80] = "";
		static char input3[80] = "";
		static int randnum;
		static double new_num;
		static double delete_num;
		static int delete_selecting=0;
		
		drawMenu();
		//清空
		setButtonColors ("buttonBackground", "wordBlack", "Red", "White", 1);
		if( button(GenUIID(0), x+3.0*w, winheight-0.3*h-up_h, w, h, "清空") )
		{	
			count=0;
			restart();
			display();
		}
		setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
		
		//随机生成数字 
		SetPenColor("boxBackground");
		drawBox(x-2.4*w, winheight-0*h-up_h, w, h, 1, "输入个数：", 'C', "wordBlack");
//		drawLabel(x-2.4*w, 16.5*h,"个数：");
		if( textbox(GenUIID(0), x-1.4*w, winheight-0*h-up_h, w, h, input3, sizeof(input3)) )
			randnum=(int)atof(input3); 
		
		if( button(GenUIID(0), x-0.2*w, winheight-0*h-up_h, w, h, "生成随机数")&&randnum<100 )
		{	
			count=randnum;
			int p;
			for(p=0;p<count;p++)
			{
				location[p]=p+1;
				num[p]=1+rand()%99;
			} 
			restart();
//			strcpy(input1,"");
			display();
		}
		
		//插入数据 
		SetPenColor("boxBackground");
		drawBox(x-2.4*w, winheight-1.3*h-up_h, w, h, 1, "插入数据：", 'C', "wordBlack");
		
		
		if( textbox(GenUIID(0), x-1.4*w, winheight-1.3*h-up_h, w, h, input1, sizeof(input1)) )
			new_num=atof(input1); 
		
		if( button(GenUIID(0), x-0.2*w, winheight-1.3*h-up_h, w, h, "插入") )
		{	
			num[count]=new_num;
			location[count]=count+1;
			count++; 
			restart();
			strcpy(input1,"");
			display();
		}
		
		//删除数据 
//		SetPenColor("newBlack");
		SetPenColor("boxBackground");
		drawBox(x-2.4*w, winheight-2.6*h-up_h, w, h, 1, "删除数据：", 'C', "wordBlack");
		
//		SetPenColor("newBlack");
		if( textbox(GenUIID(0), x-1.4*w, winheight-2.6*h-up_h, w, h, input2, sizeof(input2)) )
			delete_num=atof(input2); 
		
		#if defined(DEMO_SELECT_DELETE) 
		if(delete_selecting==1)
		{
			int j=0;
			int delete_location;
			int j_cpy;
			
			for(j=0;j<count;j++)
			{
				if( button(GenUIID(0), winwidth/count*(j+0.1), 0.5*h, winwidth/30, winwidth/30, "√") )
				{
//					delete_location=location[j];
//					j_cpy=j;
//					while(j_cpy<count)
//					{
//						num[j_cpy]=num[j_cpy+1];
//						location[j_cpy]=location[j_cpy+1];
//						j_cpy++; 
//					}
					count--;
//					for(j_cpy=0;j_cpy<count;j_cpy++)
//					{
//						if(location[j_cpy]>delete_location)
//							location[j_cpy]--;
//					}
					display();
				}
			}
			if( button(GenUIID(0), x+1.2*w, 13*h, w, h, "关闭") )
			{
				delete_selecting=0;
			} 
		}
		#endif	
		
		if( button(GenUIID(0), x+0.9*w, winheight-2.6*h-up_h, w, h, "按序号查找") )
		{	
			int i=0;
			int delete_location;
			while(location[i]!=delete_num&&i<count)
			{
				i++;
			}
			if(i==count)
			{
				drawLabel(x+1.2*w, 13.5*h,"未找到数据！");
				delete_selecting=1;
				display();
			}
			else
			{
				delete_location=location[i];
				while(i<count)
				{
					num[i]=num[i+1];
					location[i]=location[i+1];
					i++; 
				}
				count--;
				for(i=0;i<count;i++)
				{
					if(location[i]>delete_location)
					location[i]--;
				}
				strcpy(input2,"");
				display();
			}
				
		}
		
		if( button(GenUIID(0), x-0.2*w, winheight-2.6*h-up_h, w, h, "按数值查找") )
		{	
			int i=0;
			int delete_location;
			while(num[i]!=delete_num&&i<count)
			{
				i++;
			}
			if(i==count)
			{
				drawLabel(x+1*w, 13.5*h,"未找到数据！");
				delete_selecting=1;
				display();
			}
			else
			{
				delete_location=location[i];
				while(i<count)
				{
					num[i]=num[i+1];
					location[i]=location[i+1];
					i++; 
				}
				count--;
				for(i=0;i<count;i++)
				{
					if(location[i]>delete_location)
					location[i]--;
				}
				strcpy(input2,"");
				display();
			}
				
		}
		
		
		setButtonColors ("Green", "wordBlack", "Green", "DGreen", 1);
		if( button(GenUIID(0), x+3.0*w, winheight-2.3*h-up_h, w, h, "排序") )
		{	
			enable_editing=0;
			modelID=1;
			firstEnterRanking=1;
			display();
		}
		setButtonColors ("buttonBackground", "wordBlack", "Magenta", "White", 1);
	}	
}


int rankBubble(void)
{
	if(restart_rankBubble)
	{
		i_rankBubble=0;
		j_rankBubble=0;
		restart_rankBubble=0;
		finished=0;
	}
	int i=i_rankBubble, j=j_rankBubble;
	int p1=0 ,p2=0;
	if(i==count-j)
	{
		i=0;
		j++;
	}
	while(location[p1]!=i)
		p1++;
	while(location[p2]!=i+1)
		p2++;
	if(num[p1]>num[p2])
	{
		int t;
		t=location[p1];
		location[p1]=location[p2];
		location[p2]=t;
	}
	i_rankBubble=i+1;
	j_rankBubble=j;
	restart_rankSelect=1;
	
	if(j==count-1)
	{
		finished=1; 
		return 1;
	}
	else 
		return 0;
}

int rankSelect(void)//选择排序 
{
	int i,k,min,p1=0,p2=0; 
	if(restart_rankSelect)
	{
		Select_locate=0;
		restart_rankSelect=0;
		finished=0;
	}
	while(location[p1]!=Select_locate)
		p1++;
	min=p1;
	for(i=Select_locate+1;i<=count;i++)
	{
		p2=0;
		while(location[p2]!=i)
			p2++;
		if(num[p2]<num[min])
		{
			min=p2;	
		}
	}
	k=location[p1];
	location[p1]=location[min];
	location[min]=k;
	Select_locate++;


	if(Select_locate==count)
	{
		finished=1; 
		return 1;
	}
	else 
		return 0;
} 

void Merge(int low,int m,int high)
{
    
    int i = low, j = m + 1;
    int n = high;
    int temk = 0;
    int temp[100];
    int p1=0,p2=0;
    while (i <= m && j <= n)
    {
        p1=0;
        p2=0;
		while(location[p1]!=i)
			p1++;
		while(location[p2]!=j)
			p2++;
		if (num[p1] < num[p2])
		{
			temp[temk++] = p1;
			i++;
		}
        else
        {
        	temp[temk++] = p2;
        	j++;
		}
    
    }
    while (i <= m)
    {
    	p1=0;
		while(location[p1]!=i)
			p1++;
		temp[temk++] = p1;
		i++;
	}
    while (j <= n)
    {
    	p2=0;
		while(location[p2]!=j)
			p2++;
		temp[temk++] = p2;
        j++;
	} 
    for (i = 0; i < temk; i++)
	{
		location[temp[i]] = low+i;
	}
}

int MergeSort(int low,int high)
{
	/*用分治法进行二路归并排序*/  
	int mid;
	int i=0;
    if(low<high)  /*区间长度大于1*/
    {      
        mid=(low+high)/2;            /*分解*/
        i=MergeSort(low,mid)+1;/*递归地对low到mid序列排序 */ 
		          
        MergeSort(mid+1,high);        /*递归地对mid+1到high序列排序 */ 
		if(i<=n_Merge)
		{
			Merge(low,mid,high);
		}
    } 
    
	if(i>iMax)
    	iMax=i; 
    return i;
}

int rankMerge(void)//归并排序 
{
	if(restart_rankMerge)
	{
		n_Merge=1;
		iMax=1;
		restart_rankMerge=0;
		finished=0;
	}
	if(n_Merge<=iMax)
	{
		n_Merge++;
		MergeSort(1,count);
	}
	else
		finished=1; 
}



