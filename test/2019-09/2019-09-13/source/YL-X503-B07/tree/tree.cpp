/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年09月13日 星期五 10时25分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2010;

int Beign[maxn], Next[maxn], To[maxn], e, W[maxn];
int a[maxn], n, m;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    REP(i, 1, m)
    {
        int u, val; scanf("%d%d", &u, &val);
        a[u] = val;
        int ans = 0;
        REP(j, 1, n) ans = max(ans, Solve(j));
    }
    return 0;
}
