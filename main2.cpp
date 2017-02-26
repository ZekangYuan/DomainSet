#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<time.h>
using namespace std;


int yes_or_no;
const int max_node = 2000;				/*�ڵ���������*/
int Graph[max_node+1][max_node+1];		/*ʹ���ڽӾ���洢ͼ*/

int Graph_test[max_node+1][max_node+1];		/*���ڲ��Խ����ȷ�Ե��ڽӾ���*/

int same_degree = 0;
int same_degrees[max_node+1];
double similaryties[max_node+1];


int node_num;
int edge_num;

int solution1[max_node+1];				/*�洢��һ�ַ�����õĽ��*/
int solution_num1 = 0;

int vertex[max_node+1];					/*�洢�ڵ��Ƿ���ҹ�*/
int vertex_degree[max_node+1];			/*�洢�ڵ�Ķ�*/



void CreateGraph(void);
void Old_Cover();
void chooseNext(int choosed_node );


void main()
{
	memset(vertex,0,sizeof(vertex));//��ʼ�������е㶼û�ҹ�
	CreateGraph();

	int min_node_num = 0;
	cout<<"\n\n****************************Ѱ��֧�伯_̰���㷨**************************************"<<endl;
	
	clock_t start, finish; 
	double  duration = 0.0; 
	start = clock(); 

	Old_Cover();
	
	finish = clock(); 
	duration = (double)(finish - start);//�����λms
	cout<<"Time used "<<duration<<endl;
	
	for(int i = 1; i <= solution_num1; i++)
		cout<<solution1[i]<<"  ";
	
	cout<<"\n total: "<<solution_num1<<endl;
	
	
	
	/**/
	/*���ǲ��Խ���Ƿ���ȷ�Ĵ���*/
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
	}
	
}



void Old_Cover()
{
	int Maxdegree;
	int MaxdegreeNum = -1;
	//�ҵ����Ƚڵ�
	
	while(1)
	{
		Maxdegree = -1;

		for(int i = 1; i <= node_num; i++ )			//�ҵ����Ƚڵ�
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
				
				same_degree ++;//��ͬ�ȵĸ�����һ
				same_degrees[same_degree] = y;		/*������洢���Ƕ���ı��*/
			}
		}
		
		same_degree ++;								/*ע�⣬�Ա��Ƚϵ��Ǹ��㣬Ҳ��Ҫ����*/
		same_degrees[same_degree] = MaxdegreeNum;		
		
		
		for(y = 1; y <= same_degree; y++)			/*����ͬ�ȵĽڵ㴦��*/
		{
			//cout<<"Same node num :"<<same_degrees[y]<<endl;
			if(vertex_degree[same_degrees[y]] == 0  && vertex[same_degrees[y]] != -1)		/*���ȫ���ڵ�Ķ�Ϊ0�������б��Ϊ��Ϊ-1����ô��Ӧ��ȫ���������*/
			{
				solution_num1 ++;
				solution1[solution_num1] = same_degrees[y];
				vertex[same_degrees[y]] = -1;
				//cout<<"choosed... :"<<same_degrees[y]<<endl;
				//cout<<"Same degree node entered  (is 0) !   "<<same_degrees[y]<<endl;
				vertex_degree[i] --;																	
			}
			
		}
		
		chooseNext(same_degrees[same_degree]);				/*���Ӳ��ԣ�ѡȡ����һ������*/
			
		int check_num = 0;
		for(int check = 1; check <= node_num; check++)
		{
			
			if(	vertex[check] == -1 )//ֻ�й�����
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

		/*ֻҪ�м��룬����Ҫ����*/	
		for(int adj = 1; adj <= node_num; adj++ )						//�ҵ�������ӵ㣬����Ǹýڵ��Ѿ�������,
		{
			if(Graph[ choosed_node ][adj] == 1 )
			{
				
				vertex_degree[ choosed_node ] --;
				
				vertex[adj] = -1;								/*����ס���ڵĵ㣬���ı����*/
				vertex_degree[adj] --;
				//cout<<adj<<" covered"<<"  "<<endl;
				//cout<<"from :"<<MaxdegreeNum<<"  to : "<<i<<"   = "<<Graph[MaxdegreeNum][i]<<endl;
				
				for(int dd0 = 1; dd0 <= node_num; dd0++ )		/*���ڽڵ���ھӵĶ���Ҫ����*/
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
