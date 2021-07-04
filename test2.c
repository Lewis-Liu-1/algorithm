#include <stdbool.h>
#include <stdio.h>

#define MY_BUF_SIZE 10

int tmp[MY_BUF_SIZE] = {6, 7, 1, 4, 2, 9, 2, 4, 2, 8};

int search(int arr[], int val)
{
    int min, max, med;
    min = 0;
    max = sizeof(tmp);
    med = (max - min) / 2;
    while (min < max)
    {
        med = min + (max - min) / 2;
        if (arr[med] > val)
        {
            max = med - 1;
        }
        else if (arr[med] < val)
        {
            min = med + 1;
        }
        else
        {
            printf("found: index = %d\r\n", med);
            break;
        }
    }

    return -1;
}

void bubbleSort(int arr[], int size)
{
    int i, j;
    int temp;
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\r\n");
}

int main(void)
{
    bubbleSort(tmp, MY_BUF_SIZE);

    search(tmp, 5);
    search(tmp, 9);

    printf("end\r\n");
}