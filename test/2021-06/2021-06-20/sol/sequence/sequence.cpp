#include<bits/stdc++.h>
using namespace std;
 
#define cout cerr
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
 
typedef long long ll;
typedef pair<int,int> pii;
#define FR first
#define SE second
 
inline void rd(int &x){
    x=0;char ch=getchar();int f=1;
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=f;
}
 
int n,Mod;
#define Maxn 1000010
 
namespace modular{
    int dec(int a,int b){return a-b<0?a-b+Mod:a-b;}
    int add(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
    int mul(int a,int b){return 1ll*a*b%Mod;}
}using namespace modular;
 
int f[Maxn],g[Maxn][20],val[Maxn];
int sum[Maxn][20],h[Maxn];
int L[22];
 
void init(){
    rep(i,0,n){
        val[i]=h[i]=f[i]=0;
        rep(j,0,19)g[i][j]=sum[i][j]=0;
    }
}
 
 
int main(){
    rd(n);rd(Mod);
    init();
    if(Mod==1){puts("0");return 0;}
    val[0]=1;
    per(j,19,0)L[j]=L[j+1]|(1<<j);
    rep(i,0,n){
        if(i){
            val[i]=add(val[i-1],val[i-1]);val[i]=dec(val[i],f[i-1]);
        }   
        rep(j,0,19)
            if(i&(1<<j)){
                int l=(i&L[j+1]);
                if(l)g[i][j]=dec(0,sum[l-1][j]);
                f[i]=add(f[i],g[i][j]);
				cout << i << " " << j << " " << g[i][j] << endl;
            }
        rep(j,0,19){
            if(i)sum[i][j]=sum[i-1][j];
            if(i&(1<<j)){
                sum[i][j]=add(sum[i][j],g[i][j]);
                int l=(i&L[j+1]);int r=l+(1<<j)-1;
                if(l)sum[i][j]=add(sum[i][j],dec(h[r],h[l-1]));
                else sum[i][j]=add(sum[i][j],h[r]);
            }
        }   
        val[i]=add(val[i],f[i]);
        h[i]=val[i];if(i)h[i]=add(h[i],h[i-1]);
    }
    int cur=1,Ans=0;
    per(i,n,0){
		cout << f[i] << endl;
        Ans=add(Ans,mul(cur,f[i]));
        cur=add(cur,cur);
    }
    Ans=add(Ans,cur);Ans=dec(Ans,1);
    printf("%d\n",Ans);
    return 0;
}/*
5 1000000007
20 1000000007
100 1000000007
2000 1000000007
100000 1000000007
1000000 1000000007
*/

