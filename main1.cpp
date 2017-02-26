//���ƺ��� �ȴ��
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 1000;				/*�ڵ���������*/
int Graph[max_node+1][max_node+1];		/*ʹ���ڽӾ���洢ͼ*/

int node_num;
int edge_num;

int vertex_degree[max_node+1];			/*�洢�ڵ�Ķ�*/
int score[max_node+1];

int    gvertexnum;                        //ͼ�е��ʵ�ʸ���
long   gedgenum;                          //ͼ�бߵ�ʵ������
short int maxdegree;                      //����ͼ�������,�ʺ�����Ȳ�����2^15=32768
short int mindegree;                      //ͼ����С��
short int evendegreenum;                  //ͼ�Ķ�Ϊż���ĵ�ĸ���
short int onedegreenum;                   //��Ϊ1�ĵ�ĸ���


void ReadGraph(char str[]);
void Floyd(void);
void Ppath(int path[][max_node+1], int i, int j);
void Dispath(int A[][max_node+1],int path[][max_node+1],int n);


void main()
{
	char str[50];
	sprintf(str, "karate_club.txt");
	ReadGraph(str);
	Floyd();
	for(int i = 1; i <= node_num; i++)
		cout<<score[i]<<" "<<endl;
}

//***������������***

void ReadGraph(char *txtgraphfilename)
{//To read the data file of graph G=<V,E>(V={1,2,...,n}) to obtain the adjacent matrix.
 //The format of the data file is as follows: the node number,the edge number, every edge <x,y> followed
      FILE  *in;
      
      //���ݸ������ļ����ִ��ļ�������r��ʾ���ļ�����ֻ������
	  if ((in=fopen(txtgraphfilename, "r"))==NULL)
      {  	fprintf(stderr, "Cannot open the data file.\n");
		return;
      }
	
      fscanf(in,"%d",&node_num);                         //��ȡͼ��ʵ�ʵ���
      fscanf(in,"%d",&edge_num);                           //��ȡͼ�ı���
      
      int i,j,k;
      for(i=1;i<=node_num;i++)                          //initialize the adjacent matrix
		for(j=1;j<=node_num;j++)
			Graph[i][j]=0;

      k=0;                                                 //k ������סʵ�ʵı�����ע���ļ���ĳ�߿����ظ����ֶ��
      while(!feof(in))                                     //����ÿһ����(ÿ�����ļ�������һ�Ե�����ʾ��)
      {
	    fscanf(in,"%d",&i);                               
    	fscanf(in,"%d",&j);                              
		
	    if(Graph[i][j])                              //��������˾Ͳ�Ҫ�ظ���ע���ļ��б߿����ظ����ֶ��
             continue;
	    Graph[i][j]=1;
	    Graph[j][i]=Graph[i][j];                //For an undirected graph, the adjacent matrix is symmetrical
	    k++;
      }
      edge_num=k;                                         //�õ�ʵ�ʵı���
      fclose(in);                                         //�򿪵��ļ�������ر�

     //��ʼ�������,�����������(ͼ�к��й������������޽�). ����Ƿ��й�����. ������й�����,�򽫹�����������߼��ɱ�֤����������
  	 for(i=1;i<=node_num;i++)
	 {  
		 score[i] = 0;
		 vertex_degree[i]=0;
		for(j=1;j<=node_num;j++)
			if(Graph[i][j]) 
				vertex_degree[i]++;
		if(vertex_degree[i]==0)  //��ʾ�ڵ�i�ǹ�����,��ʱ���ڵ�i������ӵ���һ�ڵ�k
		{
           k=(rand()%node_num)+1;
		   if(k==i && k<node_num) 
			   k++;
		   else if(k==i && k>1)
			   k--;
           Graph[i][k]=1;
		   Graph[k][i]=1;
		   vertex_degree[i]++;
		   vertex_degree[k]++;
		   edge_num++;
		}
	 }

	 
	 //�Խڵ�Ȱ����ɴ�С����, Ȼ���ͼ���ն��ɴ�С���±��: ��1�Žڵ�����, ������node_num�Žڵ����С
	 //����ѡ�����򷽷�
	 short int temp;
	 bool tempf;
     int a;
	 for(i=1;i<node_num;i++)
	 {
		 k=i;
		 for(j=i+1;j<=node_num;j++)
			 if(vertex_degree[j]>vertex_degree[k])
			     k=j;
	     if(k!=i)
		 {//�����ڵ�i�ͽڵ�k�ı��: ��Ӧ�ڵ��Ҫ����,ͬʱҪ�����ڽӾ���ĵ�i�к͵�k��,�Լ���i�к͵�k��
            temp=vertex_degree[k];        //�������ڵ�Ķ�
			vertex_degree[k]=vertex_degree[i];
			vertex_degree[i]=temp;
			
			for(a=1;a<=node_num;a++) //�����ڽӾ�������� 
			{	tempf=Graph[k][a];
				Graph[k][a]=Graph[i][a];
				Graph[i][a]=tempf;	
			}

            for(a=1;a<=node_num;a++) //�����ڽӾ�������� 
			{	tempf=Graph[a][k];
				Graph[a][k]=Graph[a][i];
				Graph[a][i]=tempf;	
			}

		 }
	 }

	 //������maxdegree, ��С��mindegree, ���ж�Ϊ1�Ľڵ����onedegreenum, ż���Ƚڵ����evendegreenum(�����Ƚڵ����Ϊnode_num-evendegreenum)
	 maxdegree=vertex_degree[1];
	 mindegree=vertex_degree[node_num];
	 onedegreenum=0;
	 evendegreenum=0;
	 for(i=node_num;i>=1;i--)
	 {
		 
		 if(vertex_degree[i]==1)
			 onedegreenum++;
		 else if(vertex_degree[i]%2==0)
			 evendegreenum++;
	 }

	 printf("n=%d,m=%d,maxd=%d,averd=%6.2lf,dens=%10.5lf\n",node_num,edge_num,maxdegree,2.0*edge_num/node_num,2.0*edge_num/(node_num*(node_num-1.0)));
	 printf("mindegree=%d,onedegreenum=%d,evendegreenum=%d,odddegreenum=%d\n",mindegree,onedegreenum,evendegreenum,node_num-evendegreenum);

}




void Floyd(void)
{
	int A[max_node+1][max_node+1],path[max_node+1][max_node+1];
	int i,j,k;

	for(i = 1; i <= node_num; i++)
		for(j = 1; j <= node_num; j++)
	{
		if(i == j)
			A[i][j] = 0;

		else
		{
			if(Graph[i][j] == 0)
				A[i][j] = 10000;
			else 
				A[i][j] = Graph[i][j];
			//cout<<i<<"->"<<j<<":"<<Graph[i][j]<<" "<<A[i][j]<<" ";
		}
		path[i][j] = -1;
	}


		
	for(k = 1; k <= node_num; k++)
	{
		for(i = 1; i <= node_num; i++)
			for(j = 1; j <= node_num; j++)
			if(A[i][j] > A[i][k]+A[k][j])
			{
				A[i][j] = A[i][k] + A[k][j];
				path[i][j] = k;
			}
	}

	Dispath(A,path,node_num);

	/*
	for(i = 1; i <= node_num; i++)
		for(j = 1; j <= node_num; j++)
		{
				cout<<"��"<<i<<"��"<<j<<"·�������ǣ�"<<A[i][j]<<endl;
		}
	*/	
}

void Ppath(int path[][max_node+1], int i, int j)
{
	int k;
	k = path[i][j];
	if(k == -1) return;
	Ppath(path,i,k);
	cout<<k<<"  ->  ";
	score[k]++;
	Ppath(path,k,j);
}

void Dispath(int A[][max_node+1],int path[][max_node+1],int n)
{
	int i,j;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
		{
			if(A[i][j] == 0)
			{
				if(i != j)
					cout<<"��"<<i<<"��"<<j<<"û��·��"<<endl;

				else
					cout<<"��"<<i<<"��"<<j<<"������Ϊ0"<<endl;

			}

			else
			{
				cout<<"��"<<i<<"��"<<j<<"·�������ǣ�"<<A[i][j]<<endl;
				cout<<i<<endl;
				Ppath(path,i,j);
				score[i]++;
				score[j]++;
				cout<<j<<endl;
			}
		}
}



