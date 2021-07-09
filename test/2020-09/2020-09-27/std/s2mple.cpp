#include<bits/stdc++.h>
#define Fail puts("NO"),exit(0);
#define eps 1e-10
#define maxn 500010
#define maxm 500010
#define inf 1000000007
#define mod 998244353
#define pi acos(-1)
#define mp(x,y) make_pair(x,y)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef bitset<maxn> bit;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m=128,Q;
char ch[maxn];
int lg[maxn],pos[maxn];
ll ans;
struct ST{
    int st[maxn][20];
    void init(int *a)
    {
        for(int i=1;i<=n;i++)  st[i][0]=a[i];
        for(int j=1;j<=17;j++)
          for(int i=1;i+(1<<j)-1<=n;i++)  st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
    int query(int l,int r)
    {
        l++;
        int d=lg[r-l+1];
        return min(st[l][d],st[r-(1<<d)+1][d]);
    }
}st;
struct SA{
    int x[maxn],y[maxn],sa[maxn],c[maxn],rnk[maxn];
    int height[maxn];
    void get_SA()
    {
        for(int i=0;i<=m;i++)  c[i]=0;
        for(int i=1;i<=n;i++)  c[x[i]=ch[i]]++;
        for(int i=1;i<=m;i++)  c[i]+=c[i-1];
        for(int i=n;i>=1;i--)  sa[c[x[i]]--]=i;
        for(int k=1;k<=n;k<<=1)
        {
            int p=0;
            for(int i=n-k+1;i<=n;i++)  y[++p]=i;
            for(int i=1;i<=n;i++)
              if(sa[i]>k)  y[++p]=sa[i]-k;
            
            for(int i=0;i<=m;i++)  c[i]=0;
            for(int i=1;i<=n;i++)  c[x[y[i]]]++;
            for(int i=1;i<=m;i++)  c[i]+=c[i-1];
            for(int i=n;i>=1;i--)  sa[c[x[y[i]]]--]=y[i];

            p=1;
            swap(x,y);
            x[sa[1]]=1;
            for(int i=2;i<=n;i++)
            {
                if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]&&sa[i]+k<=n&&sa[i-1]+k<=n)  x[sa[i]]=p;
                else   x[sa[i]]=++p;
            }
            m=p;
        }
    }
    void get_Height()
    {
        for(int i=1;i<=n;i++)  rnk[sa[i]]=i;
        int k=0;
        for(int i=1;i<=n;i++)
        {
            if(rnk[i]==1)  continue;
            int j=sa[rnk[i]-1];
            if(k)  k--;
            while(ch[i+k]==ch[j+k]&&i+k<=n&&j+k<=n)  k++;
            height[rnk[i]]=k;
        }
        st.init(height);
    }
}sa;
struct SAM{
    int fa[maxn*2],len[maxn*2],ch[maxn*2][30],tot,las,p,np,up[maxn*2][22];
    ll f[maxn*2],sum[maxn*2],g[maxn*2];
    set<int>s[maxn*2];
    void insert(int c,int id)
    {   
        p=las,np=++tot;
        las=tot;len[np]=len[p]+1;
        while(!ch[p][c]&&p)
        {
            ch[p][c]=np;
            p=fa[p];
        }
        if(!p)  fa[np]=1;
        else{
            int q=ch[p][c];
            if(len[q]==len[p]+1)  fa[np]=q;
            else{
                int nq=++tot;len[nq]=len[p]+1;
                memcpy(ch[nq],ch[q],sizeof(ch[q]));
                fa[nq]=fa[q];
                fa[q]=fa[np]=nq;
                while(ch[p][c]==q)
                {
                    ch[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        if(id<n)  f[np]=n-id,s[np].insert(sa.rnk[id+1]);
        pos[id]=np;
    }
    int deg[maxn*2];
    queue<int>q;
    int sumx=0;
    void merge(int x,int y)
    {
        sumx+=min(s[x].size(),s[y].size());
        if(s[x].size()<s[y].size())  swap(f[x],f[y]),swap(s[x],s[y]);
        while(s[y].size())
        {
            int u=(*s[y].begin());s[y].erase(s[y].begin());
            int l=-1,r=-1;
            set<int>::iterator it=s[x].lower_bound(u);
            if(it!=s[x].end())  r=(*it);
            s[x].insert(u);
            it=s[x].lower_bound(u);
            if(it!=s[x].begin())  --it,l=(*it);

            f[x]+=n-sa.sa[u]+1;

            if(l!=-1)  f[x]-=st.query(l,u);
            if(r!=-1)  f[x]-=st.query(u,r);
            if(l!=-1&&r!=-1)  f[x]+=st.query(l,r);
        }
    }
    void solve()
    {
        for(int i=1;i<=tot;i++)  up[i][0]=fa[i];
        for(int j=1;j<=20;j++)
          for(int i=1;i<=tot;i++)  up[i][j]=up[up[i][j-1]][j-1];
        for(int i=2;i<=tot;i++)  deg[fa[i]]++;
        for(int i=1;i<=tot;i++)
          if(!deg[i])  q.push(i);
        while(q.size())
        {
            int now=q.front();q.pop();
            g[now]=f[now]+1;
            if(now!=1)
            {
                sum[fa[now]]+=sum[now]+(f[now]+1)*(len[now]-len[fa[now]]);
                merge(fa[now],now);
            }
            deg[fa[now]]--;
            if(!deg[fa[now]])  q.push(fa[now]);
        }
    }
    int find(int x,int y)
    {
        for(int i=20;i>=0;i--)
          if(len[up[x][i]]>=y)  x=up[x][i];
        return x;
    }
    void print()
    {
        for(int i=1;i<=tot;i++)
        {
            for(int j=0;j<26;j++)
            {
                if(ch[i][j])  cout<<i<<" "<<ch[i][j]<<" "<<(char)(j+'a')<<endl;
            }
        }
    }
}sam;
int main()
{
    freopen("s2mple.in", "r", stdin);
    freopen("s2mple.out", "w", stdout);
    n=read();Q=read();
    scanf("%s",ch+1);
    sa.get_SA();
    sa.get_Height();
    sam.las=sam.tot=1;
    for(int i=1;i<=n;i++)  sam.insert(ch[i]-'a',i);
    lg[1]=0;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    sam.solve();
    //sam.print();
    while(Q--)
    {
        int l=read(),r=read();
        int x=sam.find(pos[r],r-l+1);
        printf("%lld\n",sam.sum[x]+sam.g[x]*(sam.len[x]-r+l));
    }
    cerr<<sam.sumx<<endl;
    return 0;
}
