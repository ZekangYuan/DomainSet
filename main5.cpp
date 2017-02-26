//���ƺ��� �ȴ��
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 1500;				/*�ڵ���������*/
int Graph[max_node+1][max_node+1];		/*ʹ���ڽӾ���洢ͼ*/

int node_num;
int edge_num;

int solution[max_node+1];				/*�洢��һ�ַ�����õĽ��*/
int solution_counts = 0;
int vertex[max_node+1];					/*�洢�ڵ���Ϣ -1���Ѿ������ǹ�   -2���Ѿ��Ƴ�*/
int vertex_degree[max_node+1];			/*�洢�ڵ�Ķ�*/
int weight[max_node+1];

void CreateGraph(char str[]);
void Greedy(char str[]);
void AdjustWeight(int max_no);
int ChooseVertex();


void main()
{
	//̰��
	
	cout<<"\n\n****************************Ѱ��֧�伯**************************************"<<endl;
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
		myout<<"------��"<<iter<<"�ε���------"<<endl;
		cout<<"------��"<<iter<<"�ε���------"<<endl;
		start = clock();
		Greedy(str);
		finish = clock(); 
		duration = (double)(finish - start);//�����λms
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
					//cout<<solution1[i]<<" ���ڵĶ����� ��"<<j<<endl;
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
	
	myout<<"1000�ε���֧�伯�ܸ��� �� "<<sum<<endl;
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
		cout<<"�ļ���ʧ��!"<<endl;
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
	
	
	//����ڵ�Ķ�
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;//Ϊ0 ȫ��û�и���
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
		
		weight[i] = vertex_degree[i] + 1;//�ڵ��Ȩ������Ϊ�ȼ�һ
		cout<<"�ڵ�"<<i<<"�Ķ��� ��"<<weight[i]<<endl;
	}
	
}





void Greedy(char str[])
{
	CreateGraph(str);
	solution_counts = 0;
	while(1)
	{
		
		int v = 0;//ѡȡ�Ľڵ���
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
	
	else//�������Ȩ�صĽڵ��ж�������ѡȡһ��
	{
		for(int i = 1; i <= node_num; i++)
		{
			if(weight[i] == temp_weight)
			{
				same_no ++;
				same[same_no] = i;
				
			}
		}
		//cout<<"�� "<<same_no<<"����ͬ�����Ƚڵ�"<<endl;
		choosed = 1+(int)(1.0*same_no*rand()/(RAND_MAX+1.0)); 
		//choosed = same_no;
		return same[choosed];
		
	}
}

void AdjustWeight(int max_no)
{
	weight[max_no] = 0;//ѡ�еĽڵ�Ȩ�ظ�Ϊ0
	
	for(int i = 1; i <= node_num; i++)//����ѡ�нڵ���ھ� ����Ȩ�ش���0
	{
		if(Graph[max_no][i] == 1  && weight[i] > 0)
		{	
			if(vertex[max_no] != -1)//���ѡ�е�����ڵ�û�и���ס����ôѡȡ�ýڵ�����ھӱ����ǵĴ������һ�������ھӵ�Ȩ�ؼ�һ
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


