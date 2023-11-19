#include <stdlib.h>
#include <stdio.h>

/* Software versioning. */
#define VERSION_MAJOR 1 /* Major version. */
#define VERSION_MINOR 0 /* Minor version. */

/*
 * Echo arguments.
 */
int main(int argc, char *const argv[])
{
    int i;

    /* Print arguments. */
    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i + 1 < argc) ? " " : "\n");

    return (EXIT_SUCCESS);
}
