/*
Converting e-NFA to NFA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 50
#define MAX_SYMBOLS 50

int n,m;                //total states and total input symbols(no epsilon)
char symbols[MAX_SYMBOLS];
int transitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES];           //transition[i][j][k]=1 means ith state jth symbol transition to kth state
int epsilon[MAX_STATES][MAX_STATES];            //epsilon transitions
int epsilonClosure[MAX_STATES][MAX_STATES];
int closureCount[MAX_STATES];

void addToClosure(int state, int s)
{
    // s is to be added to the closure of state
    if(!epsilonClosure[state][s])
    {
        epsilonClosure[state][s] = 1;
        closureCount[state]++;
        for(int i =0 ; i < n; i++)
        {
            // if there is an epsilon transition exists from state i
            if(epsilon[s][i])
            {
                addToClosure(state, i);
            }
        }
    }

}

void computeEpsilonClosure()
{
    for(int i=0; i < n; i++)
    {
        memset(epsilonClosure[i], 0, sizeof(epsilonClosure[i]));
        closureCount[i] = 0;
        addToClosure(i, i);
    }
}

int main()
{
    printf("How many states ? : ");
    scanf("%d", &n);
    printf("How many symbols ? : ");
    scanf("%d", &m);
    printf("Enter the symbols [no epsilon] : ");
    for(int i=0; i< m; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    //clearing transition table and epsilon transitions
    memset(transitions, 0, sizeof(transitions));
    memset(epsilon, 0, sizeof(epsilon));

    printf("Enter the transitions for each state and for each symbol\n");
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < m; j++)
        {
            int num;
            printf("Enter the total number of states reachable when symbol %c on state q%d : ",symbols[j],i);
            scanf("%d", &num);
            if(num)
            {
                for(int k = 0; k < num; k++)
                {
                    printf("Enter the next state: ");
                    int s;
                    scanf("%d", &s);
                    transitions[i][j][s] = 1;
                }
            }
        }
    }
    //epsilon transition input
    printf("Enter the epsilon transition states in the form state_number state_number, -1 -1 to stop\n");
    while(1)
    {
        int a,b;
        scanf("%d %d", &a, &b);
        if(a == -1 && b == -1)
        {
            break;
        }
        epsilon[a][b] = 1;
    }

    computeEpsilonClosure();

    //transition table of NFA without epsilon transitions
    //Extreme Case: q0 -#-> q1 -j-> q2 -#-> q3
    for(int i=0; i < n; i++)
    {
        for(int j = 0; j< m; j ++)
        {
            int result[MAX_STATES] = {0};
            for(int k=0; k < n; k++)
            {
                if(epsilonClosure[i][k])
                {
                    for(int l=0; l < n; l++)
                    {
                        if(transitions[k][j][l])
                        {
                            for(int p=0; p < n; p++)
                            {
                                if(epsilonClosure[l][p])
                                {
                                    result[p] = 1;
                                }
                            }
                        }
                    }
                }
            }
            printf("Transition states when symbol %c on state q%d: {", symbols[j],i);
            for(int x=0; x < n; x++)
            {
                if(result[x])
                {
                    printf("q%d ", x);
                }
            }
            printf("}\n");
        }
    }

    return 0;
}
jessin@Jessin:~/RIT/S7/Exp17$ cat nfaetonfa.c
/*
Converting e-NFA to NFA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 50
#define MAX_SYMBOLS 50

int n,m;                //total states and total input symbols(no epsilon)
char symbols[MAX_SYMBOLS];
int transitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES];           //transition[i][j][k]=1 means ith state jth symbol transition to kth state
int epsilon[MAX_STATES][MAX_STATES];            //epsilon transitions
int epsilonClosure[MAX_STATES][MAX_STATES];
int closureCount[MAX_STATES];

void addToClosure(int state, int s)
{
    // s is to be added to the closure of state
    if(!epsilonClosure[state][s])
    {
        epsilonClosure[state][s] = 1;
        closureCount[state]++;
        for(int i =0 ; i < n; i++)
        {
            // if there is an epsilon transition exists from state i
            if(epsilon[s][i])
            {
                addToClosure(state, i);
            }
        }
    }

}

void computeEpsilonClosure()
{
    for(int i=0; i < n; i++)
    {
        memset(epsilonClosure[i], 0, sizeof(epsilonClosure[i]));
        closureCount[i] = 0;
        addToClosure(i, i);
    }
}

int main()
{
    printf("How many states ? : ");
    scanf("%d", &n);
    printf("How many symbols ? : ");
    scanf("%d", &m);
    printf("Enter the symbols [no epsilon] : ");
    for(int i=0; i< m; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    //clearing transition table and epsilon transitions
    memset(transitions, 0, sizeof(transitions));
    memset(epsilon, 0, sizeof(epsilon));

    printf("Enter the transitions for each state and for each symbol\n");
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < m; j++)
        {
            int num;
            printf("Enter the total number of states reachable when symbol %c on state q%d : ",symbols[j],i);
            scanf("%d", &num);
            if(num)
            {
                for(int k = 0; k < num; k++)
                {
                    printf("Enter the next state: ");
                    int s;
                    scanf("%d", &s);
                    transitions[i][j][s] = 1;
                }
            }
        }
    }
    //epsilon transition input
    printf("Enter the epsilon transition states in the form state_number state_number, -1 -1 to stop\n");
    while(1)
    {
        int a,b;
        scanf("%d %d", &a, &b);
        if(a == -1 && b == -1)
        {
            break;
        }
        epsilon[a][b] = 1;
    }

    computeEpsilonClosure();

    //transition table of NFA without epsilon transitions
    //Extreme Case: q0 -#-> q1 -j-> q2 -#-> q3
    for(int i=0; i < n; i++)
    {
        for(int j = 0; j< m; j ++)
        {
            int result[MAX_STATES] = {0};
            for(int k=0; k < n; k++)
            {
                if(epsilonClosure[i][k])
                {
                    for(int l=0; l < n; l++)
                    {
                        if(transitions[k][j][l])
                        {
                            for(int p=0; p < n; p++)
                            {
                                if(epsilonClosure[l][p])
                                {
                                    result[p] = 1;
                                }
                            }
                        }
                    }
                }
            }
            printf("Transition states when symbol %c on state q%d: {", symbols[j],i);
            for(int x=0; x < n; x++)
            {
                if(result[x])
                {
                    printf("q%d ", x);
                }
            }
            printf("}\n");
        }
    }

    return 0;
}
