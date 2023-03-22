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
/*-------page 22 on textbook -------*/
typedef int status;
typedef int KeyType; 
typedef struct {
	KeyType  key;
	char others[20];
} TElemType;			//二叉树结点类型定义

typedef struct BiTNode{ //二叉链表结点的定义
	TElemType  data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct{ 		//二叉树的集合类型定义  
	struct { 
		char name[30];  
		BiTree T;      
	}elem[10];  
    int length;			//用来记录已经有的二叉树数量  
} BITREES;  
BITREES BiTrees;      	//二叉树集合的定义BiTrees 

int def_cnt;			//专门用于记录函数中definition数组遍历到了哪一位 
/*-----page 19 on textbook ---------*/
status CreateBiTree(BiTree &T,TElemType definition[]);		//新建 
status DestroyBiTree(BITREES &BiTrees,char TreeName[]);		//销毁 
status ClearBiTree(BiTree &T);								//清空 
status BiTreeEmpty(BiTree T);								//判空 
status BiTreeDepth(BiTree T);								//求深度 
BiTNode* LocateNode(BiTree T,KeyType e); 					//查找结点
status Assign(BiTree &T,KeyType e,TElemType value);			//结点赋值 
BiTNode* GetSibling(BiTree T,KeyType e);					//获得兄弟节点 
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);	//插入结点
status DeleteNode(BiTree &T,KeyType e);						//删除结点 	 
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));	//前序遍历 
status InOrderTraverse(BiTree T,void (*visit)(BiTree));		//中序遍历 
status PostOrderTraverse(BiTree T,void (*visit)(BiTree)); 	//后序遍历 
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));	//按层遍历 
status MaxPathSum(BiTree T);								//求根到叶子的最大路径和 
BiTree LowestCommonAncestor(BiTree T, int e1, int e2);		//求最近公共祖先 
status InvertTree(BiTree &T);								//链表反转 
status SaveBiTree(BiTree T, char FileName[]);				//存储文件 
status LoadBiTree(BiTree &T,  char FileName[]);				//读取文件 
int check(TElemType definition[], int count); 		//创建二叉树时，用于判断definition数组中是否有重复关键字
int check2(BiTree &T, KeyType e, TElemType value);	//结点赋值时，用于判断输入的关键字是否和目标结点以外结点的关键字重复 
int check3(BiTree &T, TElemType value);				//插入结点是，用于判断输入的关键字是否和树中任一关键字重复 
BiTree reset(BiTree &L, BiTree &R);					//删除结点时，当待删除结点的度为2时，将此节点的右子树（R）作为左子树中（L）最右结点的右子树 
void visit(BiTree T);
/*--------------------------------------------*/
int main(void){
TElemType definition[100];		//创建二叉表时需要的数组，记录二叉树结点的关键字，名字 
int op=1;
BiTrees.length = 0;
char name_target[30];			//此数组用于记录每个操作的对象（二叉树名） 
int name_tarpos = 0, flag = 0;	//flag用于判断操作对象存不存在于二叉树表里 	
while(op){
	fflush(stdin);	//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
	system("cls");	printf("\n\n");				//清楚屏幕命令 
	memset(definition, 0, sizeof(definition));	//重置definition数组 
	def_cnt = 0;	//重置def_cnt 
	printf("用户您好！欢迎使用此程序！\n");
	printf("本程序创建者为	计算机2107班	陈侠锟\n\n"); 
	printf("\nPS：此程序可最多同时存在10个二叉树，你现在已有%d个二叉树\n",BiTrees.length);
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. 创建新的二叉树		2. 销毁二叉树\n");
	printf("    	  3. 清空二叉树			4. 二叉树判空\n");
	printf("    	  5. 求二叉树深度		6. 查找结点	\n");
	printf("    	  7. 结点赋值			8. 获取兄弟结点	\n");
	printf("    	  9. 插入结点			10. 删除结点\n");
	printf("    	  11. 前序遍历			12. 中序遍历\n");
	printf("    	  13. 后序遍历			14. 按层遍历\n");
	printf("    	  15. 求最大路径和		16. 最近公共祖先\n"); 
	printf("    	  17. 翻转二叉树		18. 二叉树文件读写\n"); 
	printf("    	  0. 退出\n\n");
	printf("注意：此线性表中的数据应全为整型！\n");
	printf("-------------------------------------------------\n");
	if(op < 0 || op > 18)	printf("    输入错误！请重新选择你的操作[0~18]:");
	else	printf("    请选择你的操作[0~18]:");
	if(!scanf("%d",&op))	op = 100;
	if (op != 1 && BiTrees.length && op != 0){		//1是新增二叉树，0是退出系统 
		printf("以下是你当前拥有的二叉树（按序号排列）：\n");
		for(int i = 0; i < BiTrees.length; i++){
			printf("%s ",BiTrees.elem[i].name);
		}
		if(op != 2){	//2是销毁二叉树，除1之外的操作均先输出已有二叉树名称以便查询，除1，2之外的操作均需输入要操作的二叉树名 
			fflush(stdin);		//防止输入操作指令后键入的回车让下面输入名称的操作直接读入 
			memset(name_target, 0, sizeof(name_target));	//重置存储操作对象名的数组 
			name_tarpos = 0;	flag = 0; 		//flag用来记录输入的二叉树名称是否存在于二叉树组里 
			printf("\n请输入你想要进行此操作的二叉树名称：");
			for(char c; ((c = getchar()) != ' ' && c != '\n') && name_tarpos < 29; name_tarpos++){  //为了保证线性表的名字在30个字符之内，多余的字符将舍弃 
				name_target[name_tarpos] = c;
			}
		}
	} 
	switch(op){
		case 1:{//新建二叉树 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			int num, data, lengthi;
			char name_str[30];
			if(BiTrees.length == 10){
				printf("二叉树表已满！无法创建新的二叉树！\n");
				printf("请按回车键继续……\n");getchar();
				break; 
			}
			printf("请输入你想要新建的二叉树的数量（注意：你当前还可以新建%d个二叉树）：", 10 - BiTrees.length);
renew1_1:
			while(!scanf("%d",&num)){
				printf("输入错误！请重新输入一个数字：");
				fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
			} 
			if(num > 10-BiTrees.length || num < 0){
				printf("输入数量不合理，请重新输入新建数量：");
				goto renew1_1;
			} 
			for(int i = 0; i < num; i++){
				fflush(stdin);		//为了防止在输入上一个表中的数据时多余的数据对下一个表的输入造成干扰 
				memset(name_str,0,sizeof(name_str));	//重置暂时存储二叉树名字的变量 
				printf("请输入第%d个二叉树的名字(注意：名字最多30个字符，且不可包含空格，多余的数据将会被忽略)：",i+1);
				int name_strpos = 0;
				for(char c; ((c = getchar()) != ' ' && c != '\n') && name_strpos < 29; name_strpos++){  //为了保证二叉树的名字在30个字符之内，多余的字符将舍弃 
					name_str[name_strpos] = c;
				} 
				name_str[name_strpos] = '\0';	//作为字符串的结尾标志 
renew1_2:
				fflush(stdin);	//清空输入流，避免输入二叉树名字时多余的字符对接下来的数据产生干扰 
				memset(definition, 0, sizeof(definition));	//若执行了goto renew1_2这一语句，需要重置definition数组 
				def_cnt = 0;
				printf("请依次输入二叉树各结点的关键字（只能为数字）和内容（字符串，20字符以内）,并以-1 null结束：");
				do {
					if(scanf("%d",&definition[def_cnt].key) != 1){
						printf("输入格式有误，请重新输入！\n"); 
						goto renew1_2;
					}
					scanf("%s", definition[def_cnt].others);
				} while (definition[def_cnt++].key != -1);
				def_cnt = 0;
				if(CreateBiTree(BiTrees.elem[BiTrees.length].T, definition) == OK){
					printf("第%d个二叉树创建成功！\n",i+1);
				} 
				else{
					printf("第%d个二叉树创建失败！请检查关键字是否重复！\n",i+1); 
					continue; 
				}
				strcpy(BiTrees.elem[BiTrees.length].name, name_str); 
				BiTrees.length++;		//创建完成一个二叉树，二叉树表长度加一 
			}//end of for（创建树所用的循环） 
			fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据  
			printf("\n操作已完成，以下是你已拥有的二叉树：\n\n");
			for(int k = 0; k < BiTrees.length; k++){
				printf("二叉树%d：%s \n",k+1, BiTrees.elem[k].name);
    			printf("-----------all elements -----------------------\n");
    			printf("先序遍历：");
    			PreOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
				printf("中序遍历："); 
				InOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
				printf("------------------ end ------------------------\n\n");
			} 
			printf("请按回车键继续……\n");getchar();
			break;}
		 
		case 2:{//销毁二叉树 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				int num = 0;	char name_del[30];
renew2:
				printf("\n请输入你想要删除的二叉树的数量：\n");
				while(!scanf("%d",&num)){
					printf("输入错误！请输入数字：");
					fflush(stdin);		 
				}
				if(num < 0 || num > BiTrees.length){
					printf("输入错误！你当前最多可以删除%d个二叉树！\n", BiTrees.length);
					goto renew2;
				}
				getchar();		//读取回车 
				for(int i = 0; i < num; i++){
					printf("请输入第%d个你想要删除的二叉树的名字（每次请输入一个名字，多余的数据将会被忽略）：",i+1);
					memset(name_del, 0, sizeof(name_del)); 
					int name_delpos = 0;
					for(char c; ((c = getchar()) != ' ' && c != '\n') && name_delpos < 29; name_delpos++){  //为了保证二叉树的名字在30个字符之内，多余的字符将舍弃 
						name_del[name_delpos] = c;
					} 
					name_del[name_delpos] = '\0';	//作为字符串的结尾标志 
					if(DestroyBiTree(BiTrees, name_del) == OK){
						printf("已成功销毁此二叉树！\n");
						continue; 
					}
					else	printf("此二叉树不存在！\n");
				}
				printf("销毁二叉树操作已完成！你当前还有以下二叉树：\n");	//注：销毁二叉树后 BiTrees.length-- 这一句在函数中执行 
				for(int k = 0; k < BiTrees.length; k++){
					printf("二叉树%d：%s \n",k+1, BiTrees.elem[k].name);
    				printf("-----------all elements -----------------------\n");
    				printf("先序遍历：");
    				PreOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
					printf("中序遍历："); 
					InOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
					printf("------------------ end ------------------------\n\n");
				} 
			}//end of else  
			printf("请按回车键继续");getchar();
			break;}
		 
		case 3:{//清空二叉树 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						ClearBiTree(BiTrees.elem[i].T);
						printf("已成功清空此二叉树！\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("清空失败，此二叉树不存在！\n");
			}   
			printf("请按回车键继续");getchar();
			break;}
		 
		case 4:{//二叉树判空 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
			if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						if(BiTreeEmpty(BiTrees.elem[i].T) == TRUE)	printf("此二叉树为空！\n");
						else	printf("此二叉树不为空！\n"); 
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此二叉树不存在！\n"); 
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 5:{//求深度		
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
		 	if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("此二叉树的深度为：%d\n",BiTreeDepth(BiTrees.elem[i].T));
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此二叉树不存在！\n"); 
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 6:{//查找结点 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target6 = 0;
						printf("请输入你想查找的结点的关键字，将返回此结点中的内容：\n"); 
						while(scanf("%d",&target6) != 1){
							printf("输入不合法！请重新输入：");
							fflush(stdin);	//不加这一句会直接导致死循环 
						}
						fflush(stdin);		//防止最后的getchar直接读到前面键入的回车 
						BiTree tem = LocateNode(BiTrees.elem[i].T, target6);
						if(!tem)	printf("查找失败！此结点不存在！\n"); 
						else	printf("关键字为%d的结点存储的内容是：%s\n",tem->data.key, tem->data.others); 
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此二叉树不存在！\n"); 
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 7:{//结点赋值 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						TElemType newdot7;
						int target7 = 0;
renew7:
						fflush(stdin); 		//执行goto renew7后需要清空输入流 
						printf("请依次输入你想赋值的结点的关键字，新的关键字，结点内容：\n"); 
						if(scanf("%d %d",&target7, &newdot7.key) != 2){
							printf("输入不合法，请重新输入！\n");
							goto renew7;
						}
						scanf("%s",newdot7.others);	
						fflush(stdin);		//防止最后的getchar直接读到前面键入的回车 
						if(Assign(BiTrees.elem[i].T, target7, newdot7) == ERROR)	printf("赋值失败！请检查目标结点是否存在 以及 新的关键字是否和已有结点重复！\n"); 
						else{
							printf("赋值成功！当前二叉树数据如下：\n"); 
							printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
		    				printf("-----------all elements -----------------------\n");
		    				printf("先序遍历：");
		    				PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
							printf("中序遍历："); 
							InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
							printf("------------------ end ------------------------\n\n");
						}	
						flag = 1;
						break; 		//跳出for循环 
					}	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else
			printf("请按回车键继续");getchar();
			break;}
		 
		case 8:{//获得兄弟结点 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target8 = 0;
						printf("请输入一个结点的关键字，将返回此结点的兄弟结点中的内容：\n"); 
						while(scanf("%d",&target8) != 1){
							printf("输入不合法！请重新输入：");
							fflush(stdin);	//不加这一句会直接导致死循环 
						}
						fflush(stdin);		//防止最后的getchar直接读到前面键入的回车 
						BiTree tem = GetSibling(BiTrees.elem[i].T, target8); 
						if(!tem)	printf("查找失败！此结点不存在或不存在兄弟结点！\n"); 
						else	printf("关键字为%d的结点的兄弟结点关键字是：%d；存储的内容是：%s\n",target8, tem->data.key, tem->data.others); 
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("此二叉树不存在！\n"); 
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 9:{//插入结点 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target9 = 0, mode = 0, flag0;
						TElemType newdot9; 
						printf("你想插入新的根结点吗？（1为是，其他数字为否）\n"); 
						scanf("%d",&flag0);
						fflush(stdin);
						if(flag0 != 1){
							printf("请依次输入一个结点的关键字和插入位置（0代表插入成为目标结点的左孩子，1代表插入成为目标结点的右孩子）：\n"); 
							while(scanf("%d %d",&target9, &mode) != 2){
								printf("输入不合法！请重新输入：");
								fflush(stdin);	//不加这一句会直接导致死循环 
							}
						}
						fflush(stdin);
						printf("请依次输入待插入结点的关键字和内容：\n");
						while(scanf("%d",&newdot9.key) != 1){
							printf("输入不合法！请重新输入：");
							fflush(stdin);		//不加这一句会直接导致死循环
						}
						scanf("%s",newdot9.others);
						fflush(stdin);			//防止最后的getchar直接读到前面键入的回车 
						if(flag0 == 1){			//若插入结点为根节点 
							if(check3(BiTrees.elem[i].T, newdot9) != OK){	//检查要插入结点的关键字是否与已有结点关键字重复 
								InsertNode(BiTrees.elem[i].T, 0, -1, newdot9); 
								goto next9;
							}
							else	printf("插入失败！待插入结点关键字与已有关键字重复！\n");	
						}
						else{					//若插入结点不是根节点 
							if(InsertNode(BiTrees.elem[i].T, target9, mode, newdot9) == ERROR)	
							printf("插入失败！目标结点不存在或待插入结点关键字重复！\n"); 
							else{
next9:
								printf("插入成功！当前二叉树数据如下：\n"); 
								printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
			    				printf("-----------all elements -----------------------\n");
			    				printf("先序遍历：");
			    				PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("中序遍历："); 
								InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("------------------ end ------------------------\n\n");
							}
						}
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 10:{//删除结点 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target10 = 0; 
						printf("请输入你要删除结点的关键字：\n"); 
						while(scanf("%d",&target10) != 1){
							printf("输入不合法！请重新输入：");
							fflush(stdin);		//不加这一句会直接导致死循环 
						}
						fflush(stdin);			//防止最后的getchar直接读到前面键入的回车 
						if(target10 == BiTrees.elem[i].T->data.key){		//如果待删除结点是根节点，直接在主函数里完成删除操作  
				            if(!BiTrees.elem[i].T->lchild && !BiTrees.elem[i].T->rchild){    	//根的度为0
				                free(BiTrees.elem[i].T);
				                BiTrees.elem[i].T = NULL;
				            }
				            else if(BiTrees.elem[i].T->lchild && BiTrees.elem[i].T->rchild){     //根的度为2
				                BiTree tem = BiTrees.elem[i].T;
				                BiTrees.elem[i].T = reset(BiTrees.elem[i].T->lchild, BiTrees.elem[i].T->rchild);
				                free(tem);
				            }
				            else{       		//根的度为1
				            	BiTree tem = BiTrees.elem[i].T;
				                if(BiTrees.elem[i].T->lchild)	BiTrees.elem[i].T = BiTrees.elem[i].T->lchild;
				                else	BiTrees.elem[i].T = BiTrees.elem[i].T->rchild;
				                free(tem);
				            }
				            goto next10;
						} 
						else{
							if(DeleteNode(BiTrees.elem[i].T, target10) == ERROR)	
								printf("删除失败！目标结点不存在！\n"); 
							else{
next10:
								printf("删除成功！当前二叉树数据如下：\n"); 
								printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
			    				printf("-----------all elements -----------------------\n");
			    				printf("先序遍历：");
			    				PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("中序遍历："); 
								InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("------------------ end ------------------------\n\n");
							}
						} 
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 11:{//先序遍历 
	   		fflush(stdin);		//清除输入指令时可能存在的多余的数字 	
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("此二叉树数据如下：\n"); 
						printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("先序遍历：");
		    			PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 12:{//中序遍历 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("此二叉树数据如下：\n"); 
						printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("中序遍历：");
		    			InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
		 
		case 13:{//后序遍历 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("此二叉树数据如下：\n"); 
						printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("后序遍历：");
		    			PostOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
	   
		case 14:{
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("此二叉树数据如下：\n"); 
						printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("按层遍历：");
		    			LevelOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
	   		break;}
		
		case 15:{//求根节点到叶子结点的最大路径和 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 	
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("此功能将返回根结点到叶子结点的最大路径和，按回车以继续\n"); 
						getchar();
						printf("此树的最大路径和为：%d\n",MaxPathSum(BiTrees.elem[i].T));
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
		
		case 16:{//求结点的最近公共祖先 
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int e1, e2;
						printf("请输入两个结点的关键字，将查找这两个结点的最近公共祖先： \n");
						while(scanf("%d %d",&e1,&e2) != 2){
							printf("输入不合法！请重新输入两个关键字：");
							fflush(stdin);		//不加这一句会直接导致while死循环 
						}
						fflush(stdin);
						BiTree ancestor = LowestCommonAncestor(BiTrees.elem[i].T, e1, e2);
						if(ancestor)	printf("这两个结点的最近公共祖先是：关键字：%d 内容：%s\n",ancestor->data.key, ancestor->data.others); 
						else	 printf("查找失败！请确认这两个结点是否均存在！\n"); 
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}
		
		case 17:{
			fflush(stdin);		//清除输入指令时可能存在的多余的数字 
	   		if(!BiTrees.length)	printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						InvertTree(BiTrees.elem[i].T); 
						printf("反转后此二叉树数据如下：\n"); 
						printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
			    		printf("-----------all elements -----------------------\n");
			    		printf("先序遍历：");
			    		PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("中序遍历："); 
						InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
			printf("请按回车键继续");getchar();
			break;}

		case 18:{
			fflush(stdin); 
			char FileName[30];
			strcpy(FileName, "test.txt");
			printf("此功能将会把二叉树中已有的数据写入外部的test.txt文件中，若无此文件，将创造此文件\n");
			printf("请按回车键以开始");
			getchar();
			if(!BiTrees.length)		printf("你还没有二叉树！请先创建一个二叉树！\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						if(SaveBiTree(BiTrees.elem[i].T, FileName) == ERROR) ;
						else{
							printf("已成功将二叉树中的数据导入外部文件，请查看外部文件\n");
							printf("按回车键以继续\n");
							getchar();
							ClearBiTree(BiTrees.elem[i].T);
							printf("已销毁二叉树...\n");
							printf("正在从外部文件导入数据到二叉树...\n");
							if(LoadBiTree(BiTrees.elem[i].T, FileName) == ERROR)		printf("外部文件丢失！终止操作！");
							else{
								printf("已导入完成，按回车键以输出二叉树中数据\n");
								getchar();
								printf("此二叉树数据如下：\n"); 
								printf("二叉树%d：%s \n",i+1, BiTrees.elem[i].name);
				    			printf("-----------all elements -----------------------\n");
				    			printf("先序遍历：");
				    			PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("中序遍历："); 
								InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("------------------ end ------------------------\n\n");
							}
						}
						flag = 1;
						break;	//跳出for循环 
					}//end of if	
				}//end of for循环 
				if(!flag)	printf("此二叉树不存在！\n"); 
			}//end of else 
	   		printf("请按回车键继续\n");getchar();
			break;}
			
		case 0:break;
	}//end of switch
}//end of while
printf("欢迎下次再使用本系统！\n");
for(int end = 0; end < BiTrees.length; end++){		//程序结束，释放所有二叉树的空间 
	ClearBiTree(BiTrees.elem[end].T);
}
return 0;
}//end of main()

int check(TElemType definition[], int count){
//专门用于检查definition数组中的关键字是否有重复（为了保证二叉树的关键字唯一性） 
    if(definition[count].key == -1) return 1;
    int flag=1;
    for(int j = count + 1; definition[j].key != -1; j++)
    {
        if((definition[j].key == definition[count].key) && definition[count].key!=0)
        {return 0;}
    }
    flag = check(definition,count + 1);
    return flag;
}

int check2(BiTree &T, KeyType e, TElemType value){  
//用于检查value中关键字是否与被赋值结点以外的结点的关键字相同（使结点关键字保持唯一性），return OK则说明有重复 
//用于结点赋值功能中 
    if(!T)  return ERROR;
    if((T->data.key == value.key) && (T->data.key != e)){
        return OK;
    }
    if(check2(T->lchild, e, value)) return OK;
    else    return check2(T->rchild, e, value);
}

int check3(BiTree &T, TElemType value){
//用于判断T中任一结点的关键字是否与value中的关键字相同，return OK则说明有重复 
//用于插入结点功能中 
	if(!T)  return ERROR;
    if(T->data.key == value.key){
        return OK;
    }
    if(check3(T->lchild, value)) return OK;
    else    return check3(T->rchild, value);
}

BiTree reset(BiTree &L, BiTree &R){     
//用于DeleteNode函数中，当被删除结点的度为2时，将此节点的右子树（R）作为左子树中（L）最右结点的右子树
    BiTree originL = L;
    while(L->rchild != NULL)    L = L->rchild;
    L->rchild = R;
    return originL;
}

status CreateBiTree(BiTree &T,TElemType definition[]){
//根据带空枝的二叉树先序遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，如果有相同的关键字，返回ERROR。
    if(check(definition, 0) == 0)   return ERROR;
    if(definition[def_cnt].key == 0){
        T = NULL;
        def_cnt++;
    }
    else{
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data.key = definition[def_cnt].key;		//赋值 
        strcpy(T->data.others, definition[def_cnt].others);		//赋值 
        def_cnt++;
        CreateBiTree(T->lchild, definition);		//递归，进入左子树 
        CreateBiTree(T->rchild, definition);		//递归，进入右子树 
    }
    return OK;
}

status DestroyBiTree(BITREES &BiTrees,char TreeName[]){
// BiTrees中删除一个名称为TreeName的二叉树 
	if(BiTrees.length == 0)	return ERROR;
	int j;
    for(int i = 0; i < BiTrees.length; i++){
        if(strcmp(BiTrees.elem[i].name , TreeName) == 0 && i != BiTrees.length - 1){
            ClearBiTree(BiTrees.elem[i].T);
            BiTrees.length--; //销毁二叉树后，二叉树组的总数量减一
            BiTrees.elem[i].T = (struct BiTNode* )malloc(sizeof(BiTree));   //重新为删除的二叉树分配空间，用于后续二叉树的移动操作

            for( j = i ; j < BiTrees.length ; j++){    //二叉树的移动
            	strcpy(BiTrees.elem[j].name , BiTrees.elem[j+1].name);  //二叉树名字的移动
				BiTrees.elem[j].T = BiTrees.elem[j+1].T;	//二叉树数据的移动 
            }
            j++;
            BiTrees.elem[j].T = NULL;   //置空移动完之后处于末端的T指针 
            memset(BiTrees.elem[j].name , 0 , sizeof(BiTrees.elem[j].name));
            return OK;
        }
        else if(strcmp(BiTrees.elem[i].name , TreeName) == 0 && i == BiTrees.length - 1){	//如果删除的二叉树本来就在队尾 
        	ClearBiTree(BiTrees.elem[i].T);
        	BiTrees.length--; 
        	memset(BiTrees.elem[i].name , 0 , sizeof(BiTrees.elem[i].name));
        	return OK;
		}
    }
    return ERROR;
}

status ClearBiTree(BiTree &T){
//将二叉树设置成空，并删除所有结点，释放结点空间
    if(!T)  return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status BiTreeEmpty(BiTree T){
//判断二叉树是否为空树，若为空树返回TRUE，否则返回FALSE	
	if(T != NULL)	return FALSE;
	else	return TRUE;
}

status BiTreeDepth(BiTree T){
//求二叉树T的深度
    if(!T)  return 0;  
    int left = 0, right = 0;
    // if(!T->lchild && !T->rchild){   //先找到树叶，从树叶开始往上返回深度
    //     return 1;
    // }
    left = BiTreeDepth(T->lchild) + 1;
    right = BiTreeDepth(T->rchild) + 1;
    return left > right ? left : right;
}

BiTNode* LocateNode(BiTree T,KeyType e){
//查找结点，返回此结点指针 
    if(!T)  return NULL;
    BiTree tem;
    if(T->data.key == e)    return T;
    tem = LocateNode(T->lchild, e);     //只要当前节点不是目标，遍历左子树
    if(tem != NULL) return tem;
    tem = LocateNode(T->rchild, e);     //遍历右子树
    if(tem != NULL) return tem;
    return NULL;
/*递归返回到根时，如果在之前的递归中找到了符合的节点，此时tem不为NULL，则可以返回此节点，若在之前的递归中没有找到符合的节点，
则tem就为NULL，则从根节点开始遍历右子树（若右子树未遍历）或返回NULL（若左右子树已经全部遍历完毕）。*/
}

status Assign(BiTree &T,KeyType e,TElemType value){
//实现结点赋值，赋值成功返回OK，赋值失败返回ERROR 
    if(check2(T, e, value))    return ERROR;
    if(!T)  return ERROR;
    if(T->data.key == e){
        T->data.key = value.key;
        strcpy(T->data.others, value.others);
        return OK;
    }
    else{
        if(Assign(T->lchild, e, value)) return OK;
        else return Assign(T->rchild, e, value);
    }
    return ERROR;
}

BiTNode* GetSibling(BiTree T,KeyType e){
//实现获得兄弟结点
    if(!T || (!T->lchild && !T->rchild))  return NULL;
    else{
        if(T->lchild != NULL){
            if(T->lchild->data.key == e)	return T->rchild;
        }    
        if(T->rchild != NULL){
            if(T->rchild->data.key == e)	return T->lchild;
        }
    } 
    if(GetSibling(T->lchild, e))    return GetSibling(T->lchild, e);
    else if(GetSibling(T->rchild, e))   return GetSibling(T->rchild, e); 
    return NULL;
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c){
//插入结点
    if(check3(T, c)) return ERROR;
    if(!T)  return ERROR;
    if(LR == -1){		//插入结点为头结点 
        BiTree newtree = (BiTree)malloc(sizeof(BiTNode));
        newtree->data.key = c.key;
        strcpy(newtree->data.others, c.others);
        newtree->rchild = T;
        newtree->lchild = NULL;
        T = newtree;
        return OK;
    }
    if(T->data.key == e){
        if(LR == 0){  		//作为当前T结点的左孩子结点
            BiTree indot = (BiTree)malloc(sizeof(BiTNode));
            indot->data.key = c.key;
            strcpy(indot->data.others, c.others);
            indot->rchild = T->lchild;
            indot->lchild = NULL;
            T->lchild = indot;
        }
        else if(LR == 1){  //作为当前T结点的右孩子结点
            BiTree indot = (BiTree)malloc(sizeof(BiTNode));
            indot->data.key = c.key;
            strcpy(indot->data.others, c.others);
            indot->rchild = T->rchild;
            indot->lchild = NULL;
            T->rchild = indot;
        }
        return OK;
    }
    if(InsertNode(T->lchild, e, LR, c)) return OK;
    else if(InsertNode(T->rchild, e, LR, c))    return OK;
    return ERROR;
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。（因为此函数以T->lchild或T->rchild来表示待删除结点，故对根节点的特判放在了主函数中） 
{
    if(!T)  return ERROR;
    if(T->lchild != NULL){      
        if(T->lchild->data.key == e){  //T->lchild为待删除结点
            if(!T->lchild->lchild && !T->lchild->rchild){    //删除结点的度为0
                free(T->lchild);
                T->lchild = NULL;
            }
            else if(T->lchild->lchild && T->lchild->rchild){     //删除结点的度为2
                BiTree tem = T->lchild;
                T->lchild = reset(T->lchild->lchild, T->lchild->rchild);
                free(tem);
            }
            else{       //删除节点的度为1
            	BiTree tem = T->lchild;
                if(T->lchild->lchild){	//如果待删除结点的左孩子不为空 
                    T->lchild = T->lchild->lchild;
                }
                else{	//如果待删除结点的右孩子不为空 
                    T->lchild = T->lchild->rchild;
                }
                free(tem);
            }
            return OK;    
        }
    }
    if(T->rchild != NULL){		 
        if(T->rchild->data.key == e){   //T->rchild为待删除结点
            if(!T->rchild->lchild && !T->rchild->rchild){		//删除结点的度为0
                free(T->rchild);
                T->rchild = NULL;
            }
            else if(T->rchild->lchild && T->rchild->rchild){     //删除结点的度为2
                BiTree tem = T->rchild;
                T->rchild = reset(T->rchild->lchild, T->rchild->rchild);
                free(tem);
            }
            else{       //删除节点的度为1
            	BiTree tem = T->rchild;
                if(T->rchild->lchild){	//如果待删除结点的左孩子不为空                    
                    T->rchild = T->rchild->lchild;   
                }
                else{	//如果待删除结点的右孩子不为空 
                    T->rchild = T->rchild->rchild;
                }
                free(tem);
            }
            return OK;    
        }
    }
    if(DeleteNode(T->lchild, e))    return OK;
    else if(DeleteNode(T->rchild, e))   return OK;
    return ERROR;
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree)){
//先序遍历二叉树T(非递归实现)
    BiTree stack[100], p;       
    int top = 0;
    if(T != NULL){
        stack[top++] = T;
        while(top){
            p = stack[--top];   //p指向栈顶元素（待输出）
            visit(p);
            if(p->rchild != NULL)   stack[top++] = p->rchild;   //右子树入栈
            if(p->lchild != NULL)   stack[top++] = p->lchild;   //左子树入栈
        }
    }
    return OK;
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree)){
//中序遍历二叉树T
    if(!T)  return OK;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree)){
//后序遍历二叉树T
    if(!T)  return OK;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree)){
//按层遍历二叉树T（利用队列先进先出的特性） 
    BiTree queue[100], p;   //创建临时指针p，移动它，来访问输出节点
    int front = 0, rear = 0;
    if(T){
        queue[rear++] = T;
        while(rear != front){
            p = queue[front++];
            visit(p);
            if(p->lchild != NULL)   queue[rear++] = p->lchild;
            if(p->rchild != NULL)   queue[rear++] = p->rchild;
        }
    }
    return OK;
}

status MaxPathSum(BiTree T){
//求根到叶子结点的最大路径和
	if(!T)	return 0;
	if(!T->lchild && !T->rchild)	return T->data.key;		//如果是叶子结点，直接返回叶子的权值 
	int left = MaxPathSum(T->lchild); 
	int right = MaxPathSum(T->rchild);
	
	return left > right ? (left + T->data.key) : (right + T->data.key);
}

BiTree LowestCommonAncestor(BiTree T, int e1, int e2){
//寻找最近公共祖先
/*找一个深度最大的结点，使e1结点和e2结点同时在它的子树里面*/ 
	if(!T || (T->data.key == e1) || (T->data.key == e2))	return T;
	BiTree left = LowestCommonAncestor(T->lchild, e1, e2);
	BiTree right = LowestCommonAncestor(T->rchild, e1, e2);
	if(!left && !right)	return NULL;		//说明当前结点为树根的情况下，其左右子树均没有目标结点 
	else if(!left && right)	return right;	//说明当前结点为树根的情况下，其右子树有目标结点，左子树没有 
	else if(left && !right)	return left;	//说明当前结点为树根的情况下，其左子树有目标结点，右子树没有 
	return T;
	
}

status InvertTree(BiTree &T){
//实现二叉树各结点的左右子树互换（二叉树反转） 
	BiTree queue[100], p, tem;   //创建临时指针p，移动它，来访问输出节点
    int front = 0, rear = 0;
    if(T){
        queue[rear++] = T;
        while(rear != front){
            p = queue[front++];
            tem = p->lchild;
            p->lchild = p->rchild;
            p->rchild = tem;
            if(p->lchild != NULL)   queue[rear++] = p->lchild;
            if(p->rchild != NULL)   queue[rear++] = p->rchild;
        }
    }
    return OK;
} 

status SaveBiTree(BiTree T, char FileName[]){
//将二叉树的结点数据写入到文件FileName中
    if(!T)  return INFEASIBLE;
    FILE *fp;
    if((fp = fopen(FileName,"w")) == NULL){
		printf("Failed!\n");
		return ERROR;
	}
    BiTree stack[100], p;       
    int top = 0;
    if(T != NULL){
        stack[top++] = T;
        while(top){
            p = stack[--top];   //p指向栈顶元素（待输出）
            if(p != NULL)   fprintf(fp,"%d %s\n",p->data.key, p->data.others);
            else{
                fprintf(fp,"%d %s\n",0,"NULL");
                continue;
            }        
            if(p->rchild != NULL)   stack[top++] = p->rchild;   //右子树入栈
            else    stack[top++] = NULL;
            if(p->lchild != NULL)   stack[top++] = p->lchild;   //左子树入栈
            else    stack[top++] = NULL;
        }
        fprintf(fp,"%d %s\n",0,"NULL");
        fprintf(fp,"%d %s\n",-1,"NULL");
    }    
    fclose(fp);
    return OK;
}

status LoadBiTree(BiTree &T,  char FileName[]){
//读入文件FileName的结点数据，创建二叉树
    if(T)  return INFEASIBLE;
    FILE *fp;
    if((fp = fopen(FileName,"r")) == NULL){
		printf("Failed!\n");
		return ERROR;
	}
    TElemType definition[100];
    int i=0;
    do 
    {
	    fscanf(fp,"%d %s\n",&definition[i].key,definition[i].others);
    } while (definition[i++].key!=-1);
    CreateBiTree(T, definition);
    fclose(fp);
    return OK;
}

void visit(BiTree T){
//遍历过程中对结点的操作 
    printf(" %d,%s",T->data.key,T->data.others);
}
