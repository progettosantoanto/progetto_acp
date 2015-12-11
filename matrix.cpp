#include<stdlib.h>
#include<iostream>
#include<memory>
#include<algorithm>
#include<ostream>
#include<fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main () {

const int M (4);
const int N (5);
unsigned short int mat[M][N];
const int K(4);
int k(0);
int changes1(1),changes2(1),flag(0);

for(int i=0;i<M;i++){
	for(int j=0;j<N;j++){
		mat[i][j]= rand() % 3;
		cout << mat[i][j] << " ";
	}
	cout << endl;
}
cout<<endl;

while( k<K && changes1+changes2-changes1*changes2==1) {
		if(k%2==0){
            changes1=0;
    // SPOSTA 1
    for(int j = 0; j < N; j++){
        flag = (mat[0][j] == 0) && (mat[M-1][j] == 1);//si accende solo se devo spostare l'elemento
        int i (0);
        while(i < M-1) {

            if (mat[i+1][j]==0) {
                if (mat[i][j] == 1){
                    mat[i][j] = 0;
                    mat[i+1][j] = 1;
                    i += 2;
                    if (changes1==0)
                        changes1=1;
                    }
                else {
                    i += 2;
                }

            }else {
                i += mat[i+1][j];
            }

    }
    if (flag==1){
            mat[0][j]=1;
            mat[M-1][j]=0;
            if (changes1==0)
                changes1=1;
    }
    }
}

    if(k%2==1){
        changes2=0;
    // sposta 2

    for(int i=0;i<M;i++){
        flag = (mat[i][0] == 0) && (mat[i][N-1] == 2) ; //si accende solo se devo spostare l'elemento
        int j(0);
        while(j < N-1) {

            if (mat[i][j+1]==0) {
                if (mat[i][j] == 2){
                    mat[i][j] = 0;
                    mat[i][j+1] = 2;
                    j += 2;
                    if (changes2==0)
                        changes2=1;
                }
                else {
                    j += 2;
                }
            }else{
                j += (3-mat[i][j+1]);
            }
    }
    if (flag==1){
            mat[i][0]=2;
            mat[i][N-1]=0;
            if (changes2==0)
                changes2=1;
        }
    }
}
    k++;

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    cout<<endl;
}

cout << "Num. iterations: " << k << endl;
}


