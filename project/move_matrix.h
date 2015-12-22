#ifndef MOVE_MATRIX_H
#define MOVE_MATRIX_H

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>

#define maxr 300
#define maxc 300

typedef  int mat[maxr][maxc];

using namespace std;

class move_matrix{
  unsigned short int changes;
  unsigned int M,N;
  unsigned int cont;
  public:

    move_matrix (unsigned short int changes=0,unsigned int M=0, unsigned int N=0, unsigned int cont=0):changes(changes),M(M),N(N),cont(cont){};

    unsigned short int get_changes(){
            return changes;
            }

    unsigned short int operator () (mat s) {
        unsigned short int flag;
        if(cont%2==0){
            for(int j = 0; j < N; j++){
                flag = (s[0][j] == 0) && (s[M-1][j] == 1);//si accende solo se devo spostare l'elemento
                int i (0);
                while(i < M-1) {
                    if (s[i+1][j]==0) {
                        if (s[i][j] == 1){
                            s[i][j] = 0;
                            s[i+1][j] = 1;
                            i += 2;
                            if (changes==0)
                                changes=1;
                        }
                        else {
                            i += 2;
                        }
                    }else {
                        i += s[i+1][j];
                    }
                }
                if (flag==1){
                    s[0][j]=1;
                    s[M-1][j]=0;
                    if (changes==0)
                        changes=1;
                }
            }
        }

    if(cont%2==1){
        for(int i=0;i<M;i++){
            flag = (s[i][0] == 0) && (s[i][N-1] == 2) ; //si accende solo se devo spostare l'elemento
            int j(0);
            while(j < N-1) {
                if (s[i][j+1]==0) {
                    if (s[i][j] == 2){
                        s[i][j] = 0;
                        s[i][j+1] = 2;
                        j += 2;
                        if (changes==0)
                            changes=1;
                    }
                    else {
                        j += 2;
                    }
                }else{
                    j += (3-s[i][j+1]);
                }
            }
            if (flag==1){
                s[i][0]=2;
                s[i][N-1]=0;
                if (changes==0)
                    changes=1;
            }
        }
    }
    //changes = changes1+changes2-changes1*changes2;
    }
};

#endif // MOVE_MATRIX_H
