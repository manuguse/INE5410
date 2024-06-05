#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

/* ---------- Definições Globais. ---------- */
#define TEMPO_BASE 1000000

typedef enum { 
	CONTINENTE, 
	ILHA 
} cabeceira_t;

typedef struct {
	int id;
	cabeceira_t cabeceira;
	pthread_t thread;
} veiculo_t;
/* ---------------------------------------- */

/* ---------- Variáveis Globais. ---------- */
char cabeceiras[2][11] = { { "CONTINENTE" }, { "ILHA" } };
int total_veiculos;
int veiculos_turno;
sem_t sem_ilha, sem_continente, mutex;
int veiculos_na_ponte = 0;

/* ---------------------------------------- */


/* Inicializa a ponte. */
void ponte_inicializar() {
	
	sem_init(&sem_ilha, 0, 0);                     // inicializa o semáforo da ilha com 0 (bloqueado)
	sem_init(&sem_continente, 0, veiculos_turno);  // inicializa o semáforo do continente com o número de veículos por turno (liberado)
	sem_init(&mutex, 0, 1);                        // inicializa o semáforo binário mutex com 1 (liberado)

	/* Imprime direção inicial da travessia. NÃO REMOVER! */
	printf("\n[PONTE] *** Novo sentido da travessia: CONTINENTE -> ILHA. ***\n\n");
	fflush(stdout);
}

/* Função executada pelo veículo para ENTRAR em uma cabeceira da ponte. */
void ponte_entrar(veiculo_t *v) {
	if (v->cabeceira) {            // se o veículo está na ilha (cabeceira = 1)
		sem_wait(&sem_ilha); 	   // decrementa o semáforo da ilha (bloqueia o veículo se não houver espaço)
	} else {					   // se o veículo está no continente
		sem_wait(&sem_continente); // decrementa o semáforo do continente (bloqueia o veículo se não houver espaço)
	}
}

/* Função executada pelo veículo para SAIR de uma cabeceira da ponte. */
void ponte_sair(veiculo_t *v) {
	sem_wait(&mutex); // decrementa o semáforo binário mutex
	veiculos_na_ponte++; // incrementa o número de veículos na ponte
	if (veiculos_na_ponte == veiculos_turno) { // se o número de veículos na ponte for igual ao número de veículos por turno
		veiculos_na_ponte = 0; // reseta o número de veículos na ponte
		printf("\n[PONTE] *** Novo sentido da travessia: %s -> %s. ***\n\n", cabeceiras[v->cabeceira], cabeceiras[!v->cabeceira]);
		fflush(stdout);
		for (int i = 0; i < veiculos_turno; i++) { // libera os veículos para atravessar
			if (v->cabeceira) { // se o veículo está na ilha
				sem_post(&sem_ilha); // incrementa o semáforo da ilha (libera um veículo para atravessar)
			} else { // se o veículo está no continente
				sem_post(&sem_continente); // incrementa o semáforo do continente (libera um veículo para atravessar)
			}
		}
	} sem_post(&mutex); // incrementa o semáforo binário mutex 
}

/* FINALIZA a ponte. */
void ponte_finalizar() {

	sem_close(&sem_ilha);
	sem_close(&sem_continente);
	sem_close(&mutex);
	
	/* Imprime fim da execução! */
	printf("[PONTE] FIM!\n\n");
	fflush(stdout);
}

/* Implementa o comportamento de um veículo. */
void * veiculo_executa(void *arg) {
	veiculo_t *v = (veiculo_t *) arg;
	
	printf("[Veiculo %3d] Aguardando para entrar na ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);

	/* Entra na ponte. */
	ponte_entrar(v);
	printf("[Veiculo %3d] ENTROU na ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);

	/* Faz a travessia. */
	usleep(TEMPO_BASE + rand() % 1000);
	
	/* Seta cabeceira oposta para sair. */
	v->cabeceira = !v->cabeceira;

	/* Sai da ponte na cabeceira oposta. */
	printf("[Veiculo %3d] SAIU da ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);
	ponte_sair(v);

	pthread_exit(NULL);
}

/* Função principal: NÃO PODE ALTERAR! */
int main(int argc, char **argv) {
 
	if (argc < 3) {
		printf("Indique a quantidade total de veiculos e o numero de veiculos que podem atravessar a ponte por turno:\n\n %s [QTD_TOTAL_VEICULOS] [VEICULOS_POR_TURNO]\n\n", argv[0]);
		return 1;
	}

	total_veiculos = atoi(argv[1]);
	veiculos_turno = atoi(argv[2]);

	if (total_veiculos % (veiculos_turno * 2)) {
		printf("ERRO: O valor [QTD_TOTAL_VEICULOS] deve ser divisivel por ([VEICULOS_POR_TURNO] * 2)!\n\n %s [QTD_TOTAL_VEICULOS] [VEICULOS_POR_TURNO]\n\n", argv[0]);
		return 1;
	}

	srand(time(NULL));

	/* Aloca os veículos. */
	veiculo_t veiculos[total_veiculos];

	ponte_inicializar();

	/* Cria os veículos. */
	for (int i = 0; i < total_veiculos; i++) {
		/* Define o id do veículo. */
		veiculos[i].id = i;
		
		/* Escolhe aleatoreamente se o veículo entra pela ILHA ou CONTINENTE. */
		veiculos[i].cabeceira = i % 2; 
		
		/* Cria a thread veículo. */
		pthread_create(&veiculos[i].thread, NULL, veiculo_executa, (void *) &veiculos[i]);		
	}

	/* Aguarda o término da execução de todos os veículos antes de finalizar o programa. */
	for (int i = 0; i < total_veiculos; i++) {
		pthread_join(veiculos[i].thread, NULL);
	}

	ponte_finalizar();

	return 0;
}