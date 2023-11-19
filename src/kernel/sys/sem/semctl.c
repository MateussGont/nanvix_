// Chamada de Sistema sys_semctl()

/*
int semctl(int semid, int cmd, int val);
A função semctl() permite um série de operações de controle no semáforo identificado
por semid. Essas operações são especificadas por cmd e podem ser: GETVAL, retorna
o valor corrente do semáforo; SETVAL, define o valor do semáforo como sendo val; e
IPC_RMID, desvincula o semáforo do processo corrente e o destrói caso não esteja mais
sendo usado.
O valor de retorno da função depende de cmd. Caso esse seja GETVAL, o valor corrente do
semáforo é retornado. Nos demais casos de conclusão com êxito, 0 deve ser retornado. Em
caso de erro -1 deve ser retornado retornado.
*/

#include <nanvix/const.h>
#include <nanvix/hal.h>
#include <nanvix/klib.h>
#include <nanvix/pm.h>
#include <sys/sem.h>
#include <stdio.h>

PUBLIC int sys_semctl(int semid, int cmd, int val)
{
    // IMPORTANTE VERIFICAR SE O ID POSSUi UM SEMAFORO EXISTENTE

    if (cmd == GETVAL && semid == semaphoreTable[semid].id)
    {
        kprintf("\n GETVAL - KERNEL - %d", semaphoreTable[semid].value);
        return semaphoreTable[semid].value;
    }
    else if (cmd == SETVAL && semid == semaphoreTable[semid].id)
    {
        semaphoreTable[semid].value = val;
        kprintf("\n SETVAL - KERNEL - %d ", semaphoreTable[semid].value);
        return 0;
    }
    else if (cmd == IPC_RMID && semid == semaphoreTable[semid].id)
    {
        struct process *temp = semaphoreTable[semid].process->next;
        semaphoreTable[semid].process = temp;

        if (semaphoreTable[semid].process == NULL)
        {
            destroy(&semaphoreTable[semid]);
            kprintf("\n IPC_RMID - KERNEL - %d (Se value not null conferir)", semaphoreTable[semid].value);
            return 0;
        }
    }
    else
    {
        kprintf("ERRO - SEMCTL - %d", semaphoreTable[semid].id);
        return -1;
    }
    return -1;
}