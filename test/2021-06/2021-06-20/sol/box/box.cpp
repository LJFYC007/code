 
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
 
const int Mod=1000000007;
namespace modular{
    int dec(int a,int b){return a-b<0?a-b+Mod:a-b;}
    int add(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
    int mul(int a,int b){return 1ll*a*b%Mod;}
}using namespace modular;
 
int n;
#define Maxn 200010
int to[Maxn<<1];
 
struct Dat{
    int a,b,u;
    Dat(){a=b=u=0;}
    Dat(int _a,int _b,int _u){a=_a;b=_b;u=_u;}
}dat[Maxn];int cnt;
 
int L;
bool vis[Maxn<<1];
 
int zer[Maxn],o[Maxn],oi[Maxn];
int inv[Maxn];
int le[Maxn<<1];
 
int main(){
    rd(n);int A,B;
    rep(i,1,n){
        rd(A);rd(B);
        if(A>B)swap(A,B);
        to[B]=A;
    }
    inv[0]=1;inv[1]=1;rep(i,2,n)inv[i]=mul(Mod-Mod/i,inv[Mod%i]);
    L=2*n;int sum=0;
    per(i,2*n,1)
        if(to[i]){
            per(j,L,i+1)sum-=vis[j];
            L=i;
            dat[++cnt]=Dat(to[i],i,sum);
            sum++;vis[to[i]]=true;
        }
    reverse(dat+1,dat+cnt+1);
    zer[0]=1;
    rep(i,1,cnt)zer[i]=mul(zer[i-1],dat[i].u);
    o[0]=1;
    rep(i,1,cnt)o[i]=mul(o[i-1],dat[i].u+1);
    oi[0]=1;
    rep(i,1,cnt)oi[i]=mul(oi[i-1],inv[dat[i].u+1]);
    dat[cnt+1].b=2*n+1;
    rep(i,0,cnt)
        rep(j,dat[i].b,dat[i+1].b-1)le[j]=i;
    int cur=1,res=o[n];
    per(i,cnt,1){
        res=add(res,mul(cur,o[i-1]));
        int t=le[dat[i].a];
        res=dec(res,mul(cur,mul(mul(o[i-1],oi[t]),zer[t])));
        cur=mul(cur,dat[i].u+2);
    }
    printf("%d\n",res);
    return 0;
}
