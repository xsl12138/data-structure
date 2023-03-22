/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h> 
/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_VERTEX_NUM 20
/*-------page 22 on textbook -------*/
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {     //表结点类型定义
   	int adjvex;              //顶点位置编号 
    struct ArcNode *nextarc; //下一个表结点指针
} ArcNode;

typedef struct VNode{		//头结点及其数组类型定义
   	VertexType data;       	//顶点信息
    ArcNode *firstarc;      //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  			//邻接表的类型定义
    AdjList vertices;     	//头结点数组
    int vexnum,arcnum;   	//顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

typedef struct{ 			//图的集合类型定义  
	struct { 
		char name[30];  
		ALGraph G;      
	}elem[10];  
    int length;				//用来记录已经有的图数量  
} GRAPHS;
GRAPHS Graphs;				//图集合的定义Graphs
int pos_dfs = 0; 			//dfs中使用，记录递归后应该输出数组中哪个位次的数据
int flag_dfs[20] = {0};		//dfs中使用， 判断对应位序的点是否已经输出过 
int ans_connect = 1;		//用于记录连通分量的数量（一个非空图至少有一个连通分量） 
/*-----page 19 on textbook ---------*/
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);		//新建 
status RemoveGraph(GRAPHS &Graphs,char GraphName[]);				//从图组中移除指定名字的图 
status DestroyGraph(ALGraph &G);									//销毁一个图 
status LocateVex(ALGraph G,KeyType u); 								//查找顶点 
status PutVex(ALGraph &G,KeyType u,VertexType value);				//顶点赋值 
status FirstAdjVex(ALGraph G,KeyType u);							//获得第一邻接点 
status NextAdjVex(ALGraph G,KeyType v,KeyType w);					//获得下一邻接点 
status InsertVex(ALGraph &G,VertexType v);							//插入顶点 
status DeleteVex(ALGraph &G,KeyType v);								//删除顶点 
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));			//广度优先遍历 
status InsertArc(ALGraph &G,KeyType v,KeyType w);					//插入弧	 
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));			//深度优先遍历 
status DeleteArc(ALGraph &G,KeyType v,KeyType w);					//删除弧 
status SaveGraph(ALGraph G, char FileName[]);						//存储文件 
status LoadGraph(ALGraph &G, char FileName[]);						//读取文件
status ShortestPathLength(ALGraph &G, KeyType v, KeyType w);		//顶点间最短路径
status ConnectedComponentsNums(ALGraph &G, int judge);							//求图的连通分量个数 
status VerticesSetLessThanK(ALGraph &G, KeyType v, KeyType k);		//距离小于k的顶点集合 
int check1(VertexType V[]); 						//创建图时，用于判断V数组中是否有重复关键字
void visit(VertexType v); 
/*--------------------------------------------*/
int main(void){
int op=1;
VertexType V[30];				//创建图时用于记录点的数据 
KeyType VR[100][2];				//创建图时用于记录边的数据 
Graphs.length = 0;				//初始化图组的数量 
char name_target[30];			//此数组用于记录每个操作的对象（图名） 
int name_tarpos = 0, flag = 0;	//flag用于判断操作对象存不存在于图组里 	
while(op){
	fflush(stdin);	//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
	system("cls");	printf("\n\n");				//清楚屏幕命令 
	printf("用户您好！欢迎使用此程序！\n");
	printf("本程序创建者为	计算机2107班	陈侠锟\n\n"); 
	printf("\nPS：此程序可最多同时存在10个图，你现在已有%d个图\n",Graphs.length);
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. 创建新的图			2. 销毁图\n");
	printf("    	  3. 查找顶点			4. 顶点赋值\n");
	printf("    	  5. 获得第一邻接点		6. 获得下一邻接点	\n");
	printf("    	  7. 插入顶点			8. 删除顶点	\n");
	printf("    	  9. 广度优先遍历		10. 插入弧\n");
	printf("    	  11. 深度优先遍历		12. 删除弧\n");
	printf("    	  13. 图文件读写		14. 顶点间最短路径\n");
	printf("    	  15. 图的连通分量		16. 距离小于k的顶点集合\n"); 
	printf("    	  0. 退出\n\n");
	printf("注意：此线性表中的数据应全为整型！\n");
	printf("-------------------------------------------------\n");
	if(op < 0 || op > 18)	printf("    输入错误！请重新选择你的操作[0~16]:");
	else	printf("    请选择你的操作[0~16]:");
	if(!scanf("%d",&op))	op = 100;
	if (op != 1 && Graphs.length && op != 0){		//1是新增二叉树，0是退出系统 
		printf("以下是你当前拥有的图（按序号排列）：\n");
		for(int i = 0; i < Graphs.length; i++){
			printf("%s ",Graphs.elem[i].name);
		}
		if(op != 2){	//2是销毁图，除1之外的操作均先输出已有图名称以便查询，除1，2之外的操作均需输入要操作的图名 
			fflush(stdin);		//防止输入操作指令后键入的回车让下面输入名称的操作直接读入 
			memset(name_target, 0, sizeof(name_target));	//重置存储操作对象名的数组 
			name_tarpos = 0;	flag = 0; 		//flag用来记录输入的图名称是否存在于二叉树组里 
			printf("\n请输入你想要进行此操作的图名称：");
			for(char c; ((c = getchar()) != ' ' && c != '\n') && name_tarpos < 29; name_tarpos++){  //为了保证线性表的名字在30个字符之内，多余的字符将舍弃 
				name_target[name_tarpos] = c;
			}
		}
	} 
	switch(op){
		case 1:{//新建图 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			int num, i_v = 0, i_arc = 0;		//i_v, i_arc分别用于存储点的数组V和存储边的数组VR的计数 
			char name_str[30];
			if(Graphs.length == 10){
				printf("图组已满！无法创建新的图！\n");
				printf("请按回车键继续……\n");getchar();
				break; 
			}
			printf("请输入你想要新建的图的数量（注意：你当前还可以新建%d个图）：", 10 - Graphs.length);
renew1_1:
			while(!scanf("%d",&num)){
				printf("输入错误！请重新输入一个数字：");
				fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
			} 
			if(num > 10-Graphs.length || num < 0){
				printf("输入数量不合理，请重新输入新建数量：");
				goto renew1_1;
			} 
			for(int i = 0; i < num; i++){
				fflush(stdin);		//为了防止在输入上一个表中的数据时多余的数据对下一个表的输入造成干扰 
				memset(name_str,0,sizeof(name_str));	//重置暂时存储二叉树名字的变量 
				printf("请输入第%d个图的名字(注意：名字最多30个字符，且不可包含空格，多余的数据将会被忽略)：",i+1);
				int name_strpos = 0;
				for(char c; ((c = getchar()) != ' ' && c != '\n') && name_strpos < 29; name_strpos++){  //为了保证二叉树的名字在30个字符之内，多余的字符将舍弃 
					name_str[name_strpos] = c;
				} 
				name_str[name_strpos] = '\0';	//作为字符串的结尾标志 
renew1_2:
				fflush(stdin);	//清空输入流，避免输入二叉树名字时多余的字符对接下来的数据产生干扰 
				memset(V, 0, sizeof(V));	//若执行了goto renew1_2这一语句，需要重置V和VR数组 （每次选择新建图时，也应重置） 
				i_v = 0;
				printf("请依次输入图各结点的关键字（只能为数字）和内容（字符串，20字符以内）,并以-1 null结束：");
				do {
					if(scanf("%d",&V[i_v].key) != 1){
						printf("输入格式有误，请重新输入！\n"); 
						goto renew1_2;
					}
					scanf("%s", V[i_v].others);
				} while (V[i_v++].key != -1);
renew1_3:			
				memset(VR, 0, sizeof(VR));	//若执行了goto renew1_3这一语句，需要重置V和VR数组 （每次选择新建图时，也应重置）
				i_arc = 0;
				printf("请依次输入各边的首尾结点关键字，并以-1 -1结束：");
				do {
    				if(scanf("%d %d",&VR[i_arc][0], &VR[i_arc][1]) != 2){
    					printf("输入格式有误，请重新输入！\n");
    					goto renew1_3;
					}
   				} while(VR[i_arc++][0]!=-1);
				if(CreateGraph(Graphs.elem[Graphs.length].G, V, VR) == OK){
					printf("第%d个图创建成功！\n",i+1);
				} 
				else{
					printf("第%d个图创建失败！请检查关键字是否重复以及顶点数量是否合理！\n",i+1); 
					continue; 
				}
				strcpy(Graphs.elem[Graphs.length].name, name_str); 
				Graphs.length++;		//创建完成一个二叉树，二叉树表长度加一 
			}//end of for（创建树所用的循环） 
			fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据  
			printf("\n操作已完成，以下是你已拥有的图：\n\n");
			for(int k = 0; k < Graphs.length; k++){
				printf("图%d：%s \n",k+1, Graphs.elem[k].name);
    			printf("-----------all elements -----------------------\n");
    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
    				while(p != NULL){
    					printf("%d ",p->adjvex);
    					p = p->nextarc;
					}
					printf("\n");
				}
				printf("------------------ end ------------------------\n\n");
			} 
			printf("请按回车键继续……\n");getchar();
			break;}
		 
		case 2:{//销毁图 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				int num = 0;	char name_del[30];
renew2:
				printf("\n请输入你想要删除的图的数量：\n");
				while(!scanf("%d",&num)){
					printf("输入错误！请输入数字：");
					fflush(stdin);		 
				}
				if(num < 0 || num > Graphs.length){
					printf("输入错误！你当前最多可以删除%d个图！\n",Graphs.length);
					goto renew2;
				}
				getchar();		//读取回车 
				for(int i = 0; i < num; i++){
					printf("请输入第%d个你想要删除的图的名字（每次请输入一个名字，多余的数据将会被忽略）：",i+1);
					memset(name_del, 0, sizeof(name_del)); 
					int name_delpos = 0;
					for(char c; ((c = getchar()) != ' ' && c != '\n') && name_delpos < 29; name_delpos++){  //为了保证图的名字在30个字符之内，多余的字符将舍弃 
						name_del[name_delpos] = c;
					} 
					name_del[name_delpos] = '\0';	//作为字符串的结尾标志 
					if(RemoveGraph(Graphs, name_del) == OK){
						printf("已成功销毁此图！\n");
						continue; 
					}
					else	printf("此图不存在！\n");
				}
				printf("销毁图操作已完成！你当前还有以下图：\n");	//注：销毁图后 Graphs.length-- 这一句在函数中执行 
				for(int k = 0; k < Graphs.length; k++){
					printf("图%d：%s \n",k+1, Graphs.elem[k].name);
	    			printf("-----------all elements -----------------------\n");
	    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
	    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
	    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
	    				while(p != NULL){
	    					printf("%d ",p->adjvex);
	    					p = p->nextarc;
						}
						printf("\n");
					}
					printf("------------------ end ------------------------\n\n");
				} 
			}//end of else  
			fflush(stdin);
			printf("请按回车键继续");getchar();
			break;}
		 
		case 3:{//查找顶点 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int target3;
						printf("请输入一个顶点的关键字，将返回此顶点的位序以及内容：\n");
						while(scanf("%d",&target3) != 1){
							printf("输入错误！请重新新输入：");
							fflush(stdin);	//不加这一句会导致死循环 
						} 
						int res3 = LocateVex(Graphs.elem[i].G, target3);
						if(res3 != ERROR){
							printf("关键字为%d的结点位序是 %d，内容是 %s\n",target3, res3, Graphs.elem[i].G.vertices[res3].data.others);
						}
						else	printf("操作失败，目标结点不存在！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("操作失败，此图不存在！\n");
			}   
			fflush(stdin);
			printf("请按回车键继续");getchar();
			break;}
		 
		case 4:{//结点赋值 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						VertexType value4;	int target4; 
						printf("请依次输入目标顶点关键字，新的关键字和新的内容（多余的数据会被清空）：\n");
						while(scanf("%d %d",&target4, &value4.key) != 2){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						scanf("%s",value4.others);
						if(PutVex(Graphs.elem[i].G, target4, value4) == OK){
							printf("顶点赋值成功！，当前图数据如下：\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("图%d：%s \n",k+1, Graphs.elem[k].name);
				    			printf("-----------all elements -----------------------\n");
				    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
				    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
				    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
				    				while(p != NULL){
				    					printf("%d ",p->adjvex);
				    					p = p->nextarc;
									}
									printf("\n");
								}
								printf("------------------ end ------------------------\n\n");
							} 
						}
						else	printf("操作失败！目标顶点不存在或关键字存在重复！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 5:{//获得第一邻接点		
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int target5; 
						printf("请输入目标顶点关键字，将返回它的第一邻接点：\n");
						while(scanf("%d",&target5) != 1){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						int res5 = FirstAdjVex(Graphs.elem[i].G, target5);
						if(res5 != -1){
							printf("此结点的第一邻接点关键字为 %d，内容是 %s\n",Graphs.elem[i].G.vertices[res5].data.key, Graphs.elem[i].G.vertices[res5].data.others); 
						}
						else	printf("操作失败！目标顶点不存在！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 6:{//获得下一邻接点 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int tartar6, target6; 
						printf("请依次输入两个顶点关键字v和w，将返回v的相对于w的下一邻接点：\n");
						while(scanf("%d %d",&target6, &tartar6) != 2){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						}
						int res6 = NextAdjVex(Graphs.elem[i].G, target6, tartar6); 
						if(res6 != -1){
							printf("%d 相对于 %d 的下一邻接点关键字为 %d，内容为 %s\n",target6, tartar6, Graphs.elem[i].G.vertices[res6].data.key, Graphs.elem[i].G.vertices[res6].data.others);
						}
						else	printf("操作失败！目标顶点不存在或不存在下一邻接点！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 7:{//插入结点 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						VertexType value7; 
						printf("请依次输入待插入顶点的关键字和内容：\n");
						while(scanf("%d",&value7.key) != 1){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						scanf("%s",value7.others);
						if(InsertVex(Graphs.elem[i].G, value7) == OK){
							printf("插入顶点成功！，当前图数据如下：\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("图%d：%s \n",k+1, Graphs.elem[k].name);
				    			printf("-----------all elements -----------------------\n");
				    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
				    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
				    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
				    				while(p != NULL){
				    					printf("%d ",p->adjvex);
				    					p = p->nextarc;
									}
									printf("\n");
								}
								printf("------------------ end ------------------------\n\n");
							} 
						}
						else	printf("操作失败！已达最大点数量或有关键字重复！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 8:{//删除顶点 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int target8; 
						printf("请输入待删除顶点的关键字（注意：当只剩最后一个顶点时无法删除）：\n");
						while(scanf("%d",&target8) != 1){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						if(DeleteVex(Graphs.elem[i].G, target8) == OK){
							printf("删除顶点成功！，当前图数据如下：\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("图%d：%s \n",k+1, Graphs.elem[k].name);
				    			printf("-----------all elements -----------------------\n");
				    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
				    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
				    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
				    				while(p != NULL){
				    					printf("%d ",p->adjvex);
				    					p = p->nextarc;
									}
									printf("\n");
								}
								printf("------------------ end ------------------------\n\n");
							} 
						}
						else	printf("操作失败！待删除结点不存在或图中只剩一个顶点！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 9:{//广度优先遍历 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						printf("广度优先遍历结果如下：\n");
						BFSTraverse(Graphs.elem[i].G, visit); 
						printf("\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 10:{//插入弧 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int v10, w10; 
						printf("请输入待插入弧的首尾顶点：\n");
						while(scanf("%d %d",&v10, &w10) != 2){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						if(v10 == w10){
							printf("输入错误！两顶点不能相同！\n");
							flag = 1;
							break; 
						}
						if(InsertArc(Graphs.elem[i].G, v10, w10) == OK){
							printf("插入弧成功！，当前图数据如下：\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("图%d：%s \n",k+1, Graphs.elem[k].name);
				    			printf("-----------all elements -----------------------\n");
				    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
				    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
				    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
				    				while(p != NULL){
				    					printf("%d ",p->adjvex);
				    					p = p->nextarc;
									}
									printf("\n");
								}
								printf("------------------ end ------------------------\n\n");
							} 
						}
						else	printf("操作失败！输入的顶点中有顶点不存在或两顶点之间已存在边！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 11:{//深度优先遍历 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				memset(flag_dfs, 0, sizeof(flag_dfs));	//DFS用到了两个全局变量：flag_dfs和pos_dfs，每次进行遍历前先重置 
				pos_dfs = 0;
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						printf("深度优先遍历结果如下：\n");
						DFSTraverse(Graphs.elem[i].G, visit); 
						printf("\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 12:{//删除弧 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int v12, w12; 
						printf("请输入待删除弧的首尾顶点：\n");
						while(scanf("%d %d",&v12, &w12) != 2){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						if(DeleteArc(Graphs.elem[i].G, v12, w12) == OK){
							printf("删除弧成功！，当前图数据如下：\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("图%d：%s \n",k+1, Graphs.elem[k].name);
				    			printf("-----------all elements -----------------------\n");
				    			for(int n = 0; n < Graphs.elem[k].G.vexnum; n++){
				    				printf("%d %s ",Graphs.elem[k].G.vertices[n].data.key, Graphs.elem[k].G.vertices[n].data.others);
				    				ArcNode *p = Graphs.elem[k].G.vertices[n].firstarc;
				    				while(p != NULL){
				    					printf("%d ",p->adjvex);
				    					p = p->nextarc;
									}
									printf("\n");
								}
								printf("------------------ end ------------------------\n\n");
							} 
						}
						else	printf("操作失败！输入的顶点中有顶点不存在或两顶点之间不存在边！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 13:{//图读写文件 
			fflush(stdin); 
			char FileName[30];
			strcpy(FileName, "test.txt");
			printf("此功能将会把图中已有的数据写入外部的test.txt文件中，若无此文件，将创造此文件\n");
			printf("请按回车键以开始");
			getchar();
			if(!Graphs.length)		printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						if(SaveGraph(Graphs.elem[i].G, FileName) == ERROR) ;
						else{
							printf("已成功将图中的数据导入外部文件，请查看外部文件\n");
							printf("按回车键以继续\n");
							getchar();
							DestroyGraph(Graphs.elem[i].G);
							printf("已销毁图...\n");
							printf("正在从外部文件导入数据到图...\n");
							if(LoadGraph(Graphs.elem[i].G, FileName) == ERROR)		printf("外部文件丢失！终止操作！");
							else{
								printf("已导入完成，按回车键以输出图中数据\n");
								getchar();
								printf("此图数据如下：\n"); 
								printf("图%d：%s \n",i+1, Graphs.elem[i].name);
				    			printf("-----------all elements -----------------------\n");
				    			for(int n = 0; n < Graphs.elem[i].G.vexnum; n++){
				    				printf("%d %s ",Graphs.elem[i].G.vertices[n].data.key, Graphs.elem[i].G.vertices[n].data.others);
				    				ArcNode *p = Graphs.elem[i].G.vertices[n].firstarc;
				    				while(p != NULL){
				    					printf("%d ",p->adjvex);
				    					p = p->nextarc;
									}
									printf("\n");
								}
								printf("------------------ end ------------------------\n\n");
							}
						}
						flag = 1;
						break;	//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此图不存在！\n"); 
			}//end of else 
	   		printf("请按回车键继续\n");getchar();
			break;}
	   
		case 14:{//顶点间最短路径 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int v14, w14; 
						printf("请输入两个顶点的关键字，将返回两者间的最短路径长度：\n");
						while(scanf("%d %d",&v14, &w14) != 2){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						} 
						int res14 = ShortestPathLength(Graphs.elem[i].G, v14, w14);
						if(res14 != -1){
							printf("两顶点间最短路径长度为：%d\n",res14);
						}
						else	printf("操作失败！有顶点不存在或两顶点间无通路！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
	   		break;}
		
		case 15:{//求连通分量的个数 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				ans_connect = 1;	//求连通分量的函数用到了全局变量：ans_connect，每次进行遍历前先重置 
				memset(flag_dfs, 0, sizeof(flag_dfs));	//DFS用到了两个全局变量：flag_dfs和pos_dfs，每次进行遍历前先重置 
				pos_dfs = 0;
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						printf("当前图共有 %d 个连通分量\n",ConnectedComponentsNums(Graphs.elem[i].G, 1));
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
		
		case 16:{//距离小于k的顶点集合 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!Graphs.length)	printf("你还没有图！请先创建一个图！\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int distance, v16; 
						printf("请输入目标顶点关键字和限定距离，将输出与目标顶点距离在限定范围内的所有顶点的集合：\n");
						while(scanf("%d %d",&v16, &distance) != 2){
							printf("输入错误，请重新输入：");
							fflush(stdin); 
						}
						VerticesSetLessThanK(Graphs.elem[i].G, v16, distance);
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此图不存在！\n"); 
			}
			fflush(stdin); 
			printf("请按回车键继续");getchar();
			break;}
				
		case 0:break;
	}//end of switch
}//end of while
printf("欢迎下次再使用本系统！\n");
//for(int end = 0; end < Graphs.length; end++){		//程序结束，释放所有二叉树的空间 
//	ClearBiTree(Graphs.elem[end].T);
//}
return 0;
}//end of main()

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

int check1(VertexType V[]){     //检查V中的关键字是否有重复
    int flag = 0;
    for(int i = 0; V[i].key != -1; i++){
        for(int j = i+1; V[j].key != -1; j++){
            if((V[i].key == V[j].key) || (strcmp(V[i].others, V[j].others) == 0))
                flag = 1;
                break;
        }
        if(flag)    break;
    }
    if(flag)    return ERROR;   //说明V中有关键字重复
    return OK;
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]){
//根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
    if(check1(V) == ERROR) return ERROR;	//说明V中有关键字重复 
    G.vexnum = 0, G.arcnum = 0;
    int cnt = 0;  //计数
    int flag = 0; //判断一条边是否已经连接两个结点
    int j1 = 0, j2 = 0;	//adjvex赋值用 
    while(V[cnt].key != -1){      //为顶点赋值
        G.vertices[cnt].data.key = V[cnt].key;
        strcpy(G.vertices[cnt].data.others, V[cnt].others);
        G.vertices[cnt].firstarc = NULL;
        G.vexnum++;
        cnt++;
    }
    if(G.vexnum > 20 || G.vexnum == 0){     //顶点数量已经达到最大值20还能进入while循环，说明V中的点一定大于20个；顶点数量为0说明V中根本没有输入顶点，无法创建
            memset(G.vertices, 0, sizeof(G.vertices));
            return ERROR;
    }
    for(int i = 0; VR[i][0] != -1; i++){
    	flag = 0;
        for(int j = 0; j < G.vexnum; j++){
        	if(flag == 2)   break;		 
            if(G.vertices[j].data.key == VR[i][0]){
            	j1 = j;
                ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode)); //头插法插入结点
                p->nextarc = G.vertices[j].firstarc;
                //结点赋值在循环结束之后 
                G.vertices[j].firstarc = p;
                flag++; continue;
            }
            if(G.vertices[j].data.key == VR[i][1]){
            	j2 = j;
                ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode)); //头插法插入结点
                p->nextarc = G.vertices[j].firstarc;
                //结点赋值在循环结束之后 
                G.vertices[j].firstarc = p;
                flag++; continue;
            }
        }
        if(flag != 2)	return ERROR;	//flag不等于2，说明根本没有找到VR数组里存的两个数字，说明有目标结点不存在 
        G.vertices[j1].firstarc->adjvex = j2;
        G.vertices[j2].firstarc->adjvex = j1;
        G.arcnum++;
    }
    return OK;
}

status RemoveGraph(GRAPHS &Graphs,char GraphName[]){
// Graphs中删除一个名称为GraphName的图 
	if(Graphs.length == 0)	return ERROR;
	int j;
    for(int i = 0; i < Graphs.length; i++){
        if(strcmp(Graphs.elem[i].name, GraphName) == 0 && i != Graphs.length - 1){		    
            Graphs.length--; 			//先让图组的总数量减一
            for( j = i ; j < Graphs.length ; j++){    	//图的移动
            	strcpy(Graphs.elem[j].name , Graphs.elem[j+1].name);  //图名字的移动
				memcpy(&Graphs.elem[j].G, &Graphs.elem[j+1].G, sizeof(Graphs.elem[j+1].G));	//图数据的移动（直接覆盖） 
            }
            j++;
            //然后销毁移动完之后处于末端的图 
            DestroyGraph(Graphs.elem[j].G);
            memset(Graphs.elem[j].name , 0 , sizeof(Graphs.elem[j].name));
            return OK;
        }
        else if(strcmp(Graphs.elem[i].name , GraphName) == 0 && i == Graphs.length - 1){	//如果删除的图本来就在队尾 
        	DestroyGraph(Graphs.elem[i].G);
        	Graphs.length--; 
        	memset(Graphs.elem[i].name , 0 , sizeof(Graphs.elem[i].name));
        	return OK;
		}
    }
    return ERROR;
}

status DestroyGraph(ALGraph &G){
/*销毁无向图G,删除G的全部顶点和边*/
    ArcNode *front, *last;    //用于遍历链表的每个顶点，释放各顶点空间
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].firstarc == NULL)   continue;   //说明这一支链表本来就没有数据
        front = G.vertices[i].firstarc->nextarc;
        last = G.vertices[i].firstarc;
        while(front != NULL){
            free(last);
            last = front;
            front = front->nextarc;
        }
        free(last);
        G.vertices[i].firstarc = NULL;
        memset(G.vertices[i].data.others, 0, sizeof(G.vertices[i].data.others));	//重置顶点内容 
        G.vertices[i].data.key = -1;
    }
    G.arcnum = 0;
    G.vexnum = 0;
    return OK;
}

status LocateVex(ALGraph G,KeyType u){
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u) return i;
    }
    return ERROR;
}

status PutVex(ALGraph &G,KeyType u,VertexType value){
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
    int pos = -1;
    for(int i = 0; i < G.vexnum; i++){
        if(u != G.vertices[i].data.key && value.key == G.vertices[i].data.key){
            return ERROR;   //关键字不唯一
        }
        else if(u == G.vertices[i].data.key){//目标位置
            pos = i;
        }
    }
    if(pos == -1)   return ERROR;   		//说明没找到目标结点
    G.vertices[pos].data.key = value.key;
    strcpy(G.vertices[pos].data.others, value.others);
    return OK;
}

status FirstAdjVex(ALGraph G,KeyType u){
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
    int j1 = -1;
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u) return G.vertices[i].firstarc->adjvex;
    }
    return -1;
}

status NextAdjVex(ALGraph G,KeyType v,KeyType w){
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v){
            ArcNode *p = G.vertices[i].firstarc;
            while(p != NULL){
                if(G.vertices[p->adjvex].data.key == w){
                    if(p->nextarc == NULL)  return -1;
                    else return p->nextarc->adjvex;
                } 
                p = p->nextarc;
            }
        }
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v){
//在图G中插入顶点v，成功返回OK,否则返回ERROR
    if(G.vexnum >= 20)  return ERROR;   //点的数量已满
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v.key) return ERROR; //说明有关键字重复
    }
    G.vertices[G.vexnum].data.key = v.key;
    strcpy(G.vertices[G.vexnum].data.others, v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v){
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
    int pos;		//记录待删除点的位置 
    for(int k = 0; k < G.vexnum; k++){		//先找到要删除的点的位置 
    	if(G.vertices[k].data.key == v){
    		pos = k;
    		break;
		}
	}
	if((G.vexnum == 1 && G.vertices[0].data.key == v) || (pos == -1)){
        return ERROR;   //没有目标结点或者将要删除仅有的一个结点
    }
    for(int i = 0; i < G.vexnum; i++){      //删除表结点（边）
        ArcNode *front, *last;
        front = G.vertices[i].firstarc;
        last = NULL;
        if(i != pos){			//如果头结点不是目标结点 
            while(front != NULL){
                if(front->adjvex == pos){		//如果表结点是目标结点 
                    if(!last){	//如果是第一个表结点 
                        G.vertices[i].firstarc = front->nextarc;
                    }
                    else{
                        last->nextarc = front->nextarc;
                    }
                    last = front;
                    front = front->nextarc;
                    free(last);    
                    //这里不用边数减一，只需要在删除目标结点那一支链表时候减掉即可
                    continue;
                }
                else if(front->adjvex > pos)	//如果表结点的序号在目标结点之后 
					front->adjvex--;	//被删除结点之后的结点要往前移动，导致这些结点的序号全都减一 
				last = front;
				front = front->nextarc;	
            }
        }
        else{				//如果头结点是目标结点 
            while(front != NULL){
                last = front;
                front = front->nextarc;
                free(last);   
                G.arcnum--;
            }
            G.vertices[i].firstarc = NULL;
        }
    } //end of for循环（删除表结点）

    for(int j = pos; j < G.vexnum-1; j++){  //进行头结点位置的移动
        strcpy(G.vertices[j].data.others, G.vertices[j+1].data.others);
        G.vertices[j].data.key = G.vertices[j+1].data.key;
        G.vertices[j].firstarc = G.vertices[j+1].firstarc;
        
    }
    G.vertices[G.vexnum-1].firstarc = NULL; //处理移动完毕之后留在末尾的头结点（原头结点数组的最后一个结点）
    G.vertices[G.vexnum-1].data.key = 0;
    memset(G.vertices[G.vexnum-1].data.others, 0, sizeof(G.vertices[G.vexnum-1].data.others));
    G.vexnum--;
    return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType)){
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
    int flag[20] = {0};
    int queue[20] = {0}, rear = 0, front = 0;
    for(int i = 0; i < G.vexnum; i++){
        if(flag[i] != 1){
            queue[rear++] = i;
            flag[i] = 1;
        }
        while(rear != front){
            ArcNode *p = G.vertices[queue[front]].firstarc;
            visit(G.vertices[queue[front]].data);
            front++;
            while(p != NULL){
                if(flag[p->adjvex] != 1){   //说明还未被访问过，进入队列
                    queue[rear++] = p->adjvex;
                    flag[p->adjvex] = 1;    //进队列是则被标记为访问过
                }
                p = p->nextarc;
            }
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w){
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
    int flag = 0;  //用于判断v和w两个结点是否都存在
    int t1, t2;     //用于记录v和w两个结点的位置
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v){
            flag++; t1 = i;
        }  
        if(G.vertices[i].data.key == w){
            flag++; t2 = i;    
        } 
    }
    if(flag != 2)   return ERROR;	//说明v和w这两个点至少有一个不存在 
    ArcNode *tem = G.vertices[t1].firstarc;
    while(tem != NULL){     //判断这两个顶点之间是否本来就有边
        if(tem->adjvex == t2)  {
            return ERROR;
        }
        tem = tem->nextarc;
    }
    ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));
    p1->adjvex = t1;
    p1->nextarc = G.vertices[t2].firstarc;
    G.vertices[t2].firstarc = p1;

    ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
    p2->adjvex = t2;
    p2->nextarc = G.vertices[t1].firstarc;
    G.vertices[t1].firstarc = p2;
    G.arcnum++;
    return OK;
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType)){
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
    if(G.vexnum == 0)   return ERROR;
    ArcNode *p;
    visit(G.vertices[pos_dfs].data);
    flag_dfs[pos_dfs] = 1;
    for(p = G.vertices[pos_dfs].firstarc; p != NULL; p = p->nextarc){
        if(flag_dfs[p->adjvex] != 1){  //如果当前位置还没有被访问过
            pos_dfs = p->adjvex;
            DFSTraverse(G,visit);
        }
    }
    for(int i = 0; i < G.vexnum; i++){
        if(flag_dfs[i] != 1){
            pos_dfs = i;
            DFSTraverse(G,visit);
        }
    }
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w){
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
    int flag = 0;  //用于判断v和w两个结点是否都存在
    int t1, t2;     //用于记录v和w两个结点的位置
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v){
            flag++; t1 = i;
        }  
        if(G.vertices[i].data.key == w){
            flag++; t2 = i;    
        } 
    }
    if(flag != 2)   return ERROR;   //说明v和w这两个结点并不是都存在
    ArcNode *tem = G.vertices[t1].firstarc;
    while(tem != NULL){     		//判断这两个顶点之间是否本来有边
        if(tem->adjvex == t2){
            flag = 0;
            break;
        }
        tem = tem->nextarc;
    }
    if(flag != 0)   return ERROR;   //说明两个顶点之间本来没有边
    ArcNode *p1 = G.vertices[t1].firstarc;
    if(p1->adjvex == t2){   		//如果firstarc直接指向要删除的表结点
        G.vertices[t1].firstarc = p1->nextarc;
        free(p1);  
    }
    else{
        while(p1 != NULL){
            if(p1->nextarc->adjvex == t2){
                ArcNode *tem2 = p1->nextarc;
                p1->nextarc = p1->nextarc->nextarc;
                free(tem2);    
                break;
            }
            p1 = p1->nextarc;
        }
    }
    ArcNode *p2 = G.vertices[t2].firstarc;
    if(p2->adjvex == t1){   		//如果firstarc直接指向要删除的表结点
        G.vertices[t2].firstarc = p2->nextarc;
        free(p2);  
    }
    else{
        while(p2 != NULL){
            if(p2->nextarc->adjvex == t1){
                ArcNode *tem2 = p2->nextarc;
                p2->nextarc = p2->nextarc->nextarc;
                free(tem2);   
                break;
            }
            p2 = p2->nextarc;
        }
    }
    G.arcnum--;
    return OK;
}

status SaveGraph(ALGraph G, char FileName[]){
//将图的数据写入到文件FileName中
    if(!G.vexnum)   return INFEASIBLE;
    FILE *fp;
    if((fp = fopen(FileName,"w")) == NULL){
		printf("Failed!\n");
		return ERROR;
	}
    fprintf(fp,"%d %d\n",G.vexnum, G.arcnum);
    for(int i = 0; i < G.vexnum; i++){
        fprintf(fp,"%d %s ",G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL){
            fprintf(fp,"%d ",p->adjvex);
            p = p->nextarc;
        } 
        fprintf(fp,"%d\n",-1);  //每一行以-1作为结尾
    }
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[]){
//读入文件FileName的图数据，创建图的邻接表
    if(G.vexnum)    return INFEASIBLE;
    FILE *fp;
    int tem;
    char name[20];
    memset(name, 0, sizeof(name));
    if((fp = fopen(FileName,"r")) == NULL){
		printf("Failed!\n");
		return ERROR;
	}
    fscanf(fp,"%d %d\n",&G.vexnum, &G.arcnum);
    for(int i = 0; i < G.vexnum; i++){
    	ArcNode *tail = NULL;
    	fscanf(fp, "%d %s",&G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;  //初始化
        fscanf(fp,"%d ",&tem);
        while(tem != -1){	//这里需要用尾插法 
            ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = tem;
            if(tail == NULL){	//链表插入第一个结点 
            	p->nextarc = NULL;
            	G.vertices[i].firstarc = p;
            	tail = p;
			}
			else{               //插入的如果不是第一个结点
				p->nextarc = NULL;
				tail->nextarc = p;
				tail = p;
			}
            fscanf(fp,"%d ",&tem);
        }
    }
    fclose(fp);
    return OK;
}

status ShortestPathLength(ALGraph &G, KeyType v, KeyType w){
//求得图中顶点v到顶点w的最短路径 
    int flag[20] = {0};
    int path = 0;		//用于记录最短路径 
    int cnt[20] = {0}, i_distance;	//用于记录距离目标顶点距离为i的点有cnt[i]个 
    cnt[0] = 1, i_distance = 1;
    int cnt_q = 0, j_print = 0;	//用于记录队列中已经遍历了多少个顶点（只有当cnt_q 等于 cnt[j_print] 时 path 才能加一），j_print用来表示要查找距离为 j_print 的点了 
    int queue[20] = {0}, rear = 0, front = 0;
    for(int i = 0; i < G.vexnum; i++){
    	if(G.vertices[i].data.key == v){	//开始广度优先搜索 
    		queue[rear++] = i;		//先将此顶点入队
    		flag[i] = 1;
			while(rear != front){
				ArcNode *p = G.vertices[queue[front]].firstarc;
            	front++;
            	cnt_q++;
				while(p != NULL){
					if(G.vertices[p->adjvex].data.key == w){	//找到了另一目标顶点，返回路径长度 
						return path+1;
					}
					if(flag[p->adjvex] != 1){
						queue[rear++] = p->adjvex;
                    	flag[p->adjvex] = 1;    //进队列时标记为访问过
                    	cnt[i_distance]++; 		
					}
					p = p->nextarc;	
				}
				if(cnt_q == cnt[j_print]){
					path++;
					i_distance++;
					cnt_q = 0;
					j_print++;
				}
				
			}
			return -1;	//到这里说明两个顶点之间没有通路 
		}//end of if（找到v顶点之后的操作） 
    }//end of for （遍历找v顶点的操作）
	return -1; //有顶点不存在 
}

status ConnectedComponentsNums(ALGraph &G, int judge){
//求图连通分量的个数（judge用于判断是不是第一层递归） 
	if(G.vexnum == 0)   return ERROR;
    ArcNode *p;
    flag_dfs[pos_dfs] = 1;
    for(p = G.vertices[pos_dfs].firstarc; p != NULL; p = p->nextarc){
        if(flag_dfs[p->adjvex] != 1){  //如果当前位置还没有被访问过
            pos_dfs = p->adjvex;
            ConnectedComponentsNums(G, judge+1);
        }
    }
    if(judge == 1){
    	for(int i = 0; i < G.vexnum; i++){
	        if(flag_dfs[i] != 1){
	        	ans_connect++;
	            pos_dfs = i;
	            ConnectedComponentsNums(G, judge+1);
	        }
	    }
	} 
    return ans_connect;
}

status VerticesSetLessThanK(ALGraph &G, KeyType v, KeyType k){
//输出与顶点v的距离小于k的点的集合	
	int flag[20] = {0};
    int path = 0;		//用于记录最短路径 
    int cnt[20] = {0}, i_distance;	//用于记录距离目标顶点距离为i的点有cnt[i]个 
    cnt[0] = 1, i_distance = 1;
    int cnt_q = 0, j_print = 0;	//用于记录队列中已经遍历了多少个顶点（只有当cnt_q 等于 cnt[j_print] 时 path 才能加一），j_print用来表示要查找距离为cnt[j_print]的点了 
    int queue[20] = {0}, rear = 0, front = 0;
    for(int i = 0; i < G.vexnum; i++){
    	if(G.vertices[i].data.key == v){	//开始广度优先搜索 
    		queue[rear++] = i;		//先将此顶点入队
    		flag[i] = 1;
			while(rear != front){
				ArcNode *p = G.vertices[queue[front]].firstarc;
				if(j_print < k){
					if(G.vertices[queue[front]].data.key != v) 
						printf("%d %s ",G.vertices[queue[front]].data.key, G.vertices[queue[front]].data.others);
				}
				else{
					printf("\n");	return OK; 
				} 
            	front++;
            	cnt_q++;
				while(p != NULL){
					if(flag[p->adjvex] != 1){
						queue[rear++] = p->adjvex;
                    	flag[p->adjvex] = 1;    //进队列时标记为访问过
                    	cnt[i_distance]++; 			 
					}
					p = p->nextarc;	
				}
				if(cnt_q == cnt[j_print]){
					path++;
					i_distance++;
					cnt_q = 0;
					j_print++;
				}
			}
		}//end of if（找到v顶点之后的操作） 
    }//end of for （遍历找v顶点的操作）
    if(front == rear){
		printf("\n"); 	return OK;
	}		//防止当k很大时，输出全部顶点后跳出while循环还return -1的情况 
    printf("查找失败！目标顶点不存在！\n");
	return -1; //有顶点不存在 
}
