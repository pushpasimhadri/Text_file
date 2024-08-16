#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>

#define Driver_path           "/dev/ModuleDiagnostic"
#define DIR_FAILURE           -1
#define DIR_SUCCESS           0
#define DIR_LOG               printf         /* Macro for information messages */
#define DIR_ERRLOG            printf         /* Macro for error messages */
#define OP_32BIT_READ         3
#define OP_32BIT_WRITE        6
#define MAX_CATEGORIES 10
#define MAX_LINE_LENGTH 60

struct mem {
    int operation;
    unsigned int address;
    unsigned int value;
};

int registerdata_main(void);
