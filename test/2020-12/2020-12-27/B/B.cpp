/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年12月27日 星期日 12时01分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, h, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, ans, ret;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &k, &h);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
    ans = 0x3f3f3f3f;
    REP(i, 1, n)
    {
        int ret = 0;
        Solve(i);
    }
    return 0;
}
