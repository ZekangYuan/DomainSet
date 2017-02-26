#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define node_num  800
#define M_0  5//初始时刻网络的节点数
#define du 3//节点的度



int adjacentMatrix[node_num  + 1][node_num  + 1];
int initialNetwork[M_0 + 1];
int target_node[node_num *4+1];
int target_node_nums = 0;//存储目标节点的列表长度

void initialNetwork_M0_connected(); //连接初始的M_0个节点
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


//初始化：随机选择M_0个节点构成联通网络
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
	
	
	//随机产生M_0
	for(i = 1; i <= M_0; i++)
	{
		initialNetwork[i] = rand()%node_num  + 1;
		for(j = 1; j < i;j ++)  //与之前已经产生的点进行对比 如果有重复的 则产生的点的个数减一
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
		printf("随机选取的顶点是：%d",initialNetwork[i]);
		printf("\n");
	}
	
	for(i = 1; i < M_0; i++)
	{
		adjacentMatrix[initialNetwork[i]][initialNetwork[i + 1]] = 1;
		adjacentMatrix[initialNetwork[i + 1]][initialNetwork[i]] = 1;
		printf("产生边：%d - %d\n",initialNetwork[i],initialNetwork[i+1]);
		updateTargetNodeList(initialNetwork[i+1]);

	}
	
	adjacentMatrix[initialNetwork[M_0]][initialNetwork[1]] = 1;
	adjacentMatrix[initialNetwork[1]][initialNetwork[M_0]] = 1;
	printf("产生边：%d - %d\n",initialNetwork[M_0],initialNetwork[1]);
	updateTargetNodeList(initialNetwork[1]);
	

	printf("\n目标节点列表\n");
	for(i = 1; i <= target_node_nums; i++)
		printf("%d  ",target_node[i]);

	printf("\n开始产生无标度网络----------------->\n");
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
			memset(same,0,sizeof(same));//初始化，每个节点标记都是0，代表每个节点都没有被选择过
			/*
			for(int y = 1; y <=node_num; y++)
				printf("%d ",same[y]);
				*/
			int degree = 1;
			printf("\n顶点 --------------------------------- %d\n",iter);
			while(degree <= du)
			{
				double random = (double)rand()/RAND_MAX;
				printf("\n随机数 %f",random);

				int choosed ;
				if(random <= 0.5)//以1/2的概率从列表中均匀随机的选择一个元素
				{
					
					choosed = 1+(int)(1.0*target_node_nums*rand()/(RAND_MAX+1.0));
					while(same[choosed] == -1)//代表该节点已经选择过了
					{
					choosed = 1+(int)(1.0*target_node_nums*rand()/(RAND_MAX+1.0));
					
					}
					choosed = target_node[choosed];//下标转换为节点编号
					printf("\nchoosed : %d\n",choosed);

					adjacentMatrix[iter][choosed] = 1;
					adjacentMatrix[choosed][iter] = 1;
					printf("产生第%d条边：%d - %d\n",degree,iter,choosed);
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
					printf("产生第%d条边：%d - %d\n",degree,iter,choosed);
				}
					
				printf("标记该节点/n");
				same[choosed] = -1;//标记该节点已经连接过了

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

	printf("%d 条边 \n",numberOfEdge/2);
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
