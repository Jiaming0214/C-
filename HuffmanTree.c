#include <stdio.h>
#include <stdlib.h>

typedef struct HuffmanTree
{ //定义HuffmanTree的数据结构
    int data;
    struct HuffmanTree *lchild;
    struct HuffmanTree *rchild;
} HuffmanTreeNode, *HuffmanT;

typedef struct Queue
{ //定义队列的数据结构
    int data;
    struct Queue *next;
} QueueNode, *Que;

int CreateQueue(Que q)
{ //先将输入的数据以队列的方式存储
    int i = 1, k;
    Que last = q;
    while (1)
    {
        QueueNode *p = (QueueNode *)malloc(sizeof(QueueNode));
        if (p == NULL)
        {
            printf("CreateQueue fail:malloc error");
            return i - 1;
        }
        printf("请输入第%d个数据的值（tips：-1表示结束输入）：", i);
        scanf("%d", &k);
        getchar();
        if (k == -1)
        {
            return i - 1;
        }
        p->data = k;
        p->next = NULL;
        while (last->next)
        {
            last = last->next;
        }
        last->next = p;
        i++;
    }
}

HuffmanT QueueToHuffmanTree(Que q, int cnt)
{ //将队列转化成HuffmanTree
    int i = 0, j;
    Que last = q;
    HuffmanT HuffmanTreeRoot = NULL;
    HuffmanT HuTrNoArr[cnt]; //定义了一个HuffmanT的数组

    while (last->next)
    { //先将输入的数据队列转换成一个HuffmanNode的数组
        HuffmanT pre = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        pre->data = last->next->data;
        pre->lchild = pre->rchild = NULL;
        HuTrNoArr[i] = pre;
        i++;
        last = last->next;
    }

    for (i = 1; i < cnt; i++)
    { //对这个数组里面的值进行处理，使其转换成一个HuffmanTree
        int k1 = -1, k2;
        for (j = 0; j < cnt; j++)
        {
            if (k1 == -1 && HuTrNoArr[j] != NULL)
            {
                k1 = j;
                continue;
            }
            if (HuTrNoArr[j] != NULL)
            {
                k2 = j;
                break;
            }
        }

        for (j = k2; j < cnt; j++)
        {
            if (HuTrNoArr[j] != NULL)
            {
                if (HuTrNoArr[j]->data < HuTrNoArr[k1]->data)
                {
                    k2 = k1;
                    k1 = j;
                }
                else if (HuTrNoArr[j]->data < HuTrNoArr[k2]->data)
                {
                    k2 = j;
                }
            }
        }

        HuffmanTreeRoot = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        HuffmanTreeRoot->data = HuTrNoArr[k1]->data + HuTrNoArr[k2]->data;
        HuffmanTreeRoot->lchild = HuTrNoArr[k1];
        HuffmanTreeRoot->rchild = HuTrNoArr[k2];

        HuTrNoArr[k1] = HuffmanTreeRoot;
        HuTrNoArr[k2] = NULL;
    }

    return HuffmanTreeRoot;
}

void HuffmanCoding(HuffmanT T, int len)
{ //求HuffmanTree中每个节点的编码
    static int arr[20];
    int i;
    if (T != NULL)
    {
        if (T->lchild == NULL && T->rchild == NULL)
        {
            printf("节点权值为%d的编码为：", T->data);
            for (i = 0; i < len; i++)
            {
                printf("%d", arr[i]);
            }
            printf("\n");
        }
        else
        {
            arr[len] = 0;
            HuffmanCoding(T->lchild, len + 1);
            arr[len] = 1;
            HuffmanCoding(T->rchild, len + 1);
        }
    }
}

int calculateWeightLength(HuffmanT T, int weight)
{ //计算HuffmanTree带杈路径长度
    if (T == NULL)
    {
        return 0;
    }
    else
    {
        if (T->lchild == NULL && T->rchild == NULL)
        {
            return T->data * weight;
        }
        else
        {
            return calculateWeightLength(T->lchild, weight + 1) + calculateWeightLength(T->rchild, weight + 1);
        }
    }
}

void PreTraverse(HuffmanT T)
{ // 前序遍历
    if (T == NULL)
    {
        return;
    }
    else
    {
        printf("%d\n", T->data);
        PreTraverse(T->lchild);
        PreTraverse(T->rchild);
    }
}

int main()
{
    Que q = (QueueNode *)malloc(sizeof(QueueNode));
    HuffmanT HuffmanTreeRoot;
    int cnt;
    q->next = NULL;
    printf("请输入一组数据(tips:用-1表示结束)\n");
    cnt = CreateQueue(q);
    HuffmanTreeRoot = QueueToHuffmanTree(q, cnt);
    PreTraverse(HuffmanTreeRoot);
    HuffmanCoding(HuffmanTreeRoot, 0);
    return 0;
}