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

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>

/* Software versioning. */
#define VERSION_MAJOR 1 /* Major version. */
#define VERSION_MINOR 0 /* Minor version. */

/* Default Process name. */
#define PROCESS_DEFAULT 0

/*
 * Program arguments.
 */

int id;
int cmd;
int val;

/*
 * Prints program version and exits.
 */
static void version(void)
{
    printf("semctl (Nanvix Coreutils) %d.%d\n\n", VERSION_MAJOR, VERSION_MINOR);
    printf("Copyright(C) 2011-2014 Pedro H. Penna\n");
    printf("This is free software under the ");
    printf("GNU General Public License Version 3.\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n\n");

    exit(EXIT_SUCCESS);
}

/*
 * Prints program usage and exits.
 */
static void usage(void)
{
    printf("Usage: semctl [options] <id> <cmd> <val>\n\n");
    printf("Brief: Creates a semaphore. If already exists return semaphore id.\n\n");
    printf("Options:\n");
    printf("  --help             Display this information and exit\n");
    printf("  --version          Display program version and exit\n");

    exit(EXIT_SUCCESS);
}

/*
 * Gets number of the semaphore.
 */
static void getargs(int argc, char *const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <id> <cmd> <val>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Converte argumentos da linha de comando para inteiros
    id = atoi(argv[1]);
    cmd = atoi(argv[2]);
    val = atoi(argv[3]);

    /* Invalid semaphore id. */
    if (id < 0 || id > 100 || val < 0 || cmd < 0)
    {
        fprintf(stderr, "semctl: wrong id for semaphore. Please choose a number between 0 and %d\n", 100);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *const argv[]) {
    // Processa os argumentos da linha de comando
    getargs(argc, argv);

    printf("%d - %d - %d - Valores semctl", id, cmd, val);

    // Chamada para semctl com os argumentos da linha de comando
    int result = semctl(id, cmd, val);

    // Exibindo o resultado
    printf("\n %d - retorno kernel\n", result);

    return 0;
}
