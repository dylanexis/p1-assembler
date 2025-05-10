/**
 * Project 1
 * Assembler code fragment for LC-2K
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//Every LC2K file will contain less than 1000 lines of assembly.
#define MAXLINELENGTH 1000
#define MAXLABELLENGTH 6

int readAndParse(FILE *, char *, char *, char *, char *, char *);
static void checkForBlankLinesInCode(FILE *inFilePtr);
static inline int isNumber(char *);
static inline void printHexToFile(FILE *, int);

/* Error checking */
bool intCheck(char *arg);
bool regCheck(int reg);
void saveLabel(int address, char name);


struct label{
    int address;
    char name[7];
};

/*R-type Instructions -> opcode, field0, field1, field2*/
int add(char *field0, char *field1, char *field2); /*opcode 000*/

int nor(char *field0, char *field1, char *field2); /*opcode 001*/

/*I-type Instructions -> */
int lw(char *field0, char *field1, char *field2);

int sw(char *field0, char *field1, char *field2);

int beq(char *field0, char *field1, char *field2);

/*J type -> opcode, field0, field1
int jalr(char *field0, char *field1);
*/

/* O-type Instructions -> opcode only */
int halt(); /* opcode 111*/

int noop(); /* opcode 110*/



int
main(int argc, char **argv)
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
            arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

    if (argc != 3) {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
            argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];

    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }

    // Check for blank lines in the middle of the code.
    checkForBlankLinesInCode(inFilePtr);

    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }

    /* here is an example for how to use readAndParse to read a line from
        inFilePtr */


  /* First pass here */
    
    while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) ) {
        if (!isNumber(arg2)){

        }
        
    }


    /* this is how to rewind the file ptr so that you start reading from the
        beginning of the file */
    rewind(inFilePtr);
    
    
    /* Second pass here */
    int encoding;
    //int address = 0;
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)){

    if (!strcmp(opcode, "add")) {
        /* do whatever you need to do for opcode "add" */
        //printf("add registers\n");
        encoding = add(arg0, arg1, arg2);
    }

    else if (!strcmp(opcode, "nor")){
        encoding = nor(arg0, arg1, arg2);
    }

    else if (!strcmp(opcode, "halt")){
        //printf("halt program\n");
        encoding = halt();
    }

    else if (!strcmp(opcode, "noop")){
        //printf("no operation\n");
        encoding = noop();
    }

    else{
        printf("Error: Unrecognized opcode\n");
        exit(1);
    }

    /* here is an example of using printHexToFile. This will print a
       machine code word / number in the proper hex format to the output file */
    //address++;
    printHexToFile(outFilePtr, encoding);

}

    return(0);
}

// Returns non-zero if the line contains only whitespace.
static int lineIsBlank(char *line) {
    char whitespace[4] = {'\t', '\n', '\r', ' '};
    int nonempty_line = 0;
    for(int line_idx=0; line_idx < strlen(line); ++line_idx) {
        int line_char_is_whitespace = 0;
        for(int whitespace_idx = 0; whitespace_idx < 4; ++ whitespace_idx) {
            if(line[line_idx] == whitespace[whitespace_idx]) {
                line_char_is_whitespace = 1;
                break;
            }
        }
        if(!line_char_is_whitespace) {
            nonempty_line = 1;
            break;
        }
    }
    return !nonempty_line;
}

// Exits 2 if file contains an empty line anywhere other than at the end of the file.
// Note calling this function rewinds inFilePtr.
static void checkForBlankLinesInCode(FILE *inFilePtr) {
    char line[MAXLINELENGTH];
    int blank_line_encountered = 0;
    int address_of_blank_line = 0;
    rewind(inFilePtr);

    for(int address = 0; fgets(line, MAXLINELENGTH, inFilePtr) != NULL; ++address) {
        // Check for line too long
        if (strlen(line) >= MAXLINELENGTH-1) {
            printf("error: line too long\n");
            exit(1);
        }

        // Check for blank line.
        if(lineIsBlank(line)) {
            if(!blank_line_encountered) {
                blank_line_encountered = 1;
                address_of_blank_line = address;
            }
        } else {
            if(blank_line_encountered) {
                printf("Invalid Assembly: Empty line at address %d\n", address_of_blank_line);
                exit(2);
            }
        }
    }
    rewind(inFilePtr);
}

/* Operations (and non-operations) 
    bits 31-25 unused for all
*/


/* 
R-type Instructions
    bits 24-22: opcode
    bits 21-19: reg A
    bits 18-16: reg B
    bits 15-3: unused (should all be 0)
    bits 2-0: destReg
*/

/* error check later */
int add(char *field0, char *field1, char *field2){
   int instr = 0;
   int opcode = 0;
   int regA = 0;
   int regB = 0;
   int destReg = 0;
   

    intCheck(field0);
    regA = atoi(field0);
    regCheck(regA);


    intCheck(field1);
    regB = atoi(field1);
    regCheck(regB);


    intCheck(field2);
    destReg = atoi(field2);
    regCheck(destReg);

    instr = (opcode << 22);
    instr |= (regA << 19);
    instr |= (regB << 16);
    instr |= destReg;

   return instr;
}

int nor(char *field0, char *field1, char *field2){
    int instr = 0;
    int opcode = 1;
    int regA = 0;
    int regB = 0;
    int destReg = 0;
    
    intCheck(field0);
    regA = atoi(field0);
    regCheck(regA);

    intCheck(field1);
    regB = atoi(field1);
    regCheck(regB);

    intCheck(field2);
    destReg = atoi(field2);
    regCheck(destReg);

    instr = (opcode << 22);
    instr |= (regA << 19);
    instr |= (regB << 16);
    instr |= destReg;

   return instr;
}

/* 
I-type Instructions
    bits 24-22: opcode
    bits 21-19: reg A
    bits 18-16: reg B
    bits 15-0: offsetField (a 16-bit, 2’s complement number with a range of -32768 to 32767)

*/



/*
O-type Instructions
    bits 24-22: opcode
    bits 21-0: unused (should all be 0)
*/


int halt(){
    int val = (6 << 22);
    return val;
}

int noop(){
    int val = (7 << 22);
    return val;
}



/* Helper functions */


bool intCheck(char *string){
    if (isNumber(string)){
        return true; 
    }
    else {
    printf("Error: Non-integer register argument\n");
        exit(1);
    }
}

bool regCheck(int reg){
    if (reg < 0 || reg > 7){
        printf("Error: Registers outside the range [0, 7]");
        exit(1);
    }
    else {
    return true;
    }
}

void saveLabel(int address, char name){

}





/*
* NOTE: The code defined below is not to be modifed as it is implimented correctly.
*/

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
    char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
	/* reached end of file */
        return(0);
    }

    /* check for line too long */
    if (strlen(line) == MAXLINELENGTH-1) {
	printf("error: line too long\n");
	exit(1);
    }

    // Ignore blank lines at the end of the file.
    if(lineIsBlank(line)) {
        return 0;
    }

    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label)) {
	/* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
        opcode, arg0, arg1, arg2);

    return(1);
}

static inline int
isNumber(char *string)
{
    int num;
    char c;
    return((sscanf(string, "%d%c",&num, &c)) == 1);
}


// Prints a machine code word in the proper hex format to the file
static inline void 
printHexToFile(FILE *outFilePtr, int word) {
    fprintf(outFilePtr, "0x%08X\n", word);
}
