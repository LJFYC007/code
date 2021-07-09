/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年09月13日 星期日 10时08分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, h[maxn], Begin[maxn], Next[maxn], To[maxn], e, c[2][maxn];
set<pii> Set[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int lowbit(int x) { return x & -x; }

inline void Modify(int op, int pos, int val) { for ( int i = pos; i < maxn; i += lowbit(i) ) c[op][i] += val; }

inline int Query(int op, int pos)
{
    int ret = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[op][i];
    return ret;
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    read(n); read(m);
    REP(i, 1, n) { read(h[i]); Modify(0, h[i], 1); }
    REP(i, 1, n - 1) 
    { 
        int u, v; read(u); read(v); add(u, v); add(v, u); 
        Modify(1, min(h[u], h[v]), 1); 
        if ( h[u] < h[v] ) Set[u].insert(pii(h[v], v));
        else Set[v].insert(pii(h[u], u));
    }
    while ( m -- ) 
    {
        int op, x, val; read(op); read(x);
        if ( op == 1 ) 
        {
            read(val); Modify(0, h[x], -1); Modify(0, val, 1);
            int u = x; Modify(1, h[u], -Set[u].size());
            for ( auto i : Set[u] )
            {
                if ( i.first >= val ) break ; 
                int v = i.second; 
                if ( h[v] >= val ) { Set[u].insert(pii(h[v], v)); continue ; } 
                Set[v].insert(pii(val, u)); Modify(1, h[v], 1);
            }
            while ( Set[u].size() && (*Set[u].begin()).first < val ) Set[u].erase(Set[u].begin());
            h[u] = val; Modify(1, val, Set[u].size());
        }
        else printf("%d\n", Query(1, x - 1) - Query(0, x - 1) + 1);
    }
    return 0;
}
