/*******************************************************************************
*This file is part of ta-machine.                                              *
*                                                                              *
*ta-machine is free software: you can redistribute it and/or modify            *
*it under the terms of the GNU General Public License as published by          *
*the Free Software Foundation, either version 3 of the License, or             *
*(at your option) any later version.                                           *
*                                                                              *
*ta-machine is distributed in the hope that it will be useful,                 *
*but WITHOUT ANY WARRANTY; without even the implied warranty of                *
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
*GNU General Public License for more details.                                  *
*                                                                              *
*You should have received a copy of the GNU General Public License             *
*along with ta-machine. If not, see <http://www.gnu.org/licenses/>.            *
*******************************************************************************/

//System includes
#include <stdio.h>

//Library includes
#include "argtable3.h"

//local includes
#include "ta-machine.h"
#include "ta-machine-packet.h"


/* global arg_xxx structs */
struct arg_lit *verb, *help, *version;
struct arg_int *level;
struct arg_file *o, *file;
struct arg_end *end;

int main(int argc, char *argv[])
{
    /* the global arg_xxx structs are initialised within the argtable */
    void *argtable[] = {
        help    = arg_litn(NULL, "help", 0, 1, "display this help and exit"),
        version = arg_litn(NULL, "version", 0, 1, "display version info and exit"),
        level   = arg_intn(NULL, "level", "<n>", 0, 1, "foo value"),
        verb    = arg_litn("v", "verbose", 0, 1, "verbose output"),
        o       = arg_filen("o", NULL, "myfile", 0, 1, "output file"),
        file    = arg_filen(NULL, NULL, "<file>", 1, 100, "input files"),
        end     = arg_end(20),
    };

    int exitcode = 0;
    char progname[] = TA_MACHINE;

    int nerrors;
    nerrors = arg_parse(argc,argv,argtable);

    /* special case: '--help' takes precedence over error reporting */
    if (help->count > 0)
    {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        printf("Demonstrate command-line parsing in argtable3.\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        exitcode = 0;
        goto exit;
    }

    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0)
    {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 1;
        goto exit;
    }

exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return exitcode;
}
