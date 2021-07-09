/***************************************************************
	File name: tug.cpp
	Author: ljfcnyali
	Create time: 2020年05月07日 星期四 13时26分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;
const int N = 2e5;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], d[maxn];
int Root[maxn], cnt, belong[maxn], sum[maxn], ans;
vector<int> p[maxn];
queue<int> Q;
bool use[maxn], test[maxn];
bitset<maxn> Set;

namespace Subtask
{
    inline int main()
    {
        sort(sum + 1, sum + m + 1);
        reverse(sum + 1, sum + m + 1);
        int ret = ans;
        REP(i, 1, 27000) if ( ret > 0 ) ret -= sum[i]; else ret += sum[i];
        ans = ret; ret = 100000000;
        Set[ans + N] = 1;
        REP(i, 27001, m) Set = (Set >> sum[i]) | (Set << sum[i]);
        int pos = Set._Find_first();
        while ( pos < maxn ) { ret = min(ret, abs(pos - N)); pos = Set._Find_next(pos); }
        printf("%d\n", ret);
        return 0;
    }
}

inline void add(int u, int v, int w) { ++ d[u]; To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u)
{
    p[cnt].push_back(u); belong[u] = cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] ) continue ;
        sum[cnt] += W[i]; use[v] = true; DFS1(v);
    }
}

inline void DFS2(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( belong[v] ) continue ;
        ans += W[i]; belong[v] = cnt; DFS2(v);
    }
}

inline void toposort()
{
    REP(i, 1, m) if ( d[i] <= 1 ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); use[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; -- d[v];
            if ( d[v] == 1 ) Q.push(v);
        }
    }
    REP(i, 1, m)
    {
        if ( use[i] ) continue ;
        Root[++ cnt] = i; use[i] = true; DFS1(i);
        for ( auto u : p[cnt] ) DFS2(u);
    }
}

int main()
{
    freopen("tug.in", "r", stdin);
    freopen("tug.out", "w", stdout);
    scanf("%d", &n); m = 2 * n;
    REP(i, 1, m)
    {
        int l, r, w; scanf("%d%d%d", &l, &r, &w);
        add(l, r + n, w); add(r + n, l, -w);
    }
    toposort();
    REP(i, 1, m) if ( !belong[i] ) { puts("-1"); return 0; }
    m = cnt;
    REP(i, 1, m)
    {
        int u = p[i][0], v = p[i][p[i].size() - 1];
        if ( p[i].size() == 2 ) 
        {
            sum[i] = 0;
            for ( int j = Begin[v]; j; j = Next[j] ) if ( To[j] == u && !test[j] ) 
            {
                sum[i] += W[j];
                test[j] = test[(j & 1) ? j + 1 : j - 1] = true;
                break ; 
            }
            for ( int j = Begin[u]; j; j = Next[j] ) if ( To[j] == v && !test[j] ) 
            {
                sum[i] += W[j];
                test[j] = test[(j & 1) ? j + 1 : j - 1] = true;
                break ; 
            }
        }
        else for ( int j = Begin[v]; j; j = Next[j] ) if ( To[j] == u ) sum[i] += W[j];
        sum[i] = abs(sum[i]);
    }
    if ( m > 5000 ) return Subtask :: main();
    Set[ans + N] = 1;
    REP(i, 1, m) Set = (Set >> sum[i]) | (Set << sum[i]);
    int ret = 10000000, pos = Set._Find_first();
    while ( pos < maxn ) { ret = min(ret, abs(pos - N)); pos = Set._Find_next(pos); }
    printf("%d\n", ret);
    return 0;
}
