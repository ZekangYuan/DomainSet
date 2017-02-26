//近似函数 度大的
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 1500;				/*节点的最大数量*/
int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/

int node_num;
int edge_num;

int solution[max_node+1];				/*存储第一种方法求得的结果*/
int solution_counts = 0;
int vertex[max_node+1];					/*存储节点信息 -1：已经被覆盖过   -2：已经移除*/
int vertex_degree[max_node+1];			/*存储节点的度*/
int weight[max_node+1];

void CreateGraph(char str[]);
void Greedy(char str[]);
void AdjustWeight(int max_no);
int ChooseVertex();


void main()
{
	//贪心
	
	cout<<"\n\n****************************寻找支配集**************************************"<<endl;
	clock_t start, finish; 
	double  duration = 0.0; 
	int iter = 1;
	char str[50];
	fstream myout;
	myout.open("1200yy.txt",ios::out|ios::app);
	int sum = 0;
	while(iter<=1)
	{

		sprintf(str, "%d_%f_%d.txt" , 1200,0.5,iter);
		cout<<str<<endl;
		myout<<"------第"<<iter<<"次迭代------"<<endl;
		cout<<"------第"<<iter<<"次迭代------"<<endl;
		start = clock();
		Greedy(str);
		finish = clock(); 
		duration = (double)(finish - start);//输出单位ms
		cout<<"Time used "<<duration<<endl;
		myout<<"Time used "<<duration<<endl;
		
		//for(int i = 1; i <= solution_counts; i++)
			//cout<<solution[i]<<"  ";
		
		cout<<"\n total: "<<solution_counts<<endl;
		myout<<"\n total: "<<solution_counts<<endl;
		memset(vertex,0,sizeof(vertex));
		sum+=solution_counts;
		myout<<"sum = "<<sum<<endl;
		cout<<"sum = "<<sum<<endl;
		
		for(int i = solution_counts; i >= 1; i--)
		{
			vertex[solution[i]] = -1;
			for(int j=1;j<=node_num;j++)
			{
				//cout<<Graph_test[i][j]<<"  ";
				if(Graph[solution[i]][j] == 1)
				{
					//cout<<solution1[i]<<" 相邻的顶点是 ："<<j<<endl;
					vertex[j] = -1;
				}
			}
		}
		
		for(int g = 1; g <= node_num; g++)
		{
			if(vertex[g] != -1)
			{
				cout<<"------Wrong Results!!------"<<endl;
				return ;
			}
			
		}
		
		iter++;
		cout<<sum<<endl;
	}
	
	myout<<"1000次迭代支配集总个数 ： "<<sum<<endl;
	myout.close();
		  
		  
}





void CreateGraph(char str[])
{
	int i,j;
	int k = 0;
	//char str[80];
	//cout<<"Input filename :"<<endl;
	//cin>>str;
	ifstream in(str);
	if(!in)
	{
		cout<<"文件打开失败!"<<endl;
	}
	
	in>>node_num;
	in>>edge_num;
	
	for(i=1; i<=node_num;i++)
	{
		vertex_degree[i] = weight[i] = 0;
		for(j=1;j<=node_num;j++)
		{
			Graph[i][j]  = Graph[i][j] = 0;
		}
	}
	
	while(!in.eof())
	{
		in>>i>>j;
		if(Graph[i][j])
			continue;
		
		else
		{
			Graph[i][j] = Graph[j][i] = 1;
		}
	}
	
	in.close();
	
	
	//计算节点的度
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;//为0 全都没有覆盖
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
		
		weight[i] = vertex_degree[i] + 1;//节点的权重设置为度加一
		cout<<"节点"<<i<<"的度是 ："<<weight[i]<<endl;
	}
	
}





void Greedy(char str[])
{
	CreateGraph(str);
	solution_counts = 0;
	while(1)
	{
		
		int v = 0;//选取的节点编号
		v = ChooseVertex();
		if (v != -1)
		{
			cout<<v<<"  choosed   weight="<<weight[v]<<endl;
			solution_counts++;
			solution[solution_counts] = v ;
			AdjustWeight(v);
		}
		
		else
			break;
		
	}
	
	
}


int ChooseVertex()
{
	srand((int)time(0)); 
	int choosed = 0;
	
	
	int temp_weight = 0;
	int temp_no = 0;
	int same_no = 0;
	int same[max_node + 1];
	
	for(int i = 1; i <= node_num; i++)
	{
		if(weight[i] >= temp_weight)
		{
			temp_weight = weight[i];
			temp_no = i;
		}
	}
	
	if(temp_weight == 0)
		return -1;
	
	else//如果最大的权重的节点有多个，随机选取一个
	{
		for(int i = 1; i <= node_num; i++)
		{
			if(weight[i] == temp_weight)
			{
				same_no ++;
				same[same_no] = i;
				
			}
		}
		//cout<<"有 "<<same_no<<"个相同的最大度节点"<<endl;
		choosed = 1+(int)(1.0*same_no*rand()/(RAND_MAX+1.0)); 
		//choosed = same_no;
		return same[choosed];
		
	}
}

void AdjustWeight(int max_no)
{
	weight[max_no] = 0;//选中的节点权重改为0
	
	for(int i = 1; i <= node_num; i++)//对于选中节点的邻居 并且权重大于0
	{
		if(Graph[max_no][i] == 1  && weight[i] > 0)
		{	
			if(vertex[max_no] != -1)//如果选中的这个节点没有覆盖住，那么选取该节点后，起邻居被覆盖的次数会减一。将其邻居的权重减一
				weight[i]-- ;
			
			if(vertex[i] != -1)
			{
				vertex[i] = -1;
				weight[i]-- ;
				for(int k = 1; k <= node_num; k++)
				{
					if(Graph[i][k] == 1)
					{
						if(weight[k] > 0)
							weight[k]-- ;
					}
				}
			}
		}		
	}
	vertex[max_node] = -1;
	
}


