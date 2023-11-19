// Chamada de Sistema sys_semget()

/*
int semget(unsigned key)
A função semget permite que um processo use um semáforo associado a uma chave
(key). Caso nenhum semáforo esteja associado à chave especificada (key), um novo se-
máforo com essa chave deve ser criado.
Em caso de conclusão com êxito, a função deve retornar o identificador do semáforo asso-
ciado a key. Em caso de erro, -1 deve ser retornado.
*/
#include <nanvix/const.h>
#include <nanvix/hal.h>
#include <nanvix/klib.h>
#include <nanvix/pm.h>
#include <stdio.h>
#include <sys/sem.h>

PUBLIC int sys_semget(int key)
{

    // Cria o semáforo caso não exista um
    Semaphore *createdSem = create(key);

    if (createdSem->value != 0)
    {
        // Tratar erro ao criar semáforo
        kprintf("Erro ao criar o semáforo.\n");
        return -1;
    }

    kprintf("Semaforo criado com sucesso.\n");
    return createdSem->value; // Retorna o ID do semáforo recém-criado
}