#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "vect.h"
#include "input.h"

using namespace std;

int main(){

CSVRow row, row1, row2;
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
m = m-1;
//
//cout<<m<<"x"<<n<<endl;
unsigned const int N(n), M(m);
//cout<<endl;
//cout<<numel_0<<endl;
//cout<<numel_1<<endl;
//cout<<numel_2<<endl;


// save file (decidere cosa fare: sparso vs sparso+intero, ev. controlli)
// in questo caso sto mettendo tutto in una matrice!

//array <array <unsigned short int, N>, M> s; //da mettere la nuova classe array di array
unsigned short int s[M][N];
unsigned short int changes1(1),changes2(1),flag(0),temp,curr,foll;
unsigned int cont(0);

ifstream file1("file1.csv");
if(!file1.good()) {
    cout<<"unsuccessful file loading";
    return 1;
}else{
    m = 0;
    while(file1 >> row1) {
        if(m == 0){
        m += 1;
        }
        else {
            for(n = 0; n < row1.size(); n++){
                if (!row1[n].empty()){
                    temp = stoi(row1[n]);
                    s[m-1][n] = temp;
                }
            }
            m += 1;
        }
    }
}

//cout<<"iterazioni: ";
//for (auto i = it.begin(); i != it.end(); ++i){
//    cout<< *i<<" ";
//}
//cout<<endl;


//cout<<it.size()<<endl;

//stampo la matrice iniziale
//for( int m = 0; m < M ; m++){
//    for( int n=0; n < N; n++){
//        cout<< s[m][n]<<" ";
//        }
//    cout<<endl;
//}

//m = m-1;
//cout<<endl<<M<<"x"<<N<<endl;
//cout<<endl;
//cout<<it.size()<<endl;
//cout<<endl;
//cout<<numel_0<<endl;
//cout<<numel_1<<endl;
//cout<<numel_2<<endl;



//facciamo le iterazioni!
for (auto k = it.begin(); k != it.end(); ++k){

    while( cont<*k && changes1+changes2-changes1*changes2==1) {
        if(cont%2==0){
            changes1=0;
    // SPOSTA 1
    for(int j = 0; j < N; j++){
        flag = (s[0][j] == 0) && (s[M-1][j] == 1);//si accende solo se devo spostare l'elemento
        int i (0);
        while(i < M-1) {

            if (s[i+1][j]==0) {
                if (s[i][j] == 1){
                    s[i][j] = 0;
                    s[i+1][j] = 1;
                    i += 2;
                    if (changes1==0)
                        changes1=1;
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
            if (changes1==0)
                changes1=1;
    }
    }
}

    if(cont%2==1){
        changes2=0;
    // sposta 2

    for(int i=0;i<M;i++){
        flag = (s[i][0] == 0) && (s[i][N-1] == 2) ; //si accende solo se devo spostare l'elemento
        int j(0);
        while(j < N-1) {

            if (s[i][j+1]==0) {
                if (s[i][j] == 2){
                    s[i][j] = 0;
                    s[i][j+1] = 2;
                    j += 2;
                    if (changes2==0)
                        changes2=1;
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
            if (changes2==0)
                changes2=1;
        }
    }
}
    cont++;
}

//for(int i=0;i<M;i++){
//            for(int j=0;j<N;j++){
//                cout << s[i][j] << " ";
//            }
//            cout << endl;
//        }

//        cout<<endl;

ofstream out;
out.open(to_string(*k)+".csv");
for(int i=0;i<M;i++){
            for(int j=0;j<N-1;j++){
                out << s[i][j] << ",";
            }
            out<<s[i][N-1]<<endl;
}
out.close();
}


}
