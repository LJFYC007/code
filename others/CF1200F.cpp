/***************************************************************
	File name: CF1200F.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 18时56分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;
const int N = 2520;

int n, m, f[maxn][maxn], a[maxn], Stack[maxn * 100], dep[maxn][maxn];
vector<int> Edge[maxn];
bool vis[maxn][maxn], use[maxn];

inline int DFS(int u, int ret)
{
    vis[u][ret] = true;
    if ( f[u][ret] ) return f[u][ret];
    Stack[dep[u][ret]] = u;
    int v = Edge[u][ret % Edge[u].size()], num = (ret + a[v]) % N;
    if ( vis[v][num] ) 
    {
        if ( f[v][num] ) return f[u][ret] = f[v][num];
        int l = dep[v][num], r = dep[u][ret];
        REP(i, l, r) use[Stack[i]] = false;
        REP(i, l, r) if ( !use[Stack[i]] ) { use[Stack[i]] = true; ++ f[u][ret]; }
        return f[u][ret];
    }
    dep[v][num] = dep[u][ret] + 1;
    return f[u][ret] = DFS(v, num);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);    
    REP(i, 1, n) { scanf("%d", &a[i]); a[i] = (a[i] % N + N) % N; }
    REP(i, 1, n)
    {
        int x; scanf("%d", &x);
        REP(j, 1, x) { int v; scanf("%d", &v); Edge[i].push_back(v); }
    }
    scanf("%d", &m);
    while ( m -- ) 
    {
        int x, y; scanf("%d%d", &x, &y);
        y = (y % N + a[x] + N) % N;
        printf("%d\n", DFS(x, y));
    }
    return 0;
}
