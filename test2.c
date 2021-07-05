#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MY_BUF_SIZE 10000

int sortingArray[MY_BUF_SIZE] = {6, 7, 1, 4, 2, 9, 2, 4, 2, 8};

int search(int arr[], int val)
{
    int min, max, med;
    min = 0;
    max = MY_BUF_SIZE;
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
            printf("found (%d): at (%d)\r\n", val, med);
            break;
        }
    }

    return -1;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\r\n");
}

void bubbleSort(int arr[], int size)
{
    int i, j;
    int temp;
    bool sorted = false;
    for (i = size; i > 0; i--)
    {
        sorted = true; //assume array sorted
        for (j = 1; j < i; j++)
        {
            if (arr[j] < arr[j - 1])
            {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                sorted = false; //means array not sorted
            }
        }
        if (sorted)
        {
            printf("stop at %d\r\n", i);
            break;
        }
    }
}

void bubbleSort1(int arr[], int size)
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
}

void createRandomArray(void)
{
    int i;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));

    for (i = 0; i < MY_BUF_SIZE; i++)
    {
        sortingArray[i] = rand() % MY_BUF_SIZE;
    }
}

LARGE_INTEGER frequency;
LARGE_INTEGER start;
LARGE_INTEGER end;
double interval;
void startMeasure(void)
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
}
void endMeasure(void)
{
    QueryPerformanceCounter(&end);
    interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", interval); //in seconds?
}

void LinuxMeasureTime(void)
{
#if 0
    struct timespec t2, t3;
    double dt1;

    volatile long long i;
    clock_gettime(CLOCK_MONOTONIC, &t2);
#endif
}

int main(void)
{
    createRandomArray();
    int arrCopy[MY_BUF_SIZE];
    memcpy(arrCopy, sortingArray, MY_BUF_SIZE);

    startMeasure();
    bubbleSort(sortingArray, MY_BUF_SIZE);
    endMeasure();

    startMeasure();
    bubbleSort1(arrCopy, MY_BUF_SIZE);
    endMeasure();

    //search(sortingArray, 5);
    //search(sortingArray, 9);

    printf("end\r\n");
}