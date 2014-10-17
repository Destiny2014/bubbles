#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */   

void bubble(char *items);
void thread_func(void *vptr_args);

typedef struct str_thdata
{
    int thread_no;
    char message[100];
} thdata;

int main(int argc, char *argv[])
{
	int t, i,k,x,b;
	char s[255];
	char e[255];
	char w[255];
	thdata data1,data2;
	pthread_t thread1,thread2;
	
/*Считывание массива с клавы*/
	k=0;
	for(t=1; t<argc; ++t) {
		i = 0;
	while(argv[t][i]) {
		s[i]=argv[t][i];
		//putchar(s[i]);
		++i;
		k++;}
printf("string s: %s\n", s);
/*Обнуление массивов*/
	for(i=0;i<k;i++){
		e[i]=0;	
		w[i]=0;}
/*Создание первого подмассива*/
	x=0;
	for(i=0;i<(int)k/2;i++){
		w[x]=s[x];
		x++;	}
//printf("string w: %s\n", w);
/*Создание второго подмассива*/
	x=0;
	for(t=(int)k/2;t<k;t++){
		e[x]=s[t];
		x++;	}
	//printf("string e: %s\n", e);
/*Обнуление исходного массива*/
	for(i=0;i<k;i++){
		s[i]=0;	}
/*Потоки*/	
	data1.thread_no=1;
	strcpy(data1.message, w);
	
	data2.thread_no=2;
	strcpy(data2.message, e);
 
	pthread_create(&thread1, NULL,(void *) &thread_func,(void *) &data1);
	pthread_create(&thread2, NULL,(void *) &thread_func,(void *) &data2);	 
 
	pthread_join(thread1, NULL);
   	pthread_join(thread2, NULL);

	strcpy(w,data1.message);
	strcpy(e,data2.message);
	//printf("w: %s\n", w);
	//printf("e: %s\n", e);
	//printf("k: %d\n", k);
	x=0;
	int l=0;i=0;
	
	while ((e[l]!=0)&&(w[x]!=0)){
	if(e[l]<w[x]){
		s[i]=e[l];
		l++;} 
	else{
		s[i]=w[x];
		x++;}
	i++;}

	if (e[l]==0){
		while ((w[x]!=0)){s[i]=w[x];x++;i++;}
	}
	else{
		while ((e[l]!=0)){s[i]=e[l];l++;i++;}
	}
	
	printf("string: %s\n", s);
}

return 0;
}

void thread_func(void *vptr_args)
{
    thdata *data;            
    data = (thdata *) vptr_args;  
    
   // printf("Thread %d says %s \n", data->thread_no, data->message);
	bubble(data->message);
    
    pthread_exit(0);
}

void bubble(char *items)
{
	register int a, b, count,i;
 	register char t;
	i=0;
	count=0;
	while(items[i]){
		count++;i++;}
	for(a=0; a < count; ++a)
	for(b=count-1; b >= a; --b) {
		if(items[b-1] > items[b]) {
		        t = items[b-1];
		        items[b-1] = items[b];
		        items[b] = t;
			//printf("string8: %s\n", items);
	}
    }
}
