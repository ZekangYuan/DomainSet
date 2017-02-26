//机会策略
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 17000;				/*节点的最大数量*/
int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/

int node_num;
int edge_num;

int solution[max_node+1];				/*存储第一种方法求得的结果*/
int solution_counts = 0;
int vertex[max_node+1];					/*存储节点信息 -1：已经被覆盖过   -2：已经移除*/
int vertex_degree[max_node+1];			/*存储节点的度*/
int weight[max_node+1];


void CreateGraph(char str[]);
void Greedy_Similarity(char str[]);
void AdjustWeight(int max_no);
int ChooseVertex();
double CalculateSimilary(int a,int b);


int func ;
void main()
{
	
	cout<<"\n\n****************************寻找支配集**************************************"<<endl;

	clock_t start, finish; 
	double  duration = 0.0; 
	int iter = 1;
	char str[50];
	fstream myout;
	myout.open("result_test.txt",ios::out|ios::app);
	int sum = 0;
	while(iter<=1)
	{
		//sprintf(str, "%d_%f_%d.txt" , 400,0.500000,iter);
		sprintf(str, "abiword_submatrix.txt" , 400,0.500000,iter);
		cout<<str<<endl;


	start = clock();
	myout<<"<--------- iter  "<<iter<<" --------->"<<endl;
	cout<<"<--------- iter  "<<iter<<" --------->"<<endl;
	Greedy_Similarity(str);
	finish = clock(); 
	duration = (double)(finish - start);//输出单位ms
	myout<<"Time used "<<duration<<endl;
	
		
	
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
	//cout<<"--------------"<<edge_num<<endl;
	
	for(i=1; i<=node_num;i++)
	{
		weight[i] = vertex_degree[i] = 0;//-----------------------------------此处错误原因是只将vertex[]初始化 没有将vertex_degree[]初始化
		for(j=1;j<=node_num;j++)
		{
			Graph[i][j]  = Graph[j][i] = 0;
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
		//cout<<i<<" 的度是 "<<weight[i]<<endl;
	}

	
}





void Greedy_Similarity(char str[])
{
	CreateGraph(str);
	solution_counts = 0;
	
	while(1)
	{
		
		int v = 0;//选取的节点编号
		v = ChooseVertex();
		//cout<<"choosed "<<v<<endl;
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
	int choosed_node = 0;
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
	
	else//如果最大的权重的节点有多个，选取相似度最小一个
	{
		cout<<"---   最大度的节点是  ---"<<temp_no<<"   度是 "<<temp_weight<<endl;
		for(int i = 1; i <= node_num; i++)
		{
			if(weight[i] == temp_weight)
			{
				same_no ++;
				same[same_no] = i;
				
			}
		}
		cout<<"有 "<<same_no<<"个和"<<temp_no<<"相同的最大度节点"<<endl<<endl<<"这些节点分别是 ："<<endl;

		
		//
		//
		//
		//此处使用策略 这些点度相同 但是覆盖节点的情况不同 计算这些节点之间的相似度
		if(same_no == 1)
		{
			choosed_node = temp_no;
			cout<<"只有一个度最大的节点 choosed : "<<choosed_node<<endl<<endl;
			return choosed_node;
		}
		
		else if(same_no == 2)
		{
			int choosed = 1+(int)(1.0*same_no*rand()/(RAND_MAX+1.0)); 
			cout<<"有两个度最大的节点 choosed : "<<choosed<<endl;
			return same[choosed];
		}
		
		else
		{
			double similary[max_node+1] ;
			for(int i = 1; i <= same_no; i++)//考察这些度相同的点
			{
				double temp_similary = 0;
				for(int j = 1; j <= same_no && i != j; j++)
				{
					temp_similary += CalculateSimilary(same[i],same[j]);
				}
				similary[same[i]] = temp_similary;
			}

			
		}


	

			
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
					if(Graph[i][k] == 1 )
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


double CalculateSimilary(int a,int b)
{
	double sum = 0.0;
	double qrt_A = 0;
	double qrt_B = 0;
	double temp = 0;
	double result = 0;
	int Graph_temp[max_node + 1][max_node + 1];

	
	qrt_A = 0.0;
	qrt_B = 0.0;
	sum = 0.0;
	temp = 0.0;

	for(int k = 1; k <= node_num; k++)
		for(int h = 1; h <=node_num; h++)
		{
			Graph_temp = Graph[k][h];
		}
	
	//预处理 节点的当前没有被覆盖的邻居参与计算相似度
	//如果无法覆盖节点的邻居，就将这条边设置为0
	for(int b1 = 1; b1 <=node_num; b1++)
	{
		if(Graph_temp[a][b1] == 1 && vertex[b] == -1)
			Graph_temp[a][b1] = 0;

		if(Graph_temp[b][b1] == 1 && vertex[b] == -1)
			Graph_temp[b][b1] = 0;
	}

	for(int bi = 1; bi <= node_num; bi++)
	{
		sum += Graph[a][bi]*Graph[b][bi];
		//cout<<Graph[node][bi]<<" * "<<Graph[j][bi]<<" + ";
		qrt_A += Graph[a][bi]*Graph[a][bi];
		qrt_B += Graph[b][bi]*Graph[b][bi];
	}
	if(qrt_A == 0 || qrt_B  == 0)
		result += 0;

	else
		result += 1.0*sum/(sqrt(qrt_A*qrt_B));
	
	//cout<<"  "<<node<<"和"<<j<<"的内积是 : "<<sum<<" / "<<sqrt(qrt_A)*sqrt(qrt_B)<<" = "<<temp<<endl;
	
	//cout<<similary[node];
	

	//cout<<node<<"的相似度是 : "<<result<<endl;
	return result;
}