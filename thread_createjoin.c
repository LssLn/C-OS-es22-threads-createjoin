#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);
char message[]="Hello world"; /* variabile globale condivisa dai thread*/

/* il thread di inizio è il main() */
int main(void){
    int res;
    pthread_t a_thread;
    void *thread_result;
    res=pthread_create(&a_thread,NULL,thread_function,(void *)message);
    if (res != 0){
        perror("thread creation failed");
        exit (EXIT_FAILURE);
    } /* se invece la call ha successo, da qui in poi ci sono 2 thread, che eseguono le funzioni main() e thread_function(), rispettivamente,condividendo la variabile globale message */
    printf("waiting for thread to finish...\n");
    res=pthread_join(a_thread,&thread_result);
    if (res!=0) { /* controlla se la join ha avuto successo o no */
 	    perror ("Thread join failed");
 	    exit (EXIT_FAILURE);
    }
    printf("Thread joined, it returned: %s\n", (char *)thread_result);
    printf("Message is now: %s\n", message);
    // la variabile message è condivisa tra i due thread. printf() mostra come l’altro thread l’ha modificata 
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    printf("thread_function is running. Argument was: %s\n", (char *)arg);
    /* il nuovo thread stampa l’argomento con cui è stato chiamato */
    sleep(3); /* dorme */
    strcpy(message, "Bye!"); /* aggiorna la variabile globale message, condivisa con il main thread*/
    pthread_exit("Thank you for the CPU time"); /* esce,restituendo una stringa al main thread */
}
