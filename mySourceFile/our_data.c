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
#include "our_histogram.h"

int data_status=0;

void saveData(void)//导出二进制文件 
{
	int i;
	FILE* output;
	output = fopen("data.dat","wb");//生成的文件无法用记事本打开
	if(output == NULL){
		data_status=1; 
	}
	else
	{
		fprintf(output,"%d ",finished); 
		
		fprintf(output,"%d ",count); 
		
		for(i=0;i<count;i++)
		{
			fprintf(output,"%f ",num[i]);
			fprintf(output,"%d ",location[i]);
		}
	}
	fclose(output);
	display();
}

void restoreData(void)//导入二进制文件 
{
	int i;
	FILE* input;
	input = fopen("data.dat","rb");//生成的文件无法用记事本打开
	if(input == NULL){
		data_status=2; 
	}
	else
	{
		fscanf(input,"%d",&finished);
		fscanf(input,"%d",&count);
		for(i=0;i<count;i++)
		{
			fscanf(input,"%lf",&num[i]);
			fscanf(input,"%ld",&location[i]);
		}
	}
	fclose(input);
	display();
}

void openData(void)//打开txt数据库 
{
	FILE* fp;
	char  datatype[10];
	fp = fopen("database.txt","rb");
	if(fp == NULL){
		data_status=3; 
	}
	fscanf(fp,"%s",datatype);
	count=0;
	if(strcmp(datatype,"double")==0)
	{
		while(!feof(fp))
		{
			fscanf(fp,"%lf",&num[count]);
			location[count]=count+1;
			count++;
		}
	}
	else if(strcmp(datatype,"float")==0)
	{
		while(!feof(fp))
		{
			float newnum;
			fscanf(fp,"%f",&newnum);
			num[count]=(double)newnum;
			location[count]=count+1;
			count++;
		}
	}
	else if(strcmp(datatype,"int")==0)
	{
		while(!feof(fp))
		{
			int newnum;
			fscanf(fp,"%d",&newnum);
			num[count]=(double)newnum;
			location[count]=count+1;
			count++;
		}
	}
	else
	{
		data_status=4; 
	}
}


