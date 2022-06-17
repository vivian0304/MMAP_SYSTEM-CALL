#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

void mmapEx(int mat_num)
{
    clock_t start, stop;
    double duration;
    int *ptr[mat_num];
    
    for (int i = 0; i < mat_num; i++)
    {
        ptr[i] = mmap(NULL, mat_num * sizeof(int),
                      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    }

    printf("mmap %dx%d행렬 곱셈 시작\n", mat_num, mat_num);
    start = clock();
    for (int i = 0; i < mat_num; i++)
    {
        for (int j = 0; j < mat_num; j++)
        {
            ptr[i][j] = i*j;
        }
    }
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("mmap %dx%d행렬 곱셈 수행시간:%f\n", mat_num, mat_num, duration);
    
    for (int i = 0; i < mat_num; i++)
    {
        int err = munmap(ptr[i], mat_num * sizeof(int));
        if (err != 0)
        {
            printf("UnMapping Failed\n");
        }
    }

    int matrix[mat_num][mat_num];

    printf("일반 %dx%d행렬 곱셈 시작\n", mat_num, mat_num);
    start = clock();
    for (int i = 0; i < mat_num; i++)
    {
        for (int j = 0; j < mat_num; j++)
        {
            matrix[i][j] = i*j;
        }
    }
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("일반 %dx%d행렬 곱셈 수행시간:%f\n", mat_num, mat_num, duration);

    printf("\n");
    
}

int main()
{
    for(int i=1; i<6; i++) {
        printf("<<%d회차>>\n", i);
        mmapEx(100);
        mmapEx(500);
        mmapEx(1000);
    }

    return 0;
}