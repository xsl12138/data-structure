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
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //单链表（链式结构）结点的定义	//头节点数据域（L->data）用来存储链表长度 	
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef struct{  //单链表的集合类型定义  
     struct { char name[30];  
               LinkList L;      
      } elem[10];  
      int length;  
//      LinkList head, tail;	
 }LISTS;  
 LISTS Lists;      //线性表集合的定义Lists 
/*-----page 19 on textbook ---------*/
status InitList(LinkList &L);		//新建 
status DestroyList(LinkList &L);		//销毁 
status ClearList(LinkList &L);		//清空 
status ListEmpty(LinkList L);		//判空 
status ListLength(LinkList L);		//求长度 
status GetElem(LinkList L,int i,ElemType &e);		//获得元素 
status LocateElem(LinkList L,ElemType e); 		//判断位置 
status PriorElem(LinkList L,ElemType e,ElemType &pre);		//获得前驱 
status NextElem(LinkList L,ElemType e,ElemType &next);		//货的后继 
status ListInsert(LinkList &L,int i,ElemType e);		//插入 
status ListDelete(LinkList &L,int i,ElemType &e);		//删除 
status ListTraverse(LinkList L);  		//遍历输出 
status AddList(LISTS &Lists,char ListName[]);	//多线性表插入 
status RemoveList(LISTS &Lists,char ListName[]); 	//多线性表删除 
status LocateList(LISTS Lists,char ListName[]); 	//多线性表查找 
status SaveList(LinkList L,char FileName[]);		//此函数用了fprintf写入文件，便于检查文件 
status LoadList(LinkList &L,char FileName[]);		//此函数用了fscanf写入文件，与fprintf对应
status SortList(LinkList &L, int choice);		//排序 
status reverseList(LinkList &L);		//链表反转 
status RemoveNthFromEnd(LinkList &L, int n, int &e);	//删除链表的倒数第n个节点 
/*--------------------------------------------*/
int main(void){
LinkList L;  int op=1;
L = NULL;		
while(op){
	fflush(stdin);	//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
	system("cls");	printf("\n\n");		//清楚屏幕命令 
	printf("用户您好！欢迎使用此程序！\n");
	printf("本程序创建者为	计算机2107班	陈侠锟\n\n"); 
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. 创建新的线性表		2. 销毁线性表\n");
	printf("    	  3. 清空线性表			4. 线性表判空\n");
	printf("    	  5. 求线性表长度		6. 获取元素	\n");
	printf("    	  7. 查找元素位置		8. 获取元素的前驱	\n");
	printf("    	  9. 获取元素的后继		10. 插入元素\n");
	printf("    	  11. 删除元素			12. 遍历线性表\n");
	printf("    	  13. 读写文件			14. 多线性表管理\n");
	printf("    	  15. 链表排序			16. 删除倒数节点\n"); 
	printf("    	  17. 链表反转\n"); 
	printf("    	  0. 退出\n\n");
	printf("注意：此线性表中的数据应全为整型！\n");
	printf("-------------------------------------------------\n");
	if(op < 0 || op > 16)	printf("    输入错误！请重新选择你的操作[0~16]:");
	else	printf("    请选择你的操作[0~16]:");
	if(!scanf("%d",&op))	op = 100;
	switch(op){
		case 1:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作 
			if(InitList(L) == OK) {
				int lengthi, data; 
renew1:
				fflush(stdin);		//这里的清空输入流是防止在输入长度和数据错误之后，剩余的数据对重新输入长度和数据这一步产生影响 
				printf("请依次输入此表的初始长度和初始数据（只能输入数字，多余的数据将会被忽略）：");
				if(!scanf("%d",&lengthi)){
					printf("输入不合法，请重新输入！\n");
					fflush(stdin);		//避免上一次输入的过多数据对本次输入造成干扰 
					goto renew1; 
		 		}
				for(int j = 1; j <= lengthi; j++){
					if(!scanf("%d",&data)){
						printf("输入不合法，请重新输入！\n");
						ClearList(L);	//清除在不合法数据出现之前存入线性表的数据 
						goto renew1;
					}
					ListInsert(L, j, data);
				}
			printf("线性表创建成功！当前线性表数据为：\n");
			ListTraverse(L); 
		 	}
		    else printf("线性表创建失败！\n");
		 	fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
		 	printf("请按回车键继续");getchar();
			break;}
		 
		case 2:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(DestroyList(L) == INFEASIBLE)	printf("线性表不存在！请先创建线性表！\n");
			else	printf("已成功销毁线性表！\n");   
			printf("请按回车键继续");getchar();
			break;}
		 
		case 3:{
	   		fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(ClearList(L) == OK)		printf("已成功清除线性表的所有元素！\n");
			else	printf("线性表不存在！请先创建线性表！\n");   
			printf("请按回车键继续");getchar();
			break;}
		 
		case 4:{
	   		fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(ListEmpty(L) == TRUE)	printf("此线性表为空！\n");
			else if(ListEmpty(L) == FALSE)		printf("此线性表不为空！\n");
			else	printf("线性表不存在！请先创建线性表！\n");     
			printf("请按回车键继续");getchar();
			break;}
		 
		case 5:{		
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
		 	if(!L)	printf("线性表不存在！请先创建线性表！\n");
		 	else	printf("此线性表长度为：%d\n",ListLength(L));    
		 	printf("请按回车键继续");getchar();
			break;}
		 
		case 6:{
	   		fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
	   		int pos6, target6;
			if(!L){
				printf("线性表不存在！请先创建线性表！\n");
			}
			else{
				printf("输入你想要获取的元素的位置编号，将获取该元素\n");
	   	 		printf("请输入一个数字（多余的数据将会被忽略）：");
				while(!scanf("%d",&pos6)){
					printf("只能输入数字！请重新输入：");
					fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
				}
				fflush(stdin);	 //为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 

				if(GetElem(L,pos6,target6) == ERROR)	printf("输入的位置编号不合法！\n");
				else	printf("位置编号为%d的元素是：%d\n",pos6,target6);
		 	} 
		 	printf("请按回车键继续");getchar();
			break;}
		 
		case 7:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			int target7;
			if(!L){
				printf("线性表不存在！请先创建线性表！\n");
			}
			else{
				printf("输入你想要查找的元素,将会返回此线性表中此元素第一次出现的位置\n");
				printf("请输入一个数字（多余的数据将会被忽略）：");
				while(!scanf("%d",&target7)){
					printf("只能输入数字！请重新输入：");
					fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
				}
				fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
				int judge7 = LocateElem(L,target7);
				if(judge7 == ERROR)	printf("线性表中无此元素！\n");
				else	printf("%d是此线性表中第%d个元素\n",target7, judge7); 
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 8:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(!L)		printf("线性表不存在！请先创建线性表！\n"); 
			else{
				int target8, pre;
				printf("输入一个元素，将获取它的前驱元素并输出（若有多个相同的此元素，只会返回其第一次出现位置的前驱元素）\n");
				printf("请输入一个数字（多余的数据将会被忽略）："); 
				while(!scanf("%d",&target8)){
					printf("只能输入数字！请重新输入：");
					fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
			 	}
			 	fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
			 	if(PriorElem(L,target8,pre) == OK)	printf("元素%d的前驱元素是：%d\n",target8, pre); 
//		 	由于返回值为ERROR时有两种情况：此元素没有前驱元素  或  此元素在线性表中不存在，故将关于ERROR的判断放在了函数中实现 
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 9:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(!L)		printf("线性表不存在！请先创建线性表！\n");
			else{
	   			int target9, next; 
				printf("输入一个元素，将获取它的后继元素并输出（若有多个相同的此元素，只会返回其第一次出现位置的后继元素）\n");
				printf("请输入一个数字（多余的数据将会被忽略）："); 
				while(!scanf("%d",&target9)){
					printf("只能输入数字！请重新输入：");
					fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
			 	}
			 	fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
			 	if(NextElem(L,target9,next) == OK)	printf("元素%d的后继元素是：%d\n",target9, next); 
//		 	由于返回值为ERROR时有两种情况：此元素没有前驱元素  或  此元素在线性表中不存在，故将关于ERROR的判断放在了函数中实现
			}
		 	printf("请按回车键继续");getchar();
			break;}
		 
		case 10:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(!L)		printf("线性表不存在！请先创建线性表！\n");
			else{
	   			int pos10, target10;
			 	printf("依次输入要插入的位置和元素，将在对应位置插入该元素\n");
			 	printf("请输入（两数据之间用空格隔开，多余的数据将会被忽略）：");
renew10:
			while(scanf("%d %d",&pos10, &target10) != 2){
				fflush(stdin);		//避免上一次输入的过多数据对本次输入造成干扰 
//				printf("输入位置为：%d ，输入数据为：%d\n",pos10,target10); 	//测试用 
				printf("两者均只能输入数字！请重新输入：");		 	
			}
			
			printf("您当前选择的插入位置为：%d ，输入数据为：%d，请按回车键查看结果\n",pos10,target10); 
			fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
			getchar(); 
			if(ListInsert(L,pos10,target10) == ERROR){
				printf("插入位置不合法！请重新输入插入位置和元素：");
			 	goto renew10; 
			}	
			else printf("插入成功！成功在%d号位置插入元素%d！\n",pos10,target10);	
			printf("当前线性表为：\n");
			ListTraverse(L);
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 11:{
	   		fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(!L)		printf("线性表不存在！请先创建线性表！\n");
			else if(!L->next)	printf("线性表为空，请先输入数据！\n");  
			else{
				int pos11, target11;   
				printf("请输入你要删除的元素的位置，将删除此位置上的元素\n");
				printf("请输入（多余的数据将会被忽略）："); 
renew11:
				while(!scanf("%d",&pos11)){
					printf("只能输入数字！请重新输入：");
					fflush(stdin);		//避免上一次输入的过多数据对本次输入造成干扰 
				}
				fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
				if(ListDelete(L,pos11,target11) == ERROR){
					printf("删除位置不合法！请重新输入删除位置：\n");
					goto renew11;
				}
				else	printf("第%d号元素删除成功，删除元素为%d\n",pos11, target11);	 
				printf("当前线性表为：\n");
				ListTraverse(L); 
			}
			
			printf("请按回车键继续");getchar();
			break;}
		 
		case 12:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(!L)	printf("线性表不存在！请先创建线性表！\n");   
			else {
				printf("此线性表当前数据如下：\n");
		 		if (!ListTraverse(L)) printf("线性表是空表！\n");
			}
			printf("请按回车键继续");getchar();
			break;}
		 
		case 13:{
			fflush(stdin);
			char FileName[30];
			strcpy(FileName, "test.txt");
			printf("此功能将会把线性表中已有的数据写入外部的test.txt文件中，若无此文件，将创造此文件\n");
			printf("请按回车键以开始");
			getchar();
			if(!L)		printf("线性表不存在！请先创建线性表！\n");
			else{
				if(SaveList(L,FileName) == ERROR) ;
				else{
					printf("已成功将线性表中的数据导入外部文件，请查看外部文件\n");
					printf("按回车键以继续\n");
					getchar();
					DestroyList(L);
					printf("已销毁线性表...\n");
					printf("正在从外部文件导入数据到线性表...\n");
					if(LoadList(L,FileName) == ERROR)		printf("外部文件丢失！终止操作！");
					else{
						printf("已导入完成，按回车键以输出线性表中数据\n");
						getchar();
						printf("线性表中数据如下：\n"); 
						ListTraverse(L);
					}
				}
			}
	   		printf("请按回车键继续\n");getchar();
			break;}
	   
		case 14:{
			int choice = 1; 
			while(choice){
		   		fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
				system("cls");	printf("\n\n");		//清楚屏幕命令 
				printf("您已进入多线性表管理（与1~12操作的单线性表不互相影响）\n");
		   		printf("您将拥有一个数量上限为10的线性表组，您可以对其进行如下操作\n");
		   		printf("    	  1. 创建线性表		2. 删除线性表\n");
				printf("    	  3. 查找线性表		4. 查看您已有的线性表\n");
				printf("    	  0. 退出多线性表管理\n\n"); 
				printf("注意：此线性表中的数据应全为整型！\n");
				printf("-------------------------------------------------\n");
				if(choice < 0 || choice > 5)	printf("    输入错误！请重新选择你的操作[0~5]:");
				else	printf("    请选择你的操作[0~5]:");
				scanf("%d",&choice);
				switch(choice){
					case 1:{
						fflush(stdin);		//清除输入指令时可能存在的多余的数字 
						int num, data, lengthi;
						char name_str[30];
						if(Lists.length == 10){
							printf("线性表已满！无法创建新的线性表！\n");
							printf("请按回车键继续……\n");getchar();
							break; 
						}
						printf("请输入你想要新建的线性表的数量（注意：你当前还可以新建%d个线性表）：", 10 - Lists.length);
renew14_1_1:
						while(!scanf("%d",&num)){
							printf("输入错误！请重新输入一个数字：");
							fflush(stdin);	//避免上一次输入的过多数据对本次输入造成干扰 
						} 
						if(num > 10-Lists.length || num < 0){
							printf("输入数量不合理，请重新输入新建数量：");
							goto renew14_1_1;
						} 
						for(int i = 0; i < num; i++){
							fflush(stdin);		//为了防止在输入上一个表中的数据时多余的数据对下一个表的输入造成干扰 
							memset(name_str,0,sizeof(name_str));	//重置暂时存储线性表名字的变量 
							printf("请输入第%d个线性表的名字(注意：名字最多30个字符，且不可包含空格，多余的数据将会被忽略)：",i+1);
							int name_strpos = 0;
							for(char c; ((c = getchar()) != ' ' && c != '\n') && name_strpos < 29; name_strpos++){  //为了保证线性表的名字在30个字符之内，多余的字符将舍弃 
								name_str[name_strpos] = c;
							} 
							name_str[name_strpos] = '\0';	//作为字符串的结尾标志 
							AddList(Lists, name_str);	//此步骤之后，Lists.length已加一 
renew14_1_2:
							fflush(stdin);	//清空输入流，避免输入线性表名字时多余的字符对接下来的数据产生干扰 
							printf("请依次输入此表的初始长度和初始数据（只能输入数字）：");
							if(!scanf("%d",&lengthi)){
								printf("输入不合法，请重新输入！\n");
								goto renew14_1_2; 
							}
							for(int j = 1; j <= lengthi; j++){
								if(!scanf("%d",&data)){
									printf("输入不合法，请重新输入！\n");
									ClearList(Lists.elem[Lists.length-1].L);
									goto renew14_1_2;
								}
								ListInsert(Lists.elem[Lists.length-1].L, j, data);
							}
						}
						fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据  
						printf("\n线性表创建完成，以下是您已拥有的线性表：\n\n");
						for(int k = 0; k < Lists.length; k++){
							printf("线性表%d：%s ",k+1, Lists.elem[k].name);
							ListTraverse(Lists.elem[k].L);
							printf("\n");
						} 
						printf("请按回车键继续……\n");getchar();
						break;}
						
					case 2:{
						fflush(stdin);		//清除输入指令时可能存在的多余的数字
						int num;
						char name_del[30]; 
						if(Lists.length == 0){
							printf("你现在没有线性表！\n");
							printf("请按回车键继续……\n");getchar();
							break;
						} 
						printf("以下是你目前拥有的线性表：\n");
						for(int i = 0; i < Lists.length; i++)	printf("%s ",Lists.elem[i].name);
renew14_2:
						printf("\n请输入你想要删除的线性表的数量：\n");
						while(!scanf("%d",&num)){
							printf("输入错误！请输入数字：");
							fflush(stdin);		 
						}
						if(num < 0 || num > Lists.length){
							printf("输入错误！你当前最多可以删除%d个表！\n", Lists.length);
							goto renew14_2;
						}
						getchar();		//读取回车 
						for(int i = 0; i < num; i++){
							printf("请输入第%d个你想要删除的线性表的名字（每次请输入一个名字，多余的数据将会被忽略）：",i+1);
							memset(name_del, 0, sizeof(name_del)); 
							int name_delpos = 0;
							for(char c; ((c = getchar()) != ' ' && c != '\n') && name_delpos < 29; name_delpos++){  //为了保证线性表的名字在30个字符之内，多余的字符将舍弃 
								name_del[name_delpos] = c;
							} 
							name_del[name_delpos] = '\0';	//作为字符串的结尾标志 
							if(RemoveList(Lists, name_del) == OK){
								printf("已成功销毁此线性表！\n");
								continue; 
							}
							else{
								printf("此线性表不存在！\n");
							}
						}
						printf("销毁线性表操作已完成！你当前还有以下线性表：\n");
						for(int k = 0; k < Lists.length; k++){
							printf("线性表%d：%s ",k+1, Lists.elem[k].name);
							ListTraverse(Lists.elem[k].L);
							printf("\n");
						} 
						printf("请按回车键继续……\n");getchar();
						break;}
					
					case 3:{
						fflush(stdin);		//清除输入指令时可能存在的多余的数字
						if(Lists.length == 0){
							printf("你现在没有线性表！\n");
							printf("请按回车键继续……\n");getchar();
							break;
						}
						char name_seek[30];
						printf("输入你想查找的线性表名字（不可包含空格，若输入空格，空格之后的内容将会被忽略），将返回此线性表在线性表组中的序号\n");
						printf("请输入："); 
						int name_seekpos = 0;
						for(char c; ((c = getchar()) != ' ' && c != '\n') && name_seekpos < 29; name_seekpos++){  //为了保证线性表的名字在30个字符之内，多余的字符将舍弃 
							name_seek[name_seekpos] = c;
						} 
						name_seek[name_seekpos] = '\0';	//作为字符串的结尾标志 
						if(LocateList(Lists, name_seek) == ERROR)	printf("此线性表不存在！\n");
						else	printf("此线性表在线性表组中的位置是第%d\n",LocateList(Lists, name_seek));
						printf("请按回车键继续……\n");getchar();
						break;}
					
					case 4:{
						fflush(stdin);		//清除输入指令时可能存在的多余的数字
						if(Lists.length == 0)	printf("你现在没有线性表！\n");
						else{
							printf("你当前拥有以下线性表：\n");
							for(int k = 0; k < Lists.length; k++){
								printf("线性表%d：%s ",k+1, Lists.elem[k].name);
								ListTraverse(Lists.elem[k].L);
								printf("\n");
							}
						}
						printf("请按回车键继续……\n");getchar();
						break;}
			
					case 0:break;
				}// end of the switch of case14
			}//end of the while of case14
	   		break;
		}// end of case14
		
		case 15:{
			fflush(stdin);		//清除输入指令时可能存在的多余的数字
			if(!L)	printf("线性表不存在！请先创建线性表！\n"); 
			else{
				int choice;
				printf("此功能将线性表中的元素排序，按1从小到大排序，按2从大到小排序\n");
				printf("请输入1或2（多余的数据将会被忽略）：");
				while((scanf("%d",&choice) != 1) || (choice != 1 && choice != 2)){
					printf("输入错误！请重新输入：\n");
					fflush(stdin);		//避免上一次输入的过多数据对本次输入造成干扰  
				}
				fflush(stdin);
				SortList(L,choice);
				printf("排序完成，排序后线性表如下：\n");
				ListTraverse(L);
			}
			printf("请按回车键继续\n");getchar();
			break;
		}
		
		case 16:{
			fflush(stdin);		//这里的清空输入流是防止上一次操作结束后，“按回车以继续 ”时输入了数据而影响本次操作
			if(!L)		printf("线性表不存在！请先创建线性表！\n");
			else if(!L->next)	printf("线性表为空，请先输入数据！\n");  
			else{
				int pos16, target16;   
				printf("请输入你要删除的元素的位置，将删除此位置上的元素\n");
				printf("请输入（多余的数据将会被忽略）："); 
renew16:
				while(!scanf("%d",&pos16)){
					printf("只能输入数字！请重新输入：");
					fflush(stdin);		//避免上一次输入的过多数据对本次输入造成干扰 
				}
				fflush(stdin);		//为了防止“请按回车键继续 ”之后的getchar()读到多余的数据 
				if(RemoveNthFromEnd(L, pos16, target16) == ERROR){
					printf("删除位置不合法！请重新输入删除位置：\n");
					goto renew16;
				}
				else	printf("倒数第%d个节点删除成功，此节点原有元素为%d\n",pos16, target16);	 
				printf("当前线性表为：\n");
				ListTraverse(L);
			}
			printf("请按回车键继续\n");getchar();
			break; 
		} 
		
		case 17:{
			fflush(stdin);		//清除输入指令时可能存在的多余的数字
			if(!L)	printf("线性表不存在！请先创建线性表！\n");
			else{
				printf("此功能将实现链表的反转，按回车以继续");
				getchar();
				if(reverseList(L) == ERROR)		printf("此线性表为空表，无法实现反转功能！\n"); 
				else{
					printf("反转操作完成，当前线性表为：\n");
					ListTraverse(L);
				} 
			}
			fflush(stdin);
			printf("请按回车键以继续\n");getchar();
			break;
		}
		case 0:break;
	}//end of switch
}//end of while
printf("欢迎下次再使用本系统！\n");
free(L); 
return 0;
}//end of main()

status InitList(LinkList &L){
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    if(L)  return INFEASIBLE;
    L = (struct LNode* )malloc(sizeof(LNode));
    L->next = NULL;
    L->data = 0; 
    return OK;
}

status DestroyList(LinkList &L){
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    LinkList front, last;
    front = L->next;
    last = L;
    while(front != NULL){
        free(last);
        last = front;
        front = front->next;
    }
    free(last);
    L = NULL; 
    return OK;
}

status ClearList(LinkList &L){
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    if(!L)  return INFEASIBLE;

    LinkList front, last;
    front = L->next;
    last = L;	last->data = 0;
    while(front != NULL){
        last = front;
        front = front->next;
        free(last);
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList L){
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    if(!L->next)    return TRUE;
    return FALSE;
}

status ListLength(LinkList L){
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
//	return L->data;
    if(!L)  return INFEASIBLE;
    int len = 0;
    LinkList p = L->next;
    while(p != NULL){
        len++;
        p = p->next;
    }
    return len;			//此为当头节点数据域不存储链表长度时用于求长度的代码
}

status GetElem(LinkList L,int i,ElemType &e){
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    int cnt = 0;	//cnt用于记录当前是第几个元素 
    LinkList p = L->next;
    while(p != NULL){
        cnt++;
        if(cnt == i){
            e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

status LocateElem(LinkList L,ElemType e){
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    int cnt = 0;	//cnt用于记录当前是第几个元素 
    LinkList p = L->next;
    while(p != NULL){
        cnt++;
        if(p->data == e){
            return cnt;
        }
        p = p->next;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre){
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    LinkList last = L, cur = L->next;	//cur指向当前元素，last指向当前元素的前驱 
    while(cur != NULL){		//只要没到表尾 
        if(cur->data == e){
            if(cur == L->next){		//如果元素e是首位元素
            	printf("此元素没有前驱元素！\n"); 
            	return ERROR;	 
			}   
            pre = last->data; 
            return OK;
        }
        last = cur;
        cur = cur->next;
    }
    printf("线性表中不存在此元素！\n");
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next){
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    LinkList cur = L->next;		//cur指向当前元素 
    if(cur == NULL) return ERROR;       //若线性表是空表
    LinkList behind = cur->next;	//behind指向当前元素的后继 
    while(1){
        if(cur->data == e){
            if(behind == NULL){		//已经到了倒数第一个元素 
            	printf("此元素没有后继元素！\n"); 
				return ERROR;  
			}
            next = behind->data;
            return OK;
        }
        cur = behind;
        if(cur == NULL) break;
        behind = behind->next;
    } 
    printf("线性表中不存在此元素！\n");
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e){
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    LinkList p = L;		//p指向当前（第i个）元素的前驱元素 
    int j = 0;
    while(p && j < i - 1){
        p = p->next;    
        j++;
    }
    if(!p || j > i - 1) return ERROR;   //!p说明表L不存在或者i大于了表长+1，j > i - 1说明i的值小于1（不合法）
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    L->data++;		//表长加一 
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e){
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    LinkList p = L, q;		//p指向当前元素的前驱（以p->next指向当前元素），q指向要删除的元素 
    int j = 0;		//j做计数器 
    while(p->next && j < i-1){
        p = p->next;
        j++;
    }
    if(!(p->next) || j > i-1)   return ERROR;	//!(p->next)说明L为空表或者i大于了表长+1，j > i - 1说明i的值小于1（不合法）
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    L->data--; 
    return OK;
}

status ListTraverse(LinkList L){
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    LinkList p = L->next;
    printf("\n-----------all elements -----------------------\n");
    while(p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n------------------ end ------------------------\n");
    return OK;
}

status SaveList(LinkList L,char FileName[]){
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
    if(!L)  return INFEASIBLE;
    FILE *fp;
    if((fp = fopen(FileName,"w")) == NULL){
		printf("Failed!\n");
		return ERROR;
	}
    LinkList p = L->next;
	while(p != NULL){
		fprintf(fp,"%d",p->data);
        if(p->next != NULL) fprintf(fp,"%c",' ');
        p = p->next;
	}
	fclose(fp);
	return OK;
}

status LoadList(LinkList &L,char FileName[]){
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
    if(L)	return INFEASIBLE;
	FILE *fp;
    if((fp = fopen(FileName, "r")) == NULL){
    	printf("Failed!\n");
    	return ERROR;
	}
    L = (LinkList)malloc(sizeof(LNode));    L->next = NULL;
    LinkList tail = L;
    LinkList p = (LinkList)malloc(sizeof(LNode));
    while(fscanf(fp, "%d", &p->data)){
        tail->next = p;
        p->next = NULL;
        tail = p;
        p = (LinkList)malloc(sizeof(LNode));
        if(feof(fp))	break;
    }
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[]){
// 在Lists中增加一个名称为ListName的空线性表。 
    if(Lists.length >= 10)  return ERROR;	//如果线性表组已满 
    Lists.elem[Lists.length].L = NULL;		//线性表初始化 

    InitList(Lists.elem[Lists.length].L);		//创建线性表 

    strcpy(Lists.elem[Lists.length].name , ListName);	//线性表命名 
    
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[]){
// Lists中删除一个名称为ListName的线性表
	if(Lists.length == 0)	return ERROR;
	int j;
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(Lists.elem[i].name , ListName) == 0 && i != Lists.length - 1){
            DestroyList(Lists.elem[i].L);
            Lists.length--; //销毁线性表后，多线性表的总数量减一
            Lists.elem[i].L = (struct LNode* )malloc(sizeof(LNode));   //重新为删除的线性表分配空间，用于后续线性表的移动操作

            for( j = i ; j < Lists.length ; j++){    //线性表的移动
            	strcpy(Lists.elem[j].name , Lists.elem[j+1].name);  //线性表名字的移动
				Lists.elem[j].L = Lists.elem[j+1].L;	//线性表数据的移动 
            }
            j++;
            DestroyList(Lists.elem[j].L);   //销毁移动完之后处于末端的线性表
            memset(Lists.elem[j].name , 0 , sizeof(Lists.elem[j].name));
            return OK;
        }
        else if(strcmp(Lists.elem[i].name , ListName) == 0 && i == Lists.length - 1){	//如果删除的线性表本来就在队尾 
        	DestroyList(Lists.elem[i].L);
        	Lists.length--; 
        	memset(Lists.elem[i].name , 0 , sizeof(Lists.elem[i].name));
        	return OK;
		}
    }
    return ERROR;
}

status LocateList(LISTS Lists,char ListName[]){
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
	if(Lists.length == 0)	return ERROR;
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(Lists.elem[i].name , ListName) == 0){
            return i+1;
        }
    }
    return 0;
}

status SortList(LinkList &L, int choice){
//对链表元素进行排序，choice = 1为从小到大排序， choice = 2为从大到小排序 	
	if(!L)	return INFEASIBLE;
	int tem;
	LinkList p;	//p一开始指向第一位元素 
	if(choice == 1){ 
		for(int i = L->data; i > 0; i--){
			p = L->next;	//重置p的位置 
			for(int j = 1; j < i; j++, p = p->next){		//冒泡排序，从小到大 
				if(p->data > p->next->data){
					tem = p->next->data;
					p->next->data = p->data;
					p->data = tem;
				}
			}
		}
	}
	else{
		for(int i = L->data; i > 0; i--){
			p = L->next;	//重置p的位置 
			for(int j = 1; j < i; j++, p = p->next){		//冒泡排序，从大到小 
				if(p->data < p->next->data){
					tem = p->next->data;
					p->next->data = p->data;
					p->data = tem;
				}
			}
		}
	}
	return OK; 
}

status reverseList(LinkList &L){
//迭代法实现链表反转 	
	if(!L)	return INFEASIBLE;		//线性表不存在 
	if(!L->next)	return ERROR; 	//线性表为空表 
	LinkList mid = L->next, beg = NULL, end = L->next->next;	//在原链表的状态下，beg指向mid的前驱，end指向mid的后继 
	while(end!=NULL){	//mid指向最后一个节点时，end为空 
		mid->next = beg;
		beg = mid;
		mid = end;
		end = end->next;
	} 
	mid->next = beg;
	L->next = mid;
	return OK;
}

status RemoveNthFromEnd(LinkList &L, int n, int &e){
//删除链表的倒数第n个节点，用e返回被删除节点存储的元素 
	if(!L)  return INFEASIBLE;
    LinkList p = L, q;		//p指向当前元素的前驱（以p->next指向当前元素），q指向要删除的元素 
    int j = 0, i = L->data - n + 1;		//i代表链表的正数第几个元素，j作计数器 
    while(p->next && j < i-1){
        p = p->next;
        j++;
    }
    if(!(p->next) || j > i-1)   return ERROR;	//!(p->next)说明L为空表或者i大于了表长+1，j > i - 1说明i的值小于1（不合法）
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    L->data--; 
    return OK;
}
