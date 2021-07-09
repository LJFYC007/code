#include <bits/stdc++.h>
#define F(i, l, r) for(int i = (l), _end_ = (int)(r); i <= _end_; ++i)
#define f(i, r, l) for(int i = (r), _end_ = (int)(l); i >= _end_; --i)
#define Set(a, v) memset(a, v, sizeof(a))
#define file(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
using namespace std;

bool chkmin(int &a, int b) {return b < a ? a = b, 1 : 0;}
bool chkmax(int &a, int b) {return b > a ? a = b, 1 : 0;}

inline long long read() {
 long long x = 0, fh = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar() ) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar() ) x = (x<<1) + (x<<3) + (ch ^ '0');
    return x * fh;
}
long long a,b,c,m;
long long qpow(long long x,long long y){
    long long res=1;
	while(y){
	   if(y&1)res=res*x%m;
	   x=x*x%m;
	   y>>=1;
	}
	return res;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
   if(b==0){
      x=1;
	  y=0;
	  return a;
   }
   long long xx,yy;
  long long t=exgcd(b,a%b,xx,yy);
   x=yy,y=xx-a/b*yy;
   return t;
}
int main () {
#ifndef ONLINE_JUDGE
file("guess1-2");
#endif
    int t=read();
	while(t--){
	   m=read(),a=read(),b=read(),c=read();
	   long long t=log2(m);
	   if(pow(2,t)==m){
	     long long x=1,y=1,z=1;
		 if(a>1)x=m/2;
		 else if(b>1)y=m/2;
		 else if(c>1)x=y=z=m/2;
		 else x=y=1,z=2;
		 printf("%lld %lld %lld\n",x,y,z);
		 continue;
	   }
	   else{
		   long long l,k;
	     exgcd(c,1ll*a*b,l,k);
		 k=-k;
		 while(k<0||l<0)k+=c,l+=a*b;
		 long long x=qpow(2,1ll*b*k),y=qpow(2,1ll*a*k),z=qpow(2,l);
		 printf("%lld %lld %lld\n",x,y,z);
	   }
	}
    return 0;
}
