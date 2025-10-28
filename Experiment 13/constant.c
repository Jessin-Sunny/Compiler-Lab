#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXQUADS 10
#define OPNDSIZE 5
typedef enum {false,true}bool;
int numquads=0;
typedef struct
{
	char op;
	char op1[OPNDSIZE];
	char op2[OPNDSIZE];	
	char res[OPNDSIZE];
} quadruple;
quadruple quads[MAXQUADS];
bool isint(char*s) //Check for integer constant values
{
    while(*s)
    {
        if(!isdigit(*s))
            return false;
        s++;
    }
    return true;
}
//Evaluate the given three address expression
int calculate(char *op1,char *op2, char optr)
{
  int retval = 0;
  switch(optr)
  {
    case '+': 
                retval = atoi(op1)+atoi(op2);
                break;
    case '-': 
                retval = atoi(op1)-atoi(op2);
                break;
    case '*': 
                retval = atoi(op1)*atoi(op2);
                break;
    case '/': 
                if(atoi(op2)!=0)
                    retval = atoi(op1)/atoi(op2);
                break;
    default:
                break;
  }
  return retval;
}
char *getconstval(char *opnd) //Get the constant value after folding
{
  for(int i=0;i<numquads;i++)
  {
    if(quads[i].op=='='&&!strcmp(quads[i].res,opnd))
      return quads[i].op1;
  }
  return opnd;
}
void fold() //Evaluate all constant expressions and store back
{
  for(int i=0;i<numquads;i++)
  {
    if(isint(quads[i].op1)&&isint(quads[i].op2))  //fold
    {
     int result = calculate(quads[i].op1,quads[i].op2,quads[i].op);
     quads[i].op='=';
     snprintf(quads[i].op1,OPNDSIZE,"%d",result);
     strcpy(quads[i].op2,"-");
    }
  }
}
void propogate() //Propogate the evaluated constant values
{
  for(int i=0;i<numquads;i++)
  {
    strcpy(quads[i].op1,getconstval(quads[i].op1));
    strcpy(quads[i].op2,getconstval(quads[i].op2));
    if(isint(quads[i].op1)&&isint(quads[i].op2)) // fold again if both opnds became integers
      fold(); 
  }
}
int main()
{
    memset(quads,0,sizeof(quads)); //clear the quadruples table
    printf("Enter the number of 3-address instructions\n");
    scanf("%d",&numquads);
    printf("Enter each instruction\n e.g.\n + 2 3 a\n = 3 - b\n");
    for(int i=0;i<numquads;i++)
    {
        getchar(); //Remove stray new lines
        quads[i].op=getchar();
        scanf("%s %s %s",quads[i].op1,quads[i].op2,quads[i].res);
    }
    fold(); 
    propogate();
    printf("The code after constant folding and propogation is:\n");
    printf("op\topnd1\topnd2\tresult\n");
    printf("==============================\n");
    for(int i=0;i<numquads;i++)
    {
        printf("%c\t%s\t%s\t%s\n",quads[i].op,quads[i].op1,quads[i].op2,quads[i].res);
    }
 return false;
}
