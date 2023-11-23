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
#define INVALID_KEY 0;
#define INVALID_ID 0;

Semaphore semaphoreTable[MAX_SEMAPHORES]; // Tabela de Semaforos

Semaphore *create(int value)
{
    // Encontra um ID de semáforo não utilizado.
    int id = 0;
    while (id < MAX_SEMAPHORES && semaphoreTable[id].id == id)
    {
        id++;
        // kprintf("ID = %d", id);
    }

    // Se todos os IDs estão em uso, retorna NULL.
    if (id == MAX_SEMAPHORES)
    {
        kprintf("KERNEL - SEM.C - TABELA CHEIA");
        return NULL;
    }

    // Inicializa novo semaforo na tabela
    Semaphore *sem = &semaphoreTable[id];
    sem->process = curr_proc;         // aponta para o proceso em execução
    sem->value = value;               // seta valor passado como parametro
    sem->id = id;                     // seta id do semaforo para sua posição dentro da tabela
    sem->chain = sem->process->chain; // Inicializa a lista de processos em sleep

    return sem;
}

/*
    DESTROY: destroi um semaforo fazendo com que o ponteiro da tabela aponte para variaveis invalidas

    *Atenção, não contrei uma maneira de dar flush e liberar a memoria já que a função free não estava funcionando
*/
void destroy(Semaphore *sem)
{
    sem->process = NULL;
    sem->key = -1;
    sem->value = -1;
    sem->chain = NULL;

    // Verifica se a lista de processos está vazia
    if (sem->process == NULL)
    {
        // Remove o semáforo da semaphoreTable
        sem->id = -1;
    }
}

/*
DOWN: testa o valor do semáforo. Se esse valor for maior que zero, ele é decrementado e
o processo continua sua execução normalmente. Caso contrário, o processo é bloqueado.

  *Atenção, mecanismo escolhido para exclusão mutua foi de uma pesquisa que fiz e descobri que existe uma tratativa do gcc para operações atomicas. Não sabia se era válido então não utilizei
  porem existe um erro ao fazer o test aonde aparentemente os processos estão entrando em deadlock, tenti alterar o mecanismo de exclusão mutua para algumas formas diferentes que
  procurei porem sem sucesso, não consegui encontrar o que pode estar dando o problema.
  while (__sync_lock_test_and_set(&sem->lock, 1)) {
        // Espera ativa (busy wait)
    }
    __sync_lock_release(&sem->lock);
*/
void down(Semaphore *sem)
{
    while (sem->turn != 0)
    {
        // espera ativa alternada
    }

    if (sem->value > 0)
    {
        sem->value--;
    }
    else
    { // Bloqueia o processo atual
        sleep(sem->chain, PRIO_USER);
    }

    sem->turn = 1;
}

/*
UP : up(): testa se o valor do semáforo é zero. Em caso afirmativo e existir algum processo
bloqueado no semáforo, o processo é desbloqueado. Caso contrário o valor do semáforo
é incrementado.
*/

void up(Semaphore *sem)
{
    while (sem->turn != 1)
    {
        // espera ativa alternada
    }

    if (sem->value == 0 && sem->chain != NULL)
    {
        wakeup(sem->chain);
        sem->chain = NULL;
    }
    else
    {
        sem->value++;
    }

    sem->turn = 0;
}
