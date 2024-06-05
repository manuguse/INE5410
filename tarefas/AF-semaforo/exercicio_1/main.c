#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

sem_t sem_a, sem_b;
FILE* out;

void *thread_a(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&sem_a);  // decrementa o semáforo a se for maior que 0, caso contrário, bloqueia a thread
        fprintf(out, "A");
        fflush(stdout);
        sem_post(&sem_b);  // incrementa o semáforo b e libera a thread bloqueada
    }
    return NULL;
}

void *thread_b(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&sem_b);  // decrementa o semáforo b se for maior que 0, caso contrário, bloqueia a thread
        fprintf(out, "B");
        fflush(stdout);
        sem_post(&sem_a);  // incrementa o semáforo a e libera a thread bloqueada
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s [ITERAÇÕES]\n", argv[0]);
        return 1;
    }
    int iters = atoi(argv[1]);
    srand(time(NULL));
    out = fopen("result.txt", "w");

    pthread_t ta, tb;
    
    sem_init(&sem_a, 0, 1);  // inicializa o semáforo a com 1
    sem_init(&sem_b, 0, 1);  // inicializa o semáforo b com 1

    // Cria threads
    pthread_create(&ta, NULL, thread_a, &iters);
    pthread_create(&tb, NULL, thread_b, &iters);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    sem_destroy(&sem_a);  // destroi o semáforo a
    sem_destroy(&sem_b);  // destroi o semáforo b

    //Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);
  
    return 0;
}
