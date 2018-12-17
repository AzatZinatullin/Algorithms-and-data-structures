
#include <iostream>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <curses.h>


using namespace std;
     
const int U = 26;

struct Set{
    char el;
    Set *next;
};
void Result(char* A);

int main()
{

    char A[U]={'a','A','a','A','B','C','D'} , B[U] = {'a','A','A','F','E','B'} , C[U]={'A','b','g', 'a','a','A','A','t'},  D[U]={'a','A','A','a','b','g','k'};
    
    bool f, f1;
    
   
   
    int n=0;
    char E[n];
 //   char *E = new char [U+1];
    
   
    for(int i = 0; A[i]; i++)
    {
        f = true;
        for(int j = 0; (B[j] && f) ; j++)
            if((A[i]==B[j]) || (A[i]==(B[j]-32))|| (A[i]==(B[j]+32)))
            {
                f=false;
            }
            if(f)
            {
            E[n] = A[i];
            n++;
            }
    }
    
    for (int i = 0; C[i]; i++)
    {
        f = true;
        for(int j=0; D[j] && f; j++)
        if ((C[i] == D[j]) || (C[i] == (D[j] - 32))|| (C[i] == (D[j] + 32)))
        {
            f1 = true;
            for(int k=0; E[k]; k++)
            if((E[k] == C[i])||(E[k] == (C[i]-32)) ||(E[k] == (C[i]+32)))
            {
                f1=false;
            }
            if(f)
            {
                E[n] = C[i];
                n++;
            }
        }
        
    } 
    
    
    for (int i = 0; i<strlen(E) ;i++)
    cout << E[i];
    
    cout << endl;
   
    printf("\nN is %d. Array result:\n", n);
    
    Result(E);
    
 
//    delete []E;
    
    return 0;
    
}

void Result(char* A)
{
    for(int i = 0; A[i]; i++)
    printf("%c", A[i]);
}


