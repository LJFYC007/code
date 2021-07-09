/**************************************************************
    Problem: 3690
    User: admin
    Language: C++
    Result: Accepted
    Time:1220 ms
    Memory:286460 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
using namespace std;
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
    int F()
    {
        int F=1,n=0;
        char ch;
        while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
        ch=='-'?F=0:n=ch-'0';
        while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
        return F?n:-n;
    }
    long long G()
    {
        long long F=1,n=0;
        char ch;
        while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
        ch=='-'?F=0:n=ch-'0';
        while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
        return F?n:-n;
    }
}
int R(int l,int r)
{
    return (rand()<<15|rand())%(r-l+1)+l;
}
int dis[444][444];
int ban[444];
int v[22],z[22];
int d[65555][33][33];
int f[65555][17];
int g[17][17];
int ans[444][444];
int cap[444];
int main()
{
    freopen("A.in", "r", stdin);
    freopen("A1.out", "w", stdout);
    int n=io::F(),m=io::F(),k=io::F(); 
    memset(dis,63,sizeof(dis));
    memset(d,63,sizeof(d));
    memset(g,63,sizeof(g));
    for(register int i=1;i<=n;++i)dis[i][i]=0;
    for(register int i=1;i<=m;++i)
    {
        int a=io::F(),b=io::F(),c=io::F();
        cmin(dis[a][b],c);
        cmin(dis[b][a],c);
    }
    for(register int i=0;i<k;++i)
    {
        v[i]=io::F(),z[i]=io::F();
        ban[v[i]]=1,cap[v[i]]|=1<<i;
    }
    for(register int y=1;y<=n;++y)
        if(!ban[y])
            for(register int i=1;i<=n;++i)
                for(register int j=i+1;j<=n;++j)
                    if(cmin(dis[i][j],dis[i][y]+dis[y][j]))
                        dis[j][i]=dis[i][j];
    for(register int i=0;i<k;++i)
        for(register int j=0;j<k;++j)
        {
            d[0][i][j]=dis[z[i]][z[j]];
            d[0][i+k][j]=dis[v[i]][z[j]];
            d[0][i][j+k]=dis[z[i]][v[j]];
            d[0][i+k][j+k]=dis[v[i]][v[j]];
        }
    for(register int i=1;i<1<<k;++i)
    {
        int (*D)[33]=d[i];
        int (*LA)[33]=d[i^i&-i];
        for(register int x=0;x<k+k;++x)
            for(register int y=0;y<k+k;++y)
                D[x][y]=LA[x][y];
        int o=__builtin_ctz(i);
        if((cap[v[o]]&i)==cap[v[o]])
            for(register int x=0;x<k+k;++x)
                for(register int y=x+1;y<k+k;++y)
                    if(cmin(D[x][y],D[x][o+k]+D[o+k][y]))
                        D[y][x]=D[x][y];
    }
    for(register int i=0;i<k;++i)
    {
        memset(f,63,sizeof(f));
        f[1<<i][i]=0;
        for(register int s=1<<i;s<1<<k;s=s+1|1<<i)
            for(register int t=s;t;t^=t&-t)
            {
                int o=__builtin_ctz(t);
                int F=f[s][o];
                if(F!=0x3f3f3f3f)
                {
                    int *D=d[s][o];
                    for(register int r=(1<<k)-1^s;r;r^=r&-r)
                    {
                        int j=__builtin_ctz(r);
                        if((cap[z[j]]&s)==cap[z[j]])cmin(f[s|1<<j][j],F+D[j]);
                    }
                }
                for(register int j=0;j<k;++j)
                    if((cap[v[j]]&s)==cap[v[j]])
                        cmin(g[i][j],F+d[s][o][j+k]);
            }
    }
    for(register int s=1;s<=n;++s)
        for(register int t=1;t<=n;++t)
        {
            if(ban[s]){ans[s][t]=-1;continue;}
            if(!ban[t])
            {
                ans[s][t]=dis[s][t];
                for(register int i=0;i<k;++i)
                    for(register int j=0;j<k;++j)
                        if(!ban[z[i]])cmin(ans[s][t],(long long)dis[s][z[i]]+g[i][j]+dis[v[j]][t]);
            }
            else
            {
                ans[s][t]=0x3f3f3f3f;
                int j;
                for(j=0;j<k;++j)if(v[j]==t)break;
                for(register int i=0;i<k;++i)
                    if(!ban[z[i]])cmin(ans[s][t],dis[s][z[i]]+g[i][j]);
            }
            if(ans[s][t]==0x3f3f3f3f)ans[s][t]=-1;
        }
    int q=io::F();
    for(register int i=1;i<=q;++i)
    {
        int s=io::F(),t=io::F();
        printf("%d\n",ans[s][t]);
    }
    return 0;
}
