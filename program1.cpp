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
    vector<int> iterazioni;
    unsigned int n = 0, m = 0, n1 = 0, c0 = 0, c1 = 0, c2 = 0;
    ifstream file("file1.csv");

    // check file

    if(!file.good()) {
        cout<<"unsuccessful file loading"<<endl;
        return 1;
    }
    else{
    while(file >> row) {
        if(m == 0){
            iterazioni = read_first(row);
            if(iterazioni.empty()){
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
                        c0 += 1;
                    else if (row[i] == "1")
                        c1 += 1;
                    else if (row[i] == "2")
                        c2 += 1;
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
    cout<<m<<"x"<<n<<endl;

    cout<<endl;

    cout<<c0<<endl;
    cout<<c1<<endl;
    cout<<c2<<endl;

    // save file (decidere cosa fare: sparso vs sparso+intero, ev. controlli)
    unsigned const int N = n, M = m;
    int matrix[M][N];
    unsigned int temp;

    ifstream file1("file1.csv");
    if(!file1.good()) {
        cout<<"unsuccessful file loading";
        return 1;
    }
    else{
    m = 0;
    while(file1 >> row1) {
        if(m == 0){
        m += 1;
        }
        else {
            for(n = 0; n < row1.size(); n++){
                if (!row1[n].empty()){
                    temp = stoi(row1[n]);
                    matrix[m-1][n] = temp;
                }
            }
            m += 1;
        }
    }
    }


    cout<<"iterazioni: ";
    for (auto i = iterazioni.begin(); i != iterazioni.end(); ++i){
        cout<< *i<<" ";
    }
    cout<<endl;

    //cout<<iterazioni.size()<<endl;

    for( int m = 0; m < M ; m++){
        for( int n=0; n < N; n++){
            cout<< matrix[m][n]<<" ";
         }
        cout<<endl;
     }



    m = m-1;
    cout<<endl<<M<<"x"<<N<<endl;
    cout<<endl;
    //cout<<iterazioni.size()<<endl;
    cout<<endl;

    cout<<c0<<endl;
    cout<<c1<<endl;
    cout<<c2<<endl;

}


vector<int> read_first(CSVRow row){
        unsigned int temp;
        vector<int> iterazioni;
        for(int i = 0; i < row.size(); i++){
                if (!row[i].empty()){
                    temp = stoi(row[i]);
                    iterazioni.push_back(temp);
                    }
        }
        return iterazioni;
}



