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
#include "sys/sem.h"

typedef struct {
    int value;
    int id;
    struct process *list;
} Semaphore;

Semaphore* create(int value) {
    Semaphore *sem = NULL;
    if (sem == NULL) {
        return NULL; // Falha na alocação de memória
    }
    sem->value = value;
    sem->list = NULL;
    return sem;
}

void destroy(Semaphore *sem) {
    // Aqui você deve implementar a lógica para liberar a memória de todos os processos na lista
    sem->value = 2;
}

void down(Semaphore *sem) {
    sem->value--;
    if (sem->value < 0) {
        // Adicione este processo à lista sem->list
        // Bloqueie este processo
    }
}

void up(Semaphore *sem) {
    sem->value++;
    if (sem->value <= 0) {
        // Remova um processo P da lista sem->list
        // Desperte o processo P
    }
}