#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "clvect.cpp"
#include "input.cpp"

using namespace std;

int main(){

CSVRow row, row1;
vector<unsigned int> it;
unsigned int n (0), m (0), n1 (0), numel_0 (0), numel_1 (0), numel_2 (0);
ifstream file("file1.csv");

// check file

if(!file.good()) {
    cout<<"unsuccessful file loading"<<endl;
    return 1;
}else{
    while(file >> row) {
        if(m == 0){
            it = read_first(row);
            if(it.empty()){
                cout<<"empty file"<<endl;
                return 1;
            }
            m += 1;
        }
        else {
            n1 = 0;
            for(int i = 0; i < row.size(); i++){
                if (!row[i].empty()){
                    n1 += 1;
                    if (row[i] == "0")
                        numel_0 += 1;
                    else if (row[i] == "1")
                        numel_1 += 1;
                    else if (row[i] == "2")
                        numel_2 += 1;
                    else {
                        cout<< "data is not a 0,1,2 valued matrix"<<endl;
                        return 1;
                    }
                }
            }
            if( n1 != n && m>1) {
                cout<<"data is not a matrix"<<endl;
                return 1;
            }
            n = n1;
            m += 1;
        }
    }
}

if (m == 1){
        cout<<"empty matrix";
        return 1;
}

file.close();
//definisco numero di righe e colonne;successivamente
//gli indici m ed n vengono riusati e l'info viene persa
int M(m-1),N(n);

cout<<"Matrix dimension: " << M << "x" << N <<endl;
cout<<endl;
cout<<"Number of '0' elements: " << numel_0 << endl;
cout<<"Number of '1' elements: " << numel_1 << endl;
cout<<"NUmber of '2' elements: " << numel_2 << endl;
double zeros(numel_0);
cout << "Sparsity (null elems percentage): " << zeros/(numel_0+numel_1+numel_2) << endl;

//alloco direttamente la struttura sparsa
vect<vect<int> > R(M);
vect<vect<int> > C(N);
int temp(0);

ifstream file1("file1.csv");
if(!file1.good()) {
    cout<<"unsuccessful file loading";
    return 1;
}else{
    m = 0;
    while(file1 >> row1){
        if(m==0)
            m+=1;
        else{
        for(n = 0; n < row1.size(); n++){
            if (!row1[n].empty()){
                temp = stoi(row1[n]);
                if(temp==2)
                    R[m-1].tail_add(n);
                if(temp==1)
                    C[n].tail_add(m-1);
                }
            }
        m += 1;
        }
    }
}
cout << R << endl;
cout << C << endl;

 cout <<"Iterations to be edited: ";
for (auto i = it.begin(); i != it.end(); ++i){
    cout<< *i <<" ";
}
cout<<endl;
}
