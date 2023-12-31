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
int op;

//verifica se o argumento passado e um numero
int isNumber(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);  // Tenta converter a string para um número na base 10.

    // Se o ponteiro inicial for igual ao ponteiro a string não é um número.
    return *endptr == '\0';
}

/*
 * Prints program version and exits.
 */
static void version(void)
{
    printf("semop (Nanvix Coreutils) %d.%d\n\n", VERSION_MAJOR, VERSION_MINOR);
    printf("Copyright(C) 2011-2014 Pedro H. Penna\n");
    printf("This is free software under the ");
    printf("GNU General Public License Version 3.\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n\n");

    exit(EXIT_SUCCESS);
}

/*
 * Prints program usage and exits.
 */
static void usage(int status)
{
    printf("Usage: semop [options] <id> <op>\n\n");
    printf("Brief: Creates a semaphore. If already exists return semaphore id.\n\n");
    printf("Options:\n");
    printf("  --help             Display this information and exit\n");
    printf("  --version          Display program version and exit\n");

    exit(status);
}

/*
 * Gets number of the semaphore.
 */
static void getargs(int argc, char *const argv[]) {

   /* if (argc != 4) {
        fprintf(stderr, "Uso: %s <id> <op>\n", argv[0]);
        exit(EXIT_FAILURE);
    }*/

    // Converte argumentos da linha de comando para inteiros

    for (int i = 1; i < argc; i++)
    {
        /* Parse command line argument. */
        if (!strcmp(argv[i], "--help"))
        {
            usage(EXIT_SUCCESS);
        }
        else if (!strcmp(argv[i], "--version"))
        {
            version();
        }else if (!isNumber(argv[i])) 
        {
            fprintf(stderr, "Error: argument is invalid.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
      
    }

    id = atoi(argv[1]);
    op = atoi(argv[2]);

    /* Invalid semaphore id. */
    if (id < 0 || id  > MAX_SEMAPHORES)
    {
        fprintf(stderr, "semop: wrong id for semaphore. Please choose a number between 0 and %d\n", 100);
        exit(EXIT_FAILURE);
    }

    if(op ==  0){
        fprintf(stderr, "semop: wrong value for operation . Please choose a number less than 0 or bigger than 0 %d\n", 0);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *const argv[]) {
   
    

    getargs(argc, argv);

    int result = semop(id, op);

    if (result >= 0){
        printf("\n %d - retorno kernel ", result);
        return result;
    } else{
        return -1;
    }

}
    
    
