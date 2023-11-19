/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of Nanvix.
 *
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEM_H_
#define SEM_H_

#include <nanvix/const.h>
#include <nanvix/pm.h>
#include "sys/sem.h"

#define MAX_SEMAPHORES 100
#ifndef _ASM_FILE_

/**
 * @brief Comand values for semaphores.
 */
/**@{*/
#define GETVAL 0   /**< Returns the value of a semaphore. */
#define SETVAL 1   /**< Sets the value of a semaphore.    */
#define IPC_RMID 3 /**< Destroys a semaphore.            */
/**@}*/
typedef struct
{
    int value;
    int id;
    volatile int lock; // Adiciona um bloqueio à estrutura do semáforo
    struct process *list;
} Semaphore;

extern Semaphore semaphoreTable[MAX_SEMAPHORES];
extern Semaphore *create(int id);
extern void destroy(Semaphore *sem);
extern void down(Semaphore *sem);
extern void up(Semaphore *sem);

/* Forward definitions. */
extern int semget(unsigned int key);
extern int semctl(int semid, int cmd, int val);
extern int semop(int semid, int op);

#endif /* _ASM_FILE_ */
#endif /* SEM_H_ */
