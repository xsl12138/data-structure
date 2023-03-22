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
} VertexType; //�������Ͷ���

typedef struct ArcNode {     //�������Ͷ���
   	int adjvex;              //����λ�ñ�� 
    struct ArcNode *nextarc; //��һ������ָ��
} ArcNode;

typedef struct VNode{		//ͷ��㼰���������Ͷ���
   	VertexType data;       	//������Ϣ
    ArcNode *firstarc;      //ָ���һ����
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  			//�ڽӱ�����Ͷ���
    AdjList vertices;     	//ͷ�������
    int vexnum,arcnum;   	//������������
    GraphKind  kind;        //ͼ������
} ALGraph;

typedef struct{ 			//ͼ�ļ������Ͷ���  
	struct { 
		char name[30];  
		ALGraph G;      
	}elem[10];  
    int length;				//������¼�Ѿ��е�ͼ����  
} GRAPHS;
GRAPHS Graphs;				//ͼ���ϵĶ���Graphs
int pos_dfs = 0; 			//dfs��ʹ�ã���¼�ݹ��Ӧ������������ĸ�λ�ε�����
int flag_dfs[20] = {0};		//dfs��ʹ�ã� �ж϶�Ӧλ��ĵ��Ƿ��Ѿ������ 
int ans_connect = 1;		//���ڼ�¼��ͨ������������һ���ǿ�ͼ������һ����ͨ������ 
/*-----page 19 on textbook ---------*/
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);		//�½� 
status RemoveGraph(GRAPHS &Graphs,char GraphName[]);				//��ͼ�����Ƴ�ָ�����ֵ�ͼ 
status DestroyGraph(ALGraph &G);									//����һ��ͼ 
status LocateVex(ALGraph G,KeyType u); 								//���Ҷ��� 
status PutVex(ALGraph &G,KeyType u,VertexType value);				//���㸳ֵ 
status FirstAdjVex(ALGraph G,KeyType u);							//��õ�һ�ڽӵ� 
status NextAdjVex(ALGraph G,KeyType v,KeyType w);					//�����һ�ڽӵ� 
status InsertVex(ALGraph &G,VertexType v);							//���붥�� 
status DeleteVex(ALGraph &G,KeyType v);								//ɾ������ 
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));			//������ȱ��� 
status InsertArc(ALGraph &G,KeyType v,KeyType w);					//���뻡	 
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));			//������ȱ��� 
status DeleteArc(ALGraph &G,KeyType v,KeyType w);					//ɾ���� 
status SaveGraph(ALGraph G, char FileName[]);						//�洢�ļ� 
status LoadGraph(ALGraph &G, char FileName[]);						//��ȡ�ļ�
status ShortestPathLength(ALGraph &G, KeyType v, KeyType w);		//��������·��
status ConnectedComponentsNums(ALGraph &G, int judge);							//��ͼ����ͨ�������� 
status VerticesSetLessThanK(ALGraph &G, KeyType v, KeyType k);		//����С��k�Ķ��㼯�� 
int check1(VertexType V[]); 						//����ͼʱ�������ж�V�������Ƿ����ظ��ؼ���
void visit(VertexType v); 
/*--------------------------------------------*/
int main(void){
int op=1;
VertexType V[30];				//����ͼʱ���ڼ�¼������� 
KeyType VR[100][2];				//����ͼʱ���ڼ�¼�ߵ����� 
Graphs.length = 0;				//��ʼ��ͼ������� 
char name_target[30];			//���������ڼ�¼ÿ�������Ķ���ͼ���� 
int name_tarpos = 0, flag = 0;	//flag�����жϲ�������治������ͼ���� 	
while(op){
	fflush(stdin);	//���������������Ƿ�ֹ��һ�β��������󣬡����س��Լ��� ��ʱ���������ݶ�Ӱ�챾�β���
	system("cls");	printf("\n\n");				//�����Ļ���� 
	printf("�û����ã���ӭʹ�ô˳���\n");
	printf("�����򴴽���Ϊ	�����2107��	�����\n\n"); 
	printf("\nPS���˳�������ͬʱ����10��ͼ������������%d��ͼ\n",Graphs.length);
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. �����µ�ͼ			2. ����ͼ\n");
	printf("    	  3. ���Ҷ���			4. ���㸳ֵ\n");
	printf("    	  5. ��õ�һ�ڽӵ�		6. �����һ�ڽӵ�	\n");
	printf("    	  7. ���붥��			8. ɾ������	\n");
	printf("    	  9. ������ȱ���		10. ���뻡\n");
	printf("    	  11. ������ȱ���		12. ɾ����\n");
	printf("    	  13. ͼ�ļ���д		14. ��������·��\n");
	printf("    	  15. ͼ����ͨ����		16. ����С��k�Ķ��㼯��\n"); 
	printf("    	  0. �˳�\n\n");
	printf("ע�⣺�����Ա��е�����ӦȫΪ���ͣ�\n");
	printf("-------------------------------------------------\n");
	if(op < 0 || op > 18)	printf("    �������������ѡ����Ĳ���[0~16]:");
	else	printf("    ��ѡ����Ĳ���[0~16]:");
	if(!scanf("%d",&op))	op = 100;
	if (op != 1 && Graphs.length && op != 0){		//1��������������0���˳�ϵͳ 
		printf("�������㵱ǰӵ�е�ͼ����������У���\n");
		for(int i = 0; i < Graphs.length; i++){
			printf("%s ",Graphs.elem[i].name);
		}
		if(op != 2){	//2������ͼ����1֮��Ĳ��������������ͼ�����Ա��ѯ����1��2֮��Ĳ�����������Ҫ������ͼ�� 
			fflush(stdin);		//��ֹ�������ָ������Ļس��������������ƵĲ���ֱ�Ӷ��� 
			memset(name_target, 0, sizeof(name_target));	//���ô洢���������������� 
			name_tarpos = 0;	flag = 0; 		//flag������¼�����ͼ�����Ƿ�����ڶ��������� 
			printf("\n����������Ҫ���д˲�����ͼ���ƣ�");
			for(char c; ((c = getchar()) != ' ' && c != '\n') && name_tarpos < 29; name_tarpos++){  //Ϊ�˱�֤���Ա��������30���ַ�֮�ڣ�������ַ������� 
				name_target[name_tarpos] = c;
			}
		}
	} 
	switch(op){
		case 1:{//�½�ͼ 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			int num, i_v = 0, i_arc = 0;		//i_v, i_arc�ֱ����ڴ洢�������V�ʹ洢�ߵ�����VR�ļ��� 
			char name_str[30];
			if(Graphs.length == 10){
				printf("ͼ���������޷������µ�ͼ��\n");
				printf("�밴�س�����������\n");getchar();
				break; 
			}
			printf("����������Ҫ�½���ͼ��������ע�⣺�㵱ǰ�������½�%d��ͼ����", 10 - Graphs.length);
renew1_1:
			while(!scanf("%d",&num)){
				printf("�����������������һ�����֣�");
				fflush(stdin);	//������һ������Ĺ������ݶԱ���������ɸ��� 
			} 
			if(num > 10-Graphs.length || num < 0){
				printf("�������������������������½�������");
				goto renew1_1;
			} 
			for(int i = 0; i < num; i++){
				fflush(stdin);		//Ϊ�˷�ֹ��������һ�����е�����ʱ��������ݶ���һ�����������ɸ��� 
				memset(name_str,0,sizeof(name_str));	//������ʱ�洢���������ֵı��� 
				printf("�������%d��ͼ������(ע�⣺�������30���ַ����Ҳ��ɰ����ո񣬶�������ݽ��ᱻ����)��",i+1);
				int name_strpos = 0;
				for(char c; ((c = getchar()) != ' ' && c != '\n') && name_strpos < 29; name_strpos++){  //Ϊ�˱�֤��������������30���ַ�֮�ڣ�������ַ������� 
					name_str[name_strpos] = c;
				} 
				name_str[name_strpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
renew1_2:
				fflush(stdin);	//����������������������������ʱ������ַ��Խ����������ݲ������� 
				memset(V, 0, sizeof(V));	//��ִ����goto renew1_2��һ��䣬��Ҫ����V��VR���� ��ÿ��ѡ���½�ͼʱ��ҲӦ���ã� 
				i_v = 0;
				printf("����������ͼ�����Ĺؼ��֣�ֻ��Ϊ���֣������ݣ��ַ�����20�ַ����ڣ�,����-1 null������");
				do {
					if(scanf("%d",&V[i_v].key) != 1){
						printf("�����ʽ�������������룡\n"); 
						goto renew1_2;
					}
					scanf("%s", V[i_v].others);
				} while (V[i_v++].key != -1);
renew1_3:			
				memset(VR, 0, sizeof(VR));	//��ִ����goto renew1_3��һ��䣬��Ҫ����V��VR���� ��ÿ��ѡ���½�ͼʱ��ҲӦ���ã�
				i_arc = 0;
				printf("������������ߵ���β���ؼ��֣�����-1 -1������");
				do {
    				if(scanf("%d %d",&VR[i_arc][0], &VR[i_arc][1]) != 2){
    					printf("�����ʽ�������������룡\n");
    					goto renew1_3;
					}
   				} while(VR[i_arc++][0]!=-1);
				if(CreateGraph(Graphs.elem[Graphs.length].G, V, VR) == OK){
					printf("��%d��ͼ�����ɹ���\n",i+1);
				} 
				else{
					printf("��%d��ͼ����ʧ�ܣ�����ؼ����Ƿ��ظ��Լ����������Ƿ����\n",i+1); 
					continue; 
				}
				strcpy(Graphs.elem[Graphs.length].name, name_str); 
				Graphs.length++;		//�������һ�������������������ȼ�һ 
			}//end of for�����������õ�ѭ���� 
			fflush(stdin);		//Ϊ�˷�ֹ���밴�س������� ��֮���getchar()�������������  
			printf("\n��������ɣ�����������ӵ�е�ͼ��\n\n");
			for(int k = 0; k < Graphs.length; k++){
				printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
			printf("�밴�س�����������\n");getchar();
			break;}
		 
		case 2:{//����ͼ 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				int num = 0;	char name_del[30];
renew2:
				printf("\n����������Ҫɾ����ͼ��������\n");
				while(!scanf("%d",&num)){
					printf("����������������֣�");
					fflush(stdin);		 
				}
				if(num < 0 || num > Graphs.length){
					printf("��������㵱ǰ������ɾ��%d��ͼ��\n",Graphs.length);
					goto renew2;
				}
				getchar();		//��ȡ�س� 
				for(int i = 0; i < num; i++){
					printf("�������%d������Ҫɾ����ͼ�����֣�ÿ��������һ�����֣���������ݽ��ᱻ���ԣ���",i+1);
					memset(name_del, 0, sizeof(name_del)); 
					int name_delpos = 0;
					for(char c; ((c = getchar()) != ' ' && c != '\n') && name_delpos < 29; name_delpos++){  //Ϊ�˱�֤ͼ��������30���ַ�֮�ڣ�������ַ������� 
						name_del[name_delpos] = c;
					} 
					name_del[name_delpos] = '\0';	//��Ϊ�ַ����Ľ�β��־ 
					if(RemoveGraph(Graphs, name_del) == OK){
						printf("�ѳɹ����ٴ�ͼ��\n");
						continue; 
					}
					else	printf("��ͼ�����ڣ�\n");
				}
				printf("����ͼ��������ɣ��㵱ǰ��������ͼ��\n");	//ע������ͼ�� Graphs.length-- ��һ���ں�����ִ�� 
				for(int k = 0; k < Graphs.length; k++){
					printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
			printf("�밴�س�������");getchar();
			break;}
		 
		case 3:{//���Ҷ��� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int target3;
						printf("������һ������Ĺؼ��֣������ش˶����λ���Լ����ݣ�\n");
						while(scanf("%d",&target3) != 1){
							printf("������������������룺");
							fflush(stdin);	//������һ��ᵼ����ѭ�� 
						} 
						int res3 = LocateVex(Graphs.elem[i].G, target3);
						if(res3 != ERROR){
							printf("�ؼ���Ϊ%d�Ľ��λ���� %d�������� %s\n",target3, res3, Graphs.elem[i].G.vertices[res3].data.others);
						}
						else	printf("����ʧ�ܣ�Ŀ���㲻���ڣ�\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("����ʧ�ܣ���ͼ�����ڣ�\n");
			}   
			fflush(stdin);
			printf("�밴�س�������");getchar();
			break;}
		 
		case 4:{//��㸳ֵ 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						VertexType value4;	int target4; 
						printf("����������Ŀ�궥��ؼ��֣��µĹؼ��ֺ��µ����ݣ���������ݻᱻ��գ���\n");
						while(scanf("%d %d",&target4, &value4.key) != 2){
							printf("����������������룺");
							fflush(stdin); 
						} 
						scanf("%s",value4.others);
						if(PutVex(Graphs.elem[i].G, target4, value4) == OK){
							printf("���㸳ֵ�ɹ�������ǰͼ�������£�\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
						else	printf("����ʧ�ܣ�Ŀ�궥�㲻���ڻ�ؼ��ִ����ظ���\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 5:{//��õ�һ�ڽӵ�		
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int target5; 
						printf("������Ŀ�궥��ؼ��֣����������ĵ�һ�ڽӵ㣺\n");
						while(scanf("%d",&target5) != 1){
							printf("����������������룺");
							fflush(stdin); 
						} 
						int res5 = FirstAdjVex(Graphs.elem[i].G, target5);
						if(res5 != -1){
							printf("�˽��ĵ�һ�ڽӵ�ؼ���Ϊ %d�������� %s\n",Graphs.elem[i].G.vertices[res5].data.key, Graphs.elem[i].G.vertices[res5].data.others); 
						}
						else	printf("����ʧ�ܣ�Ŀ�궥�㲻���ڣ�\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 6:{//�����һ�ڽӵ� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int tartar6, target6; 
						printf("������������������ؼ���v��w��������v�������w����һ�ڽӵ㣺\n");
						while(scanf("%d %d",&target6, &tartar6) != 2){
							printf("����������������룺");
							fflush(stdin); 
						}
						int res6 = NextAdjVex(Graphs.elem[i].G, target6, tartar6); 
						if(res6 != -1){
							printf("%d ����� %d ����һ�ڽӵ�ؼ���Ϊ %d������Ϊ %s\n",target6, tartar6, Graphs.elem[i].G.vertices[res6].data.key, Graphs.elem[i].G.vertices[res6].data.others);
						}
						else	printf("����ʧ�ܣ�Ŀ�궥�㲻���ڻ򲻴�����һ�ڽӵ㣡\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 7:{//������ 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						VertexType value7; 
						printf("��������������붥��Ĺؼ��ֺ����ݣ�\n");
						while(scanf("%d",&value7.key) != 1){
							printf("����������������룺");
							fflush(stdin); 
						} 
						scanf("%s",value7.others);
						if(InsertVex(Graphs.elem[i].G, value7) == OK){
							printf("���붥��ɹ�������ǰͼ�������£�\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
						else	printf("����ʧ�ܣ��Ѵ������������йؼ����ظ���\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 8:{//ɾ������ 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int target8; 
						printf("�������ɾ������Ĺؼ��֣�ע�⣺��ֻʣ���һ������ʱ�޷�ɾ������\n");
						while(scanf("%d",&target8) != 1){
							printf("����������������룺");
							fflush(stdin); 
						} 
						if(DeleteVex(Graphs.elem[i].G, target8) == OK){
							printf("ɾ������ɹ�������ǰͼ�������£�\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
						else	printf("����ʧ�ܣ���ɾ����㲻���ڻ�ͼ��ֻʣһ�����㣡\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 9:{//������ȱ��� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						printf("������ȱ���������£�\n");
						BFSTraverse(Graphs.elem[i].G, visit); 
						printf("\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 10:{//���뻡 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int v10, w10; 
						printf("����������뻡����β���㣺\n");
						while(scanf("%d %d",&v10, &w10) != 2){
							printf("����������������룺");
							fflush(stdin); 
						} 
						if(v10 == w10){
							printf("������������㲻����ͬ��\n");
							flag = 1;
							break; 
						}
						if(InsertArc(Graphs.elem[i].G, v10, w10) == OK){
							printf("���뻡�ɹ�������ǰͼ�������£�\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
						else	printf("����ʧ�ܣ�����Ķ������ж��㲻���ڻ�������֮���Ѵ��ڱߣ�\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 11:{//������ȱ��� 
	   		fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				memset(flag_dfs, 0, sizeof(flag_dfs));	//DFS�õ�������ȫ�ֱ�����flag_dfs��pos_dfs��ÿ�ν��б���ǰ������ 
				pos_dfs = 0;
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						printf("������ȱ���������£�\n");
						DFSTraverse(Graphs.elem[i].G, visit); 
						printf("\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 12:{//ɾ���� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int v12, w12; 
						printf("�������ɾ��������β���㣺\n");
						while(scanf("%d %d",&v12, &w12) != 2){
							printf("����������������룺");
							fflush(stdin); 
						} 
						if(DeleteArc(Graphs.elem[i].G, v12, w12) == OK){
							printf("ɾ�����ɹ�������ǰͼ�������£�\n");
							for(int k = 0; k < Graphs.length; k++){
								printf("ͼ%d��%s \n",k+1, Graphs.elem[k].name);
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
						else	printf("����ʧ�ܣ�����Ķ������ж��㲻���ڻ�������֮�䲻���ڱߣ�\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		 
		case 13:{//ͼ��д�ļ� 
			fflush(stdin); 
			char FileName[30];
			strcpy(FileName, "test.txt");
			printf("�˹��ܽ����ͼ�����е�����д���ⲿ��test.txt�ļ��У����޴��ļ�����������ļ�\n");
			printf("�밴�س����Կ�ʼ");
			getchar();
			if(!Graphs.length)		printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						if(SaveGraph(Graphs.elem[i].G, FileName) == ERROR) ;
						else{
							printf("�ѳɹ���ͼ�е����ݵ����ⲿ�ļ�����鿴�ⲿ�ļ�\n");
							printf("���س����Լ���\n");
							getchar();
							DestroyGraph(Graphs.elem[i].G);
							printf("������ͼ...\n");
							printf("���ڴ��ⲿ�ļ��������ݵ�ͼ...\n");
							if(LoadGraph(Graphs.elem[i].G, FileName) == ERROR)		printf("�ⲿ�ļ���ʧ����ֹ������");
							else{
								printf("�ѵ�����ɣ����س��������ͼ������\n");
								getchar();
								printf("��ͼ�������£�\n"); 
								printf("ͼ%d��%s \n",i+1, Graphs.elem[i].name);
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
						break;	//����forѭ�� 
					}//end of if	
				}//end of forѭ�� 
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}//end of else 
	   		printf("�밴�س�������\n");getchar();
			break;}
	   
		case 14:{//��������·�� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int v14, w14; 
						printf("��������������Ĺؼ��֣����������߼�����·�����ȣ�\n");
						while(scanf("%d %d",&v14, &w14) != 2){
							printf("����������������룺");
							fflush(stdin); 
						} 
						int res14 = ShortestPathLength(Graphs.elem[i].G, v14, w14);
						if(res14 != -1){
							printf("����������·������Ϊ��%d\n",res14);
						}
						else	printf("����ʧ�ܣ��ж��㲻���ڻ����������ͨ·��\n");
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
	   		break;}
		
		case 15:{//����ͨ�����ĸ��� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				ans_connect = 1;	//����ͨ�����ĺ����õ���ȫ�ֱ�����ans_connect��ÿ�ν��б���ǰ������ 
				memset(flag_dfs, 0, sizeof(flag_dfs));	//DFS�õ�������ȫ�ֱ�����flag_dfs��pos_dfs��ÿ�ν��б���ǰ������ 
				pos_dfs = 0;
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						printf("��ǰͼ���� %d ����ͨ����\n",ConnectedComponentsNums(Graphs.elem[i].G, 1));
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
		
		case 16:{//����С��k�Ķ��㼯�� 
			fflush(stdin);		//�������ָ��ʱ���ܴ��ڵĶ�������� 
			if(!Graphs.length)	printf("�㻹û��ͼ�����ȴ���һ��ͼ��\n");
			else{
				for(int i = 0; i < Graphs.length; i++){
					if(strcmp(Graphs.elem[i].name, name_target) == 0){
						int distance, v16; 
						printf("������Ŀ�궥��ؼ��ֺ��޶����룬�������Ŀ�궥��������޶���Χ�ڵ����ж���ļ��ϣ�\n");
						while(scanf("%d %d",&v16, &distance) != 2){
							printf("����������������룺");
							fflush(stdin); 
						}
						VerticesSetLessThanK(Graphs.elem[i].G, v16, distance);
						flag = 1;
						break; 
					}	
				}
				if(!flag)	printf("��ͼ�����ڣ�\n"); 
			}
			fflush(stdin); 
			printf("�밴�س�������");getchar();
			break;}
				
		case 0:break;
	}//end of switch
}//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
//for(int end = 0; end < Graphs.length; end++){		//����������ͷ����ж������Ŀռ� 
//	ClearBiTree(Graphs.elem[end].T);
//}
return 0;
}//end of main()

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

int check1(VertexType V[]){     //���V�еĹؼ����Ƿ����ظ�
    int flag = 0;
    for(int i = 0; V[i].key != -1; i++){
        for(int j = i+1; V[j].key != -1; j++){
            if((V[i].key == V[j].key) || (strcmp(V[i].others, V[j].others) == 0))
                flag = 1;
                break;
        }
        if(flag)    break;
    }
    if(flag)    return ERROR;   //˵��V���йؼ����ظ�
    return OK;
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]){
//����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
    if(check1(V) == ERROR) return ERROR;	//˵��V���йؼ����ظ� 
    G.vexnum = 0, G.arcnum = 0;
    int cnt = 0;  //����
    int flag = 0; //�ж�һ�����Ƿ��Ѿ������������
    int j1 = 0, j2 = 0;	//adjvex��ֵ�� 
    while(V[cnt].key != -1){      //Ϊ���㸳ֵ
        G.vertices[cnt].data.key = V[cnt].key;
        strcpy(G.vertices[cnt].data.others, V[cnt].others);
        G.vertices[cnt].firstarc = NULL;
        G.vexnum++;
        cnt++;
    }
    if(G.vexnum > 20 || G.vexnum == 0){     //���������Ѿ��ﵽ���ֵ20���ܽ���whileѭ����˵��V�еĵ�һ������20������������Ϊ0˵��V�и���û�����붥�㣬�޷�����
            memset(G.vertices, 0, sizeof(G.vertices));
            return ERROR;
    }
    for(int i = 0; VR[i][0] != -1; i++){
    	flag = 0;
        for(int j = 0; j < G.vexnum; j++){
        	if(flag == 2)   break;		 
            if(G.vertices[j].data.key == VR[i][0]){
            	j1 = j;
                ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode)); //ͷ�巨������
                p->nextarc = G.vertices[j].firstarc;
                //��㸳ֵ��ѭ������֮�� 
                G.vertices[j].firstarc = p;
                flag++; continue;
            }
            if(G.vertices[j].data.key == VR[i][1]){
            	j2 = j;
                ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode)); //ͷ�巨������
                p->nextarc = G.vertices[j].firstarc;
                //��㸳ֵ��ѭ������֮�� 
                G.vertices[j].firstarc = p;
                flag++; continue;
            }
        }
        if(flag != 2)	return ERROR;	//flag������2��˵������û���ҵ�VR���������������֣�˵����Ŀ���㲻���� 
        G.vertices[j1].firstarc->adjvex = j2;
        G.vertices[j2].firstarc->adjvex = j1;
        G.arcnum++;
    }
    return OK;
}

status RemoveGraph(GRAPHS &Graphs,char GraphName[]){
// Graphs��ɾ��һ������ΪGraphName��ͼ 
	if(Graphs.length == 0)	return ERROR;
	int j;
    for(int i = 0; i < Graphs.length; i++){
        if(strcmp(Graphs.elem[i].name, GraphName) == 0 && i != Graphs.length - 1){		    
            Graphs.length--; 			//����ͼ�����������һ
            for( j = i ; j < Graphs.length ; j++){    	//ͼ���ƶ�
            	strcpy(Graphs.elem[j].name , Graphs.elem[j+1].name);  //ͼ���ֵ��ƶ�
				memcpy(&Graphs.elem[j].G, &Graphs.elem[j+1].G, sizeof(Graphs.elem[j+1].G));	//ͼ���ݵ��ƶ���ֱ�Ӹ��ǣ� 
            }
            j++;
            //Ȼ�������ƶ���֮����ĩ�˵�ͼ 
            DestroyGraph(Graphs.elem[j].G);
            memset(Graphs.elem[j].name , 0 , sizeof(Graphs.elem[j].name));
            return OK;
        }
        else if(strcmp(Graphs.elem[i].name , GraphName) == 0 && i == Graphs.length - 1){	//���ɾ����ͼ�������ڶ�β 
        	DestroyGraph(Graphs.elem[i].G);
        	Graphs.length--; 
        	memset(Graphs.elem[i].name , 0 , sizeof(Graphs.elem[i].name));
        	return OK;
		}
    }
    return ERROR;
}

status DestroyGraph(ALGraph &G){
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
    ArcNode *front, *last;    //���ڱ��������ÿ�����㣬�ͷŸ�����ռ�
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].firstarc == NULL)   continue;   //˵����һ֧��������û������
        front = G.vertices[i].firstarc->nextarc;
        last = G.vertices[i].firstarc;
        while(front != NULL){
            free(last);
            last = front;
            front = front->nextarc;
        }
        free(last);
        G.vertices[i].firstarc = NULL;
        memset(G.vertices[i].data.others, 0, sizeof(G.vertices[i].data.others));	//���ö������� 
        G.vertices[i].data.key = -1;
    }
    G.arcnum = 0;
    G.vexnum = 0;
    return OK;
}

status LocateVex(ALGraph G,KeyType u){
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u) return i;
    }
    return ERROR;
}

status PutVex(ALGraph &G,KeyType u,VertexType value){
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
    int pos = -1;
    for(int i = 0; i < G.vexnum; i++){
        if(u != G.vertices[i].data.key && value.key == G.vertices[i].data.key){
            return ERROR;   //�ؼ��ֲ�Ψһ
        }
        else if(u == G.vertices[i].data.key){//Ŀ��λ��
            pos = i;
        }
    }
    if(pos == -1)   return ERROR;   		//˵��û�ҵ�Ŀ����
    G.vertices[pos].data.key = value.key;
    strcpy(G.vertices[pos].data.others, value.others);
    return OK;
}

status FirstAdjVex(ALGraph G,KeyType u){
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
    int j1 = -1;
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u) return G.vertices[i].firstarc->adjvex;
    }
    return -1;
}

status NextAdjVex(ALGraph G,KeyType v,KeyType w){
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
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
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
    if(G.vexnum >= 20)  return ERROR;   //�����������
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v.key) return ERROR; //˵���йؼ����ظ�
    }
    G.vertices[G.vexnum].data.key = v.key;
    strcpy(G.vertices[G.vexnum].data.others, v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v){
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
    int pos;		//��¼��ɾ�����λ�� 
    for(int k = 0; k < G.vexnum; k++){		//���ҵ�Ҫɾ���ĵ��λ�� 
    	if(G.vertices[k].data.key == v){
    		pos = k;
    		break;
		}
	}
	if((G.vexnum == 1 && G.vertices[0].data.key == v) || (pos == -1)){
        return ERROR;   //û��Ŀ������߽�Ҫɾ�����е�һ�����
    }
    for(int i = 0; i < G.vexnum; i++){      //ɾ�����㣨�ߣ�
        ArcNode *front, *last;
        front = G.vertices[i].firstarc;
        last = NULL;
        if(i != pos){			//���ͷ��㲻��Ŀ���� 
            while(front != NULL){
                if(front->adjvex == pos){		//���������Ŀ���� 
                    if(!last){	//����ǵ�һ������ 
                        G.vertices[i].firstarc = front->nextarc;
                    }
                    else{
                        last->nextarc = front->nextarc;
                    }
                    last = front;
                    front = front->nextarc;
                    free(last);    
                    //���ﲻ�ñ�����һ��ֻ��Ҫ��ɾ��Ŀ������һ֧����ʱ���������
                    continue;
                }
                else if(front->adjvex > pos)	//�������������Ŀ����֮�� 
					front->adjvex--;	//��ɾ�����֮��Ľ��Ҫ��ǰ�ƶ���������Щ�������ȫ����һ 
				last = front;
				front = front->nextarc;	
            }
        }
        else{				//���ͷ�����Ŀ���� 
            while(front != NULL){
                last = front;
                front = front->nextarc;
                free(last);   
                G.arcnum--;
            }
            G.vertices[i].firstarc = NULL;
        }
    } //end of forѭ����ɾ�����㣩

    for(int j = pos; j < G.vexnum-1; j++){  //����ͷ���λ�õ��ƶ�
        strcpy(G.vertices[j].data.others, G.vertices[j+1].data.others);
        G.vertices[j].data.key = G.vertices[j+1].data.key;
        G.vertices[j].firstarc = G.vertices[j+1].firstarc;
        
    }
    G.vertices[G.vexnum-1].firstarc = NULL; //�����ƶ����֮������ĩβ��ͷ��㣨ԭͷ�����������һ����㣩
    G.vertices[G.vexnum-1].data.key = 0;
    memset(G.vertices[G.vexnum-1].data.others, 0, sizeof(G.vertices[G.vexnum-1].data.others));
    G.vexnum--;
    return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType)){
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
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
                if(flag[p->adjvex] != 1){   //˵����δ�����ʹ����������
                    queue[rear++] = p->adjvex;
                    flag[p->adjvex] = 1;    //���������򱻱��Ϊ���ʹ�
                }
                p = p->nextarc;
            }
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w){
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
    int flag = 0;  //�����ж�v��w��������Ƿ񶼴���
    int t1, t2;     //���ڼ�¼v��w��������λ��
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v){
            flag++; t1 = i;
        }  
        if(G.vertices[i].data.key == w){
            flag++; t2 = i;    
        } 
    }
    if(flag != 2)   return ERROR;	//˵��v��w��������������һ�������� 
    ArcNode *tem = G.vertices[t1].firstarc;
    while(tem != NULL){     //�ж�����������֮���Ƿ������б�
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
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
    if(G.vexnum == 0)   return ERROR;
    ArcNode *p;
    visit(G.vertices[pos_dfs].data);
    flag_dfs[pos_dfs] = 1;
    for(p = G.vertices[pos_dfs].firstarc; p != NULL; p = p->nextarc){
        if(flag_dfs[p->adjvex] != 1){  //�����ǰλ�û�û�б����ʹ�
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
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
    int flag = 0;  //�����ж�v��w��������Ƿ񶼴���
    int t1, t2;     //���ڼ�¼v��w��������λ��
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == v){
            flag++; t1 = i;
        }  
        if(G.vertices[i].data.key == w){
            flag++; t2 = i;    
        } 
    }
    if(flag != 2)   return ERROR;   //˵��v��w��������㲢���Ƕ�����
    ArcNode *tem = G.vertices[t1].firstarc;
    while(tem != NULL){     		//�ж�����������֮���Ƿ����б�
        if(tem->adjvex == t2){
            flag = 0;
            break;
        }
        tem = tem->nextarc;
    }
    if(flag != 0)   return ERROR;   //˵����������֮�䱾��û�б�
    ArcNode *p1 = G.vertices[t1].firstarc;
    if(p1->adjvex == t2){   		//���firstarcֱ��ָ��Ҫɾ���ı���
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
    if(p2->adjvex == t1){   		//���firstarcֱ��ָ��Ҫɾ���ı���
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
//��ͼ������д�뵽�ļ�FileName��
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
        fprintf(fp,"%d\n",-1);  //ÿһ����-1��Ϊ��β
    }
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[]){
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
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
        G.vertices[i].firstarc = NULL;  //��ʼ��
        fscanf(fp,"%d ",&tem);
        while(tem != -1){	//������Ҫ��β�巨 
            ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = tem;
            if(tail == NULL){	//��������һ����� 
            	p->nextarc = NULL;
            	G.vertices[i].firstarc = p;
            	tail = p;
			}
			else{               //�����������ǵ�һ�����
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
//���ͼ�ж���v������w�����·�� 
    int flag[20] = {0};
    int path = 0;		//���ڼ�¼���·�� 
    int cnt[20] = {0}, i_distance;	//���ڼ�¼����Ŀ�궥�����Ϊi�ĵ���cnt[i]�� 
    cnt[0] = 1, i_distance = 1;
    int cnt_q = 0, j_print = 0;	//���ڼ�¼�������Ѿ������˶��ٸ����㣨ֻ�е�cnt_q ���� cnt[j_print] ʱ path ���ܼ�һ����j_print������ʾҪ���Ҿ���Ϊ j_print �ĵ��� 
    int queue[20] = {0}, rear = 0, front = 0;
    for(int i = 0; i < G.vexnum; i++){
    	if(G.vertices[i].data.key == v){	//��ʼ����������� 
    		queue[rear++] = i;		//�Ƚ��˶������
    		flag[i] = 1;
			while(rear != front){
				ArcNode *p = G.vertices[queue[front]].firstarc;
            	front++;
            	cnt_q++;
				while(p != NULL){
					if(G.vertices[p->adjvex].data.key == w){	//�ҵ�����һĿ�궥�㣬����·������ 
						return path+1;
					}
					if(flag[p->adjvex] != 1){
						queue[rear++] = p->adjvex;
                    	flag[p->adjvex] = 1;    //������ʱ���Ϊ���ʹ�
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
			return -1;	//������˵����������֮��û��ͨ· 
		}//end of if���ҵ�v����֮��Ĳ����� 
    }//end of for ��������v����Ĳ�����
	return -1; //�ж��㲻���� 
}

status ConnectedComponentsNums(ALGraph &G, int judge){
//��ͼ��ͨ�����ĸ�����judge�����ж��ǲ��ǵ�һ��ݹ飩 
	if(G.vexnum == 0)   return ERROR;
    ArcNode *p;
    flag_dfs[pos_dfs] = 1;
    for(p = G.vertices[pos_dfs].firstarc; p != NULL; p = p->nextarc){
        if(flag_dfs[p->adjvex] != 1){  //�����ǰλ�û�û�б����ʹ�
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
//����붥��v�ľ���С��k�ĵ�ļ���	
	int flag[20] = {0};
    int path = 0;		//���ڼ�¼���·�� 
    int cnt[20] = {0}, i_distance;	//���ڼ�¼����Ŀ�궥�����Ϊi�ĵ���cnt[i]�� 
    cnt[0] = 1, i_distance = 1;
    int cnt_q = 0, j_print = 0;	//���ڼ�¼�������Ѿ������˶��ٸ����㣨ֻ�е�cnt_q ���� cnt[j_print] ʱ path ���ܼ�һ����j_print������ʾҪ���Ҿ���Ϊcnt[j_print]�ĵ��� 
    int queue[20] = {0}, rear = 0, front = 0;
    for(int i = 0; i < G.vexnum; i++){
    	if(G.vertices[i].data.key == v){	//��ʼ����������� 
    		queue[rear++] = i;		//�Ƚ��˶������
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
                    	flag[p->adjvex] = 1;    //������ʱ���Ϊ���ʹ�
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
		}//end of if���ҵ�v����֮��Ĳ����� 
    }//end of for ��������v����Ĳ�����
    if(front == rear){
		printf("\n"); 	return OK;
	}		//��ֹ��k�ܴ�ʱ�����ȫ�����������whileѭ����return -1����� 
    printf("����ʧ�ܣ�Ŀ�궥�㲻���ڣ�\n");
	return -1; //�ж��㲻���� 
}
