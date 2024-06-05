#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao iniciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprimir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seus descendentes diretos antes de terminar

int main(int argc, char** argv) {

    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            for (int j = 0; j < 3; j++) {
                if (fork() == 0) {
                    printf("Processo %d, filho de %d\n", getpid(), getppid());
                    sleep(5);
                    printf("Processo %d finalizado\n", getpid());
                    exit(0);
                }
            }
            while (wait(NULL) >= 0);
            printf("Processo %d finalizado\n", getpid());
            exit(0);
        }
    }

    while (wait(NULL) >= 0);

    printf("Processo principal %d finalizado\n", getpid());
    return 0;
}
