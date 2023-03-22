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
} TElemType;			//������������Ͷ���

typedef struct BiTNode{ //����������Ķ���
	TElemType  data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct{ 		//�������ļ������Ͷ���  
	struct { 
		char name[30];  
		BiTree T;      
	}elem[10];  
    int length;			//������¼�Ѿ��еĶ���������  
} BITREES;  
BITREES BiTrees;      	//���������ϵĶ���BiTrees 

int def_cnt;			//ר�����ڼ�¼������definition�������������һλ 
/*-----page 19 on textbook ---------*/
status CreateBiTree(BiTree &T,TElemType definition[]);		//�½� 
status DestroyBiTree(BITREES &BiTrees,char TreeName[]);		//���� 
status ClearBiTree(BiTree &T);								//��� 
status BiTreeEmpty(BiTree T);								//�п� 
status BiTreeDepth(BiTree T);								//����� 
BiTNode* LocateNode(BiTree T,KeyType e); 					//���ҽ��
status Assign(BiTree &T,KeyType e,TElemType value);			//��㸳ֵ 
BiTNode* GetSibling(BiTree T,KeyType e);					//����ֵܽڵ� 
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);	//������
status DeleteNode(BiTree &T,KeyType e);						//ɾ����� 	 
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));	//ǰ����� 
status InOrderTraverse(BiTree T,void (*visit)(BiTree));		//������� 
status PostOrderTraverse(BiTree T,void (*visit)(BiTree)); 	//������� 
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));	//������� 
status MaxPathSum(BiTree T);								//�����Ҷ�ӵ����·���� 
BiTree LowestCommonAncestor(BiTree T, int e1, int e2);		//������������� 
status InvertTree(BiTree &T);								//����ת 
status SaveBiTree(BiTree T, char FileName[]);				//�洢�ļ� 
status LoadBiTree(BiTree &T,  char FileName[]);				//��ȡ�ļ� 
int check(TElemType definition[], int count); 		//����������ʱ�������ж�definition�������Ƿ����ظ��ؼ���
int check2(BiTree &T, KeyType e, TElemType value);	//��㸳ֵʱ�������ж�����Ĺؼ����Ƿ��Ŀ����������Ĺؼ����ظ� 
int check3(BiTree &T, TElemType value);				//�������ǣ������ж�����Ĺؼ����Ƿ��������һ�ؼ����ظ� 
BiTree reset(BiTree &L, BiTree &R);					//ɾ�����ʱ������ɾ�����Ķ�Ϊ2ʱ�����˽ڵ����������R����Ϊ�������У�L�����ҽ��������� 
void visit(BiTree T);
/*--------------------------------------------*/
int main(void){
TElemType definition[100];		//���������ʱ��Ҫ�����飬��¼���������Ĺؼ��֣����� 
int op=1;
BiTrees.length = 0;
char name_target[30];			//���������ڼ�¼ÿ�������Ķ��󣨶��������� 
int name_tarpos = 0, flag = 0;	//flag�����жϲ�������治�����ڶ��������� 	
while(op){
	fflush(stdin);	//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
	system("cls");	printf("\n\n");				//�����Ļ���� 
	memset(definition, 0, sizeof(definition));	//����definition���� 
	def_cnt = 0;	//����def_cnt 
	printf("�û����ã���ӭʹ�ô˳���\n");
	printf("�����򴴽���Ϊ	�����2107��	�����\n\n"); 
	printf("\nPS���˳�������ͬʱ����10��������������������%d��������\n",BiTrees.length);
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. �����µĶ�����		2. ���ٶ�����\n");
	printf("    	  3. ��ն�����			4. �������п�\n");
	printf("    	  5. ����������		6. ���ҽ��	\n");
	printf("    	  7. ��㸳ֵ			8. ��ȡ�ֵܽ��	\n");
	printf("    	  9. ������			10. ɾ�����\n");
	printf("    	  11. ǰ�����			12. �������\n");
	printf("    	  13. �������			14. �������\n");
	printf("    	  15. �����·����		16. �����������\n"); 
	printf("    	  17. ��ת������		18. �������ļ���д\n"); 
	printf("    	  0. �˳�\n\n");
	printf("ע�⣺�����Ա��е�����ӦȫΪ���ͣ�\n");
	printf("-------------------------------------------------\n");
	if(op < 0 || op > 18)	printf("    �������������ѡ����Ĳ���[0~18]:");
	else	printf("    ��ѡ����Ĳ���[0~18]:");
	if(!scanf("%d",&op))	op = 100;
	if (op != 1 && BiTrees.length && op != 0){		//1��������������0���˳�ϵͳ 
		printf("�������㵱ǰӵ�еĶ���������������У���\n");
		for(int i = 0; i < BiTrees.length; i++){
			printf("%s ",BiTrees.elem[i].name);
		}
		if(op != 2){	//2�����ٶ���������1֮��Ĳ�������������ж����������Ա��ѯ����1��2֮��Ĳ�����������Ҫ�����Ķ������� 
			fflush(stdin);		//��ֹ�������ָ������Ļس��������������ƵĲ���ֱ�Ӷ��� 
			memset(name_target, 0, sizeof(name_target));	//���ô洢���������������� 
			name_tarpos = 0;	flag = 0; 		//flag������¼����Ķ����������Ƿ�����ڶ��������� 
			printf("\n����������Ҫ���д˲����Ķ��������ƣ�");
			for(char c; ((c = getchar()) != ' ' && c != '\n') && name_tarpos < 29; name_tarpos++){  //Ϊ�˱�֤���Ա��������30���ַ�֮�ڣ�������ַ������� 
				name_target[name_tarpos] = c;
			}
		}
	} 
	switch(op){
		case 1:{//�½������� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			int num, data, lengthi;
			char name_str[30];
			if(BiTrees.length == 10){
				printf("���������������޷������µĶ�������\n");
				printf("�밴�س�����������\n");getchar();
				break; 
			}
			printf("����������Ҫ�½��Ķ�������������ע�⣺�㵱ǰ�������½�%d������������", 10 - BiTrees.length);
renew1_1:
			while(!scanf("%d",&num)){
				printf("�����������������һ�����֣�");
				fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
			} 
			if(num > 10-BiTrees.length || num < 0){
				printf("�������������������������½�������");
				goto renew1_1;
			} 
			for(int i = 0; i < num; i++){
				fflush(stdin);		//Ϊ�˷�ֹ��������һ�����е�����ʱ��������ݶ���һ�����������ɸ��� 
				memset(name_str,0,sizeof(name_str));	//������ʱ�洢���������ֵı��� 
				printf("�������%d��������������(ע�⣺�������30���ַ����Ҳ��ɰ����ո񣬶�������ݽ��ᱻ����)��",i+1);
				int name_strpos = 0;
				for(char c; ((c = getchar()) != ' ' && c != '\n') && name_strpos < 29; name_strpos++){  //Ϊ�˱�֤��������������30���ַ�֮�ڣ�������ַ������� 
					name_str[name_strpos] = c;
				} 
				name_str[name_strpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
renew1_2:
				fflush(stdin);	//����������������������������ʱ������ַ��Խ����������ݲ������� 
				memset(definition, 0, sizeof(definition));	//��ִ����goto renew1_2��һ��䣬��Ҫ����definition���� 
				def_cnt = 0;
				printf("��������������������Ĺؼ��֣�ֻ��Ϊ���֣������ݣ��ַ�����20�ַ����ڣ�,����-1 null������");
				do {
					if(scanf("%d",&definition[def_cnt].key) != 1){
						printf("�����ʽ�������������룡\n"); 
						goto renew1_2;
					}
					scanf("%s", definition[def_cnt].others);
				} while (definition[def_cnt++].key != -1);
				def_cnt = 0;
				if(CreateBiTree(BiTrees.elem[BiTrees.length].T, definition) == OK){
					printf("��%d�������������ɹ���\n",i+1);
				} 
				else{
					printf("��%d������������ʧ�ܣ�����ؼ����Ƿ��ظ���\n",i+1); 
					continue; 
				}
				strcpy(BiTrees.elem[BiTrees.length].name, name_str); 
				BiTrees.length++;		//�������һ�������������������ȼ�һ 
			}//end of for�����������õ�ѭ���� 
			fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()�������������  
			printf("\n��������ɣ�����������ӵ�еĶ�������\n\n");
			for(int k = 0; k < BiTrees.length; k++){
				printf("������%d��%s \n",k+1, BiTrees.elem[k].name);
    			printf("-----------all elements -----------------------\n");
    			printf("���������");
    			PreOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
				printf("���������"); 
				InOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
				printf("------------------ end ------------------------\n\n");
			} 
			printf("�밴�س�����������\n");getchar();
			break;}
		 
		case 2:{//���ٶ����� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				int num = 0;	char name_del[30];
renew2:
				printf("\n����������Ҫɾ���Ķ�������������\n");
				while(!scanf("%d",&num)){
					printf("����������������֣�");
					fflush(stdin);		 
				}
				if(num < 0 || num > BiTrees.length){
					printf("��������㵱ǰ������ɾ��%d����������\n", BiTrees.length);
					goto renew2;
				}
				getchar();		//��ȡ�س� 
				for(int i = 0; i < num; i++){
					printf("�������%d������Ҫɾ���Ķ����������֣�ÿ��������һ�����֣���������ݽ��ᱻ���ԣ���",i+1);
					memset(name_del, 0, sizeof(name_del)); 
					int name_delpos = 0;
					for(char c; ((c = getchar()) != ' ' && c != '\n') && name_delpos < 29; name_delpos++){  //Ϊ�˱�֤��������������30���ַ�֮�ڣ�������ַ������� 
						name_del[name_delpos] = c;
					} 
					name_del[name_delpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
					if(DestroyBiTree(BiTrees, name_del) == OK){
						printf("�ѳɹ����ٴ˶�������\n");
						continue; 
					}
					else	printf("�˶����������ڣ�\n");
				}
				printf("���ٶ�������������ɣ��㵱ǰ�������¶�������\n");	//ע�����ٶ������� BiTrees.length-- ��һ���ں�����ִ�� 
				for(int k = 0; k < BiTrees.length; k++){
					printf("������%d��%s \n",k+1, BiTrees.elem[k].name);
    				printf("-----------all elements -----------------------\n");
    				printf("���������");
    				PreOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
					printf("���������"); 
					InOrderTraverse(BiTrees.elem[k].T, visit);		printf("\n");
					printf("------------------ end ------------------------\n\n");
				} 
			}//end of else  
			printf("�밴�س�������");getchar();
			break;}
		 
		case 3:{//��ն����� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						ClearBiTree(BiTrees.elem[i].T);
						printf("�ѳɹ���մ˶�������\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("���ʧ�ܣ��˶����������ڣ�\n");
			}   
			printf("�밴�س�������");getchar();
			break;}
		 
		case 4:{//�������п� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						if(BiTreeEmpty(BiTrees.elem[i].T) == TRUE)	printf("�˶�����Ϊ�գ�\n");
						else	printf("�˶�������Ϊ�գ�\n"); 
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 5:{//�����		
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
		 	if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("�˶����������Ϊ��%d\n",BiTreeDepth(BiTrees.elem[i].T));
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 6:{//���ҽ�� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target6 = 0;
						printf("������������ҵĽ��Ĺؼ��֣������ش˽���е����ݣ�\n"); 
						while(scanf("%d",&target6) != 1){
							printf("���벻�Ϸ������������룺");
							fflush(stdin);	//������һ���ֱ�ӵ�����ѭ�� 
						}
						fflush(stdin);		//��ֹ����getcharֱ�Ӷ���ǰ�����Ļس� 
						BiTree tem = LocateNode(BiTrees.elem[i].T, target6);
						if(!tem)	printf("����ʧ�ܣ��˽�㲻���ڣ�\n"); 
						else	printf("�ؼ���Ϊ%d�Ľ��洢�������ǣ�%s\n",tem->data.key, tem->data.others); 
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 7:{//��㸳ֵ 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						TElemType newdot7;
						int target7 = 0;
renew7:
						fflush(stdin); 		//ִ��goto renew7����Ҫ��������� 
						printf("�������������븳ֵ�Ľ��Ĺؼ��֣��µĹؼ��֣�������ݣ�\n"); 
						if(scanf("%d %d",&target7, &newdot7.key) != 2){
							printf("���벻�Ϸ������������룡\n");
							goto renew7;
						}
						scanf("%s",newdot7.others);	
						fflush(stdin);		//��ֹ����getcharֱ�Ӷ���ǰ�����Ļس� 
						if(Assign(BiTrees.elem[i].T, target7, newdot7) == ERROR)	printf("��ֵʧ�ܣ�����Ŀ�����Ƿ���� �Լ� �µĹؼ����Ƿ�����н���ظ���\n"); 
						else{
							printf("��ֵ�ɹ�����ǰ�������������£�\n"); 
							printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
		    				printf("-----------all elements -----------------------\n");
		    				printf("���������");
		    				PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
							printf("���������"); 
							InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
							printf("------------------ end ------------------------\n\n");
						}	
						flag = 1;
						break; 		//����forѭ�� 
					}	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else
			printf("�밴�س�������");getchar();
			break;}
		 
		case 8:{//����ֵܽ�� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target8 = 0;
						printf("������һ�����Ĺؼ��֣������ش˽����ֵܽ���е����ݣ�\n"); 
						while(scanf("%d",&target8) != 1){
							printf("���벻�Ϸ������������룺");
							fflush(stdin);	//������һ���ֱ�ӵ�����ѭ�� 
						}
						fflush(stdin);		//��ֹ����getcharֱ�Ӷ���ǰ�����Ļس� 
						BiTree tem = GetSibling(BiTrees.elem[i].T, target8); 
						if(!tem)	printf("����ʧ�ܣ��˽�㲻���ڻ򲻴����ֵܽ�㣡\n"); 
						else	printf("�ؼ���Ϊ%d�Ľ����ֵܽ��ؼ����ǣ�%d���洢�������ǣ�%s\n",target8, tem->data.key, tem->data.others); 
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}
			printf("�밴�س�������");getchar();
			break;}
		 
		case 9:{//������ 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target9 = 0, mode = 0, flag0;
						TElemType newdot9; 
						printf("��������µĸ�����𣿣�1Ϊ�ǣ���������Ϊ��\n"); 
						scanf("%d",&flag0);
						fflush(stdin);
						if(flag0 != 1){
							printf("����������һ�����Ĺؼ��ֺͲ���λ�ã�0��������ΪĿ��������ӣ�1��������ΪĿ������Һ��ӣ���\n"); 
							while(scanf("%d %d",&target9, &mode) != 2){
								printf("���벻�Ϸ������������룺");
								fflush(stdin);	//������һ���ֱ�ӵ�����ѭ�� 
							}
						}
						fflush(stdin);
						printf("�����������������Ĺؼ��ֺ����ݣ�\n");
						while(scanf("%d",&newdot9.key) != 1){
							printf("���벻�Ϸ������������룺");
							fflush(stdin);		//������һ���ֱ�ӵ�����ѭ��
						}
						scanf("%s",newdot9.others);
						fflush(stdin);			//��ֹ����getcharֱ�Ӷ���ǰ�����Ļس� 
						if(flag0 == 1){			//��������Ϊ���ڵ� 
							if(check3(BiTrees.elem[i].T, newdot9) != OK){	//���Ҫ������Ĺؼ����Ƿ������н��ؼ����ظ� 
								InsertNode(BiTrees.elem[i].T, 0, -1, newdot9); 
								goto next9;
							}
							else	printf("����ʧ�ܣ���������ؼ��������йؼ����ظ���\n");	
						}
						else{					//�������㲻�Ǹ��ڵ� 
							if(InsertNode(BiTrees.elem[i].T, target9, mode, newdot9) == ERROR)	
							printf("����ʧ�ܣ�Ŀ���㲻���ڻ��������ؼ����ظ���\n"); 
							else{
next9:
								printf("����ɹ�����ǰ�������������£�\n"); 
								printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
			    				printf("-----------all elements -----------------------\n");
			    				printf("���������");
			    				PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("���������"); 
								InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("------------------ end ------------------------\n\n");
							}
						}
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 10:{//ɾ����� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int target10 = 0; 
						printf("��������Ҫɾ�����Ĺؼ��֣�\n"); 
						while(scanf("%d",&target10) != 1){
							printf("���벻�Ϸ������������룺");
							fflush(stdin);		//������һ���ֱ�ӵ�����ѭ�� 
						}
						fflush(stdin);			//��ֹ����getcharֱ�Ӷ���ǰ�����Ļس� 
						if(target10 == BiTrees.elem[i].T->data.key){		//�����ɾ������Ǹ��ڵ㣬ֱ���������������ɾ������  
				            if(!BiTrees.elem[i].T->lchild && !BiTrees.elem[i].T->rchild){    	//���Ķ�Ϊ0
				                free(BiTrees.elem[i].T);
				                BiTrees.elem[i].T = NULL;
				            }
				            else if(BiTrees.elem[i].T->lchild && BiTrees.elem[i].T->rchild){     //���Ķ�Ϊ2
				                BiTree tem = BiTrees.elem[i].T;
				                BiTrees.elem[i].T = reset(BiTrees.elem[i].T->lchild, BiTrees.elem[i].T->rchild);
				                free(tem);
				            }
				            else{       		//���Ķ�Ϊ1
				            	BiTree tem = BiTrees.elem[i].T;
				                if(BiTrees.elem[i].T->lchild)	BiTrees.elem[i].T = BiTrees.elem[i].T->lchild;
				                else	BiTrees.elem[i].T = BiTrees.elem[i].T->rchild;
				                free(tem);
				            }
				            goto next10;
						} 
						else{
							if(DeleteNode(BiTrees.elem[i].T, target10) == ERROR)	
								printf("ɾ��ʧ�ܣ�Ŀ���㲻���ڣ�\n"); 
							else{
next10:
								printf("ɾ���ɹ�����ǰ�������������£�\n"); 
								printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
			    				printf("-----------all elements -----------------------\n");
			    				printf("���������");
			    				PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("���������"); 
								InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("------------------ end ------------------------\n\n");
							}
						} 
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 11:{//������� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 	
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("�˶������������£�\n"); 
						printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("���������");
		    			PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 12:{//������� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("�˶������������£�\n"); 
						printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("���������");
		    			InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 13:{//������� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("�˶������������£�\n"); 
						printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("���������");
		    			PostOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
	   
		case 14:{
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("�˶������������£�\n"); 
						printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
		    			printf("-----------all elements -----------------------\n");
		    			printf("���������");
		    			LevelOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
	   		break;}
		
		case 15:{//����ڵ㵽Ҷ�ӽ������·���� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 	
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						printf("�˹��ܽ����ظ���㵽Ҷ�ӽ������·���ͣ����س��Լ���\n"); 
						getchar();
						printf("���������·����Ϊ��%d\n",MaxPathSum(BiTrees.elem[i].T));
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
		
		case 16:{//���������������� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						int e1, e2;
						printf("�������������Ĺؼ��֣���������������������������ȣ� \n");
						while(scanf("%d %d",&e1,&e2) != 2){
							printf("���벻�Ϸ������������������ؼ��֣�");
							fflush(stdin);		//������һ���ֱ�ӵ���while��ѭ�� 
						}
						fflush(stdin);
						BiTree ancestor = LowestCommonAncestor(BiTrees.elem[i].T, e1, e2);
						if(ancestor)	printf("����������������������ǣ��ؼ��֣�%d ���ݣ�%s\n",ancestor->data.key, ancestor->data.others); 
						else	 printf("����ʧ�ܣ���ȷ������������Ƿ�����ڣ�\n"); 
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}
		
		case 17:{
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
	   		if(!BiTrees.length)	printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						InvertTree(BiTrees.elem[i].T); 
						printf("��ת��˶������������£�\n"); 
						printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
			    		printf("-----------all elements -----------------------\n");
			    		printf("���������");
			    		PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("���������"); 
						InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
						printf("------------------ end ------------------------\n\n");
						flag = 1;
						break; 		//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
			printf("�밴�س�������");getchar();
			break;}

		case 18:{
			fflush(stdin); 
			char FileName[30];
			strcpy(FileName, "test.txt");
			printf("�˹��ܽ���Ѷ����������е�����д���ⲿ��test.txt�ļ��У����޴��ļ�����������ļ�\n");
			printf("�밴�س����Կ�ʼ");
			getchar();
			if(!BiTrees.length)		printf("�㻹û�ж����������ȴ���һ����������\n");
			else{
				for(int i = 0; i < BiTrees.length; i++){
					if(strcmp(BiTrees.elem[i].name, name_target) == 0){
						if(SaveBiTree(BiTrees.elem[i].T, FileName) == ERROR) ;
						else{
							printf("�ѳɹ����������е����ݵ����ⲿ�ļ�����鿴�ⲿ�ļ�\n");
							printf("���س����Լ���\n");
							getchar();
							ClearBiTree(BiTrees.elem[i].T);
							printf("�����ٶ�����...\n");
							printf("���ڴ��ⲿ�ļ��������ݵ�������...\n");
							if(LoadBiTree(BiTrees.elem[i].T, FileName) == ERROR)		printf("�ⲿ�ļ���ʧ����ֹ������");
							else{
								printf("�ѵ�����ɣ����س��������������������\n");
								getchar();
								printf("�˶������������£�\n"); 
								printf("������%d��%s \n",i+1, BiTrees.elem[i].name);
				    			printf("-----------all elements -----------------------\n");
				    			printf("���������");
				    			PreOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("���������"); 
								InOrderTraverse(BiTrees.elem[i].T, visit);		printf("\n");
								printf("------------------ end ------------------------\n\n");
							}
						}
						flag = 1;
						break;	//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("�˶����������ڣ�\n"); 
			}//end of else 
	   		printf("�밴�س�������\n");getchar();
			break;}
			
		case 0:break;
	}//end of switch
}//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
for(int end = 0; end < BiTrees.length; end++){		//����������ͷ����ж������Ŀռ� 
	ClearBiTree(BiTrees.elem[end].T);
}
return 0;
}//end of main()

int check(TElemType definition[], int count){
//ר�����ڼ��definition�����еĹؼ����Ƿ����ظ���Ϊ�˱�֤�������Ĺؼ���Ψһ�ԣ� 
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
//���ڼ��value�йؼ����Ƿ��뱻��ֵ�������Ľ��Ĺؼ�����ͬ��ʹ���ؼ��ֱ���Ψһ�ԣ���return OK��˵�����ظ� 
//���ڽ�㸳ֵ������ 
    if(!T)  return ERROR;
    if((T->data.key == value.key) && (T->data.key != e)){
        return OK;
    }
    if(check2(T->lchild, e, value)) return OK;
    else    return check2(T->rchild, e, value);
}

int check3(BiTree &T, TElemType value){
//�����ж�T����һ���Ĺؼ����Ƿ���value�еĹؼ�����ͬ��return OK��˵�����ظ� 
//���ڲ����㹦���� 
	if(!T)  return ERROR;
    if(T->data.key == value.key){
        return OK;
    }
    if(check3(T->lchild, value)) return OK;
    else    return check3(T->rchild, value);
}

BiTree reset(BiTree &L, BiTree &R){     
//����DeleteNode�����У�����ɾ�����Ķ�Ϊ2ʱ�����˽ڵ����������R����Ϊ�������У�L�����ҽ���������
    BiTree originL = L;
    while(L->rchild != NULL)    L = L->rchild;
    L->rchild = R;
    return originL;
}

status CreateBiTree(BiTree &T,TElemType definition[]){
//���ݴ���֦�Ķ����������������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR��
    if(check(definition, 0) == 0)   return ERROR;
    if(definition[def_cnt].key == 0){
        T = NULL;
        def_cnt++;
    }
    else{
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data.key = definition[def_cnt].key;		//��ֵ 
        strcpy(T->data.others, definition[def_cnt].others);		//��ֵ 
        def_cnt++;
        CreateBiTree(T->lchild, definition);		//�ݹ飬���������� 
        CreateBiTree(T->rchild, definition);		//�ݹ飬���������� 
    }
    return OK;
}

status DestroyBiTree(BITREES &BiTrees,char TreeName[]){
// BiTrees��ɾ��һ������ΪTreeName�Ķ����� 
	if(BiTrees.length == 0)	return ERROR;
	int j;
    for(int i = 0; i < BiTrees.length; i++){
        if(strcmp(BiTrees.elem[i].name , TreeName) == 0 && i != BiTrees.length - 1){
            ClearBiTree(BiTrees.elem[i].T);
            BiTrees.length--; //���ٶ������󣬶����������������һ
            BiTrees.elem[i].T = (struct BiTNode* )malloc(sizeof(BiTree));   //����Ϊɾ���Ķ���������ռ䣬���ں������������ƶ�����

            for( j = i ; j < BiTrees.length ; j++){    //���������ƶ�
            	strcpy(BiTrees.elem[j].name , BiTrees.elem[j+1].name);  //���������ֵ��ƶ�
				BiTrees.elem[j].T = BiTrees.elem[j+1].T;	//���������ݵ��ƶ� 
            }
            j++;
            BiTrees.elem[j].T = NULL;   //�ÿ��ƶ���֮����ĩ�˵�Tָ�� 
            memset(BiTrees.elem[j].name , 0 , sizeof(BiTrees.elem[j].name));
            return OK;
        }
        else if(strcmp(BiTrees.elem[i].name , TreeName) == 0 && i == BiTrees.length - 1){	//���ɾ���Ķ������������ڶ�β 
        	ClearBiTree(BiTrees.elem[i].T);
        	BiTrees.length--; 
        	memset(BiTrees.elem[i].name , 0 , sizeof(BiTrees.elem[i].name));
        	return OK;
		}
    }
    return ERROR;
}

status ClearBiTree(BiTree &T){
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
    if(!T)  return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status BiTreeEmpty(BiTree T){
//�ж϶������Ƿ�Ϊ��������Ϊ��������TRUE�����򷵻�FALSE	
	if(T != NULL)	return FALSE;
	else	return TRUE;
}

status BiTreeDepth(BiTree T){
//�������T�����
    if(!T)  return 0;  
    int left = 0, right = 0;
    // if(!T->lchild && !T->rchild){   //���ҵ���Ҷ������Ҷ��ʼ���Ϸ������
    //     return 1;
    // }
    left = BiTreeDepth(T->lchild) + 1;
    right = BiTreeDepth(T->rchild) + 1;
    return left > right ? left : right;
}

BiTNode* LocateNode(BiTree T,KeyType e){
//���ҽ�㣬���ش˽��ָ�� 
    if(!T)  return NULL;
    BiTree tem;
    if(T->data.key == e)    return T;
    tem = LocateNode(T->lchild, e);     //ֻҪ��ǰ�ڵ㲻��Ŀ�꣬����������
    if(tem != NULL) return tem;
    tem = LocateNode(T->rchild, e);     //����������
    if(tem != NULL) return tem;
    return NULL;
/*�ݹ鷵�ص���ʱ�������֮ǰ�ĵݹ����ҵ��˷��ϵĽڵ㣬��ʱtem��ΪNULL������Է��ش˽ڵ㣬����֮ǰ�ĵݹ���û���ҵ����ϵĽڵ㣬
��tem��ΪNULL����Ӹ��ڵ㿪ʼ��������������������δ�������򷵻�NULL�������������Ѿ�ȫ��������ϣ���*/
}

status Assign(BiTree &T,KeyType e,TElemType value){
//ʵ�ֽ�㸳ֵ����ֵ�ɹ�����OK����ֵʧ�ܷ���ERROR 
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
//ʵ�ֻ���ֵܽ��
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
//������
    if(check3(T, c)) return ERROR;
    if(!T)  return ERROR;
    if(LR == -1){		//������Ϊͷ��� 
        BiTree newtree = (BiTree)malloc(sizeof(BiTNode));
        newtree->data.key = c.key;
        strcpy(newtree->data.others, c.others);
        newtree->rchild = T;
        newtree->lchild = NULL;
        T = newtree;
        return OK;
    }
    if(T->data.key == e){
        if(LR == 0){  		//��Ϊ��ǰT�������ӽ��
            BiTree indot = (BiTree)malloc(sizeof(BiTNode));
            indot->data.key = c.key;
            strcpy(indot->data.others, c.others);
            indot->rchild = T->lchild;
            indot->lchild = NULL;
            T->lchild = indot;
        }
        else if(LR == 1){  //��Ϊ��ǰT�����Һ��ӽ��
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
//ɾ����㡣����Ϊ�˺�����T->lchild��T->rchild����ʾ��ɾ����㣬�ʶԸ��ڵ�����з������������У� 
{
    if(!T)  return ERROR;
    if(T->lchild != NULL){      
        if(T->lchild->data.key == e){  //T->lchildΪ��ɾ�����
            if(!T->lchild->lchild && !T->lchild->rchild){    //ɾ�����Ķ�Ϊ0
                free(T->lchild);
                T->lchild = NULL;
            }
            else if(T->lchild->lchild && T->lchild->rchild){     //ɾ�����Ķ�Ϊ2
                BiTree tem = T->lchild;
                T->lchild = reset(T->lchild->lchild, T->lchild->rchild);
                free(tem);
            }
            else{       //ɾ���ڵ�Ķ�Ϊ1
            	BiTree tem = T->lchild;
                if(T->lchild->lchild){	//�����ɾ���������Ӳ�Ϊ�� 
                    T->lchild = T->lchild->lchild;
                }
                else{	//�����ɾ�������Һ��Ӳ�Ϊ�� 
                    T->lchild = T->lchild->rchild;
                }
                free(tem);
            }
            return OK;    
        }
    }
    if(T->rchild != NULL){		 
        if(T->rchild->data.key == e){   //T->rchildΪ��ɾ�����
            if(!T->rchild->lchild && !T->rchild->rchild){		//ɾ�����Ķ�Ϊ0
                free(T->rchild);
                T->rchild = NULL;
            }
            else if(T->rchild->lchild && T->rchild->rchild){     //ɾ�����Ķ�Ϊ2
                BiTree tem = T->rchild;
                T->rchild = reset(T->rchild->lchild, T->rchild->rchild);
                free(tem);
            }
            else{       //ɾ���ڵ�Ķ�Ϊ1
            	BiTree tem = T->rchild;
                if(T->rchild->lchild){	//�����ɾ���������Ӳ�Ϊ��                    
                    T->rchild = T->rchild->lchild;   
                }
                else{	//�����ɾ�������Һ��Ӳ�Ϊ�� 
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
//�������������T(�ǵݹ�ʵ��)
    BiTree stack[100], p;       
    int top = 0;
    if(T != NULL){
        stack[top++] = T;
        while(top){
            p = stack[--top];   //pָ��ջ��Ԫ�أ��������
            visit(p);
            if(p->rchild != NULL)   stack[top++] = p->rchild;   //��������ջ
            if(p->lchild != NULL)   stack[top++] = p->lchild;   //��������ջ
        }
    }
    return OK;
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree)){
//�������������T
    if(!T)  return OK;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree)){
//�������������T
    if(!T)  return OK;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree)){
//�������������T�����ö����Ƚ��ȳ������ԣ� 
    BiTree queue[100], p;   //������ʱָ��p���ƶ���������������ڵ�
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
//�����Ҷ�ӽ������·����
	if(!T)	return 0;
	if(!T->lchild && !T->rchild)	return T->data.key;		//�����Ҷ�ӽ�㣬ֱ�ӷ���Ҷ�ӵ�Ȩֵ 
	int left = MaxPathSum(T->lchild); 
	int right = MaxPathSum(T->rchild);
	
	return left > right ? (left + T->data.key) : (right + T->data.key);
}

BiTree LowestCommonAncestor(BiTree T, int e1, int e2){
//Ѱ�������������
/*��һ��������Ľ�㣬ʹe1����e2���ͬʱ��������������*/ 
	if(!T || (T->data.key == e1) || (T->data.key == e2))	return T;
	BiTree left = LowestCommonAncestor(T->lchild, e1, e2);
	BiTree right = LowestCommonAncestor(T->rchild, e1, e2);
	if(!left && !right)	return NULL;		//˵����ǰ���Ϊ����������£�������������û��Ŀ���� 
	else if(!left && right)	return right;	//˵����ǰ���Ϊ����������£�����������Ŀ���㣬������û�� 
	else if(left && !right)	return left;	//˵����ǰ���Ϊ����������£�����������Ŀ���㣬������û�� 
	return T;
	
}

status InvertTree(BiTree &T){
//ʵ�ֶ���������������������������������ת�� 
	BiTree queue[100], p, tem;   //������ʱָ��p���ƶ���������������ڵ�
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
//���������Ľ������д�뵽�ļ�FileName��
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
            p = stack[--top];   //pָ��ջ��Ԫ�أ��������
            if(p != NULL)   fprintf(fp,"%d %s\n",p->data.key, p->data.others);
            else{
                fprintf(fp,"%d %s\n",0,"NULL");
                continue;
            }        
            if(p->rchild != NULL)   stack[top++] = p->rchild;   //��������ջ
            else    stack[top++] = NULL;
            if(p->lchild != NULL)   stack[top++] = p->lchild;   //��������ջ
            else    stack[top++] = NULL;
        }
        fprintf(fp,"%d %s\n",0,"NULL");
        fprintf(fp,"%d %s\n",-1,"NULL");
    }    
    fclose(fp);
    return OK;
}

status LoadBiTree(BiTree &T,  char FileName[]){
//�����ļ�FileName�Ľ�����ݣ�����������
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
//���������жԽ��Ĳ��� 
    printf(" %d,%s",T->data.key,T->data.others);
}
