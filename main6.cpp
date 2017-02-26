//2
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 20000;				/*节点的最大数量*/
int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/

int node_num;
int edge_num;

int solution[max_node+1];				/*存储第一种方法求得的结果*/
int solution_counts = 0;
int vertex[max_node+1];					/*存储节点信息 -1：已经被覆盖过   -2：已经移除*/
int vertex_degree[max_node+1];			/*存储节点的度*/
double weight[max_node+1];
double vote[max_node+1];

void CreateGraph(char str[]);
void Greedy_Vote(char str[]);
void AdjustWeight(int i);
int ChooseVertex();


void main()
{
	
	cout<<"\n\n****************************寻找支配集**************************************"<<endl;
	clock_t start, finish; 
	double  duration = 0.0; 
	int iter = 1;
	char str[50];
	fstream myout;
	myout.open("400.txt",ios::out|ios::app);
	int sum = 0;
	while(iter<=1)
	{
		//机会策略
		//sprintf(str, "%d_%f_%d.txt" , 400,0.1,iter);
		sprintf(str, "ncstrlwg2_submatrix.txt" , 1200,0.5,iter);
		cout<<str<<endl;
		
		start = clock();
		Greedy_Vote(str);
		finish = clock(); 
		duration = (double)(finish - start);//输出单位ms
		myout<<"Time used "<<duration<<endl;


		myout<<"<--------- iter  "<<iter<<" --------->"<<endl;
		cout<<"<--------- iter  "<<iter<<" --------->"<<endl;
		myout<<"支配集个数"<<solution_counts<<endl;
		sum+=solution_counts;
		myout<<"sum = "<<sum<<endl;
		cout<<"sum = "<<sum<<endl;
		
		for(int i = 1; i <= solution_counts; i++)
		{
			//cout<<solution[i]<<"  ";
			myout<<solution[i]<<"  ";
		}

		myout<<endl<<endl;

		cout<<"\n total: "<<solution_counts<<endl;
		memset(vertex,0,sizeof(vertex));
		  
			  
		for(i = solution_counts; i >= 1; i--)
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
				myout<<"------Wrong Results!!------"<<endl;
				cout<<"------Wrong Results!!------"<<endl;
				return ;
			}
			
		}
		
		iter++;
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
		vertex[i] = vote[i] = weight[i] = 0;
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
		
		vote[i] = 1.0/(1.0+vertex_degree[i]);//每个节点对邻居的期盼度
		weight[i] = vote[i];//节点的权重设置为票数
		
	}
	
	
	//计算节点的票数,等于自身的票数加上邻居的票数
	for(i = 1; i <= node_num; i++)
	{
		for(int j = 1; j <= node_num; j++)
		{
			if(Graph[i][j] == 1)
			{
				weight[i] = weight[i] + vote[j];
				//cout<<i<<"邻居是 ："<<j<<" "<<vote[j]<<endl;
			}
		}
		//cout<<i<<" "<<vote[i]<<endl;
		//cout<<i<<" "<<weight[i]<<"-------------------- "<<vertex_degree[i]<<endl<<endl;
	}
}





void Greedy_Vote(char str[])
{
	CreateGraph(str);
	solution_counts = 0;

	while(1)
	{
		int v = 0;//选取的节点编号
		v = ChooseVertex();
		if (v != -1)
		{
			//cout<<v<<"  choosed "<<endl;
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
	
	
	double temp_weight = 0.0;
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
	
	if(temp_weight == 0.0)
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
		return same[choosed];
		
	}
}

void AdjustWeight(int i)
{
	weight[i] = 0;//选中的节点权重改为0
	
	for(int j = 1; j <= node_num; j++)//对于选中节点的邻居 并且权重大于0
	{
		if(Graph[i][j] == 1  && weight[j] > 0)
		{	
			vertex_degree[j]--;//邻居的度减一
			
			vote[j] = (double)1/(vertex_degree[j]+1);//更新邻居的vote
			//printf("--%f--",vote[j]);
			

			if(vertex[i] != -1)//如果选中的这个节点没有覆盖住，那么选取该节点后，起邻居被覆盖的次数会减一。将其邻居的权重减一
				weight[j] = weight[j] - vote[i] ;
			
			if(vertex[j] != -1)
			{
				
				vertex[j] = -1;
				weight[j] = weight[j] - vote[j] ;
				for(int k = 1; k <= node_num; k++)
				{
					if(Graph[j][k] == 1)
					{
						if(weight[k] > 0)
							weight[k] = weight[k] - vote[j];
					}
				}
			}
		}		
	}
	vertex[i] = -1;
	
}


