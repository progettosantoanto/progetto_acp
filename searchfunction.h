bool search(vect<T>& x,T a){
		int n(x.n);
		if(n==0)
            return false;
        if(n==1){
            if (x[0]==a)
                return true;
            else
                return false;
            }
        else{
            T b = x[n/2];
            if(b==a)
                return true;
            if(b>a)
                vect<T> xx(n/2);
                for(int i=0;i<n/2;i++)
                    xx.p[i]=x.p[i];
                return search(xx,a);
            else{
                vect<T> xx(n-n/2-1);
                for(int i=n/2+1;i<n;i++)
                    xx.p[i-n/2-1]=x.p[i];
                return search(xx,a);
            }
        }
};
