#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define VARLEN 10       // maximum allowed operand size is 10 [10digit]
#define MAXSIZE 50

char opndstack[MAXSIZE][VARLEN] = {'\0'};
char opstack[MAXSIZE] = {'\0'};
int optop = -1, opndtop = -1;
char expr[MAXSIZE] = {'\0'};

int priority(char c)
{
    return (c == '+' || c == '-')?1:(c == '*' || c == '/' ) ? 2 : c == '=' ? -1 : 0;
}


void icg()
{
    int i = 0;
    int tempCount = 1;
    while(expr[i] != '\0')
    {
        char tempopnd[MAXSIZE] = {'\0'};
        int j = 0;
        // get all operands in case of more than 1 digit like 20, 100, 3000
        while(isalnum(expr[i]))
        {
            tempopnd[j++] = expr[i++];
        }
        // if operand exists
        if(j != 0)
        {
            strcpy(opndstack[++opndtop],tempopnd);
        }
        //if whitespace skip
        if(expr[i] == ' ')
        {
            i++;
            continue;
        }
        //push operator on higher priority incoming operator
        if((optop >= 0 && (priority(opstack[optop]) < priority(expr[i])))||optop < 0)
        {
            opstack[++optop] = expr[i++];
        }
        //pop else lower priority
        else if(optop >= 0)
        {
            // creating an array of size 2 for storing operator
            char op[2] = {'\0'};
            op[0] = opstack[optop--];
            printf("t%d = %s %s %s\n",tempCount, opndstack[opndtop - 1], op, opndstack[opndtop]);
            sprintf(opndstack[--opndtop], "t%d", tempCount++);          //updating top of opernad stack with temporary variable
        }
    }
    // pop remaining elements from operator stack
    while(optop >= 0)
    {
        char op[2] = {'\0'};
        op[0] = opstack[optop--];
        if(strcmp(op, "="))             //returns 0 on equal
        {
            printf("t%d = %s %s %s\n",tempCount, opndstack[opndtop - 1], op, opndstack[opndtop]);
            sprintf(opndstack[--opndtop], "t%d", tempCount++);          //updating top of opernad stack with temporary variable
        }
        else
        {
            //usually last
            printf("%s = t%d\n",opndstack[opndtop--],tempCount - 1);
        }
    }
}

int main()
{
    printf("Enter the expression without whitespaces : ");
    scanf("%[^\n]", expr);
    icg();
    return 0;
}
