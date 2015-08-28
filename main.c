/* 
 * File:   main.c
 * Author: Donatello
 *
 * Created on 27 de Agosto de 2015, 14:01
 */

#include <stdio.h>
#include <stdlib.h>
#include "aritmetica.h"
#include "Arq/mongoose.h"
#include "Arq/sqlite3.h"

int main(int argc, char** argv) {

    fprintf(stdout, "2 + 3 = %d \n", adicao(2, 3));
    return 0;
}

