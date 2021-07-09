/***************************************************************
	File name: hotchkiss.cpp
	Author: ljfcnyali
	Create time: 2019年10月11日 星期五 09时45分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2000010;

int n, m, a[maxn], f[maxn], Root[maxn], l[maxn], r[maxn], dep[maxn], anc[maxn][20];
stack<int> Stack;
vector<int> son[maxn];

inline void DFS(int u, int top)
{
    // cerr << u << " " << top << endl;
    Root[u] = top; anc[u][0] = f[u];
    REP(j, 1, 18) 
        if ( anc[u][j - 1] != -1 )
            anc[u][j] = anc[anc[u][j - 1]][j - 1];
    for ( auto v : son[u] ) 
    {
        dep[v] = dep[u] + 1;
        DFS(v, top);
    }
}

inline int LCA(int x, int y)
{
    if ( dep[x] < dep[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( (1 << j) <= dep[x] - dep[y] && dep[anc[x][j]] >= dep[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( (1 << j) <= dep[x] && anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

int main()
{
    freopen("hotchkiss.in", "r", stdin);
    freopen("hotchkiss.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, 2 * n) 
    {
        scanf("%d", &a[i]);
        l[i] = min(i, a[i]); r[i] = max(i, a[i]);
        while ( !Stack.empty() && Stack.top() >= l[i] ) 
        {
            int x = Stack.top(); Stack.pop();
            l[i] = min(l[i], l[x]); r[i] = max(r[i], r[x]);
        }
        Stack.push(i);
    }
    memset(Root, -1, sizeof(Root)); memset(f, -1, sizeof(f));
    REP(i, 1, 2 * n)
        if ( i == r[i] ) 
        {
            f[i] = l[i] - 1;
            son[f[i]].push_back(i);
        }
    REP(i, 0, 2 * n) if ( son[i].size() && Root[i] == -1 ) { dep[i] = 1; DFS(i, i); }
    while ( m -- ) 
    {
        int r1, r2; scanf("%d%d", &r1, &r2);
        if ( Root[r1] == -1 || Root[r2] == -1 || Root[r1] != Root[r2] ) puts("0");
        else printf("%d\n", dep[LCA(f[r1], f[r2])]);
    }
    return 0;
}
