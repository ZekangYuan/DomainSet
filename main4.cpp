//���ƺ���
#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 2000;				/*�ڵ���������*/
int Graph[max_node+1][max_node+1];		/*ʹ���ڽӾ���洢ͼ*/

int Graph_test[max_node+1][max_node+1];		/*���ڲ��Խ����ȷ�Ե��ڽӾ���*/
int Graph_covered[max_node+1][max_node+1];

long double similaryties[max_node+1];


int node_num;
int edge_num;
int covered_num = 0;
int edge_changed = 0;


int solution[max_node+1];				/*�洢��һ�ַ�����õĽ��*/
int solution_counts = 0;
int vertex[max_node+1];					/*�洢�ڵ��Ƿ���ҹ�*/
int vertex_degree[max_node+1];			/*�洢�ڵ�Ķ�*/
int weight[max_node+1];					/*�洢�ڵ��ܸ�ס��ǰδ����ס�Ľڵ�ĸ�����ע����Ȳ�ͬ*/

void CreateGraph(void);
long double CalculateSimilary(int node);
void Old_Cover();
double function(double a,double b);

void main()
{
	memset(vertex,0,sizeof(vertex));//��ʼ�������е㶼û�ҹ�
	CreateGraph();

	int min_node_num = 0;
	
	cout<<"\n\n****************************Ѱ��֧�伯**************************************"<<endl;
	clock_t start, finish; 
	double  duration = 0.0; 
	start = clock(); 
	
	Old_Cover();
	
	
	finish = clock(); 
	duration = (double)(finish - start);//�����λms
	cout<<"Time used "<<duration<<endl;
	//for(int s = 1; s <= node_num; s++)
	//CalculateSimilary(s);
	
	
	for(int i = 1; i <= solution_counts; i++)
		cout<<solution[i]<<"  ";
	
	cout<<"\n total: "<<solution_counts<<endl;
	
	
	
	/**/
	/*���ǲ��Խ���Ƿ���ȷ�Ĵ���*/
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
		//cout<<solution1[i]<<" ���ڵĶ����� ��"<<j<<endl;
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
		if(node != j && vertex[j] != -1)								//����ýڵ��������ڵ�����ƶ�֮��	
		{											//�˴���Ӧ�ü������������нڵ�����ƶȣ���Ӧ��������δ���ǵĽڵ�
			
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
			//cout<<"  "<<node<<"��"<<j<<"���ڻ��� : "<<sum<<" / "<<sqrt(qrt_A)*sqrt(qrt_B)<<" = "<<temp<<"  "<<j<<" �ı��Ϊ "<<vertex[j]<<endl;
			if(temp > 0)
				similary = similary + 1.0*temp;		
		}
		
	}
	//cout<<node<<"�����ƶ��� �� "<<1.0/similary<<endl;
	return 1.0/similary;
}





void Old_Cover()
{
	while(1)
	{
		//
		//��һ����ȡ���similaryties[]ֵ�Ķ������֧�伯
		//
		//
			//for(int j = 1; j <= node_num; j++)
		//{
		//	cout<<"�ڵ㣺"<<j<<" ���ǣ� "<<weight[j]<<"  "<<endl;
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
			//cout<<node<<"��Ŀ�꺯��ֵ�� ----------------------------------- : "<<similaryties[node]<<" ���ж�Ϊ "<<1.0 * weight[node]/total_weight<<endl;
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
		//2.�ڶ�������������ȫ����Ϣ�ĸ��£������������ھ�
		//
		//
		//����1:���붥���similaryties()��Ϊ-1
		//����2:���붥��ı����Ϊ-1
		//����3:����ڵ���ھӽڵ�ı�ǲ���Ϊ-1,���Ǹ���ѡ�еĶ����Ƿ񱻸��ǣ��ı�����Ķ�
		//����4:���ھӽڵ������Ľڵ㻹δ���ǣ�������ȵı仯��similaryties()�ı仯
		//����5:���ݽڵ��Ƿ��Ѿ����ǣ�����ͼ
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
		//3.�ڶ��������¼�������similarytiesֵ
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
			//cout<<tot<<" �Ķ��� "<<vertex_degree[tot]<<"  ����� "<<vertex[tot]<<endl;
		}
		for(i = 1; i<= node_num; i++)
		{
			if(vertex[i] != -1)
			{
				similaryties[i] = function(CalculateSimilary(i) , 1.0*vertex_degree[i]/total_degree);
				//cout<<i<<"��Ŀ�꺯��ֵchanged++++++++++++++++++++++++++++++++ : "<<similaryties[i]<<" ���ж�ռ��Ϊ "<<1.0 * vertex_degree[i]/total_degree<<"  "<<
					//" �� "<<vertex_degree[i]<<"    �ܶ�  "<<total_degree<<endl;
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
		cout<<"�ļ���ʧ��!"<<endl;
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
	
	
	//����ڵ�Ķ�
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
		weight[i] = vertex_degree[i] + 1;
	}
	
	cout<<k<<" ���� "<<endl;
}


double function(double a, double b)
{
	return a*b;
}