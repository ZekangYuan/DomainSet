//�������
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;


const int max_node = 17000;				/*�ڵ���������*/
int Graph[max_node+1][max_node+1];		/*ʹ���ڽӾ���洢ͼ*/

int node_num;
int edge_num;

int solution[max_node+1];				/*�洢��һ�ַ�����õĽ��*/
int solution_counts = 0;
int vertex[max_node+1];					/*�洢�ڵ���Ϣ -1���Ѿ������ǹ�   -2���Ѿ��Ƴ�*/
int vertex_degree[max_node+1];			/*�洢�ڵ�Ķ�*/
int weight[max_node+1];


void CreateGraph(char str[]);
void Greedy_Similarity(char str[]);
void AdjustWeight(int max_no);
int ChooseVertex();
double CalculateSimilary(int a,int b);


int func ;
void main()
{
	
	cout<<"\n\n****************************Ѱ��֧�伯**************************************"<<endl;

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
	duration = (double)(finish - start);//�����λms
	myout<<"Time used "<<duration<<endl;
	
		
	
	myout<<"֧�伯����"<<solution_counts<<endl;
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
	//cout<<"--------------"<<edge_num<<endl;
	
	for(i=1; i<=node_num;i++)
	{
		weight[i] = vertex_degree[i] = 0;//-----------------------------------�˴�����ԭ����ֻ��vertex[]��ʼ�� û�н�vertex_degree[]��ʼ��
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
	
	
	//����ڵ�Ķ�
	for(i = 1; i <= node_num; i++)
	{
		vertex[i] = 0;//Ϊ0 ȫ��û�и���
		for(j = 1; j <= node_num; j++)
			vertex_degree[i] += Graph[i][j];
		
		weight[i] = vertex_degree[i] + 1;//�ڵ��Ȩ������Ϊ�ȼ�һ
		//cout<<i<<" �Ķ��� "<<weight[i]<<endl;
	}

	
}





void Greedy_Similarity(char str[])
{
	CreateGraph(str);
	solution_counts = 0;
	
	while(1)
	{
		
		int v = 0;//ѡȡ�Ľڵ���
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
	
	else//�������Ȩ�صĽڵ��ж����ѡȡ���ƶ���Сһ��
	{
		cout<<"---   ���ȵĽڵ���  ---"<<temp_no<<"   ���� "<<temp_weight<<endl;
		for(int i = 1; i <= node_num; i++)
		{
			if(weight[i] == temp_weight)
			{
				same_no ++;
				same[same_no] = i;
				
			}
		}
		cout<<"�� "<<same_no<<"����"<<temp_no<<"��ͬ�����Ƚڵ�"<<endl<<endl<<"��Щ�ڵ�ֱ��� ��"<<endl;

		
		//
		//
		//
		//�˴�ʹ�ò��� ��Щ�����ͬ ���Ǹ��ǽڵ�������ͬ ������Щ�ڵ�֮������ƶ�
		if(same_no == 1)
		{
			choosed_node = temp_no;
			cout<<"ֻ��һ�������Ľڵ� choosed : "<<choosed_node<<endl<<endl;
			return choosed_node;
		}
		
		else if(same_no == 2)
		{
			int choosed = 1+(int)(1.0*same_no*rand()/(RAND_MAX+1.0)); 
			cout<<"�����������Ľڵ� choosed : "<<choosed<<endl;
			return same[choosed];
		}
		
		else
		{
			double similary[max_node+1] ;
			for(int i = 1; i <= same_no; i++)//������Щ����ͬ�ĵ�
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
	
	//Ԥ���� �ڵ�ĵ�ǰû�б����ǵ��ھӲ���������ƶ�
	//����޷����ǽڵ���ھӣ��ͽ�����������Ϊ0
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
	
	//cout<<"  "<<node<<"��"<<j<<"���ڻ��� : "<<sum<<" / "<<sqrt(qrt_A)*sqrt(qrt_B)<<" = "<<temp<<endl;
	
	//cout<<similary[node];
	

	//cout<<node<<"�����ƶ��� : "<<result<<endl;
	return result;
}