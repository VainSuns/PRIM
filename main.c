#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define INFINITY			65535
#define MAX_VERTEX_NUM		20
#define OK					1
#define ERROR				0


typedef	char		VertexType;
typedef int 		VRType; 
typedef int 		Status; 

//���帨�����飬��¼����U��V-U��Ĵ�����С�ı� 
struct {
	int	adjvex;
	VRType		lowcost;
}closeedge[MAX_VERTEX_NUM]; 

//------------ͼ�����飨�ڽӾ��󣩴洢��ʾ---------------// 
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];				//�������� 
	VRType	arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//�ڽӾ��� 
	int     vernum,arcnum;							//����ͻ��� 
}MAGraph;

int visited[MAX_VERTEX_NUM];

//����������
Status CreateUDN(MAGraph *g){
	
	int i,j;
	int start ,end ,num;
	printf("������ͼ�Ķ������ͻ�����(Ҫ�󶥵���С�ڶ�ʮ)\n");
	scanf("%d %d", &g->vernum, &g->arcnum ); 	
	printf("ͼ�Ķ�������%d�ͻ�����%d\n", g->vernum, g->arcnum );
	printf("������ͼ�Ķ����ֵ\n");
	
	for(i = 0; i < g->vernum ; i++){
		getchar();
		scanf("%c", &g->vexs[i]);
		printf("��%d�������ֵ�ǣ�%c\n", i , g->vexs[i]);
	} 
	
	//��ʼ���ڽӾ��� 
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			g->arcs[i][j] = INFINITY ;
		}
	}
	printf("�����뻡�����Ķ����Ȩֵ��\n");
	for( i = 0 ; i < g->arcnum ; i++ ){
		getchar();		
		scanf("%d %d %d", &start, &end ,&num );

		g->arcs[start][end] = num ;
		g->arcs[end][start] = g->arcs[start][end] ;
		printf("����%c������%c��Ȩֵ��%d\n", g->vexs[start] , g->vexs[end] , num);
	} 
	
	printf("����ͼ��ʼ���ɹ���\n");
	return OK;
} 

//���ڽӾ������ʽ�������ͼ 
void MAGraphPrint(MAGraph *g){
	
	int i,j;
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			printf("%7d  ", g->arcs[i][j]);
		}
		printf("\n");
	}
}

int min(MAGraph *g){
	
	int i;
	int index = -1;
	int min = INFINITY;
	for(i = 0 ; i < g->vernum ; i++ ){
		if(visited[i] == 0 && closeedge[i].lowcost < min){
			min = closeedge[i].lowcost;
			index = i;
		}
		
	}
	return index;
}

void MiniSpanTree_PTIM(MAGraph *g, int v){
	
	int i,j;
	for(i = 0 ; i < g->vernum ; i++){						//���������ʼ�� ����ʼ��֮��closeedge[i]�����ʾͼ���±�Ϊi�Ķ�����붥���±�Ϊv��Ȩֵ 
		if (i != v){
			visited[i] = 0;
			closeedge[i].adjvex = v;						//v��ʾ�����������±꣬ 
			closeedge[i].lowcost = g->arcs[v][i];			//g->arcs[v][i]��ʾ�������Ȩֵ�� 
		}
	}
	visited[v] = 1;
	closeedge[v].lowcost = MAX_VERTEX_NUM;
	printf("��³ķ�㷨�������С��������\n");
	for( i = 1 ; i < g->vernum ; i++ ){
		v = min(g);												//�ҳ���СȨֵ�Ķ����±� 
		if(v == -1)
			break;
		printf("���� %c ������ %c ��ȨֵΪ��%d\n",g->vexs[closeedge[v].adjvex], g->vexs[v], closeedge[v].lowcost );
		
		visited[v] = 1;
		closeedge[v].lowcost = INFINITY ;
		for(j = 0; j < g->vernum ; j++){
			if(visited[j] == 0 && g->arcs[v][j] < closeedge[j].lowcost){
				closeedge[j].adjvex = v;													//������ı���closeedge�������ԵĶ��� 
				closeedge[j].lowcost = g->arcs[v][j];										// ������ı���closeedge�������ԵĶ����Ȩֵ 
			}
		}
		
	} 
	
	
} 

int main(int argc, char *argv[]) {
	
	MAGraph *g;
	
	g = (MAGraph *)malloc(sizeof(MAGraph));
	CreateUDN(g);
	MAGraphPrint(g);
	MiniSpanTree_PTIM(g, 0);
	return 0;
}
