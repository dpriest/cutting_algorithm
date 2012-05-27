#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> /*包含动态内存分配函数的头文件*/
#include "lib/functions.c"
//node链表，存储下料方式
typedef struct node
{
    //type分别对应该种下料方式还总每种原料的数量
	int type[8];
	struct node *link;
}way;
//计算总共需要的原料数
int total_needs(int type_num,int type_lengths[], int needs[])
{
	int i, total_meterial = 0;
	for (i = 0; i < type_num; ++i)
	{
		total_meterial += type_lengths[i]*needs[i];
	}
	return total_meterial;
}
//为每种坯料需要的原料排序
void get_marks(int type_lengths[], int type_num, int marks[])
{
	int i, j, key, max;
	for (i = 0; i < type_num; ++i)
	{
		key = 0;
		max = type_lengths[0];
		for (j = 0; j < type_num; ++j)
		{
			if (type_lengths[j] > max){
				key = j;
				max = type_lengths[j];
			}
		}
		type_lengths[key] = -1;
        //marks为最后从大到小排列的种数
		marks[i] = key;
	}
}
//获取所有下料方式
void get_all_ways(int per_length, int type_lengths[], int type_num, int type[])
{
	int i, j;
	for (i = 0; i < type_num; ++i)
	{
		for (j = i; j < type_num; ++j)
		{
		}
	}
}
//生成下料数据，未完成
way * create(int per_length, int type_lengths[], int type_num)
{
	way *p,*h,*s; /* *h保存表头结点的指针，*p指向当前结点的前一个结点，*s指向当前结点*/
	int i; /*计数器*/
	if((h=(way *)malloc(sizeof(way)))==NULL) /*分配空间并检测*/
	{
		printf("不能分配内存空间!");
		exit(0);
	}
	h->type[0]=0; /*把表头结点的数据域置空*/
	h->link=NULL; /*把表头结点的链域置空*/
	p=h; /*p指向表头结点*/
	for(i=0;i<type_num;i++)
	{
		if((s= (way *) malloc(sizeof(way)))==NULL) /*分配新存储空间并检测*/
		{
			printf("no enough size");
			exit(0);
		}
		p->link=s; /*把s的地址赋给p所指向的结点的链域，这样就把p和s所指向的结点连接起来了*/
		get_all_ways(per_length, type_lengths, type_num, s->type);
		s->link=NULL;
		p=s;
	}
	return(h);
}
int main()
{
    //原材料总长度
	int init_meterial=200;
    //坯料种数
	int type_num = 8;
    //各坯料需要的原料长度
	int type_lengths[8] = {2,1,4,3,3,6,4,5}, marks[8];
    //每段原料长度
	int per_length = 10;
    //每种坯料需要的数目
	int needs[8] = {2,7,4,3,3,6,4,5};
    //生成所有坯料需要的总原料
	int total;
	total = total_needs(type_num, type_lengths, needs);
    //原材料不足
	if (total > init_meterial) {
		printf("meterial not enough\n");
		return 0;
	}
    //根据坯料需要的原料排序
	get_marks(type_lengths, type_num, marks);
    //打印数组
	array_dump(marks, type_num);
	return 0;
}
