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

typedef struct Sem
{
    int id;
    float mutex;
    char l;
} Sem;

Sem *sem_create()
{
    Sem *semaforo = NULL;
    return semaforo;
}

void down(/*Sem sem*/)
{
}

void up(/*Sem sem*/)
{
}

void destroy(/*Sem sem*/)
{
    // free(sem);
}