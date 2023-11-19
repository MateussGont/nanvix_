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

PUBLIC int sys_semget(unsigned key)
{
    int pos = 0;
    while (semaphoreTable[pos].key != key && pos < 100) // percorre tabela de semaforos procurando semaforo com a key especificada
    {
        pos++;
    }

    if (semaphoreTable[pos].key == key) // se semaforo existe com a key
    {
        semaphoreTable[pos].process = curr_proc; // processo atual utiliza o semaforo
        kprintf("\n %d - SEMAFORO JA EXISTE COM ESSA KEY");
        return semaphoreTable[pos].id; // retorna o id do semaforo
    }
    else if (pos <= MAX_SEMAPHORES && semaphoreTable[pos].key != key)
    {                                // se semaforo não encontrado
        Semaphore *temp = create(0); // cria semaforo com valor 0 e salva em um ponteiro
        if (temp == NULL)
        {
            return -1;
        }

        semaphoreTable[temp->id].key = key; // define a Key do id criado como a key especificada
        kprintf("\n %d - SEMAFORO CRIADO ID DO SEMAFORO", semaphoreTable[temp->id].id);
        return semaphoreTable[temp->id].id; // retorna o id do semaforo criado
    }
    else
    {
        kprintf("\n KERNEL: ERRO Na criacao de semaforo SEMGET.c");
        return -1;
    }
}