 
#include<bits/stdc++.h>
using namespace std;
 
#define cout cerr
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
 
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
 
int n,m,K;
#define Maxn 100010
#define Maxm 105
int a[Maxn];
bool cov[Maxn];
 
const int inf=1000000000;
int L[Maxn][Maxm],R[Maxn][Maxm];
int lst[Maxm];
void init(int way[][Maxm],int *p,bool ty){
    if(ty)reverse(p,p+n);
    int tag=0;
    rep(i,0,m-1)lst[i]=inf;
    rep(i,0,n-1){
        tag++;
        lst[a[i]]=-tag;
    }
    rep(i,0,n-1){
        tag++;
        lst[a[i]]=-tag;
        int mn=inf;
        rep(j,0,m-1)way[i][j]=inf;
        per(j,a[i]+K,a[i]+1){
            mn=min(mn,lst[j%m]);
            way[i][(j-1-K+m)%m]=mn+tag;
        }
    }
    if(ty){
        reverse(p,p+n);
        rep(i,0,(n-1)/2) 
            rep(j,0,m-1)swap(way[i][j],way[n-1-i][j]);
    }
}
 
int dt[Maxm],to[Maxm];
 
int ra[Maxn];
vector<int> vec[Maxm];
int b[Maxn];
void calc(int I){
    int p=-1,z;
    per(i,I+2*K,I+K+1)
        if(to[i%m]!=-1){
            p=to[i%m];z=i-I-K;
            break;
        }
    rep(i,I+K+1,I+2*K)
        if(to[i%m]!=-1){
            z=i-I-K;
            break;
        } 
    if(p==-1){
        for(int i=0;i<vec[I].size();++i)cov[vec[I][i]]=true;
        return;
    }
    for(int i=0;i<vec[I].size();++i)ra[vec[I][i]]=0;
    int res=0;
    rep(i,p,n-1)
        if(dt[a[i]]>K)res=0;
        else{
            res=max(res,dt[a[i]]);
            if(a[i]==I)ra[i]=max(ra[i],res);
        }
    rep(i,0,p-1)
        if(dt[a[i]]>K)res=0;
        else{
            res=max(res,dt[a[i]]);
            if(a[i]==I)ra[i]=max(ra[i],res);
        }
    per(i,p,0)
        if(dt[a[i]]>K)res=0;
        else{
            res=max(res,dt[a[i]]);
            if(a[i]==I)ra[i]=max(ra[i],res);
        }
    per(i,n-1,p+1)
        if(dt[a[i]]>K)res=0;
        else{
            res=max(res,dt[a[i]]);
            if(a[i]==I)ra[i]=max(ra[i],res);
        }
    for(int i=0;i<vec[I].size();++i){
        int u=vec[I][i];
        if(ra[u]>=z)cov[u]=true;
    }
    memset(b,0,sizeof(int)*n);
    rep(i,0,n-1)
        if(dt[a[i]]<=K){
            int l=L[i][I],r=R[i][I];
            if(l+r+1>=n)continue;
            int o=(i+r+1)%n,e=(i-l-1+n)%n;
            if(o<=e){
                b[o]++;
                b[e+1]--;
            }else{
                b[o]++;
                b[0]++;b[e+1]--;
            }
        }
    rep(i,1,n-1)b[i]+=b[i-1];
    for(int i=0;i<vec[I].size();++i){
        int u=vec[I][i];
        if(b[u]>=1)cov[u]=true;
    }
}
 
int main(){
    rd(n);rd(m);K=m/2;
    rep(i,0,m-1)to[i]=-1;
    rep(i,0,n-1){
        rd(a[i]);
        a[i]=(m-a[i])%m;
    }
    rep(i,0,n-1)to[a[i]]=i,vec[a[i]].push_back(i);
    if(m==1||n==1){
        printf("%d\n",n);
        rep(i,1,n)printf("%d ",i);
        return 0;
    }   
    init(L,a,0);init(R,a,1);
    rep(i,0,m-1){
        rep(j,0,m-1)dt[(i+j)%m]=j;
        if(to[i]!=-1)calc(i);
    }
    int cnt=0;
    rep(i,0,n-1)cnt+=cov[i];
    printf("%d\n",cnt);
    rep(i,0,n-1)
        if(cov[i])printf("%d ",i+1);
    return 0;
}/*
9 3
1 1 1 1 1 1 1 1 1
 
10 11
6 6 3 6 8 7 6 4 3 6
 
6 101
100 1 60 30 60 1
*/

