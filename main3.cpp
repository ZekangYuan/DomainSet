//机会策略
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

const int max_node = 2000;				/*节点的最大数量*/
int node_num = max_node;
int edge_num;
const int proper = 1;					/*随即图产生边的概率*/
int random;								/*用于产生随机边*/			
ofstream fout;

int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/
int Graph_test[max_node+1][max_node+1];
double weight[max_node+1];				/*存储节点的机会值*/
int covered_num = 0;					/*存储被覆盖节点的个数*/

int vertex[max_node+1];					/*存储节点是否查找过*/
int vertex_degree[max_node+1];			/*存储节点的度*/

int solution_counts = 0;				/*存储答案的个数*/
int solution[max_node+1];				/*存储答案*/

void CreateGraph(void);
int Cover(void);




void main()
{
	time_t t;
	srand((unsigned)time(&t));
	memset(vertex,0,sizeof(vertex));
	
	CreateGraph();
	
	//for(int b = 1; b <= node_num; b++)
	//{
	//	cout<<weight[b]<<" "<<endl;
	//}
	
	fout<<"\n\n****************************寻找支配集**************************************"<<endl;
	ofstream fout("result.txt",ios::app);
	int flag = 1;
	while(1)
	{
		flag = Cover();
		if(flag == -1)
		{
			for(int i = 1; i<= solution_counts; i++)
				cout<<solution[i]<<"  ";

			cout<<endl<<"Total : "<<solution_counts<<endl;
			return ;
		}
			
		
	}
	
	
	
	/*这是测试结果是否正确的代码
		*/
	  memset(vertex,0,sizeof(vertex));
	  
		
		  for(int i = solution_counts; i >= 1; i--)
		  {
			  vertex[solution[i]] = -1;
			  for(int j=1;j<=node_num;j++)
			  {
				  //cout<<Graph_test[i][j]<<"  ";
				  if(Graph_test[solution[i]][j] == 1)
				  {
				  //cout<<solution1[i]<<" 相邻的顶点是 ："<<j<<endl;
				  vertex[j] = -1;
				  }
			  }
		  }
		  
		  
			for(int g = 1; g <= node_num; g++)
			{
				if(vertex[g] == 0)
				{
				cout<<"------Wrong Results!!------"<<endl;
				return ;
				}
			
			 }

	fout.close();
}



void CreateGraph()
{
	
	int i,j;
	int k = 0;
	char str[80];
	cout<<"Input filename :"<<endl;
	cin>>str;
	ifstream in(str);
	if(!in)
	{
		cout<<"文件打开失败!"<<endl;
	}
	
	in>>node_num;
	in>>edge_num;
	for(i=1; i<=node_num;i++)
	{
		for(j=1;j<=node_num;j++)
		{
			Graph_test[i][j] = Graph[i][j] = 0;
		}
	}
	
	while(!in.eof())
	{
		in>>i>>j;
		if(Graph[i][j])
			continue;
		
		else
		{
			Graph_test[i][j] = Graph_test[j][i] = Graph[i][j] = Graph[j][i] = 1;
		}
	}
	
	//cout<<"Edge num :"<<k<<endl;
	in.close();
	
	
	
	/*
	int i,j;
	for(i=1; i<=node_num;i++)
	{
	weight[i] = 0.0;
	for(j=1;j<=node_num;j++)
	{
	Graph[i][j] = 0;
	}
	}
	
	  
		for(i=1; i<=node_num;i++)
		{
		for(j=1;j<=node_num;j++)
		{
		random = rand()%10;
		//cout<<"random = "<<random<<endl;
		if(random <= proper)
		Graph[i][j] = Graph[j][i] = 1;
		}
		}
	*/	
	
	//计算节点的度
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
	}
	
	
	
	//计算节点的 Weight值
	//weight(w)值等于w的邻居v的vote(v)之和
	for(i = 1; i<= node_num; i++)
	{
		for(j = 1; j<= node_num; j++)
		{
			if(Graph[i][j] == 1)
				weight[i] += 1.0/(1+vertex_degree[j]);
		}
	}
}





int Cover(void)
{
	//
	//1.第一步，选取最大Weight()值的点加入支配集
	//
	long double max_value= 0.0;
	int max_no = -1;
	for(int i = 1; i <= node_num; i++ )
	{
		if(weight[i] >= max_value)
		{
			max_value = weight[i];
			max_no = i;
		}
	}
	
	bool flag =true;
	for(i = 1; i <= node_num; i++)
	{
		if(vertex[i] == 0)
			flag = false;
		
	}
	if(flag || max_no == -1)
	{
		cout<<"All checked !"<<endl;
		return -1;
	}
	solution_counts++;
	solution[solution_counts] = max_no ;
	
	
	cout<<"Max_no = "<<max_no<<endl;
	cout<<"Max_value = "<<max_value<<endl;
	
	//
	//2.第二步，加入后进行全局信息的更新，包括加入点的邻居
	//
	//
	//更新1:加入顶点的weight()变为-1
	//更新2:加入顶点的标记设为-1
	//更新3:加入节点的邻居节点的标记设为-1,加入顶点与邻居节点的边销毁
	//更新4:与邻居节点相连的节点还未覆盖，更改其度的变化，weight()的变化
	weight[max_no] = -1;
	
	covered_num ++;
	
	for(i = 1; i <= node_num; i++)
	{
		if(Graph[max_no][i] == 1 && weight[i] > 0)
			{
				//cout<<"Covered num = "<<i<<endl<<endl;
				if(vertex[max_node] == 0)
				{
					vertex_degree[i] --;
					
				}
				if(vertex[i] == 0)
				{
					vertex[i] = -1;
					vertex_degree[i] --;
					for(int j = 1; j <= node_num; j++)
					{
						if(Graph[i][j] == 1 && weight[j] > 0)
						{
							vertex_degree[j] --;
						}
					}
				}	
			}		
		
		
	}
	vertex[max_no] = -1;
	cout<<"Covered num = "<<covered_num<<endl<<endl;
	

	//
	//3.第二步，重新计算各点的weight()值
	//
	for(i = 1; i<= node_num; i++)
	{
		if(vertex[i] != -1)
		{
			for(int j = 1; j<= node_num; j++)
			{
				if(Graph[i][j] == 1)
					weight[i] += 1.0/(1+vertex_degree[j]);
			}
		}
		
	}
	
	return 1;
}

