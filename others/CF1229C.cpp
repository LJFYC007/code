/***************************************************************
	File name: CF1229C.cpp
	Author: ljfcnyali
	Create time: 2019年10月27日 星期日 21时29分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int d1[maxn], d2[maxn], n, m, q;
LL ans;
vector<int> Edge1[maxn], Edge2[maxn];

inline LL Solve(int x)
{
    ans -= (LL)d1[x] * d2[x];
    for ( auto v : Edge2[x] ) ans += d1[v] - d2[v] - 1;
    for ( auto v : Edge2[x] )
    {
        -- d1[v]; ++ d2[v];
        Edge2[v].push_back(x);
    }
    Edge2[x].clear(); 
    d1[x] += d2[x]; d2[x] = 0;
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) 
    {
        int u, v; scanf("%d%d", &u, &v);
        if ( u < v ) swap(u, v);
        ++ d1[u]; ++ d2[v]; 
        Edge1[u].push_back(v); Edge2[v].push_back(u);
    }
    REP(u, 1, n) for ( auto v : Edge1[u] ) ans += d1[v];
    printf("%I64d\n", ans);
    scanf("%d", &q);
    while ( q -- )  
    {
        int x; scanf("%d", &x);
        printf("%I64d\n", Solve(x));
    }
    return 0;
}
