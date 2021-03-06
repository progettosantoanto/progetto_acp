#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "clvect.h"
#include "input.h"


using namespace std;

int main(){

CSVRow row, row2;
vector<unsigned int> it;
unsigned int n (0), m (0), n1 (0), numel_0 (0), numel_1 (0), numel_2 (0), temp(0);
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

vect<vect<int> > R(M);
vect<vect<int> > C(N);

ifstream file2("file1.csv");
if(!file2.good()) {
    cout<<"unsuccessful file loading";
    return 1;
}else{
    m = 0;
    while(file2 >> row2) {
    if(m==0)
        m+=1;
    else{
            for(n = 0; n < row2.size(); n++){
                if (!row2[n].empty()){
                    temp = stoi(row2[n]);
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
file2.close();

//cout << R << endl; //NB: l'input funziona
//cout << C << endl;

//da qui
unsigned short int changes1(1),changes2(1),flag(0);
unsigned int cont(0),l;
for (auto k = it.begin(); k != it.end(); ++k){

    while( cont<*k && changes1+changes2-changes1*changes2==1) {
        if(cont%2==0){
            changes1=0;
    // SPOSTA 1
    for(int j = 0; j < N; j++){
			l = C[j].get_length();
			if(l==1 && l<M){
				if(!R[(C[j][0]+1)%M].search(j)){
					C[j][0]=(C[j][0]+1)%M;
					if(changes1==0)
						changes1=1;
				}
			}
			if(l>1){
				flag=C[j][0]==0 && C[j][l-1]==M-1;
				for(int i=0;i<l-flag;i++){
					if(mod_dist(C[j][i+1],C[j][i],M)>1 && !R[(C[j][i]+1)%M].search(j)){
						C[j][i]=(C[j][i]+1)%M;
						if(changes1==0)
							changes1=1;
						if(C[j][i]==0)
							C[j].last_first();
					}
				}
			}
		}
}

    if(cont%2==1){
        changes2=0;
    // sposta 2

    for(int i=0;i<M;i++){
			l = R[i].get_length();
			if(l==1 && l<N){
				if(!C[(R[i][0]+1)%N].search(i)){
					R[i][0]=(R[i][0]+1)%N;
					if(changes2==0)
						changes2=1;
				}
			}
			if(l>1){
				flag=R[i][0]==0 && R[i][l-1]==N-1;
				for(int j=0;j<l-flag;j++){
					if(mod_dist(R[i][j+1],R[i][j],N)>1 && !C[(R[i][j]+1)%N].search(i)){
						R[i][j]=(R[i][j]+1)%N;
						if(changes2==0)
							changes2=1;
						if(R[i][j]==0)
							R[i].last_first();
					}
				}
			}
		}
}
    cont++;
}

//output!
//cout << "Num. iterations: " << *k << endl;
//cout << R << endl;
//cout << C << endl;

//i problemi dell'output non sono spiegabili con problemi nei cicli
ofstream out;
out.open("sparse"+to_string(*k)+".csv");

int lr;
for(int i=0;i<M;i++){
	lr = R[i].get_length();
	if(lr==0){
		for(int j=0;j<N;j++)
			out<<C[j].search(i)<<",";
		}
	if(lr==1){

		for(int j=0;j<R[i][0];j++)
			out<<C[j].search(i)<<",";
        out<<2<<",";
		for(int j=R[i][0]+1;j<N;j++)
			out<<C[j].search(i)<<",";
	}
	else{
		for(int j=0;j<R[i][0];j++)
			out<<C[j].search(i)<<",";
		for(int r=0;r<lr;r++){
			out<<2;
			for(int j=R[i][r]+1;j<R[i][r+1];j++)
				out<<C[j].search(i);
		}
		for(int j=R[i][lr-1]+1;j<N;j++)
				out<<C[j].search(i);
		}
    out<<endl;
}

out.close();

}

}

