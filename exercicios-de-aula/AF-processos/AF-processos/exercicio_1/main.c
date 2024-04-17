#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>


//       (pai)
//         |        
//    +----+----+
//    |         |   
// filho_1   filho_2


// ~~~ printfs ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!


int main(int argc, char** argv) {

    for (int i = 0; i < 2; i++) {
        if (fork() == 0 && printf("Processo pai criou %d\n", getpid())) {
            printf("Processo filho %d criado\n", getpid());
            exit(0);
        }
    }

    while (wait(NULL) > 0);

    printf("Processo pai finalizado!\n");
    return 0;

}

