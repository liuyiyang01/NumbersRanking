#ifndef __our_option_h______________________
#define __our_option_h______________________


extern int i_rankBubble;
extern int j_rankBubble;//记录冒泡排序当前位置 
extern int restart_rankBubble;//判断冒泡排序是否需要重新开始 
extern int func; //标记目前正在使用何种排序方式 

extern int finished;//标记排序是否结束 

extern int bubble_flag;//是否开始自动排序 ，数据传递给main.c 

extern int restart_rankSelect;//判断选择排序是否需要重新开始 
extern int Select_locate;//记录选择排序当前位置
extern int Select_flag;
extern int Merge_flag;

extern int restart_rankMerge;
extern int n_Merge;
extern int iMax;

extern int firstEnterRanking;



void drawMenu(void);

//===========================================================================
//	函数名称： drawButtons(void);
//	作者：刘逸洋	邮箱：3200104898@zju.edu.cn	联系电话：15757168776
// 	函数功能：	界面按钮 
//  最近修改：2020年5月21日 
//===========================================================================
void drawButtons(void);

//===========================================================================
//	函数名称： rankBubble(void);
//	作者：刘逸洋	邮箱：3200104898@zju.edu.cn	联系电话：15757168776
// 	函数功能：	实现单步执行的冒泡排序，
//				并将当前运行状态记录在全局变量i_rankBubble和 j_rankBubble，
//				以便于下一次调用。 
//  最近修改：2020年5月16日 
//===========================================================================
int rankBubble(void);

//===========================================================================
//	函数名称： rankSelect(void);
//	作者：章仁翔	邮箱：3200104748@zju.edu.cn	联系电话：17300989171
// 	函数功能：	
//  最近修改：2020年5月27日 
//===========================================================================
int rankSelect(void);

//===========================================================================
//	函数名称： rankMerge(void);
//	作者：吴创		邮箱：3200102123@zju.edu.cn	联系电话：19883143610
// 	函数功能：	
//  最近修改：2020年5月16日 
//===========================================================================
int rankMerge(void);


#endif // ifndef __our_option_h______________________
