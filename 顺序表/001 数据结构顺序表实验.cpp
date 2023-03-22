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
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;

typedef struct{  //���Ա�ļ������Ͷ���  
     struct { char name[30];  
               SqList L;      
      } elem[10];  
      int length;  
 }LISTS;  
 LISTS Lists;      //���Ա��ϵĶ���Lists 
/*-----page 19 on textbook ---------*/
status InitList(SqList& L);		//�½� 
status DestroyList(SqList& L);		//���� 
status ClearList(SqList&L);		//��� 
status ListEmpty(SqList L);		//�п� 
status ListLength(SqList L);		//�󳤶� 
status GetElem(SqList L,int i,ElemType &e);		//���Ԫ�� 
status LocateElem(SqList L,ElemType e); 		//�ж�λ�� 
status PriorElem(SqList L,ElemType cur,ElemType &pre);		//���ǰ�� 
status NextElem(SqList L,ElemType cur,ElemType &next);		//���ĺ�� 
status ListInsert(SqList &L,int i,ElemType e);		//���� 
status ListDelete(SqList &L,int i,ElemType &e);		//ɾ�� 
status ListTraverse(SqList L);  		//������� 
status AddList(LISTS &Lists,char ListName[]);	//�����Ա���� 
status RemoveList(LISTS &Lists,char ListName[]); 	//�����Ա�ɾ�� 
status LocateList(LISTS Lists,char ListName[]); 	//�����Ա���� 
status SaveList(SqList &L,char FileName[]);		//�˺�������fwrite�Զ�����д���ļ������ļ������벻���ڼ�� 
status SaveList2(SqList &L, char FileName[]);		//�˺�������fprintfд���ļ������ڼ���ļ� 
status LoadList(SqList &L,char FileName[]);		//�˺�������fread��ȡ�ļ�����fwrite��Ӧ 
status LoadList2(SqList &L, char FileName[]);		//�˺�������fscanfд���ļ�����fprintf��Ӧ 
status SortList(SqList &L, int choice);		//���� 
status MaxSubArray(SqList &L);		//���������� 
status SubArrayNum(SqList &L, int k);	//��ֵΪk��������� 
/*--------------------------------------------*/
int main(void){
SqList L;  int op=1;
L.elem = NULL;		
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
	printf("    	  15. ���Ա�����		16. ����������\n"); 
	printf("    	  17. ��ֵΪk���������\n"); 
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
					fflush(stdin);		//�������������Ĺ������ݵ�����һ��getchar()ֱ������
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
		 	if(ListLength(L) == INFEASIBLE)	printf("���Ա����ڣ����ȴ������Ա�\n");
		 	else	printf("�����Ա���Ϊ��%d\n",ListLength(L));    
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 6:{
	   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
	   		int pos6, target6;
			if(!L.elem){
				printf("���Ա����ڣ����ȴ������Ա�\n");
			}
			else{
				printf("��������Ҫ��ȡ��Ԫ�ص�λ�ñ�ţ�����ȡ��Ԫ��\n");
	   	 		printf("������һ�����֣���������ݽ��ᱻ���ԣ���");
				while(!scanf("%d",&pos6)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//�������ᵼ����ѭ�� 
				}
				fflush(stdin);	 //Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 

				if(GetElem(L,pos6,target6) == ERROR)	printf("�����λ�ñ�Ų��Ϸ���\n");
				else	printf("λ�ñ��Ϊ%d��Ԫ���ǣ�%d\n",pos6,target6);
		 	} 
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 7:{
			fflush(stdin);			//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			int target7;
			if(!L.elem){
				printf("���Ա����ڣ����ȴ������Ա�\n");
			}
			else{
				printf("��������Ҫ���ҵ�Ԫ��,���᷵�ش����Ա��д�Ԫ�ص�һ�γ��ֵ�λ��\n");
				printf("������һ�����֣���������ݽ��ᱻ���ԣ���");
				while(!scanf("%d",&target7)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//�������ᵼ����ѭ�� 
				}
				fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
				int judge7 = LocateElem(L,target7);
				if(judge7 == ERROR)	printf("���Ա����޴�Ԫ�أ�\n");
				else	printf("%d�Ǵ����Ա��е�%d��Ԫ��\n",target7, judge7); 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 8:{
			fflush(stdin);			//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L.elem)		printf("���Ա����ڣ����ȴ������Ա�\n"); 
			else{
				int target8, pre;
				printf("����һ��Ԫ�أ�����ȡ����ǰ��Ԫ�ز����\n");
				printf("������һ�����֣���������ݽ��ᱻ���ԣ���"); 
				while(!scanf("%d",&target8)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//�������ᵼ����ѭ�� 
			 	}
			 	fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
			 	if(PriorElem(L,target8,pre) == OK)	printf("Ԫ��%d��ǰ��Ԫ���ǣ�%d\n",target8, pre); 
//		 	���ڷ���ֵΪERRORʱ�������������Ԫ��û��ǰ��Ԫ��  ��  ��Ԫ�������Ա��в����ڣ��ʽ�����ERROR���жϷ����˺�����ʵ�� 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 9:{
			fflush(stdin);			//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L.elem)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
	   			int target9, next; 
				printf("����һ��Ԫ�أ�����ȡ���ĺ��Ԫ�ز����\n");
				printf("������һ�����֣���������ݽ��ᱻ���ԣ���"); 
				while(!scanf("%d",&target9)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);	//�������ᵼ����ѭ�� 
			 	}
			 	fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
			 	if(NextElem(L,target9,next) == OK)	printf("Ԫ��%d�ĺ��Ԫ���ǣ�%d\n",target9, next); 
//		 	���ڷ���ֵΪERRORʱ�������������Ԫ��û��ǰ��Ԫ��  ��  ��Ԫ�������Ա��в����ڣ��ʽ�����ERROR���жϷ����˺�����ʵ��
			}
		 	printf("�밴�س�������");getchar();
			break;}
		 
		case 10:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L.elem)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
	   			int pos10, target10;
			 	printf("��������Ҫ�����λ�ú�Ԫ�أ����ڶ�Ӧλ�ò����Ԫ��\n");
			 	printf("�����루������֮���ÿո��������������ݽ��ᱻ���ԣ���");
renew10:
			while(scanf("%d %d",&pos10, &target10) != 2){
				fflush(stdin);		//�������ᵼ����ѭ�� 
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
			}
			printf("��ǰ���Ա�Ϊ��\n");
			ListTraverse(L);
		 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 11:{
	   		fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L.elem)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else if(!L.length)	printf("���Ա�Ϊ�գ������������ݣ�\n"); 
			else{
				int pos11, target11;   
				printf("��������Ҫɾ����Ԫ�ص�λ�ã���ɾ����λ���ϵ�Ԫ��\n");
				printf("�����루��������ݽ��ᱻ���ԣ���"); 
renew11:
				while(!scanf("%d",&pos11)){
					printf("ֻ���������֣����������룺");
					fflush(stdin);		//�������ᵼ����ѭ�� 
				}
				fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()������������� 
				if(ListDelete(L,pos11,target11) == ERROR){
					printf("ɾ��λ�ò��Ϸ�������������ɾ��λ�ã�\n");
					goto renew11;
				}
				else{
					printf("��%d��Ԫ��ɾ���ɹ���ɾ��Ԫ��Ϊ%d\n",pos11, target11);
				}	 
			}
			printf("��ǰ���Ա�Ϊ��\n");
			ListTraverse(L); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 12:{
			fflush(stdin);		//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
			if(!L.elem)	printf("���Ա����ڣ����ȴ������Ա�\n");   
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
			if(!L.elem)		printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
				if(SaveList2(L,FileName) == ERROR) ;
				else{
					printf("�ѳɹ������Ա��е����ݵ����ⲿ�ļ�����鿴�ⲿ�ļ�\n");
					printf("���س����Լ���\n");
					getchar();
					DestroyList(L);
					printf("���������Ա�...\n");
					printf("���ڴ��ⲿ�ļ��������ݵ����Ա�...\n");
					if(LoadList2(L,FileName) == ERROR)		printf("�ⲿ�ļ���ʧ����ֹ������");
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
						fflush(stdin);			//�������ָ��ʱ���ܴ��ڵĶ�������� 
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
							fflush(stdin);		//�������ᵼ����ѭ�� 
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
			if(!L.elem)	printf("���Ա����ڣ����ȴ������Ա�\n"); 
			else{
				int choice;
				printf("�˹��ܽ����Ա��е�Ԫ�����򣬰�1��С�������򣬰�2�Ӵ�С����\n");
				printf("������1��2����������ݽ��ᱻ���ԣ���");
				while(scanf("%d",&choice) != 1 &&(choice != 1 && choice != 2)){
					printf("����������������룺\n");
					fflush(stdin);		//�������ᵼ����ѭ�� 
				}
				fflush(stdin);
				if(choice == 1){
					SortList(L,choice);
					printf("������ɣ���������Ա����£�\n");
					ListTraverse(L); 
				}
				else{
					SortList(L,choice);
					printf("������ɣ���������Ա����£�\n");
					ListTraverse(L);
				}
			}
			printf("�밴�س�������\n");getchar();
			break;
		}
		
		case 16:{
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
			if(!L.elem)	printf("���Ա����ڣ����ȴ������Ա�\n");
			else{
				printf("�˹��ܽ��ҳ��������͵����������飬���������ͣ����س��Լ���");
				getchar();
				printf("����������Ϊ��%d\n",MaxSubArray(L)); 
			}
			printf("�밴�س����Լ���\n");getchar();
			break;
		} 
		
		case 17:{
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ��������
			if(!L.elem)	printf("���Ա����ڣ����ȴ������Ա�\n");
			int k;
			printf("�˹��ܽ��ҳ��м������������飬���ǡ�õ���kֵ\n");
			printf("������һ������k����������ݽ��ᱻ���ԣ���");
			while(!scanf("%d",&k)){
				printf("�����������������һ�����֣�");
				fflush(stdin);		//�������ᵼ����ѭ�� 
			}
			fflush(stdin);
			printf("��Ϊ%d�����������鹲��%d��\n",k,SubArrayNum(L, k));
			printf("�밴�س����Լ���\n");getchar();
			break;
		}
		case 0:break;
	}//end of switch
}//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
free(L.elem); 
return 0;
}//end of main()

/*--------page 23 on textbook --------------------*/
status InitList(SqList& L){		//������Ա�L�����ڣ��½����Ա� 
	if(L.elem)		return INFEASIBLE;
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
	if(!L.elem)		exit(OVERFLOW);
	L.length=0;		//��ʼ������ 
	L.listsize=LIST_INIT_SIZE;		//��ʼ����С 
	return OK;
}

status DestroyList(SqList& L){	// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
    if(L.elem)  {
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else return INFEASIBLE;  
}

status ClearList(SqList& L){	// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
    if(L.elem){
        memset(L.elem, 0, L.length * sizeof(ElemType));		//�������Ա�ռ� 
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else return INFEASIBLE;
}

status ListEmpty(SqList L){	// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
    if(L.elem) {
        if(L.length)    return FALSE;
        else    return TRUE;
    }
    else    return INFEASIBLE;
}

status ListLength(SqList L){	// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    else return L.length;
}

status GetElem(SqList L,int i,ElemType &e){
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    else if( i < 1 || i > L.length)    return ERROR;
    else{
        e = *(L.elem + i - 1);
        return OK;
    }
}

status LocateElem(SqList L,ElemType e){
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
    if(!L.elem) return INFEASIBLE;

    for(int i = 0; i < L.length; i++){
        if(*(L.elem + i) == e)  return i + 1;	//Ԫ�ص��߼����Ϊ������±��һ 
    }
    return ERROR;
}

status PriorElem(SqList L,ElemType cur,ElemType &pre){
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    int *now = L.elem;	//nowָ��ǰԪ�� 
    if(*now == cur){
    	printf("��Ԫ��û��ǰ��Ԫ�أ�\n");
		return ERROR;  //���Ŀ��Ԫ������λԪ�أ���û��ǰ��������ERROR 
	}   
    else{
        now++;
        int *last = L.elem;		//lastָ��ǰ��Ԫ�� 
        for(int i = 0; i < L.length + 1; i++){	//���� 
            if(*now == cur)    {
                pre = *last;
                return OK;
            }
            now++;  last++;		//���� 
        }
        printf("���Ա��в����ڴ�Ԫ�أ�\n");
        return ERROR;	//���Ա���Ŀ��Ԫ�أ�����ERROR 
    }
}

status NextElem(SqList L,ElemType cur,ElemType &next){
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    int *p = L.elem;
    for(int i = 0; i < L.length; i++){
        if(*(p+i) == cur){		//p+iָ��ǰԪ�� 
            if(i == L.length - 1){
            	printf("��Ԫ��û�к��Ԫ�أ�\n");
            	return ERROR;
			}    
            next = *(p+1+i);
            return OK;
        }
    }
    printf("���Ա��в����ڴ�Ԫ�أ�\n");
    return ERROR; 
}

status ListInsert(SqList &L,int i,ElemType e){
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length + 1)   return ERROR;
    if(L.length >= L.listsize) {  //���Ŀǰ�ռ䲻����
        int* newbase = (ElemType *)realloc(L.elem , (L.listsize + LISTINCREMENT) * sizeof(ElemType));	//�����¿ռ� 
        if(!newbase)    return OVERFLOW;
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }

    int *q = &(L.elem[i - 1]);		//�����λ�� 
    for(int *p = &(L.elem[L.length - 1]); p >= q; p--){		//���κ���Ԫ�� 
        *(p + 1) = *p;
    }
    *q = e;		//����Ԫ�� 
    ++L.length;
    return OK;
}


status ListDelete(SqList &L,int i,ElemType &e){
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length)   return ERROR;

    int *p = &(L.elem[i-1]);  //ɾ��λ��
    e = *p;
    int *tail = L.elem + L.length - 1;  //��βλ��
    for( ; p < tail; p++){
        *p = *(p+1);
    }
    L.length --;
    return OK;
}

status AddList(LISTS &Lists,char ListName[]){
// ��Lists������һ������ΪListName�Ŀ����Ա� 
    if(Lists.length >= 10)  return ERROR;	//������Ա������� 
    Lists.elem[Lists.length].L.elem = NULL;		//���Ա��ʼ�� 

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
            Lists.elem[i].L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);   //����Ϊɾ�������Ա����ռ䣬���ں������Ա���ƶ�����
            Lists.elem[i].L.listsize = LIST_INIT_SIZE;

            for( j = i ; j < Lists.length ; j++){    //���Ա���ƶ�
                strcpy(Lists.elem[j].name , Lists.elem[j+1].name);  //���Ա����ֵ��ƶ�
                memcpy(&Lists.elem[j].L , &Lists.elem[j+1].L , sizeof(SqList));   //���Ա����ݵ��ƶ�
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


status ListTraverse(SqList L){		//������������Ա��е����� 
	if(!L.elem)	return INFEASIBLE;
	int i;
	printf("\n-----------all elements -----------------------\n");
	for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L.length;
}

status SaveList(SqList &L,char FileName[]){		//��fwriteʵ���ļ���д�� 
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
    if(!L.elem) return INFEASIBLE;
    FILE *fp;
    if((fp = fopen(FileName, "w")) == NULL){
    	printf("Failed!\n");
    	return ERROR;
	}
    fwrite(L.elem,sizeof(ElemType),L.length,fp);
    fclose(fp);
    return OK;
}

status SaveList2(SqList &L, char FileName[]){		//��fprintfʵ���ļ���д�� 
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
	if(!L.elem)	return INFEASIBLE;
	FILE*fp;
	if((fp = fopen(FileName,"w")) == NULL){
		printf("Failed!\n");
		return ERROR;
	}
	for(int i = 0; i < L.length; i++){
		fprintf(fp,"%c",' ');
		fprintf(fp,"%d",L.elem[i]);
	}
	fclose(fp);
	return OK;
} 

status LoadList(SqList &L,char FileName[]){		//��freadʵ���ļ��Ķ�ȡ 
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
    if(L.elem)  return INFEASIBLE;
    FILE *fp;
    if((fp = fopen(FileName, "r")) == NULL){
    	printf("Failed!\n");
    	return ERROR;
	}
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    L.length = 0;
    while(fread(&L.elem[L.length],sizeof(ElemType),1,fp)){
        L.length++;
    }
    fclose(fp);
    return OK;
}

status LoadList2(SqList &L, char FileName[]){		//��fscanfʵ���ļ��Ķ�ȡ
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE�� 
	if(L.elem)	return INFEASIBLE;
	FILE *fp;
    if((fp = fopen(FileName, "r")) == NULL){
    	printf("Failed!\n");
    	return ERROR;
	}
    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    L.length = 0;
    while(fscanf(fp, "%d", &L.elem[L.length])){
        L.length++;
        if(feof(fp))	break;
    }
    fclose(fp);
    return OK;
}

status SortList(SqList &L, int choice){
	if(!L.elem)	return INFEASIBLE;
	int tem;
	if(choice == 1){
		for(int i = L.length-1; i >= 0; i--){
			for(int j = 0; j  < i; j++){		//ð�����򣬴�С���� 
				if(L.elem[j] > L.elem[j+1]){
					tem = L.elem[j+1];
					L.elem[j+1] = L.elem[j];
					L.elem[j] = tem;
				}
			}
		}
	}
	else{
		for(int i = L.length-1; i >= 0; i--){
			for(int j = 0; j  < i; j++){		//ð�����򣬴Ӵ�С 
				if(L.elem[j] < L.elem[j+1]){
					tem = L.elem[j+1];
					L.elem[j+1] = L.elem[j];
					L.elem[j] = tem;
				}
			}
		}
	}
	return OK; 
}

status MaxSubArray(SqList &L){		//�����������ͣ����ظ�ֵ 
	if(!L.elem)	return INFEASIBLE;
	int sum = 0, max = -999999999, maxnum = -999999999;		//maxnum��Ϊ�˷�ֹ��������ȫΪ��������������������maxΪ0���������������ͣ� 
	for(int i = 0; i < L.length; i++){
		sum += L.elem[i];		//��ǰ׺�� 
		if(L.elem[i] > maxnum)	maxnum = L.elem[i];
		if(sum > max)	max = sum;		//�����ݲ�ȫΪ����������£���ȡǰ׺�����ֵ��Ϊ���������� 
		if(sum < 0)	sum = 0;	//��ǰ׺��Ϊ����ʱ����������һ��ѭ����ʼ���¼���ǰ׺�� 
	}
	return max > maxnum ? max : maxnum;
}

status SubArrayNum(SqList &L, int k){
	if(!L.elem)	return INFEASIBLE;
	int cnt = 0;
	for(int i = 0; i < L.length; i++){
		int sum = 0;
		for(int j = i; j < L.length; j++){
			sum += L.elem[j];
			if(sum == k)	cnt++;
		}
	}
	return cnt;
}
