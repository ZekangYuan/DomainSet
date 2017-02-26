#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define node_num  800
#define M_0  5//��ʼʱ������Ľڵ���
#define du 3//�ڵ�Ķ�



int adjacentMatrix[node_num  + 1][node_num  + 1];
int initialNetwork[M_0 + 1];
int target_node[node_num *4+1];
int target_node_nums = 0;//�洢Ŀ��ڵ���б�����

void initialNetwork_M0_connected(); //���ӳ�ʼ��M_0���ڵ�
void updateTargetNodeList(int node);
void generateFreeScaleNetwork();
int showAdjacentMatrix();
void writeDataToFile(int edges);

int main()
{
	srand((unsigned)time(NULL));
	initialNetwork_M0_connected();
	generateFreeScaleNetwork();
	
	int edges = showAdjacentMatrix();
	writeDataToFile(edges);
	return 0;
}


//��ʼ�������ѡ��M_0���ڵ㹹����ͨ����
void initialNetwork_M0_connected()
{
	int i;
	int j;
	//int randomFirst;
	//int randomSecond;
	
	
	for(i = 1; i <= node_num ; i++)
	{
		for(j = 1; j <= node_num ; j++)
		{
			adjacentMatrix[i][j] = 0;
		}
	}
	
	
	//�������M_0
	for(i = 1; i <= M_0; i++)
	{
		initialNetwork[i] = rand()%node_num  + 1;
		for(j = 1; j < i;j ++)  //��֮ǰ�Ѿ������ĵ���жԱ� ������ظ��� ������ĵ�ĸ�����һ
		{
			if(initialNetwork[i] == initialNetwork[j])
			{
				i -- ;
				break;
			}
		}
	}
	
	
	
	
	for(i = 1; i <=M_0; i++)
	{
		printf("���ѡȡ�Ķ����ǣ�%d",initialNetwork[i]);
		printf("\n");
	}
	
	for(i = 1; i < M_0; i++)
	{
		adjacentMatrix[initialNetwork[i]][initialNetwork[i + 1]] = 1;
		adjacentMatrix[initialNetwork[i + 1]][initialNetwork[i]] = 1;
		printf("�����ߣ�%d - %d\n",initialNetwork[i],initialNetwork[i+1]);
		updateTargetNodeList(initialNetwork[i+1]);

	}
	
	adjacentMatrix[initialNetwork[M_0]][initialNetwork[1]] = 1;
	adjacentMatrix[initialNetwork[1]][initialNetwork[M_0]] = 1;
	printf("�����ߣ�%d - %d\n",initialNetwork[M_0],initialNetwork[1]);
	updateTargetNodeList(initialNetwork[1]);
	

	printf("\nĿ��ڵ��б�\n");
	for(i = 1; i <= target_node_nums; i++)
		printf("%d  ",target_node[i]);

	printf("\n��ʼ�����ޱ������----------------->\n");
	printf("\n");
}


void updateTargetNodeList(int node)
{
	
	 target_node_nums ++;
	 target_node[target_node_nums] = node;
	
}


void generateFreeScaleNetwork()
{
	int iter = M_0 + 1;
	while(iter <= node_num )
	{
			int same[node_num+1];
			memset(same,0,sizeof(same));//��ʼ����ÿ���ڵ��Ƕ���0������ÿ���ڵ㶼û�б�ѡ���
			/*
			for(int y = 1; y <=node_num; y++)
				printf("%d ",same[y]);
				*/
			int degree = 1;
			printf("\n���� --------------------------------- %d\n",iter);
			while(degree <= du)
			{
				double random = (double)rand()/RAND_MAX;
				printf("\n����� %f",random);

				int choosed ;
				if(random <= 0.5)//��1/2�ĸ��ʴ��б��о��������ѡ��һ��Ԫ��
				{
					
					choosed = 1+(int)(1.0*target_node_nums*rand()/(RAND_MAX+1.0));
					while(same[choosed] == -1)//�����ýڵ��Ѿ�ѡ�����
					{
					choosed = 1+(int)(1.0*target_node_nums*rand()/(RAND_MAX+1.0));
					
					}
					choosed = target_node[choosed];//�±�ת��Ϊ�ڵ���
					printf("\nchoosed : %d\n",choosed);

					adjacentMatrix[iter][choosed] = 1;
					adjacentMatrix[choosed][iter] = 1;
					printf("������%d���ߣ�%d - %d\n",degree,iter,choosed);
				}

				else
				{
					choosed = 1+(int)(1.0*node_num *rand()/(RAND_MAX+1.0));
					while(same[choosed] == -1)
					{
					choosed = 1+(int)(1.0*node_num *rand()/(RAND_MAX+1.0));
					
					}
					printf("\nchoosed : %d\n",choosed);

					adjacentMatrix[iter][choosed] = 1;
					adjacentMatrix[choosed][iter] = 1;
					printf("������%d���ߣ�%d - %d\n",degree,iter,choosed);
				}
					
				printf("��Ǹýڵ�/n");
				same[choosed] = -1;//��Ǹýڵ��Ѿ����ӹ���

				updateTargetNodeList(choosed);

					
				printf("\n");
				degree++;
				
			}
		iter++;
	}
	
}

int showAdjacentMatrix()
{
	int i;
	int j;
	int numberOfEdge = 0;
	//printf("show-----------------------> \n");
	for(i = 1; i <= node_num ; i++)
	{
		for(j = 1; j <= node_num ; j++)
		{
			//printf("%d",adjacentMatrix[i][j]);
			if(adjacentMatrix[i][j] == 1)
				numberOfEdge++;
		}

		//printf("\n");

	}

	printf("%d ���� \n",numberOfEdge/2);
	return numberOfEdge/2;
}


	void writeDataToFile(int edges)
	{
		FILE* fout;
		if(NULL == (fout = fopen("3freeScaleNetwork800.txt","w")))
		{
			exit(0);
		}


		fprintf(fout,"%d\n",node_num );
		fprintf(fout,"%d\n",edges);

		int i;
		int j;
		for(i = 1; i <= node_num ; i++)
		{
			for(j = 1; j <= node_num ; j++)
			{
				if(adjacentMatrix[i][j] == 1)
				fprintf(fout,"%d  %d \n",i,j);
			}

		

		}
	}