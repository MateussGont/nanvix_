// Abstração de Semáforo

/*
create(n): cria um semáforo semáforo e o inicializa com o valor n.

down(): testa o valor do semáforo. Se esse valor for maior que zero, ele é decrementado e
o processo continua sua execução normalmente. Caso contrário, o processo é bloqueado.

up(): testa se o valor do semáforo é zero. Em caso afirmativo e existir algum processo
bloqueado no semáforo, o processo é desbloqueado. Caso contrário o valor do semáforo
é incrementado.

destroy(): destrói o semáforo
*/

#include <stdio.h>
#include <stdlib.h>
#include <nanvix/pm.h>
#include <sys/sem.h>
#include <nanvix/klib.h>

#define MAX_SEMAPHORES 100

Semaphore semaphoreTable[MAX_SEMAPHORES];

Semaphore *create(int value)
{
    // Encontra um ID de semáforo não utilizado.
    int id = 0;
    while (id < MAX_SEMAPHORES && semaphoreTable[id].id == id)
    {
        id++;
    }

    // Se todos os IDs estão em uso, retorna NULL.
    if (id == MAX_SEMAPHORES)
    {
        kprintf("KERNEL - SEM.C - TABELA CHEIA");
        return NULL;
    }

    // Inicializa novo semaforo na tabela
    Semaphore *sem = &semaphoreTable[id];
    sem->process = curr_proc; // aponta para o proceso em execução
    sem->value = value;
    sem->id = id;
    sem->chain = sem->process->chain; // Inicializa a lista de processos em sleep

    return sem;
}

void destroy(Semaphore *sem)
{
    sem->process = NULL;

    // Verifica se a lista de processos está vazia
    if (sem->process == NULL)
    {
        // Remove o semáforo da semaphoreTable
        sem->id = -1;
    }
}

void down(Semaphore *sem)
{
    while (__sync_lock_test_and_set(&sem->lock, 1))
        ; // Adquire o bloqueio

    if (sem->value > 0)
    {
        sem->value--;
    }
    else
    { // Bloqueia o processo atual
        sleep(sem->chain, 0);
    }

    __sync_lock_release(&sem->lock); // Libera o bloqueio
}

void up(Semaphore *sem)
{
    if (sem->value == 0 && sem->chain != NULL)
    {
        wakeup(sem->chain);
        sem->chain = NULL;
    }
    else
    {
        sem->value++;
    }
}