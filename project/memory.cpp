#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>

using namespace std;

int main(){
    int M(1000),N(1000);
    int s[M][N];
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++)
                s[i][j]=i*j;
    }
    cout<<"ciao"<<endl;
    int k(1000000);
    int t[k];
    for (int i=0;i<k;i++)
        t[i]=i;

}
