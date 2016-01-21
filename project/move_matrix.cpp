#ifndef MOVE_MATRIX_H
#define MOVE_MATRIX_H

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include"output_matrix.h"

using namespace std;

class move_matrix{
  unsigned short int changes;
  public:

    move_matrix (unsigned short int changes=0):changes(changes){};

    unsigned short int get_changes(){
            return changes;
            }

    void operator () (unsigned short int s[], string car, unsigned int M, unsigned int N) {
        unsigned short int flag;
        unsigned int i(0), j(0),eov(M*N);
        if(car=="blue"){
            for(int j = 0; j < N; j++){
                i=j;
                flag = (s[i] == 0) && (s[i+eov-N] == 1);//si accende solo se devo spostare l'elemento
                while(i < j+eov-N) {
                    if (s[i+N]==0) {
                        if (s[i] == 1){
                            s[i] = 0;
                            s[i+N] = 1;
                            i += 2*N;
                            if (changes==0)
                                changes=1;
                        }
                        else {
                            i += 2*N;
                        }
                    }else {
                        i += s[i+N]*N;
                    }
                }
                if (flag==1){
                    s[i]=1;
                    s[i+eov-N]=0;
                    if (changes==0)
                        changes=1;
                }
            }
        }

    else if(car=="red"){
        while( i < eov-N+1 ){
            j = i;
            flag = (s[j] == 0) && (s[j+N-1] == 2) ; //si accende solo se devo spostare l'elemento
            while(j < i+N-1) {
                if (s[j+1]==0) {
                    if (s[j] == 2){
                        s[j] = 0;
                        s[j+1] = 2;
                        j += 2;
                        if (changes==0)
                            changes=1;
                    }
                    else {
                        j += 2;
                    }
                }else{
                    j += (3-s[j+1]);
                }
            }
            if (flag==1){
                s[j]=2;
                s[j+N-1]=0;
                if (changes==0)
                    changes=1;
            }
        i += N;
        }
    }
    else
        exit(1);
    //changes = changes1+changes2-changes1*changes2;
    }
};

#endif // MOVE_MATRIX_H
int main(){

string car("blue");
unsigned int M(3), N(5);
unsigned short int s[M*N];
s[0]=s[10]=s[12]=2;
s[1]=s[2]=s[4]=s[7]=s[8]=s[5]=s[14]=1;
s[3]=s[6]=s[11]=s[13]=s[9]=0;
output_matrix output;
ofstream out;
out.open(to_string(0)+".csv");
output(s,M,N,out);
move_matrix step(0);
step(s,car,M,N);
output_matrix output1;
ofstream out1;
out1.open(to_string(1)+".csv");
output(s,M,N,out1);
return 1;}
