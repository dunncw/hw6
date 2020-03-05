#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t lock;
int LEN_OF_STR;
int counter = 0;

typedef struct {

    int t_number;
    char *str;

} my_struct_t;

void *mythread(void *arg) {

    my_struct_t *mys = arg;

    int chr = 97 + mys->t_number;
    char output = chr;

    while(counter < LEN_OF_STR - 1){
        
        assert(pthread_mutex_lock(&lock) == 0);  
             
        *(mys->str + counter) = output; 
        printf("In thread fn, t_number <%d>, char <%c>, index <%d>\n", mys->t_number, output, counter);
        counter = counter + 1;  

        assert(pthread_mutex_unlock(&lock) == 0);  
    
    }  
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 2) {
	fprintf(stderr, "usage: p_thread <#_of_threads_to_start> <len_of_string_to_gen>\n");
	exit(1);
    }
	
    int threads_ts = atoi(argv[1]);
    int len_of_str  = atoi(argv[2]);
    LEN_OF_STR = len_of_str + 1;

    char str[LEN_OF_STR];
    char *str_pt = str;

    memset(str, '\0', sizeof(char)*LEN_OF_STR );

    printf("string: <%s>\n", str);
 
    my_struct_t vals[threads_ts];
    pthread_t threads[threads_ts];
    for(int i = 0; i < threads_ts; i++){

        vals[i].t_number = i;
        vals[i].str = str_pt;
    
        if (pthread_create(&threads[i], NULL, mythread, &vals[i]) != 0) {
            printf("Unable to create thread\n");
            exit(1);
        } 
    }


    for(int i = 0; i < threads_ts; i++){
        assert(pthread_join(threads[i], NULL ) == 0);
    }
	
    printf("string: <%s> count <%d>\n", str, counter);

    return 0;
}
