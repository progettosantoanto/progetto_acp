#include<stdlib.h>
#include<iostream>
#include<ostream>
#include<memory>
#include<algorithm>
#include<math.h>
#include "clvect.cpp"
#define nullptr NULL

using namespace std;

int main(){
	int M = 4;
	int N = 5;
	int K = 2;
	int m[M][N];
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			m[i][j]=rand()%3;
			cout << m[i][j] << " ";
		};
		cout << endl;
	};
	vect<vect<int> > R(M);
	vect<vect<int> > C(N);
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			if(m[i][j]==2)
				R[i].tail_add(j);
			if(m[i][j]==1)
				C[j].tail_add(i);
		};
	};
	cout << R << endl;
	cout << C << endl;
	cout << "Begin iterations" << endl;
	int changes1(1),changes2(1);
	int flag(0);
	int l(0);
	int k=0;
	while(k<K && changes1+changes2-changes1*changes2==1){
		if(k%2==0){
		changes1=0;
		for(int j=0;j<N;j++){
			l = C[j].get_length();
			if(l==1 && l<M){
				if(!R[(C[j][0]+1)%M].search(j)){
					C[j][0]=(C[j][0]+1)%M;
					if(changes1==0)
						changes1=1;
				};
			};
			if(l>1){
				flag=C[j][0]==0 && C[j][l-1]==M-1;
				for(int i=0;i<l-flag;i++){
					if(mod_dist(C[j][i+1],C[j][i],M)>1 && !R[(C[j][i]+1)%M].search(j)){
						C[j][i]=(C[j][i]+1)%M;
						if(changes1==0)
							changes1=1;
						if(C[j][i]==0)
							C[j].last_first();
					};
				};
			};
		};
		};
		if(k%2==1){
			changes2=0;
		for(int i=0;i<M;i++){
			l = R[i].get_length();
			if(l==1 && l<N){
				if(!C[(R[i][0]+1)%N].search(i)){
					R[i][0]=(R[i][0]+1)%N;
					if(changes2==0)
						changes2=1;
				};
			};
			if(l>1){
				flag=R[i][0]==0 && R[i][l-1]==N-1;
				for(int j=0;j<l-flag;j++){
					if(mod_dist(R[i][j+1],R[i][j],N)>1 && !C[(R[i][j]+1)%N].search(i)){
						R[i][j]=(R[i][j]+1)%N;
						if(changes2==0)
							changes2=1;
						if(R[i][j]==0)
							R[i].last_first();
					};
				};
			};
		};
		};
		k++;
	};
	cout << "Num. iterations: " << k << endl;
	cout << R << endl;
	cout << C << endl;
}

