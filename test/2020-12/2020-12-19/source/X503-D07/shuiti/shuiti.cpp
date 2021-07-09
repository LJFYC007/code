/***************************************************************
	File name: shuiti.cpp
	Author: ljfcnyali
	Create time: 2020年12月19日 星期六 09时22分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 160;

int n, m, t, a[maxn][maxn], ans, num[maxn * maxn], belong[maxn * maxn], W[maxn * maxn], lst;
bitset<maxn> Vis[maxn * maxn][maxn];
struct node 
{ 
    int u, v, w;
    bool operator < (const node &a) const { return w < a.w; }
    node ( int a = 0, int b = 0, int c = 0 ) { u = a; v = b; w = c; }
} A[maxn * maxn];
bool use[maxn * maxn][maxn];

inline void Add(int pos, int u, int v)
{
    REP(i, 1, n) if ( !use[pos][i] && Vis[pos][i][u] )
    {
        Vis[pos][i] |= Vis[pos][v];
        if ( Vis[pos][i].count() == n ) { use[pos][i] = true; ++ num[pos]; }
    }
}

inline void Insert(int val, node x)
{
    for ( int i = lst; i >= 1; -- i ) if ( x.w < W[i] && num[belong[i]] != n ) 
    {
        Add(belong[i], x.u, x.v);
        if ( num[belong[i]] == n ) ans = min(ans, W[i] + val);
    }
    else if ( num[belong[i]] == n ) lst = i - 1;
    else if ( x.w >= W[i] ) break ; 
    int pos = 1;
    for ( int i = lst; i >= 1; -- i ) 
        if ( x.w < W[i] ) { W[i + 1] = W[i]; belong[i + 1] = belong[i]; }
        else { pos = i + 1; break ; }
    ++ t; ++ lst; W[pos] = x.w; belong[pos] = t; pos = belong[pos - 1]; num[t] = num[pos]; 
    if ( num[t] == n ) return ;
    REP(i, 1, n) { use[t][i] = use[pos][i]; Vis[t][i] = Vis[pos][i]; }
    Add(t, x.u, x.v); if ( num[t] == n ) ans = min(ans, x.w + val);
}

int main()
{
    freopen("shuiti.in", "r", stdin);
    freopen("shuiti.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, n) { int x; scanf("%d", &x); A[++ m] = node(i, j, x); }
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &a[i][j]);    
    ans = 2147483647; sort(A + 1, A + m + 1);     
    REP(i, 1, n) Vis[0][i][i] = true;
    REP(o, 1, m)
    {
        if ( A[o].w >= ans ) break ; 
        Insert(A[o].w, node(A[o].u, A[o].v, a[A[o].u][A[o].v]));
    }
    printf("%d\n", ans);
    return 0;
}
