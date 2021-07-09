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

int n, m, t, a[maxn][maxn], ans, num;
bitset<maxn> Vis[maxn];
struct node 
{ 
    int u, v, w;
    bool operator < (const node &a) const { return w < a.w; }
    node ( int a = 0, int b = 0, int c = 0 ) { u = a; v = b; w = c; }
} A[maxn * maxn], B[maxn * maxn];
bool use[maxn];

inline void Sort(int l, int r)
{
    REP(i, l, r) REP(j, 1, i - 1) if ( B[i] < B[j] ) swap(B[j], B[i]);
}

int main()
{
    freopen("shuiti.in", "r", stdin);
    freopen("shuiti1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, n) { int x; scanf("%d", &x); A[++ m] = node(i, j, x); }
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &a[i][j]);    
    ans = 2147483647; sort(A + 1, A + m + 1);     
    REP(o, 1, m)
    {
        if ( A[o].w >= ans ) break ; 
        int now = t; B[++ t] = node(A[o].u, A[o].v, a[A[o].u][A[o].v]);
        while ( o <= m && A[o].w == A[o + 1].w ) { ++ o; B[++ t] = node(A[o].u, A[o].v, a[A[o].u][A[o].v]); }
        Sort(now + 1, t);
        REP(i, 1, n) { Vis[i].reset(); use[i] = false; Vis[i][i] = true; }
        num = 0;
        REP(i, 1, t)
        {
            int u = B[i].u, v = B[i].v; 
            REP(j, 1, n) if ( !use[j] && Vis[j][u] )
            {
                Vis[j] |= Vis[v];
                if ( Vis[j].count() == n ) { use[j] = true; ++ num; }
            }
            if ( num == n ) { ans = min(ans, A[o].w + B[i].w); break ; }
        }
    }
    printf("%d\n", ans);
    return 0;
}
