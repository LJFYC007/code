/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年04月13日 星期一 21时46分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, dis[maxn], size[maxn], ans2;
bool flag1, flag2;
vector<int> Edge[maxn];

inline void DFS(int u, int fa)
{
    size[u] = 1; int sum = 0;
    for ( auto v : Edge[u] )
    {
        if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        DFS(v, u);
        size[u] += size[v];
        if ( size[v] == 1 ) ++ sum;
    }
    if ( size[u] == 1 ) 
    {
        if ( dis[u] & 1 ) flag1 = true;
        else flag2 = true;
    }
    if ( sum ) ans2 -= sum - 1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); ans2 = n - 1;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); Edge[u].push_back(v); Edge[v].push_back(u); }
    REP(i, 1, n) if ( Edge[i].size() != 1 ) { DFS(i, 0); break ; }
    if ( flag1 && flag2 ) printf("3 "); else printf("1 ");
    printf("%d\n", ans2);
    return 0;
}
