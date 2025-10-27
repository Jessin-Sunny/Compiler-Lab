#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 5
#define SIZE 20

//Three Address Code
struct {
    char res[LEN];
    char op;
    char opnd1[LEN];
    char opnd2[LEN];
} tac[SIZE];
int total_tac;
char instr[SIZE];

void read_tac()
{
    printf("How many Three Address Instructions ? : ");
    scanf("%d", &total_tac);
    printf("Enter the instructions in the format result = operator1 operand operator2\n");
    for(int i = 0; i < total_tac; i++)
    {
        scanf("%s = %s %c %s", tac[i].res, tac[i].opnd1, &tac[i].op, tac[i].opnd2);
    }
}

char *get_instr(char op)
{
    switch(op)
    {
        case '+' : strcpy(instr, "ADD"); break;
        case '-' : strcpy(instr,"SUB"); break;
        case '*' : strcpy(instr,"MUL"); break;
        case '/' : strcpy(instr,"DIV"); break;
        default : strcpy(instr, "INVALID"); break;
    }
    return instr;
}

void generate_tc()
{
    /*
        MOV  Destination, Source
        1. Move Operator1 to AX
        2. Instruction is done with AX and Operator2
        3. Move AX to result
    */
    for(int i = 0; i < total_tac; i++)
    {
        printf("MOV AX, %s\n%s AX, %s\nMOV %s, AX\n", tac[i].opnd1, get_instr(tac[i].op), tac[i].opnd2, tac[i].res);
    }
}

int main()
{
    read_tac();
    generate_tc();
    return 0;
}
