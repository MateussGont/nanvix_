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
    kprintf("hello kernel: %d - %d", semid, op);
    return op;
}