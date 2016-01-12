#ifndef vect_h
#define vect_h

#include<iostream>

using namespace std;

template <class T> class vect{
	unsigned int n;
	T* p;
	public:
	vect(int n=0):n(n),p(nullptr){
		if(n>0)
			p= new T[n];
			for(int i=0;i<n;++i)
				p[i]=0;
	};
	vect(const vect<T> &x):n(x.n),p(nullptr){
		p = new T[n];
		for(int i=0;i<n;++i){
			p[i]=x.p[i];
		}
	};
	~vect(){
		delete []p;
	};
	int get_length(){
		return n;
	};
	vect& operator=(vect<T> x){
		swap(n,x.n);
		swap(p,x.p);
		return *this;
	};
	T& operator[](const int& j){
		if(j==n)
			return p[0];
		else
			return p[j];
	};
	template <typename S>
	inline friend ostream& operator<<(ostream& o,const vect<S>& x);

	void tail_add(T e){
		T* q;
		q = new T[n+1];
		for(int i=0;i<n;++i)
			q[i]=p[i];
		q[n]=e;
		n+=1;
		swap(p,q);
	};
	void last_first(){
		T* q;
		q = new T[n];
		for(int i=0;i<n-1;i++)
			q[i+1]=p[i];
		q[0]=p[n-1];
		swap(p,q);
	};
	bool search(int a){
		if(n==0)
			return false;
		for(int i=0;i<n;i++){
			if(p[i]==a){
				return true;
			};
		};
		return false;
	};
};

template <typename T>
ostream& operator<<(ostream& o,const vect<T>& x){
	o << "length: " << x.n << endl;
	for(int i=0;i<x.n;i++)
		o << x.p[i]<<" ";
	o<< endl;
	return o;
};

int mod_dist(const int& a,const int& b,const int& D){
	return (a-b)*(a-b>=0)+(a-b+D)*(a-b<0);
};

#endif
