/***************************************************************
    File name: A.cpp
    Author: ljfcnyali-AKIOI-Winner
    Create time: 2020年06月13日 星期六 09时09分01秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 410;
const unsigned int INF = 0x3f3f3f3f;
 
int q, n, m, k, p1[maxn], p2[maxn], key1[30], key2[30], num1, num2;
unsigned int f[410][410], sum[410][410], ans[410][410], dis[1 << 16][32];
bool Vis[maxn], vis[32];
bitset <32> pig;
inline void chkmin(unsigned &x, unsigned y) { if (x > y) x = y; } 

#define getchar getchar_unlocked
inline int read()
{
    int x = 0;char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    return x;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) REP(j, 1, n) f[i][j] = INF;
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, m) { int u(read()), v(read()); unsigned int w(read()); f[u][v] = f[v][u] = min(f[u][v], w); }
 
    REP(i, 0, k - 1) 
    { 
        int x(read()), y(read());
        p1[x] |= (1 << i); p2[y] |= (1 << i); 
        key1[num1 ++] = x; key2[num2 ++] = y;
        Vis[x] = true;
    }
    REP(o, 1, n) 
    {
        if ( Vis[o] ) continue ;
        REP(i, 1, n) if (f[i][o] < INF) REP(j, 1, n) chkmin(f[i][j], f[i][o] + f[o][j]);
    }
 
    REP(i, 0, 31) REP(j, 0, 31) sum[i][j] = INF;

    REP(S, 0, num2 - 1) 
    {
        REP(i, 0, (1 << k) - 1) REP(j, 0, 31) dis[i][j] = INF;
        dis[p2[key2[S]]][S] = 0; 
        REP(j, 0, (1 << k) - 1)
        {
            static int t1[20], t2[20];
            int n1 = 0, n2 = 0;
            REP(i, 0, num2 - 1)
                if ( !((j & p1[key2[i]]) ^ p1[key2[i]]) ) t1[++ n1] = i;
            REP(i, 0, num1 - 1)
                if ( !((j & p1[key1[i]]) ^ p1[key1[i]]) ) t2[++ n2] = i;
            pig.set();
            while ( 1 ) 
            {
                int Min = INF, pos = -1;
                for (int x = pig._Find_first(); x < num1 + num2; x = pig._Find_next(x))
                    if (Min > dis[j][x]) Min = dis[j][pos = x];
                if ( pos == -1 ) break ;  
                pig.reset(pos);
                int t = pos < num2 ? key2[pos] : key1[pos - num2];
                
                REP(i, 1, n1) if ( dis[j][t1[i]] > Min + f[t][key2[t1[i]]] )
                    dis[j][t1[i]] = Min + f[t][key2[t1[i]]];
                REP(i, 1, n2) if ( dis[j][t2[i] + num2] > Min + f[t][key1[t2[i]]] )
                    dis[j][t2[i] + num2] = Min + f[t][key1[t2[i]]];
            }
            REP(i, 0, num2 - 1) 
            {
                chkmin(sum[S][i], dis[j][i]);
                chkmin(dis[j | p2[key2[i]]][i], dis[j][i]);
            }
            REP(i, 0, num1 - 1)
            {
                chkmin(sum[S][i + num2], dis[j][i + num2]);
                chkmin(dis[j | p2[key1[i]]][i + num2], dis[j][i + num2]);
            }
        }
    }
 
    REP(u, 1, n) REP(v, 1, n)
    {
        ans[u][v] = INF;
        if ( p1[u] ) continue ;
        if ( !p1[u] && !p1[v] ) chkmin(ans[u][v], f[u][v]);
        REP(i, 0, num2 - 1)
        {
            if ( p1[key2[i]] ) continue ;
            if ( !p1[v] ) REP(j, 0, num2 - 1) chkmin(ans[u][v], f[u][key2[i]] + sum[i][j] + f[key2[j]][v]);
            REP(j, 0, num1 - 1) if ( !p1[v] || v == key1[j] ) 
                chkmin(ans[u][v], f[u][key2[i]] + sum[i][num2 + j] + f[key1[j]][v]);
        }
    }
    q = read();
    REP(i, 1, q)
    {
        int u(read()), v(read());
        printf("%d\n", ans[u][v] >= INF ? -1 : ans[u][v]);
    }
    return 0;
}
