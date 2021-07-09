/**************************************************************
    Problem: 3673
    User: admin
    Language: C++
    Result: Accepted
    Time:24 ms
    Memory:7924 kb
****************************************************************/
 
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long 
int ans=2147483647,z,y,x,M;//ans will not be greater than n*1260,otherwise ans is -1
int nxt[200050],la,lb,f[35],lis[200050],lcnt,np[400050],bel[35],a,b;
int id[35],clen[35],nb[35],tmp,cnt,l1[200050],l2[400050],lst[35],ep[35];
char s[400050],t[200050],s1[35];
bool vis[400050],pvis[400050];
int gcd(int a,int b){return !(a%b)?b:gcd(b,a%b);}
void dfs(int u,int lb,int nu){
    bel[u]=lb;
    id[u]=nu;
    tmp++;
    if (!bel[f[u]])dfs(f[u],lb,nu+1);
}
void kmp(){
    nxt[0]=-1;int j=-1;
    for (int i=1;i<lb;i++){
        while (j!=-1&&l1[j+1]!=l1[i])j=nxt[j];
        if (l1[j+1]==l1[i])j++;
        nxt[i]=j;
    }
}
void getp(){
    int j=-1;
    for (int i=0;i<la;i++){
        while (j!=-1&&l2[i]!=l1[j+1])j=nxt[j];
        if (l1[j+1]==l2[i])j++;
        if (j==lb-1)vis[i]=1,j=nxt[j];
    }
} 
void inv(ll a,ll b) {
    if (a%b==0){z=0;y=1;return;}
    inv(b,a%b);
    ll r=z;
    z=y,y=r-a/b*y;
}
bool solve(ll A,ll k,int m){
    int d;
    d=gcd(A,m),m/=d,A/=d;
    if ((k%d))return 0;
    k/=d;
    inv(A,m);
    k*=z;A=k-x;//k*z may greater than 2147483647
    d=gcd(M,m);
    if ((A%d))return 0;
    inv(M/d,m/d);
    int kp=A/d*1ll*z%(m/d);
    x+=kp*M;
    M*=m/d;
    return 1;
}
int main(){
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    scanf("%d%d%d",&lb,&a,&b);
    a%=lb;
    la=lb*2;
    scanf("%s",s1);
    for (int i=0;i<26;i++)f[i]=s1[i]-'a';
    for (int i=0;i<26;i++)if (!bel[i]){dfs(i,++cnt,1);clen[cnt]=tmp;nb[cnt]=b%tmp;tmp=0;}
    scanf("%s%s",s,t);
    for (int i=0;i<lb;i++)s[i+lb]=s[i];
    for (int i=0;i<lb;i++)l1[i]=bel[t[i]-'a'];
    for (int i=0;i<la;i++)l2[i]=bel[s[i]-'a'];
    kmp();getp();//match with ring's num
    memcpy(pvis,vis,sizeof pvis);
    memset(vis,0,sizeof vis);
    for (int i=0;i<lb;i++){
        if (lst[l2[i]])l2[i]=(id[s[i]-'a']-lst[l2[i]]+clen[l2[i]])%clen[l2[i]];
        else np[i]=1;
        lst[bel[s[i]-'a']]=id[s[i]-'a'];
    }
    for (int i=0;i<lb;i++)if (np[i])l2[i]=(id[s[i]-'a']-lst[bel[s[i]-'a']]+clen[bel[s[i]-'a']])%clen[bel[s[i]-'a']];
    for (int i=0;i<lb;i++)l2[i+lb]=l2[i];
    memset(lst,0,sizeof lst);
    memset(nxt,0,sizeof nxt);
    memset(np,0,sizeof np);
    memset(ep,-1,sizeof ep);
    for (int i=0;i<lb;i++){
        if (lst[l1[i]])l1[i]=(id[t[i]-'a']-lst[l1[i]]+clen[l1[i]])%clen[l1[i]];
        else np[i]=1;
        lst[bel[t[i]-'a']]=id[t[i]-'a'];
        ep[bel[t[i]-'a']]=i;
    }
    for (int i=0;i<lb;i++)if (np[i])
    l1[i]=(id[t[i]-'a']-lst[bel[t[i]-'a']]+clen[bel[t[i]-'a']])%clen[bel[t[i]-'a']];
    kmp();getp();//match with ring's differences 
    int k;
    for (int i=lb-1;i<la-1;i++)if (vis[i]&&pvis[i])lis[++lcnt]=(i-lb+1)%lb;
    for (int i=1;i<=lcnt;i++){
        x=0,M=1; 
        bool flag=1;//solve congruence equations
        for (int j=1;j<=cnt&&flag;j++)if(ep[j]!=-1){
            int pos=(lis[i]+ep[j])%lb;
            k=(id[t[ep[j]]-'a']-id[s[pos]-'a']+clen[j])%clen[j];
            if (!nb[j]){if (!k)continue;flag=0;continue;}
            flag&=solve(nb[j],k,clen[j]);
        }
        if (!a){if (lis[i])continue;}
        else flag&=solve(a,lis[i],lb);
        if (!flag)continue;
        x<=0?x+=M:0;
        ans=std::min(ans,x);
    }
    if (ans>1e9)printf("-1\n");
    else printf("%d\n",ans);
}
