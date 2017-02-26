//近似函数
#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 2000;				/*节点的最大数量*/
int Graph[max_node+1][max_node+1];		/*使用邻接矩阵存储图*/

int Graph_test[max_node+1][max_node+1];		/*用于测试结果正确性的邻接矩阵*/
int Graph_covered[max_node+1][max_node+1];

long double similaryties[max_node+1];


int node_num;
int edge_num;
int covered_num = 0;
int edge_changed = 0;


int solution[max_node+1];				/*存储第一种方法求得的结果*/
int solution_counts = 0;
int vertex[max_node+1];					/*存储节点是否查找过*/
int vertex_degree[max_node+1];			/*存储节点的度*/
int weight[max_node+1];					/*存储节点能盖住当前未被盖住的节点的个数，注意与度不同*/

void CreateGraph(void);
long double CalculateSimilary(int node);
void Old_Cover();
double function(double a,double b);

void main()
{
	memset(vertex,0,sizeof(vertex));//初始化，所有点都没找过
	CreateGraph();

	int min_node_num = 0;
	
	cout<<"\n\n****************************寻找支配集**************************************"<<endl;
	clock_t start, finish; 
	double  duration = 0.0; 
	start = clock(); 
	
	Old_Cover();
	
	
	finish = clock(); 
	duration = (double)(finish - start);//输出单位ms
	cout<<"Time used "<<duration<<endl;
	//for(int s = 1; s <= node_num; s++)
	//CalculateSimilary(s);
	
	
	for(int i = 1; i <= solution_counts; i++)
		cout<<solution[i]<<"  ";
	
	cout<<"\n total: "<<solution_counts<<endl;
	
	
	
	/**/
	/*这是测试结果是否正确的代码*/
	/**/
	/*
	*/
	memset(vertex,0,sizeof(vertex));
	
	  
		for(i = solution_counts; i >= 1; i--)
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
	
}





long double CalculateSimilary(int node)
{
	double sum = 0.0;
	double qrt_A = 0.0;
	double qrt_B = 0.0;
	double temp = 0.0;
	long double similary = 0.0;
	
	for(int j = 1; j <= node_num; j++)
	{
		//cout<<Graph[node][j]<<" ";
		if(node != j && vertex[j] != -1)								//计算该节点与其他节点的相似度之和	
		{											//此处不应该计算与其他所有节点的相似度，而应该是其他未覆盖的节点
			
			qrt_A = 0.0;
			qrt_B = 0.0;
			sum = 0.0;
			temp = 0.0;
			for(int bi = 1; bi <= node_num; bi++)
			{
				if(Graph[node][bi] != 1 || weight[node] <= 0 || weight[bi] <= 0)
					Graph[node][bi] = 0;
				if(Graph[j][bi] != 1 || weight[j] <= 0 || weight[bi] <= 0)
					Graph[j][bi] = 0;
				sum += Graph[node][bi]*Graph[j][bi];
				//cout<<Graph[node][bi]<<" * "<<Graph[j][bi]<<" + ";
				qrt_A += Graph[node][bi]*Graph[node][bi];
				qrt_B += Graph[j][bi]*Graph[j][bi];
			}
			temp = 1.0*sum/(sqrt(qrt_A*qrt_B));
			//cout<<"  "<<node<<"和"<<j<<"的内积是 : "<<sum<<" / "<<sqrt(qrt_A)*sqrt(qrt_B)<<" = "<<temp<<"  "<<j<<" 的标记为 "<<vertex[j]<<endl;
			if(temp > 0)
				similary = similary + 1.0*temp;		
		}
		
	}
	//cout<<node<<"的相似度是 ： "<<1.0/similary<<endl;
	return 1.0/similary;
}





void Old_Cover()
{
	while(1)
	{
		//
		//第一步：取最大similaryties[]值的顶点加入支配集
		//
		//
			//for(int j = 1; j <= node_num; j++)
		//{
		//	cout<<"节点："<<j<<" 度是： "<<weight[j]<<"  "<<endl;
		//}
	
		int total_weight = 0;
		for(int tot = 1; tot <= node_num; tot++)
		{
			if(weight[tot] >= 0)
			total_weight += weight[tot];
		}
		for(int node = 1; node <= node_num; node++)
		{
			if(vertex_degree[node] == 0 && vertex[node] != -1)
			{
				solution_counts++;
				solution[solution_counts] = node ;
				vertex[node] = -1;
				similaryties[node] = -1;
				continue;
			}
			
			if(weight[node] > 0)
			{
			similaryties[node] = function(CalculateSimilary(node) ,  1.0*weight[node]/total_weight );
			//cout<<node<<"的目标函数值是 ----------------------------------- : "<<similaryties[node]<<" 其中度为 "<<1.0 * weight[node]/total_weight<<endl;
			}
		}
		
		double max_value = 0.0;
		int max_no = -1;
		for(int i = 1; i <= node_num; i++ )		
		{
			
			if(similaryties[i] >= max_value && vertex[i] != -1)
			{
				max_value = similaryties[i];
				max_no = i;
			}
			
		}


		if(max_no == -1)
			return;
		
		else
		{
		cout<<max_no<<" choosed ,value is"<<max_value<<endl;
		solution_counts++;
		solution[solution_counts] = max_no ;
		vertex[max_no] = -1;
		//cout<<"Max_no = "<<max_no<<endl;
		//cout<<"Max_value = "<<max_value<<endl;

		
		//
		//2.第二步，加入后进行全局信息的更新，包括加入点的邻居
		//
		//
		//更新1:加入顶点的similaryties()变为-1
		//更新2:加入顶点的标记设为-1
		//更新3:加入节点的邻居节点的标记不设为-1,而是根据选中的顶点是否被覆盖，改变自身的度
		//更新4:与邻居节点相连的节点还未覆盖，更改其度的变化，similaryties()的变化
		//更新5:根据节点是否已经覆盖，更新图
		similaryties[max_no] = -1;
	
		
		for(i = 1; i <= node_num; i++)
		{
			if(Graph[max_no][i] == 1 && weight[i] > 0)
			{
				//cout<<"Covered num = "<<i<<endl<<endl;
				if(vertex[max_node] == 0)
				{
					weight[i] --;
					
				}
				if(vertex[i] == 0)
				{
					vertex[i] = -1;
					weight[i] --;
					for(int j = 1; j <= node_num; j++)
					{
						if(Graph[i][j] == 1 && weight[j] > 0)
						{
							weight[j] --;
						}
					}
				}	
			}		
		}
		vertex[max_no] = -1;
		covered_num ++;
		//cout<<"Total covered : "<<covered_num<<endl;
		//cout<<"Edge changed :"<<edge_changed<<endl<<endl;
		
		
		
		
		//
		//3.第二步，重新计算各点的similaryties值
		//
/*
		for(int s = 1; s <= node_num; s++)
			for(int t = 1; t < node_num; t++)
			{
				if(vertex[s] == -1 && vertex[t] == -1)
					Graph[s][t] = 0;
			}

		for(tot = 1; tot <= node_num; tot++)
		{
			if(vertex[tot] != -1)
			total_degree += vertex_degree[tot];
			//cout<<tot<<" 的度是 "<<vertex_degree[tot]<<"  标记是 "<<vertex[tot]<<endl;
		}
		for(i = 1; i<= node_num; i++)
		{
			if(vertex[i] != -1)
			{
				similaryties[i] = function(CalculateSimilary(i) , 1.0*vertex_degree[i]/total_degree);
				//cout<<i<<"的目标函数值changed++++++++++++++++++++++++++++++++ : "<<similaryties[i]<<" 其中度占比为 "<<1.0 * vertex_degree[i]/total_degree<<"  "<<
					//" 度 "<<vertex_degree[i]<<"    总度  "<<total_degree<<endl;
			}
			
		}
	*/	
	
		}

		bool flag =true;
		for(i = 1; i <= node_num; i++)
		{
			if(vertex[i] == 0)
			{
				flag = false;
				break;
			}
			
		}
		if(flag || max_no == -1)
		{
			cout<<"All checked !"<<endl;
			return ;
		}

	}
		
		

		return ;
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
		similaryties[i] = 0.0;
		for(j=1;j<=node_num;j++)
		{
			Graph_covered[i][j] = Graph_test[i][j] = Graph[i][j] = 0;
		}
	}
	
	while(!in.eof())
	{
		in>>i>>j;
		if(Graph[i][j])
			continue;
		
		else
		{
			Graph_covered[i][j] = Graph_covered[j][i] = Graph_test[i][j] = Graph_test[j][i] = Graph[i][j] = Graph[j][i] = 1;
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
		weight[i] = vertex_degree[i] + 1;
	}
	
	cout<<k<<" 条边 "<<endl;
}


double function(double a, double b)
{
	return a*b;
}