/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年12月23日 星期三 10时47分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
double f[maxn], lamda;
bool flag;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS(int u, int fa)
{
    f[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); f[u] += W[i] * W[i] * 1.0 / (4 * f[v]);
    }
    f[u] = lamda * a[u] - f[u];
    if ( f[u] < 0 ) flag = true;
}

inline bool Check(double x)
{
    lamda = x; flag = false;
    DFS(1, 0); return flag;
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    // Check(0.5); return 0; 
    double L = 0, R = 1000000;
    REP(i, 1, 100)
    {
        double Mid = (L + R) / 2;
        if ( Check(Mid) ) L = Mid;
        else R = Mid;
    }
    printf("%.9lf\n", (L + R) / 2);
    return 0;
}
