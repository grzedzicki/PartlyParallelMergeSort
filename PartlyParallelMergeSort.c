#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define THREADS 4
typedef struct {
    int p_id;
    int p_o;
    int p_n;
    int* p_array;
}thread_struct;
//MERGESORT-----------------------------------
void merge_sorting(void* arg){
   int a,pom_id;
    thread_struct *t_s = arg;
    if(t_s->p_o == 0) a=1;
    else a=2;
    int l = 0;
    int r = t_s->p_n-a; 
    int id = t_s->p_id;
    if( l < r){
    merge_sort(t_s->p_array,l,r);
    if( id !=0) pom_id = 100 +id;
    else pom_id=100;
    writefile(t_s->p_array,r+1,pom_id);
    }
}
 
void merge_sort(int *array, int l, int r){
    if( l < r){ 
        int m = l + ( r - l) / 2;
        merge_sort(array,l,m);
        merge_sort(array,m+1,r);
        merge_function(array,l,m,r);
    }
}
 
void merge_function(int *array, int l, int m, int r){
    int tmp_left = m - l +1;
    int tmp_right = r - m;
    int array_left[tmp_left];
    int array_right[tmp_right];
 
 
    for(int i=0; i< tmp_left;i++)
        array_left[i] = array[l + i];
 
    for(int i=0; i<  tmp_right;i++)
        array_right[i] = array[m + 1 + i];
    int i=0,j=0,k=0;
 
    while(i < tmp_left && j < tmp_right){
        if(array_left[i] <= array_right[j]){
            array[l + k] = array_left[i];
            i++;
        }else{
            array[l + k] = array_right[j];
            j++;
        }
    k++;
    }
 
    while(i< tmp_left){
        array[l + k] = array_left[i];
        k++;
        i++;
    }
    while(j < tmp_right){
        array[l + k] = array_right[j];
        k++;
        j++;
    }
}
 
void final_merge(int *array, int n, int ag, int len,int s){
    int l,r,m;
    for(int i =0; i<n; i = i+2){
        l = i * (len * ag);
        r = ((i + 2) * len * ag) - 1;
        m = l + (len * ag) -1;
        if(r >= s)
            r = s -1;
        merge_function(array,l,m,r);
    }
    if(n/ 2 >= 1)
        final_merge(array, n/2,ag*2,len,s);
}
 
//MERGESORT-----------------------------------
 
void testsort(int *array,int n,int s){
    for(int i=0;i<n-1;i++)
        if(!(array[i] <= array[i+1])){
            switch(s){
        case 2:
            printf("Out of order in Parallel Merge Sort! %d %d\n", array[i], array[i+1]);
            break;
        case 3:
            printf("Out of order in Serial Merge Sort! %d %d\n", array[i], array[i+1]);
            break;
        }
        return -1;
        }
    printf("Sorting is in order.");
}
void writefile(int* array,int n, int s){
    FILE *fp;
    int num;
    switch(s){
        case 0:
            fp = fopen ("array.txt","w");
            break;
        case 1:
             fp = fopen ("bubble.txt","w");
            break;
        case 100:
             fp = fopen ("merge1.txt","w");
            break;
        case 101:
             fp = fopen ("merge2.txt","w");
            break;
        case 102:
            fp = fopen ("merge3.txt","w");
            break;
        case 103:
            fp = fopen ("merge4.txt","w");
            break;
        case 104:
            fp = fopen ("merge5.txt","w");
            break;
        case 105:
            fp = fopen ("merge6.txt","w");
            break;
        case 106:
            fp = fopen ("merge7.txt","w");
            break;
        case 107:
            fp = fopen ("merge8.txt","w");
            break;
        case 108:
            fp = fopen ("merge9.txt","w");
            break;
        case 109:
            fp = fopen ("merge10.txt","w");
            break;
        case 110:
            fp = fopen ("merge11.txt","w");
            break;
        case 120:
            fp = fopen ("mergeserial.txt","w");
            break;
    }
 
    if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    for(int i=0;i<n;i++)
        fprintf(fp,"%d ",array[i]);
 
   fclose(fp);
}
 
void init(int n,int *array){
    for(int i=0; i<n;i++){
        array[i]= rand();
    }
    writefile(array,n,0);
    display(n,array,0);
}
 
void display(int n, int *array,int s){
    switch(s){
        case 0:
            printf("Array: ");
            break;
        case 2:
            printf("Parallel MergeSort: ");
            break;
        case 3:
            printf("\nSerial MergeSort: ");
            break;
 
    }
    printf("");
    for(int i=0; i<n;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}
 
int main(int argc, char **argv)
{
    int n,seed;
	printf("Wielkosc tablicy oraz seed:\n");
    scanf("%d %d", &n,&seed);
    srand(seed);
    int* array= (int*)malloc(sizeof(int)*n);
    init(n,array);
    pthread_t threads[THREADS];
    int divide,mod,div;
    printf("\n____________\n");
    struct timespec start, finish;
    double elapsed;
    int* arraytomerge= (int*)malloc(sizeof(int)*(n));
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i=0;i<THREADS;i++){
        divide = n/THREADS;
        thread_struct args[THREADS];
        args[i].p_id=i;
        int mod=n%THREADS;
        if(mod !=0) div = divide + mod;
        else div = divide + mod;
        args[i].p_n=div;
        args[i].p_o=mod;
 
        if(i == THREADS-1) {args[i].p_array = (int*)malloc(sizeof(int) * div);
        memcpy(args[i].p_array,array+(i*divide),(div  * sizeof(int)));
        }
        else if( i==0) {args[i].p_array = (int*)malloc(sizeof(int) * divide);
        memcpy(args[i].p_array,array,(divide * sizeof(int)));
        }
        else {args[i].p_array = (int*)malloc(sizeof(int) * divide);
        memcpy(args[i].p_array,array+(i*divide),(divide * sizeof(int)));
        }
 
    if (pthread_create(&threads[i], NULL, &merge_sorting, (void *)&args[i]) != 0) {
        printf("pthread error[%d]", i);
        return -1;
    }
    }
    thread_struct rec[THREADS];
    for(int i=0;i<THREADS;i++)
    pthread_join(threads[i], &rec[i]);
 
 
    memcpy(arraytomerge,rec[0].p_array,(divide * sizeof(int)));
    for(int i=1;i<THREADS;i++){
        if(i!= THREADS-1) memcpy(arraytomerge + (divide * i),rec[i].p_array,(divide * sizeof(int)));
        else memcpy(arraytomerge + (divide * i),rec[i].p_array,(div * sizeof(int)));
    }
 
    final_merge(arraytomerge, THREADS,1,divide,n);
    if(THREADS == 2) writefile(arraytomerge,n,102);
    else if(THREADS == 4) writefile(arraytomerge,n,104);
    else if(THREADS == 10) writefile(arraytomerge,n,110);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("\nElapsed Pararrel Merge Sort Time: %lf\n",elapsed);
    display(n,arraytomerge,2);
    testsort(arraytomerge,n,2);
 
    clock_gettime(CLOCK_MONOTONIC, &start);
    merge_sort(array,0,n-1);
    writefile(array,n,120);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("\nElapsed Serial Merge Sort Time: %lf\n",elapsed);
    display(n,array,4);
    testsort(array,n,4);
	return 0;
}