#include<bits/stdc++.h>
using namespace std;
#define MN 200005
#define LL long long
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
inline void chkmax(int &a,int b){if(a<b)a=b;}
inline void chkmin(int &a,int b){if(a>b)a=b;}
inline int read(){
	   int a=0,fh=1;char c=getchar();
	   while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	   while('0'<=c&&c<='9'){
		   a=a*10+c-48;
		   c=getchar();
	   }
	   return a*fh;
}
#define Mod 1000000000
int n,a[MN],F[MN],m;
int main(){
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;++i)a[i]=read();
	F[0]=F[1]=1;for(int i=2;i<=n;++i)F[i]=(F[i-1]+F[i-2])%Mod;
	for(int i=1;i<=m;++i){
		int op=read(),x=read(),y=read();
		if(op==1)a[x]=y;
		else if(op==2){
			LL ans=0;
			for(int j=0;j<=y-x;++j){
				ans+=(LL)F[j]*a[x+j]%Mod;
			}
			printf("%lld\n",ans%Mod);
		}
		else{
			int d=read();
			for(int j=x;j<=y;++j)
				a[j]=(a[j]+d)%Mod;
		}
	}
	return 0;
}
