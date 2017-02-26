#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<time.h>
using namespace std;


int yes_or_no;
const int max_node = 2000;				/*节点的最大数量*/
int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/

int Graph_test[max_node+1][max_node+1];		/*用于测试结果正确性的邻接矩阵*/

int same_degree = 0;
int same_degrees[max_node+1];
double similaryties[max_node+1];


int node_num;
int edge_num;

int solution1[max_node+1];				/*存储第一种方法求得的结果*/
int solution_num1 = 0;

int vertex[max_node+1];					/*存储节点是否查找过*/
int vertex_degree[max_node+1];			/*存储节点的度*/



void CreateGraph(void);
void Old_Cover();
void chooseNext(int choosed_node );


void main()
{
	memset(vertex,0,sizeof(vertex));//初始化，所有点都没找过
	CreateGraph();

	int min_node_num = 0;
	cout<<"\n\n****************************寻找支配集_贪心算法**************************************"<<endl;
	
	clock_t start, finish; 
	double  duration = 0.0; 
	start = clock(); 

	Old_Cover();
	
	finish = clock(); 
	duration = (double)(finish - start);//输出单位ms
	cout<<"Time used "<<duration<<endl;
	
	for(int i = 1; i <= solution_num1; i++)
		cout<<solution1[i]<<"  ";
	
	cout<<"\n total: "<<solution_num1<<endl;
	
	
	
	/**/
	/*这是测试结果是否正确的代码*/
	/**/
	memset(vertex,0,sizeof(vertex));
	
	
	for(i = solution_num1; i >= 1; i--)
	{
		vertex[solution1[i]] = -1;
		for(int j=1;j<=node_num;j++)
		{
			//cout<<Graph_test[i][j]<<"  ";
			if(Graph_test[solution1[i]][j] == 1)
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
			//cout<<i<<"  "<<j<<endl;
			k++;
		}
	}
	
	//cout<<"Edge num :"<<k<<endl;
	in.close();
	
	
	//计算节点的度
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
	}
	
}



void Old_Cover()
{
	int Maxdegree;
	int MaxdegreeNum = -1;
	//找到最大度节点
	
	while(1)
	{
		Maxdegree = -1;

		for(int i = 1; i <= node_num; i++ )			//找到最大度节点
		{
			
			if(vertex_degree[i] >= Maxdegree && vertex[Maxdegree] != -1)
			{
				Maxdegree = vertex_degree[i];
				MaxdegreeNum = i;
			}
			
		}


		memset(same_degrees,0,sizeof(same_degrees));
		same_degree = 0;
		
		for(int y = 1; y <= node_num; y++) 
		{
			if(vertex_degree[y] == Maxdegree && y != MaxdegreeNum)
			{
				
				same_degree ++;//相同度的个数加一
				same_degrees[same_degree] = y;		/*该数组存储的是顶点的编号*/
			}
		}
		
		same_degree ++;								/*注意，对被比较的那个点，也需要加入*/
		same_degrees[same_degree] = MaxdegreeNum;		
		
		
		for(y = 1; y <= same_degree; y++)			/*对相同度的节点处理*/
		{
			//cout<<"Same node num :"<<same_degrees[y]<<endl;
			if(vertex_degree[same_degrees[y]] == 0  && vertex[same_degrees[y]] != -1)		/*如果全部节点的度为0，而且有标记为不为-1，那么就应当全部加入答案中*/
			{
				solution_num1 ++;
				solution1[solution_num1] = same_degrees[y];
				vertex[same_degrees[y]] = -1;
				//cout<<"choosed... :"<<same_degrees[y]<<endl;
				//cout<<"Same degree node entered  (is 0) !   "<<same_degrees[y]<<endl;
				vertex_degree[i] --;																	
			}
			
		}
		
		chooseNext(same_degrees[same_degree]);				/*不加策略，选取任意一个即可*/
			
		int check_num = 0;
		for(int check = 1; check <= node_num; check++)
		{
			
			if(	vertex[check] == -1 )//只有孤立点
			{ 
				check_num++;
				
			}
			
		}		
		if(check_num == node_num)
		{
			cout<<"All Checked!"<<endl;
			break ;
		}
		
		
		
		
		}
	}
	
	
	
	
	void chooseNext(int choosed_node )
	{
		if(vertex[choosed_node] != -1)
		{
			solution_num1 ++;
			solution1[solution_num1] = choosed_node;
			//	cout<<"choosed... "<<choosed_node<<endl;
			vertex[choosed_node] = -1 ;
		}

		/*只要有加入，就需要更新*/	
		for(int adj = 1; adj <= node_num; adj++ )						//找到相关连接点，并标记该节点已经被查找,
		{
			if(Graph[ choosed_node ][adj] == 1 )
			{
				
				vertex_degree[ choosed_node ] --;
				
				vertex[adj] = -1;								/*覆盖住相邻的点，并改变其度*/
				vertex_degree[adj] --;
				//cout<<adj<<" covered"<<"  "<<endl;
				//cout<<"from :"<<MaxdegreeNum<<"  to : "<<i<<"   = "<<Graph[MaxdegreeNum][i]<<endl;
				
				for(int dd0 = 1; dd0 <= node_num; dd0++ )		/*相邻节点的邻居的度需要更新*/
				{
					
						if(Graph[dd0][adj] == 1 || Graph[adj][dd0] == 1)
						{
							Graph[adj][dd0] = Graph[dd0][adj] = 0;
							vertex_degree[dd0] --;
							vertex_degree[adj] --;
						}
					
					
				}
				
				
			}
			
		}
		
		
	}
