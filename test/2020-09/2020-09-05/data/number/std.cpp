#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
using namespace std;

inline char nc() {
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template <class T>
inline void rd(T &x) {
	x=0; char c=nc(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=nc(); }
	while(isdigit(c)) x=x*10-'0'+c,c=nc(); x*=f;
}

const int mod=998244353;
int Pow(int x,int y) {
    int res=1;
    while(y) {
        if(y&1) res=res*(ll)x%mod;
        x=x*(ll)x%mod,y>>=1;
    }
    return res;
}
namespace Poly {
    const int MAXLOG=18;
    const int N=(1<<MAXLOG);
    int wn[2][N],rev[N];
    void init() {
        for(int i=1;i<N;i<<=1) {
            int w0=Pow(3,(mod-1)/(i<<1)),w1=Pow(3,mod-1-(mod-1)/(i<<1));
            wn[0][i]=wn[1][i]=1;
            for(int j=1;j<i;++j)
                wn[0][i+j]=wn[0][i+j-1]*(ll)w0%mod,
                wn[1][i+j]=wn[1][i+j-1]*(ll)w1%mod;
        }
    }
    inline void getr(int len) { for(int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)?(len>>1):0); }
/*    inline void FFT(int *A,int len,int f) {
        for(int i=0;i<len;++i) if(rev[i]<i) swap(A[i],A[rev[i]]);
        for(int l=1;l<len;l<<=1)
            for(int i=0;i<len;i+=l<<1) {
            	for(int *p1=A+i,*p2=A+i+l,j=0;j<l;++p1,++p2,++j) {
            		int t0=(*p1),t1=(*p2)*(ll)wn[f][l+j]%mod;
            		(*p1)=(t0+t1)%mod;
            		(*p2)=(t0-t1)%mod;
            	}
                for(int j=0;j<l;++j) {
                    int t0=A[i+j],t1=A[i+l+j]*(ll)wn[f][l+j]%mod;
                    A[i+j]=(t0+t1)%mod;
                    A[i+l+j]=(t0-t1)%mod;
                }
            }
        if(f==1) { int Inv=Pow(len,mod-2); for(int i=0;i<len;++i) A[i]=A[i]*(ll)Inv%mod; }
    }*/
    inline void FFT(int *A,int len,int f) {
    	static ll a[N];
    	for(int i=0;i<len;++i) a[i]=A[rev[i]];
    	for(int l=1;l<len;l<<=1)
    		for(int i=0;i<len;i+=l<<1) {
    			ll *p1=a+i,*p2=a+l+i;
    			for(int j=0;j<l;++j,++p1,++p2) {
    				ll tmp=(*p2)%mod*wn[f][l+j]%mod;
    				(*p2)=(*p1)-tmp;
    				(*p1)+=tmp;
    			}
    		}
		for(int i=0;i<len;++i) A[i]=a[i]%mod;
		if(f==1) { int Inv=Pow(len,mod-2); for(int i=0;i<len;++i) A[i]=A[i]*(ll)Inv%mod; }
	}
    int a[N],b[N],c[N],d[N];
    inline void Mul(int *A,int *B,int *C,int n,int m,int l3) {
    	if(n+m<100) {
    		for(int i=0;i<l3;++i) C[i]=0;
    		for(int i=0;i<n;++i) for(int j=0;j<m&&i+j<l3;++j) C[i+j]=(C[i+j]+A[i]*(ll)B[j])%mod;
    		return;
    	}
        int len=1; while(len<n+m-1||len<l3) len<<=1; getr(len);
        for(int i=0;i<len;++i) a[i]=b[i]=0;
        for(int i=0;i<n;++i) a[i]=A[i];
        for(int i=0;i<m;++i) b[i]=B[i];
        FFT(a,len,0),FFT(b,len,0); for(int i=0;i<len;++i) a[i]=a[i]*(ll)b[i]%mod; FFT(a,len,1);
        for(int i=0;i<l3;++i) C[i]=a[i];
    }
    inline void Mul(int *A,int *B,int *C,int n,int m) {
    	if(n+m<100) {
    		for(int i=0;i<n+m-1;++i) C[i]=0;
    		for(int i=0;i<n;++i) for(int j=0;j<m;++j) C[i+j]=(C[i+j]+A[i]*(ll)B[j])%mod;
    		return;
    	}
        int len=1; while(len<n+m-1) len<<=1; getr(len);
        for(int i=0;i<len;++i) a[i]=b[i]=0;
        for(int i=0;i<n;++i) a[i]=A[i];
        for(int i=0;i<m;++i) b[i]=B[i];
        FFT(a,len,0),FFT(b,len,0); for(int i=0;i<len;++i) a[i]=a[i]*(ll)b[i]%mod; FFT(a,len,1);
        for(int i=0;i<n+m-1;++i) C[i]=a[i];
    }
    void Inv(int *A,int *B,int n) {
        if(n==1) return (void)(B[0]=Pow(A[0],mod-2));
        /*int len=n+1>>1; Inv(A,B,len);
        for(int i=len;i<n;++i) B[i]=0;
        Mul(B,B,C,len,len,n);
        Mul(C,A,C,n,n,n);
        for(int i=0;i<n;++i) B[i]=(2ll*B[i]-C[i])%mod;*/
        int l=n+1>>1; Inv(A,B,l);
        for(int i=l;i<n;++i) B[i]=0;
        int len=1; while(len<l+l+n-2) len<<=1; getr(len);
        for(int i=0;i<len;++i) a[i]=b[i]=0;
        for(int i=0;i<l;++i) b[i]=B[i];
        for(int i=0;i<n;++i) a[i]=A[i];
        FFT(a,len,0),FFT(b,len,0); for(int i=0;i<len;++i) a[i]=a[i]*(ll)b[i]%mod*b[i]%mod; FFT(a,len,1);
        for(int i=0;i<n;++i) B[i]=(2ll*B[i]-a[i])%mod;
    }
    inline void Div(int *F,int *G,int n,int m,int *R) {
    	static int a[N],b[N];
    	if(n<m) {
    		for(int i=0;i<n;++i) R[i]=F[i];
    		for(int i=n;i<m-1;++i) R[i]=0;
    		return;
    	}
        for(int i=0;i<m;++i) a[m-1-i]=G[i];
        Inv(a,b,n-m+1);
        /*
        static int a[N],b[N],c[N],d[N];
        int len=1; while(len<n+n-m) len<<=1; getr(len);
        for(int i=0;i<len;++i) a[i]=b[i]=c[i]=d[i]=0;
        for(int i=0;i<n;++i) a[i]=F[n-i-1];
        for(int i=0;i<n-m+1;++i) b[i]=h[i];
        FFT(a,len,0),FFT(b,len,0); for(int i=0;i<len;++i) a[i]=a[i]*(ll)b[i]%mod; FFT(a,len,1);
        
        for(int i=0;i<=n-m;++i) c[i]=a[n-m-i];
        for(int i=0;i<m;++i) d[i]=G[i];
        FFT(c,len,0),FFT(d,len,0); for(int i=0;i<len;++i) c[i]=c[i]*(ll)d[i]%mod; FFT(c,len,1);
        for(int i=0;i<m-1;++i) R[i]=(F[i]-c[i])%mod;
        */
        for(int i=0;i<n;++i) c[n-1-i]=F[i];
        Mul(c,b,d,n,n-m+1);
        for(int i=0;i<n-m-i;++i) swap(d[i],d[n-m-i]);
        Mul(G,d,a,m,n-m+1);
        for(int i=0;i<m-1;++i) R[i]=(F[i]-a[i])%mod;
    }
}
const int N=(1<<17)+10;
int calcy(int x,int *f,int n) {
	int ans=0;
	for(int t=1,i=0;i<n;++i)
		ans=(ans+f[i]*(ll)t)%mod,t=t*(ll)x%mod;
	return ans;
}
int *P[N<<2];
int xi[N],yi[N];
void predo(int l,int r,int c) {
	P[c]=new int[r-l+2];
	if(l==r) return (void)(P[c][0]=mod-xi[l],P[c][1]=1);
	int mid=l+r>>1;
	predo(l,mid,c<<1),predo(mid+1,r,c<<1|1);
	Poly::Mul(P[c<<1],P[c<<1|1],P[c],mid-l+2,r-mid+1);
}
namespace Divide_and_Conquer2 {
	int *f[17];
	void sol(int l,int r,int c,int d) {
//		if(l==r) return (void)(yi[l]=f[d][0]);
		if(r-l<=100) {
			for(int i=l;i<=r;++i) yi[i]=calcy(xi[i],f[d],r-l+1);
			return;
		}
		int mid=l+r>>1;
		Poly::Div(f[d],P[c<<1],r-l+1,mid-l+2,f[d-1]);
		sol(l,mid,c<<1,d-1);
		Poly::Div(f[d],P[c<<1|1],r-l+1,r-mid+1,f[d-1]);
		sol(mid+1,r,c<<1|1,d-1);
	}
	void gety(int *F,int m,int n) {
		int l=0;
		for(;(1<<l-1)<n;l++)
			f[l]=new int[1<<l];
		l--;
		Poly::Div(F,P[1],m,n+1,f[l]);
		sol(0,n-1,1,l);
	}
}
using Divide_and_Conquer2::gety;
int m,n,f[N];
int A[N],B[N],C[N<<1];
int fac[N],inv[N],facn[N];
int main() {
	Poly::init();
	rd(n),rd(m);
	for(int i=0;i<=m;++i) rd(f[i]),xi[i]=i;
	predo(0,m,1),gety(f,m+1,m+1);
	
	fac[0]=1; for(int i=1;i<=m;++i) fac[i]=1ll*fac[i-1]*i%mod;
	inv[m]=Pow(fac[m],mod-2); for(int i=m;i>=1;--i) inv[i-1]=1ll*inv[i]*i%mod;
	facn[0]=1; for(int i=1;i<=m;++i) facn[i]=facn[i-1]*(ll)(n-i+1)%mod;
	
//	int ans=0;
//	for(int j=0;j<=m;++j)
//		for(int t=0;t<=j;++t)
//			 ans=(ans+1ll*facn[j]*Pow(2,n-j)%mod*(j-t&1 ? -1 : 1)*inv[t]%mod*inv[j-t]%mod*yi[t])%mod;
	
	for(int i=0;i<=m;++i) A[i]=1ll*yi[i]*inv[i]%mod;
	for(int i=0;i<=m;++i) B[i]=(i&1 ? -1 : 1)*inv[i];
	Poly::Mul(A,B,C,m+1,m+1);
	int ans=0;
	for(int i=0;i<=m;++i) ans=(ans+1ll*C[i]*facn[i]%mod*Pow(2,n-i))%mod;

	printf("%d",(ans+mod)%mod);
	return 0;
}
