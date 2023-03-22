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
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���	//ͷ�ڵ�������L->data�������洢������ 	
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef struct{  //������ļ������Ͷ���  
     struct { char name[30];  
               LinkList L;      
      } elem[10];  
      int length;  
//      LinkList head, tail;	
 }LISTS;  
 LISTS Lists;      //���Ա��ϵĶ���Lists 
/*-----page 19 on textbook ---------*/
status InitList(LinkList &L);		//�½� 
status DestroyList(LinkList &L);		//���� 
status ClearList(LinkList &L);		//��� 
status ListEmpty(LinkList L);		//�п� 
status ListLength(LinkList L);		//�󳤶� 
status GetElem(LinkList L,int i,ElemType &e);		//���Ԫ�� 
status LocateElem(LinkList L,ElemType e); 		//�ж�λ�� 
status PriorElem(LinkList L,ElemType e,ElemType &pre);		//���ǰ�� 
status NextElem(LinkList L,ElemType e,ElemType &next);		//���ĺ�� 
status ListInsert(LinkList &L,int i,ElemType e);		//���� 
status ListDelete(LinkList &L,int i,ElemType &e);		//ɾ�� 
status ListTraverse(LinkList L);  		//������� 
status AddList(LISTS &Lists,char ListName[]);	//�����Ա���� 
status RemoveList(LISTS &Lists,char ListName[]); 	//�����Ա�ɾ�� 
status LocateList(LISTS Lists,char ListName[]); 	//�����Ա���� 
status SaveList(LinkList L,char FileName[]);		//�˺�������fprintfд���ļ������ڼ���ļ� 
status LoadList(LinkList &L,char FileName[]);		//�˺�������fscanfд���ļ�����fprintf��Ӧ
status SortList(LinkList &L, int choice);		//���� 
status reverseList(LinkList &L);		//����ת 
status RemoveNthFromEnd(LinkList &L, int n, int &e);	//ɾ������ĵ�����n���ڵ� 
/*--------------------------------------------*/
int main(void){
LinkList L;  int op=1;
L = NULL;		
while(op){
	fflush(stdin);	//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
	system("cls");	printf("\n\n");		//�����Ļ���� 
	printf("�û����ã���ӭʹ�ô˳���\n");
	printf("�����򴴽���Ϊ	�����2107��	�����\n\n"); 
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. �����µ����Ա�		2. �������Ա�\n");
	printf("    	  3. ������Ա�			4. ���Ա��п�\n");
	printf("    	  5. �����Ա���		6. ��ȡԪ��	\n");
	printf("    	  7. ����Ԫ��λ��		8. ��ȡԪ�ص�ǰ��	\n");
	printf("    	  9. ��ȡԪ�صĺ��		10. ����Ԫ��\n");
	printf("    	  11. ɾ��Ԫ��			12. �������Ա�\n");
	printf("    	  13. ��д�ļ�			14. �����Ա����\n");
	printf("    	  15. ��������			16. ɾ�������ڵ�\n"); 
	printf("    	  17. ����ת\n"); 
	printf("    	  0. �˳�\n\n");
	printf("ע�⣺�����Ա��е�����ӦȫΪ���ͣ�\n");
	printf("-------------------------------------------------\n");
	if(op < 0 || op > 16)	printf("    �������������ѡ����Ĳ���[0~16]:");
	else	printf("    ��ѡ����Ĳ���[0~16]:");
	if(!scanf("%d",&op))	op = 100;
	switch(op){
		case 1:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β��� 
			if(InitList(L) == OK) {
				int lengthi, data; 
renew1:
				fflush(stdin);		//���������������Ƿ�ֹ�����볤�Ⱥ����ݴ���֮��ʣ������ݶ��������볤�Ⱥ�������һ������Ӱ�� 
				printf("����������˱�ĳ�ʼ���Ⱥͳ�ʼ���ݣ�ֻ���������֣���������ݽ��ᱻ���ԣ���");
				if(!scanf("%d",&lengthi)){
					printf("���벻�Ϸ������������룡\n");
					fflush(stdin);		//������һ������Ĺ������ݶԱ���������ɸ��� 
					goto renew1; 
		 		}
				for(int j = 1; j <= lengthi; j++){
					if(!scanf("%d",&data)){
						printf("���벻�Ϸ������������룡\n");
						ClearList(L);	//����ڲ��Ϸ����ݳ���֮ǰ�������Ա������ 
						goto renew1;
					}
					ListInsert(L, j, data);
				}
			printf("���Ա����ɹ�����ǰ���Ա�����Ϊ��\n");
			ListTraverse(L); 
		 	}
		    else printf("���Ա���ʧ�ܣ�\n");
		 	fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 2:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(DestroyList(L) == INFEASIBLE)	printf("���Ա����ڣ����ȴ������Ա�\n");
			else	printf("�ѳɹ��������Ա�\n");   
			printf("�밴�س�������");getchar();
			break;}
		 
		case 3:{
	   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(ClearList(L) == OK)		printf("�ѳɹ�������Ա������Ԫ�أ�\n");
			else	printf("���Ա����ڣ����ȴ������Ա�\n");   
			printf("�밴�س�������");getchar();
			break;}
		 
		case 4:{
	   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(ListEmpty(L) == TRUE)	printf("�����Ա�Ϊ�գ�\n");
			else if(ListEmpty(L) == FALSE)		printf("�����Ա�Ϊ�գ�\n");
			else	printf("���Ա����ڣ����ȴ������Ա�\n");     
			printf("�밴�س�������");getchar();
			break;}
		 
		case 5:{		
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
		 	if(!L)	printf("���Ա����ڣ����ȴ������Ա�\n");
		 	else	printf("�����Ա���Ϊ��%d\n",ListLength(L));    
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 6:{
	   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
	   		int pos6, target6;
			if(!L){
				printf("���Ա����ڣ����ȴ������Ա�\n");
			}
			else{
				printf("��������Ҫ��ȡ��Ԫ�ص�λ�ñ�ţ�����ȡ��Ԫ��\n");
	   	 		printf("������һ�����֣���������ݽ��ᱻ���ԣ���");
				while(!scanf("%d",&pos6)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
				}
				fflush(stdin);	 //Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 

				if(GetElem(L,pos6,target6) == ERROR)	printf("�����λ�ñ�Ų��Ϸ���\n");
				else	printf("λ�ñ��Ϊ%d��Ԫ���ǣ�%d\n",pos6,target6);
		 	} 
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 7:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			int target7;
			if(!L){
				printf("���Ա����ڣ����ȴ������Ա�\n");
			}
			else{
				printf("��������Ҫ���ҵ�Ԫ��,���᷵�ش����Ա��д�Ԫ�ص�һ�γ��ֵ�λ��\n");
				printf("������һ�����֣���������ݽ��ᱻ���ԣ���");
				while(!scanf("%d",&target7)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
				}
				fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
				int judge7 = LocateElem(L,target7);
				if(judge7 == ERROR)	printf("���Ա����޴�Ԫ�أ�\n");
				else	printf("%d�Ǵ����Ա��е�%d��Ԫ��\n",target7, judge7); 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 8:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L)		printf("���Ա����ڣ����ȴ������Ա�\n"); 
			else{
				int target8, pre;
				printf("����һ��Ԫ�أ�����ȡ����ǰ��Ԫ�ز���������ж����ͬ�Ĵ�Ԫ�أ�ֻ�᷵�����һ�γ���λ�õ�ǰ��Ԫ�أ�\n");
				printf("������һ�����֣���������ݽ��ᱻ���ԣ���"); 
				while(!scanf("%d",&target8)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
			 	}
			 	fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
			 	if(PriorElem(L,target8,pre) == OK)	printf("Ԫ��%d��ǰ��Ԫ���ǣ�%d\n",target8, pre); 
//		 	���ڷ���ֵΪERRORʱ�������������Ԫ��û��ǰ��Ԫ��  ��  ��Ԫ�������Ա��в����ڣ��ʽ�����ERROR���жϷ����˺�����ʵ�� 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 9:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
	   			int target9, next; 
				printf("����һ��Ԫ�أ�����ȡ���ĺ��Ԫ�ز���������ж����ͬ�Ĵ�Ԫ�أ�ֻ�᷵�����һ�γ���λ�õĺ��Ԫ�أ�\n");
				printf("������һ�����֣���������ݽ��ᱻ���ԣ���"); 
				while(!scanf("%d",&target9)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
			 	}
			 	fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
			 	if(NextElem(L,target9,next) == OK)	printf("Ԫ��%d�ĺ��Ԫ���ǣ�%d\n",target9, next); 
//		 	���ڷ���ֵΪERRORʱ�������������Ԫ��û��ǰ��Ԫ��  ��  ��Ԫ�������Ա��в����ڣ��ʽ�����ERROR���жϷ����˺�����ʵ��
			}
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 10:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
	   			int pos10, target10;
			 	printf("��������Ҫ�����λ�ú�Ԫ�أ����ڶ�Ӧλ�ò����Ԫ��\n");
			 	printf("�����루������֮���ÿո��������������ݽ��ᱻ���ԣ���");
renew10:
			while(scanf("%d %d",&pos10, &target10) != 2){
				fflush(stdin);		//������һ������Ĺ������ݶԱ���������ɸ��� 
//				printf("����λ��Ϊ��%d ����������Ϊ��%d\n",pos10,target10); 	//������ 
				printf("���߾�ֻ���������֣����������룺");		 	
			}
			
			printf("����ǰѡ��Ĳ���λ��Ϊ��%d ����������Ϊ��%d���밴�س����鿴���\n",pos10,target10); 
			fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
			getchar(); 
			if(ListInsert(L,pos10,target10) == ERROR){
				printf("����λ�ò��Ϸ����������������λ�ú�Ԫ�أ�");
			 	goto renew10; 
			}	
			else printf("����ɹ����ɹ���%d��λ�ò���Ԫ��%d��\n",pos10,target10);	
			printf("��ǰ���Ա�Ϊ��\n");
			ListTraverse(L);
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 11:{
	   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else if(!L->next)	printf("���Ա�Ϊ�գ������������ݣ�\n");  
			else{
				int pos11, target11;   
				printf("��������Ҫɾ����Ԫ�ص�λ�ã���ɾ����λ���ϵ�Ԫ��\n");
				printf("�����루��������ݽ��ᱻ���ԣ���"); 
renew11:
				while(!scanf("%d",&pos11)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);		//������һ������Ĺ������ݶԱ���������ɸ��� 
				}
				fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
				if(ListDelete(L,pos11,target11) == ERROR){
					printf("ɾ��λ�ò��Ϸ�������������ɾ��λ�ã�\n");
					goto renew11;
				}
				else	printf("��%d��Ԫ��ɾ���ɹ���ɾ��Ԫ��Ϊ%d\n",pos11, target11);	 
				printf("��ǰ���Ա�Ϊ��\n");
				ListTraverse(L); 
			}
			
			printf("�밴�س�������");getchar();
			break;}
		 
		case 12:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L)	printf("���Ա����ڣ����ȴ������Ա�\n");   
			else {
				printf("�����Ա�ǰ�������£�\n");
		 		if (!ListTraverse(L)) printf("���Ա��ǿձ�\n");
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 13:{
			fflush(stdin);
			char FileName[30];
			strcpy(FileName, "test.txt");
			printf("�˹��ܽ�������Ա������е�����д���ⲿ��test.txt�ļ��У����޴��ļ�����������ļ�\n");
			printf("�밴�س����Կ�ʼ");
			getchar();
			if(!L)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
				if(SaveList(L,FileName) == ERROR) ;
				else{
					printf("�ѳɹ������Ա��е����ݵ����ⲿ�ļ�����鿴�ⲿ�ļ�\n");
					printf("���س����Լ���\n");
					getchar();
					DestroyList(L);
					printf("���������Ա�...\n");
					printf("���ڴ��ⲿ�ļ��������ݵ����Ա�...\n");
					if(LoadList(L,FileName) == ERROR)		printf("�ⲿ�ļ���ʧ����ֹ������");
					else{
						printf("�ѵ�����ɣ����س�����������Ա�������\n");
						getchar();
						printf("���Ա����������£�\n"); 
						ListTraverse(L);
					}
				}
			}
	   		printf("�밴�س�������\n");getchar();
			break;}
	   
		case 14:{
			int choice = 1; 
			while(choice){
		   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
				system("cls");	printf("\n\n");		//�����Ļ���� 
				printf("���ѽ�������Ա������1~12�����ĵ����Ա�����Ӱ�죩\n");
		   		printf("����ӵ��һ����������Ϊ10�����Ա��飬�����Զ���������²���\n");
		   		printf("    	  1. �������Ա�		2. ɾ�����Ա�\n");
				printf("    	  3. �������Ա�		4. �鿴�����е����Ա�\n");
				printf("    	  0. �˳������Ա����\n\n"); 
				printf("ע�⣺�����Ա��е�����ӦȫΪ���ͣ�\n");
				printf("-------------------------------------------------\n");
				if(choice < 0 || choice > 5)	printf("    �������������ѡ����Ĳ���[0~5]:");
				else	printf("    ��ѡ����Ĳ���[0~5]:");
				scanf("%d",&choice);
				switch(choice){
					case 1:{
						fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
						int num, data, lengthi;
						char name_str[30];
						if(Lists.length == 10){
							printf("���Ա��������޷������µ����Ա�\n");
							printf("�밴�س�����������\n");getchar();
							break; 
						}
						printf("����������Ҫ�½������Ա��������ע�⣺�㵱ǰ�������½�%d�����Ա���", 10 - Lists.length);
renew14_1_1:
						while(!scanf("%d",&num)){
							printf("�����������������һ�����֣�");
							fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
						} 
						if(num > 10-Lists.length || num < 0){
							printf("�������������������������½�������");
							goto renew14_1_1;
						} 
						for(int i = 0; i < num; i++){
							fflush(stdin);		//Ϊ�˷�ֹ��������һ�����е�����ʱ��������ݶ���һ�����������ɸ��� 
							memset(name_str,0,sizeof(name_str));	//������ʱ�洢���Ա����ֵı��� 
							printf("�������%d�����Ա������(ע�⣺�������30���ַ����Ҳ��ɰ����ո񣬶�������ݽ��ᱻ����)��",i+1);
							int name_strpos = 0;
							for(char c; ((c = getchar()) != ' ' && c != '\n') && name_strpos < 29; name_strpos++){  //Ϊ�˱�֤���Ա��������30���ַ�֮�ڣ�������ַ������� 
								name_str[name_strpos] = c;
							} 
							name_str[name_strpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
							AddList(Lists, name_str);	//�˲���֮��Lists.length�Ѽ�һ 
renew14_1_2:
							fflush(stdin);	//����������������������Ա�����ʱ������ַ��Խ����������ݲ������� 
							printf("����������˱�ĳ�ʼ���Ⱥͳ�ʼ���ݣ�ֻ���������֣���");
							if(!scanf("%d",&lengthi)){
								printf("���벻�Ϸ������������룡\n");
								goto renew14_1_2; 
							}
							for(int j = 1; j <= lengthi; j++){
								if(!scanf("%d",&data)){
									printf("���벻�Ϸ������������룡\n");
									ClearList(Lists.elem[Lists.length-1].L);
									goto renew14_1_2;
								}
								ListInsert(Lists.elem[Lists.length-1].L, j, data);
							}
						}
						fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()�������������  
						printf("\n���Ա�����ɣ�����������ӵ�е����Ա�\n\n");
						for(int k = 0; k < Lists.length; k++){
							printf("���Ա�%d��%s ",k+1, Lists.elem[k].name);
							ListTraverse(Lists.elem[k].L);
							printf("\n");
						} 
						printf("�밴�س�����������\n");getchar();
						break;}
						
					case 2:{
						fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
						int num;
						char name_del[30]; 
						if(Lists.length == 0){
							printf("������û�����Ա�\n");
							printf("�밴�س�����������\n");getchar();
							break;
						} 
						printf("��������Ŀǰӵ�е����Ա�\n");
						for(int i = 0; i < Lists.length; i++)	printf("%s ",Lists.elem[i].name);
renew14_2:
						printf("\n����������Ҫɾ�������Ա��������\n");
						while(!scanf("%d",&num)){
							printf("����������������֣�");
							fflush(stdin);		 
						}
						if(num < 0 || num > Lists.length){
							printf("��������㵱ǰ������ɾ��%d����\n", Lists.length);
							goto renew14_2;
						}
						getchar();		//��ȡ�س� 
						for(int i = 0; i < num; i++){
							printf("�������%d������Ҫɾ�������Ա�����֣�ÿ��������һ�����֣���������ݽ��ᱻ���ԣ���",i+1);
							memset(name_del, 0, sizeof(name_del)); 
							int name_delpos = 0;
							for(char c; ((c = getchar()) != ' ' && c != '\n') && name_delpos < 29; name_delpos++){  //Ϊ�˱�֤���Ա��������30���ַ�֮�ڣ�������ַ������� 
								name_del[name_delpos] = c;
							} 
							name_del[name_delpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
							if(RemoveList(Lists, name_del) == OK){
								printf("�ѳɹ����ٴ����Ա�\n");
								continue; 
							}
							else{
								printf("�����Ա����ڣ�\n");
							}
						}
						printf("�������Ա��������ɣ��㵱ǰ�����������Ա�\n");
						for(int k = 0; k < Lists.length; k++){
							printf("���Ա�%d��%s ",k+1, Lists.elem[k].name);
							ListTraverse(Lists.elem[k].L);
							printf("\n");
						} 
						printf("�밴�س�����������\n");getchar();
						break;}
					
					case 3:{
						fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
						if(Lists.length == 0){
							printf("������û�����Ա�\n");
							printf("�밴�س�����������\n");getchar();
							break;
						}
						char name_seek[30];
						printf("����������ҵ����Ա����֣����ɰ����ո�������ո񣬿ո�֮������ݽ��ᱻ���ԣ��������ش����Ա������Ա����е����\n");
						printf("�����룺"); 
						int name_seekpos = 0;
						for(char c; ((c = getchar()) != ' ' && c != '\n') && name_seekpos < 29; name_seekpos++){  //Ϊ�˱�֤���Ա��������30���ַ�֮�ڣ�������ַ������� 
							name_seek[name_seekpos] = c;
						} 
						name_seek[name_seekpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
						if(LocateList(Lists, name_seek) == ERROR)	printf("�����Ա����ڣ�\n");
						else	printf("�����Ա������Ա����е�λ���ǵ�%d\n",LocateList(Lists, name_seek));
						printf("�밴�س�����������\n");getchar();
						break;}
					
					case 4:{
						fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
						if(Lists.length == 0)	printf("������û�����Ա�\n");
						else{
							printf("�㵱ǰӵ���������Ա�\n");
							for(int k = 0; k < Lists.length; k++){
								printf("���Ա�%d��%s ",k+1, Lists.elem[k].name);
								ListTraverse(Lists.elem[k].L);
								printf("\n");
							}
						}
						printf("�밴�س�����������\n");getchar();
						break;}
			
					case 0:break;
				}// end of the switch of case14
			}//end of the while of case14
	   		break;
		}// end of case14
		
		case 15:{
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
			if(!L)	printf("���Ա����ڣ����ȴ������Ա�\n"); 
			else{
				int choice;
				printf("�˹��ܽ����Ա��е�Ԫ�����򣬰�1��С�������򣬰�2�Ӵ�С����\n");
				printf("������1��2����������ݽ��ᱻ���ԣ���");
				while((scanf("%d",&choice) != 1) || (choice != 1 && choice != 2)){
					printf("����������������룺\n");
					fflush(stdin);		//������һ������Ĺ������ݶԱ���������ɸ���  
				}
				fflush(stdin);
				SortList(L,choice);
				printf("������ɣ���������Ա����£�\n");
				ListTraverse(L);
			}
			printf("�밴�س�������\n");getchar();
			break;
		}
		
		case 16:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else if(!L->next)	printf("���Ա�Ϊ�գ������������ݣ�\n");  
			else{
				int pos16, target16;   
				printf("��������Ҫɾ����Ԫ�ص�λ�ã���ɾ����λ���ϵ�Ԫ��\n");
				printf("�����루��������ݽ��ᱻ���ԣ���"); 
renew16:
				while(!scanf("%d",&pos16)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);		//������һ������Ĺ������ݶԱ���������ɸ��� 
				}
				fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
				if(RemoveNthFromEnd(L, pos16, target16) == ERROR){
					printf("ɾ��λ�ò��Ϸ�������������ɾ��λ�ã�\n");
					goto renew16;
				}
				else	printf("������%d���ڵ�ɾ���ɹ����˽ڵ�ԭ��Ԫ��Ϊ%d\n",pos16, target16);	 
				printf("��ǰ���Ա�Ϊ��\n");
				ListTraverse(L);
			}
			printf("�밴�س�������\n");getchar();
			break; 
		} 
		
		case 17:{
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
			if(!L)	printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
				printf("�˹��ܽ�ʵ������ķ�ת�����س��Լ���");
				getchar();
				if(reverseList(L) == ERROR)		printf("�����Ա�Ϊ�ձ��޷�ʵ�ַ�ת���ܣ�\n"); 
				else{
					printf("��ת������ɣ���ǰ���Ա�Ϊ��\n");
					ListTraverse(L);
				} 
			}
			fflush(stdin);
			printf("�밴�س����Լ���\n");getchar();
			break;
		}
		case 0:break;
	}//end of switch
}//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
free(L); 
return 0;
}//end of main()

status InitList(LinkList &L){
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
    if(L)  return INFEASIBLE;
    L = (struct LNode* )malloc(sizeof(LNode));
    L->next = NULL;
    L->data = 0; 
    return OK;
}

status DestroyList(LinkList &L){
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L)  return INFEASIBLE;
    if(!L->next)    return TRUE;
    return FALSE;
}

status ListLength(LinkList L){
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
//	return L->data;
    if(!L)  return INFEASIBLE;
    int len = 0;
    LinkList p = L->next;
    while(p != NULL){
        len++;
        p = p->next;
    }
    return len;			//��Ϊ��ͷ�ڵ������򲻴洢������ʱ�����󳤶ȵĴ���
}

status GetElem(LinkList L,int i,ElemType &e){
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L)  return INFEASIBLE;
    int cnt = 0;	//cnt���ڼ�¼��ǰ�ǵڼ���Ԫ�� 
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
    if(!L)  return INFEASIBLE;
    int cnt = 0;	//cnt���ڼ�¼��ǰ�ǵڼ���Ԫ�� 
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L)  return INFEASIBLE;
    LinkList last = L, cur = L->next;	//curָ��ǰԪ�أ�lastָ��ǰԪ�ص�ǰ�� 
    while(cur != NULL){		//ֻҪû����β 
        if(cur->data == e){
            if(cur == L->next){		//���Ԫ��e����λԪ��
            	printf("��Ԫ��û��ǰ��Ԫ�أ�\n"); 
            	return ERROR;	 
			}   
            pre = last->data; 
            return OK;
        }
        last = cur;
        cur = cur->next;
    }
    printf("���Ա��в����ڴ�Ԫ�أ�\n");
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next){
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L)  return INFEASIBLE;
    LinkList cur = L->next;		//curָ��ǰԪ�� 
    if(cur == NULL) return ERROR;       //�����Ա��ǿձ�
    LinkList behind = cur->next;	//behindָ��ǰԪ�صĺ�� 
    while(1){
        if(cur->data == e){
            if(behind == NULL){		//�Ѿ����˵�����һ��Ԫ�� 
            	printf("��Ԫ��û�к��Ԫ�أ�\n"); 
				return ERROR;  
			}
            next = behind->data;
            return OK;
        }
        cur = behind;
        if(cur == NULL) break;
        behind = behind->next;
    } 
    printf("���Ա��в����ڴ�Ԫ�أ�\n");
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e){
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L)  return INFEASIBLE;
    LinkList p = L;		//pָ��ǰ����i����Ԫ�ص�ǰ��Ԫ�� 
    int j = 0;
    while(p && j < i - 1){
        p = p->next;    
        j++;
    }
    if(!p || j > i - 1) return ERROR;   //!p˵����L�����ڻ���i�����˱�+1��j > i - 1˵��i��ֵС��1�����Ϸ���
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    L->data++;		//����һ 
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e){
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L)  return INFEASIBLE;
    LinkList p = L, q;		//pָ��ǰԪ�ص�ǰ������p->nextָ��ǰԪ�أ���qָ��Ҫɾ����Ԫ�� 
    int j = 0;		//j�������� 
    while(p->next && j < i-1){
        p = p->next;
        j++;
    }
    if(!(p->next) || j > i-1)   return ERROR;	//!(p->next)˵��LΪ�ձ����i�����˱�+1��j > i - 1˵��i��ֵС��1�����Ϸ���
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    L->data--; 
    return OK;
}

status ListTraverse(LinkList L){
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
// ��Lists������һ������ΪListName�Ŀ����Ա� 
    if(Lists.length >= 10)  return ERROR;	//������Ա������� 
    Lists.elem[Lists.length].L = NULL;		//���Ա��ʼ�� 

    InitList(Lists.elem[Lists.length].L);		//�������Ա� 

    strcpy(Lists.elem[Lists.length].name , ListName);	//���Ա����� 
    
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[]){
// Lists��ɾ��һ������ΪListName�����Ա�
	if(Lists.length == 0)	return ERROR;
	int j;
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(Lists.elem[i].name , ListName) == 0 && i != Lists.length - 1){
            DestroyList(Lists.elem[i].L);
            Lists.length--; //�������Ա�󣬶����Ա����������һ
            Lists.elem[i].L = (struct LNode* )malloc(sizeof(LNode));   //����Ϊɾ�������Ա����ռ䣬���ں������Ա���ƶ�����

            for( j = i ; j < Lists.length ; j++){    //���Ա���ƶ�
            	strcpy(Lists.elem[j].name , Lists.elem[j+1].name);  //���Ա����ֵ��ƶ�
				Lists.elem[j].L = Lists.elem[j+1].L;	//���Ա����ݵ��ƶ� 
            }
            j++;
            DestroyList(Lists.elem[j].L);   //�����ƶ���֮����ĩ�˵����Ա�
            memset(Lists.elem[j].name , 0 , sizeof(Lists.elem[j].name));
            return OK;
        }
        else if(strcmp(Lists.elem[i].name , ListName) == 0 && i == Lists.length - 1){	//���ɾ�������Ա������ڶ�β 
        	DestroyList(Lists.elem[i].L);
        	Lists.length--; 
        	memset(Lists.elem[i].name , 0 , sizeof(Lists.elem[i].name));
        	return OK;
		}
    }
    return ERROR;
}

status LocateList(LISTS Lists,char ListName[]){
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
	if(Lists.length == 0)	return ERROR;
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(Lists.elem[i].name , ListName) == 0){
            return i+1;
        }
    }
    return 0;
}

status SortList(LinkList &L, int choice){
//������Ԫ�ؽ�������choice = 1Ϊ��С�������� choice = 2Ϊ�Ӵ�С���� 	
	if(!L)	return INFEASIBLE;
	int tem;
	LinkList p;	//pһ��ʼָ���һλԪ�� 
	if(choice == 1){ 
		for(int i = L->data; i > 0; i--){
			p = L->next;	//����p��λ�� 
			for(int j = 1; j < i; j++, p = p->next){		//ð�����򣬴�С���� 
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
			p = L->next;	//����p��λ�� 
			for(int j = 1; j < i; j++, p = p->next){		//ð�����򣬴Ӵ�С 
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
//������ʵ������ת 	
	if(!L)	return INFEASIBLE;		//���Ա����� 
	if(!L->next)	return ERROR; 	//���Ա�Ϊ�ձ� 
	LinkList mid = L->next, beg = NULL, end = L->next->next;	//��ԭ�����״̬�£�begָ��mid��ǰ����endָ��mid�ĺ�� 
	while(end!=NULL){	//midָ�����һ���ڵ�ʱ��endΪ�� 
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
//ɾ������ĵ�����n���ڵ㣬��e���ر�ɾ���ڵ�洢��Ԫ�� 
	if(!L)  return INFEASIBLE;
    LinkList p = L, q;		//pָ��ǰԪ�ص�ǰ������p->nextָ��ǰԪ�أ���qָ��Ҫɾ����Ԫ�� 
    int j = 0, i = L->data - n + 1;		//i��������������ڼ���Ԫ�أ�j�������� 
    while(p->next && j < i-1){
        p = p->next;
        j++;
    }
    if(!(p->next) || j > i-1)   return ERROR;	//!(p->next)˵��LΪ�ձ����i�����˱�+1��j > i - 1˵��i��ֵС��1�����Ϸ���
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    L->data--; 
    return OK;
}
