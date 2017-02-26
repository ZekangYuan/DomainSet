//近似函数 度大的
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 1000;				/*节点的最大数量*/
int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/

int node_num;
int edge_num;

int vertex_degree[max_node+1];			/*存储节点的度*/
int score[max_node+1];

int    gvertexnum;                        //图中点的实际个数
long   gedgenum;                          //图中边的实际条数
short int maxdegree;                      //保存图的最大点度,适合最大点度不超过2^15=32768
short int mindegree;                      //图的最小度
short int evendegreenum;                  //图的度为偶数的点的个数
short int onedegreenum;                   //度为1的点的个数


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

//***输入和输出函数***

void ReadGraph(char *txtgraphfilename)
{//To read the data file of graph G=<V,E>(V={1,2,...,n}) to obtain the adjacent matrix.
 //The format of the data file is as follows: the node number,the edge number, every edge <x,y> followed
      FILE  *in;
      
      //根据给定的文件名字打开文件。参数r表示对文件进行只读操作
	  if ((in=fopen(txtgraphfilename, "r"))==NULL)
      {  	fprintf(stderr, "Cannot open the data file.\n");
		return;
      }
	
      fscanf(in,"%d",&node_num);                         //读取图的实际点数
      fscanf(in,"%d",&edge_num);                           //读取图的边数
      
      int i,j,k;
      for(i=1;i<=node_num;i++)                          //initialize the adjacent matrix
		for(j=1;j<=node_num;j++)
			Graph[i][j]=0;

      k=0;                                                 //k 用来记住实际的边数。注：文件中某边可能重复出现多次
      while(!feof(in))                                     //读出每一条边(每条边文件中是用一对点来表示的)
      {
	    fscanf(in,"%d",&i);                               
    	fscanf(in,"%d",&j);                              
		
	    if(Graph[i][j])                              //如果边有了就不要重复。注：文件中边可能重复出现多次
             continue;
	    Graph[i][j]=1;
	    Graph[j][i]=Graph[i][j];                //For an undirected graph, the adjacent matrix is symmetrical
	    k++;
      }
      edge_num=k;                                         //得到实际的边数
      fclose(in);                                         //打开的文件最后必须关闭

     //初始化各点度,并处理孤立点(图中含有孤立点则问题无解). 检查是否含有孤立点. 如果含有孤立点,则将孤立点随机连边即可保证不含孤立点
  	 for(i=1;i<=node_num;i++)
	 {  
		 score[i] = 0;
		 vertex_degree[i]=0;
		for(j=1;j<=node_num;j++)
			if(Graph[i][j]) 
				vertex_degree[i]++;
		if(vertex_degree[i]==0)  //表示节点i是孤立点,此时将节点i随机连接到另一节点k
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

	 
	 //对节点度按照由大到小排序, 然后对图按照度由大到小重新编号: 新1号节点度最大, 新最后第node_num号节点度最小
	 //采用选择排序方法
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
		 {//交换节点i和节点k的编号: 相应节点度要交换,同时要交换邻接矩阵的第i行和第k行,以及第i列和第k列
            temp=vertex_degree[k];        //交换两节点的度
			vertex_degree[k]=vertex_degree[i];
			vertex_degree[i]=temp;
			
			for(a=1;a<=node_num;a++) //交换邻接矩阵的两行 
			{	tempf=Graph[k][a];
				Graph[k][a]=Graph[i][a];
				Graph[i][a]=tempf;	
			}

            for(a=1;a<=node_num;a++) //交换邻接矩阵的两列 
			{	tempf=Graph[a][k];
				Graph[a][k]=Graph[a][i];
				Graph[a][i]=tempf;	
			}

		 }
	 }

	 //求最大度maxdegree, 最小度mindegree, 所有度为1的节点个数onedegreenum, 偶数度节点个数evendegreenum(奇数度节点个数为node_num-evendegreenum)
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
				cout<<"从"<<i<<"到"<<j<<"路径长度是："<<A[i][j]<<endl;
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
					cout<<"从"<<i<<"到"<<j<<"没有路径"<<endl;

				else
					cout<<"从"<<i<<"到"<<j<<"到自身为0"<<endl;

			}

			else
			{
				cout<<"从"<<i<<"到"<<j<<"路径长度是："<<A[i][j]<<endl;
				cout<<i<<endl;
				Ppath(path,i,j);
				score[i]++;
				score[j]++;
				cout<<j<<endl;
			}
		}
}



