
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MY_BUF_SIZE 10000

struct node
{
    struct node *parent;
    struct node *left;
    struct node *right;
    int val;
};

struct node *nodeList = NULL;
int total = 0;
int orgArray[MY_BUF_SIZE];

void nextLine(void)
{
    printf("\r\n==============\r\n\r\n");
}

void insertNode(struct node *node, struct node *tmpList)
{
    if (node->val > tmpList->val)
    {
        if (tmpList->right)
        {
            printf("%d ", tmpList->val);
            insertNode(node, tmpList->right);
        }
        else
        {
            tmpList->right = node;
            node->parent = tmpList;
            printf("%d ", tmpList->val);
            total++;
        }
        return;
    }
    else if (node->val == tmpList->val)
    {
        struct node *prevLeft = tmpList->left;
        if (prevLeft == NULL)
        {
            tmpList->left = node;
        }
        else
        {
            prevLeft->parent = node;
            tmpList->left = node;
            node->left = prevLeft;
        }
        node->parent = tmpList;

        printf("%d ", tmpList->val);
        total++;
    }
    else if (tmpList->left)
    {
        printf("%d ", tmpList->val);
        insertNode(node, tmpList->left);
    }
    else
    {
        tmpList->left = node;
        node->parent = tmpList;
        printf("%d ", tmpList->val);
        total++;
    }
}

void addVal(int val)
{
    struct node *pNode = calloc(1, sizeof(struct node));
    if (!pNode)
    {
        return;
    }
    pNode->val = val;
    if (nodeList == NULL)
    {
        nodeList = pNode;
        printf("[%d]\r\n", pNode->val);
        total++;
        return;
    }

    printf("[%d: ", pNode->val);
    insertNode(pNode, nodeList);
    printf("]\r\n");
}

void printOrg(void)
{
    for (int i = 0; i < MY_BUF_SIZE; i++)
    {
        printf("%d ", orgArray[i]);
    }
    printf("\r\n");
}

void createRandomArray(void)
{
    int i;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));

    for (i = 0; i < MY_BUF_SIZE; i++)
    {
        orgArray[i] = rand() % MY_BUF_SIZE;
    }
}

void printList(struct node *head)
{
    if (head)
    {
        if (head->left)
        {
            printList(head->left);
        }
        if (head->right)
        {
            printf("%d ", head->val);
            printList(head->right);
            return;
        }
        printf("%d ", head->val);
    }
}
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

void printTree(struct node *head)
{
    static int left = 0;
    static int right = 0;
    static int deep = 0;
    deep++;
    if (head)
    {
        if (head->left)
        {
            left++;
            printTree(head->left);
        }
        if (head->right)
        {
            right++;
            gotoxy(left*4, right*4);
            printf("%d ", head->val);
            printTree(head->right);
            return;
        }
        gotoxy(left*4, right*4);
        printf("%d ", head->val);
    }
}

int tmp[MY_BUF_SIZE] = {6, 7, 1, 4, 2, 9, 2, 4, 2, 8};
int copyArray()
{
    memcpy(orgArray, tmp, sizeof(tmp));
}

int main(void)
{
    int i;
    nextLine();
    createRandomArray();
    //copyArray();
    printOrg();
    nextLine();

    for (i = 0; i < MY_BUF_SIZE; i++)
    {
        nextLine();
        addVal(orgArray[i]);
    }
    nextLine();

    printf("total %d \r\n", total);
    nextLine();
    struct node *head = nodeList;
    printList(head);

    getchar();
    //clear();
    //printTree(head);
    //nextLine();

    //getchar();
}