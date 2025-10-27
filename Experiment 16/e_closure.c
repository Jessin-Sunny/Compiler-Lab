#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 50

int total_states, total_transitions;
bool epstable[MAX][MAX] = {false};

void get_enfa()
{
    char transitions[MAX], *p;
    printf("Enter the number of states : ");
    scanf("%d", &total_states);
    printf("Enter the number of transitions : ");
    scanf("%d", &total_transitions);
    printf("Enter the transitions in the form statesymbolstate, use # for epsilon\n");
    for(int i=0; i < total_transitions; i++)
    {
        scanf(" %[^\n]", transitions);
        if((p=strchr(transitions, '#'))!=NULL)  //contains epsilon transitions
        {
            //int j,k;
            //sscanf(transitions, "q%d", &j);   //store starting state number
            //j = atoi(p+2);                    //p+2 is pointer, returns the integer in that pointer coversion takes place
            //epstable[i][j] = true;
            int from, to;
            sscanf(transitions, "q%d#q%d", &from, &to);
            epstable[from][to] = true;
        }
    }
}

void find_eclosure(int state, bool visited[])   //recursive procedure
{
    visited[state] = true;
    for(int i=0; i < total_states; i++)
    {
        if(epstable[state][i] && !visited[i])   //epsilon transition and not visited
        {
            find_eclosure(i, visited);
        }
    }
}

void print_eclosure()
{
    for(int i=0; i < total_states; i++)
    {
        bool visited[MAX] = {false};
        char outstr[MAX] = {'\0'}, tempstr[MAX] = {'\0'};
        find_eclosure(i, visited);
        printf("eclosure(q%d) = {",i);
        for(int j=0; j < total_states; j++)
        {
            if(visited[j])
            {
                sprintf(tempstr, "q%d,", j);
                strcat(outstr, tempstr);
            }
        }
        outstr[strlen(outstr) - 1] = '\0';      //removing last  comma
        printf("%s}\n", outstr);
    }
}

int main()
{
    get_enfa();
    print_eclosure();
    return 0;
}
