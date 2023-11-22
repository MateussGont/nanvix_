// Chamada de Sistema sys_semop()

/*
int semop(int semid, int op);
A função semop permite operações atômicas de incremento/decremento no semáforo
identificado por semid. Um valor negativo para op especifica um operação down() e
um valor positivo uma operação up().
A função deve retornar 0 em uma conclusão com êxito, ou então -1 em caso de erro.
*/

#include <nanvix/const.h>
#include <nanvix/hal.h>
#include <nanvix/klib.h>
#include <nanvix/pm.h>
#include <sys/sem.h>
#include <stdio.h>

PUBLIC int sys_semop(int semid, int op)
{
    if (semid <= 0 || semid > MAX_SEMAPHORES)
    {
        kprintf("ID INVÁLIDO - SEMOP.C");
        return -1;
    }
    int pos = 0;
    while (semaphoreTable[pos].id != semid && pos < MAX_SEMAPHORES) // percorre tabela de semaforos procurando semaforo
    {
        pos++;
        kprintf("POS - %d", pos);
    }
    if (semaphoreTable[pos].id == semid)
    {
        if (op <= -1)
        {
            down(&semaphoreTable[semid]);
            kprintf("\n DOWN REALIZADO - ID: %d", semaphoreTable[semid].id);
            return 0;
        }
        else if (op >= 1)
        {
            up(&semaphoreTable[semid]);
            kprintf("\n UP REALIZADO - ID: %d", semaphoreTable[semid].id);
            return 0;
        }
        else
        {
            kprintf("Operador invalido SEMOP.C");
            return -1;
        }
    }
    else
    {
        kprintf("Semaforo inexistente com esse ID SEMOP.C");
        return -1;
    }
}