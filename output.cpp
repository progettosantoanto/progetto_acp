#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "clvect.cpp"
#define nullptr NULL

using namespace std;

int main(){
	int M = 10;
	int N = 10;
	int K = 10;
	int m[M][N];
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			m[i][j]=j%3;
		};
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
	int out[M][N];
	int lr;
	for(int i=0;i<M;i++){
		lr = R[i].get_length();
		if(lr==0){
			for(int j=0;j<N;j++)
				out[i][j]=C[j].search(i);
		};
		if(lr==1){
			out[i][R[i][0]]=2;
			for(int j=0;j<R[i][0];j++)
				out[i][j]=C[j].search(i);
			for(int j=R[i][0]+1;j<N;j++)
				out[i][j]=C[j].search(i);
		}
		else{
			for(int j=0;j<R[i][0];j++)
				out[i][j]=C[j].search(i);
			for(int r=0;r<lr;r++){
				out[i][R[i][r]]=2;
				for(int j=R[i][r]+1;j<R[i][r+1];j++)
					out[i][j]=C[j].search(i);
			};
			for(int j=R[i][lr-1]+1;j<N;j++)
					out[i][j]=C[j].search(i);
			};
	};
};
