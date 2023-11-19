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

#define MAX_SEMAPHORES 100

Semaphore semaphoreTable[MAX_SEMAPHORES];

Semaphore *create(int id)
{
    if (id < 0 || id >= MAX_SEMAPHORES)
    {
        return NULL; // ID inválido
    }

    if (semaphoreTable[id].id == id)
    {
        return NULL; // O semáforo já existe com este ID
    }

    Semaphore *sem = &semaphoreTable[id];
    sem->value = 0;
    sem->id = id;
    sem->list = NULL;

    return sem;
}

void destroy(Semaphore *sem)
{
    struct process *current = sem->list;
    struct process *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = NULL;
        current = next;
    }

    sem->list = NULL;

    // Verifica se a lista de processos está vazia
    if (sem->list == NULL)
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
    {
        // Bloqueia o processo atual
        struct process *current = sem->list; // Obtenha o processo atual
        current->state = PROC_DEAD;
    }

    __sync_lock_release(&sem->lock); // Libera o bloqueio
}

void up(Semaphore *sem)
{
    sem->value++;
    if (sem->value <= 0)
    {
        // Remove o processo da sem->list
        struct process *p = sem->list;
        sem->list = sem->list->next;

        // desperta o processo
        p->state = PROC_RUNNING;
        p->next = NULL;
    }
}