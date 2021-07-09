/***************************************************************
	File name: LibreOJ_523.cpp
	Author: ljfcnyali
	Create time: 2020年05月06日 星期三 20时25分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, T, a[maxn], b[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int ans, d[maxn], vis[maxn], Root[maxn], cnt;
bool use[maxn], flag;
pii Edge[maxn];
queue<int> Q;
vector<int> Point;

inline void add(int u, int v, int w) 
{ 
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
    ++ d[u]; Edge[e] = pii(u, v);
}

inline void DFS1(int u)
{
    if ( vis[u] != 0 ) return ; vis[u] = -1;
    if ( use[u] == false ) Point.push_back(u); 
    for ( int i = Begin[u]; i; i = Next[i] ) DFS1(To[i]);
}

inline void DFS2(int u)
{
    if ( vis[u] > 0 ) return ; vis[u] = flag + 1;
    for ( int i = Begin[u]; i; i = Next[i] ) DFS2(To[i]);
}

inline void toposort()
{
    REP(i, 1, n) if ( d[i] == 1 ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); use[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; -- d[v];
            if ( d[v] == 1 ) Q.push(v);
        }
    }
    REP(i, 1, n) 
    {
        if ( vis[i] ) continue ;
        Point.clear();
        DFS1(i); flag = Point.size(); DFS2(i);
        if ( flag == false ) Root[++ cnt] = i;
        else
        {
            for ( auto u : Point ) 
            {
                DFS3(u);
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &m, &n, &T);
    REP(i, 0, m - 1) scanf("%d", &a[i]);
    REP(i, 0, m - 1) scanf("%d", &b[i]);
    REP(i, 0, m - 1)
    {
        int x = (a[i] + b[i]) % n, y = (a[i] - b[i] + n) % n;
        printf("%d %d\n", x, y);
        ++ x; ++ y;
        if ( x > y ) swap(x, y);
        int w; scanf("%d", &w); 
        if ( x == y ) { ans += w; vis[x] = 2; d[x] = -1; }
        add(x, y, w); scanf("%d", &w); add(y, x, w);
    }
    toposort();
    REP(i, 1, n) printf("%d ", vis[i]); puts("");
    return 0;
}
