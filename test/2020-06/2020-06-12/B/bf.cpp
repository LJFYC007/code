/**************************************************************
    Problem: 3688
    User: admin
    Language: C++
    Result: Accepted
    Time:318 ms
    Memory:7084 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
#define MN 3000
#define MM 10000
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
bool f[MM+5];
int n,K,len[MN+5],p[MM*2+5];
string st[MN+5],ans,S;
bitset<10003> b[MN+5];
void ExKMP()
{
    int m=S.length()-1;p[1]=m;
    for(int i=2,l=1,r=1;i<=m;++i)
    {
        if(r>=i) p[i]=min(r-i+1,p[i-l+1]); else p[i]=0;
        while(i+p[i]<=m&&S[i+p[i]]==S[p[i]+1]) ++p[i];
        if(i+p[i]-1>r) l=i,r=i+p[i]-1;
    }
}
int Small(int x,int y,int l)
{
    if(x+l<=y) 
    {
        int L=p[l+x+2];
        if(L>=l) return 0;
        else  return S[L+1]>S[l+x+L+2]?1:-1;
    }
    int L1=p[l+x+2];
    if(L1<y-x) return S[L1+1]>S[l+x+L1+2]?1:-1;
    int L2=p[y-x+1];
    if(L2>=l-(y-x)) return 0;
    else return S[y-x+L2+1]>S[L2+1]?1:-1;
}
int main()
{  
    freopen("B.in", "r", stdin);
    freopen("B1.out", "w", stdout);
    n=read();K=read();b[n+1][K]=1;f[0]=1;
    for(int i=1;i<=n;++i) cin>>st[i],len[i]=st[i].length();
    for(int i=n;i>=1;--i) b[i]=b[i+1]|(b[i+1]>>len[i]);
    for(int i=1;i<=n;++i)
    {
        S='*'+st[i]+'@'+ans;ExKMP();int mn=-1,LL=ans.length();
        for(int j=0;j<=LL&&j+len[i]<=K;++j) if(f[j]&&b[i+1][j+len[i]])
        {
            if(mn==-1)
            {
                if(j==LL) mn=j;
                else
                {
                    int L=p[len[i]+j+2];
                    if(L<len[i]&&(j+L==LL||S[L+1]<S[len[i]+j+L+2])) mn=j;
                }
                continue;
            }
            if(Small(mn,j,len[i])>=0) mn=j;
        }
        if(mn==-1)
        {
            for(int j=LL-len[i];j>=0;--j)
                if(f[j]&&p[len[i]+j+2]==len[i]&&b[i+1][j+len[i]]) f[j+len[i]]=1;
            continue;
        }
        memset(f+mn+len[i]+1,0,sizeof(bool)*(K-mn-len[i]+3));
        for(int j=mn+len[i];~j;--j) 
        {
            if((j<=mn||p[len[i]+mn+2]>=j-mn)&&f[j]&&b[i+1][j]) f[j]=1;
            else if(j>=len[i]&&f[j-len[i]]&&b[i+1][j]&&(j-len[i]==mn||Small(j-len[i],mn,len[i])==0)) f[j]=1;
            else f[j]=0;
        }
        ans=ans.substr(0,mn)+st[i];
    }
    cout<<ans << endl;
    return 0;
}
