//�������
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

const int max_node = 2000;				/*�ڵ���������*/
int node_num = max_node;
int edge_num;
const int proper = 1;					/*�漴ͼ�����ߵĸ���*/
int random;								/*���ڲ��������*/			
ofstream fout;

int Graph[max_node+1][max_node+1];		/*ʹ���ڽӾ���洢ͼ*/
int Graph_test[max_node+1][max_node+1];
double weight[max_node+1];				/*�洢�ڵ�Ļ���ֵ*/
int covered_num = 0;					/*�洢�����ǽڵ�ĸ���*/

int vertex[max_node+1];					/*�洢�ڵ��Ƿ���ҹ�*/
int vertex_degree[max_node+1];			/*�洢�ڵ�Ķ�*/

int solution_counts = 0;				/*�洢�𰸵ĸ���*/
int solution[max_node+1];				/*�洢��*/

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
	
	fout<<"\n\n****************************Ѱ��֧�伯**************************************"<<endl;
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
	
	
	
	/*���ǲ��Խ���Ƿ���ȷ�Ĵ���
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
		cout<<"�ļ���ʧ��!"<<endl;
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
	
	//����ڵ�Ķ�
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
	}
	
	
	
	//����ڵ�� Weightֵ
	//weight(w)ֵ����w���ھ�v��vote(v)֮��
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
	//1.��һ����ѡȡ���Weight()ֵ�ĵ����֧�伯
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
	//2.�ڶ�������������ȫ����Ϣ�ĸ��£������������ھ�
	//
	//
	//����1:���붥���weight()��Ϊ-1
	//����2:���붥��ı����Ϊ-1
	//����3:����ڵ���ھӽڵ�ı����Ϊ-1,���붥�����ھӽڵ�ı�����
	//����4:���ھӽڵ������Ľڵ㻹δ���ǣ�������ȵı仯��weight()�ı仯
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
	//3.�ڶ��������¼�������weight()ֵ
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

