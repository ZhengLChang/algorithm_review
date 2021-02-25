#include<stdio.h>
#include<string.h>
#include"jhash.h"

//常规算法的黄金分隔
#define VOICE_HASH_GOLDEN_INTERER   0x9e370001

//hash桶的大小为2的11次方，即2047+1
#define HASH_SIZE                   2048

//常用的黄金分隔的hash算法
#define VOICE_HASH_INTERGER(uiKey,uiHash) \
{\
    uiHash = uiKey * (VOICE_HASH_GOLDEN_INTERER);\
    uiHash = uiHash >> 21;\
}

//统计指定节点数量的hash桶冲突情况
void show_hash_node(int num,int *TestArray,int IsJhash)
{
    int conflic_num = 0;
    char *pcHashName = "common";
    int i = 0;
    for(i=0;i<HASH_SIZE;i++)
    {
        if(num == TestArray[i])
        {
            conflic_num++;
        }
    }
    if (1 == IsJhash)
    {
        pcHashName = "Jhash";
    }

    printf("算法%s:节点数为%d的hash桶的个数为:%d\n",pcHashName,num,conflic_num);
    return;
}

//显示hash冲突的情况
void show_hash_conflict(int *TestArray,int IsJhash)
{
    //统计节点数为0到9的hash桶冲突个数
    int i = 0;
    for(i=0;i<10;i++)
    {
        show_hash_node(i,TestArray,IsJhash);
    }
    return;
}
void main()
{

    int index      =0;
    long HashIndex =0;
    long JHashIndex=0;

    //测试key样本为0到1024
    int MaxIndex   =1024;

    //每一个HashIndex对应数组里的一个节点
    int TestArray1[HASH_SIZE];
    int TestArray2[HASH_SIZE];
    memset(TestArray1,0,sizeof(TestArray1));
    memset(TestArray2,0,sizeof(TestArray2));    

    for(index=0;index<MaxIndex;index++)
    {
        //使用传统Hash算法计算HashIndex
        VOICE_HASH_INTERGER(index,HashIndex);
        //在数组对应的节点+1,模拟实际项目中下挂的数据结构
        TestArray1[HashIndex] +=1;

        //使用Jhash算法计算JHashIndex
        JHashIndex = jhash_1word(index,VOICE_HASH_GOLDEN_INTERER);
        //只取指定位数的
        JHashIndex = JHashIndex & (HASH_SIZE-1);
        //在数组对应的节点+1,模拟实际项目中下挂的数据结构
        TestArray2[JHashIndex] +=1;     
    }

    //统计传统的Hash冲突的情况
    show_hash_conflict(TestArray1,0);
    //统计JHash冲突的情况
    show_hash_conflict(TestArray2,1);
}
