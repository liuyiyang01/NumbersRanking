#ifndef __main_h______________________
#define __main_h______________________


// 全局变量
extern double winwidth, winheight;   // 窗口尺寸

extern double num[100];//存储需要排序的数据，运行过程中数值不交换；
extern int location[100];//对应存储数据当前所在的位置，运行过程中数值交换；
extern int count;//数据个数；
extern int enable_editing;//判断是否允许操作（正在处理数据……）；

extern int modelID;


#endif // ifndef __main_h______________________
