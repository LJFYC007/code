/***************************************************************
	File name: kingdom.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 09时02分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2000010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, Root[maxn], d[maxn];
int size[maxn], dis[maxn], sum[maxn], ret, num[maxn], ans, sum1[maxn], sum2[maxn], sum3[maxn];
int sum_size, sum_sum;
bool use[maxn], vis[maxn];
vector<int> p;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa, int t)
{
    ++ size[t]; p.push_back(u); ++ num[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || use[v] ) continue ;
        dis[v] = dis[u] + 1; sum[t] += dis[v]; 
        DFS(v, u, t); num[u] += num[v];
    }
}

inline void DFS1(int u, int fa)
{
    Root[++ m] = u; vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || !use[v] || vis[v] ) continue ;
        DFS1(v, u);
    }
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || use[v] ) continue ;
        num[v] += num[u]; DFS2(v, u);
    }
}

inline void toposort()
{
    memset(use, true, sizeof(use));
    queue<int> Q; REP(i, 1, n) if ( d[i] == 1 ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); use[u] = false;  Q.pop(); 
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i]; -- d[v];
            if ( d[v] == 1 ) Q.push(v);
        }
    }
    int x;
    REP(i, 1, n) if ( use[i] ) { x = i; break ; }
    DFS1(x, 0);
}

signed main()
{
    freopen("kingdom.in", "r", stdin);
    freopen("kingdom.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); ++ d[u]; ++ d[v]; }
    toposort();    
    REP(i, 1, m) 
    {
        p.clear(); DFS(Root[i], 0, Root[i]); DFS2(Root[i], 0);
        ret += size[Root[i]] * (sum[Root[i]] + size[Root[i]]);
        for ( auto j : p ) ret -= num[j];
        sum_size += size[Root[i]];
        sum_sum += sum[Root[i]];
    }

    for ( int i = m; i >= 1; -- i )
    {
        sum1[i] = sum1[i + 1] + sum[Root[i]];
        sum2[i] = sum2[i + 1] + size[Root[i]];
        sum3[i] = sum3[i + 1] + size[Root[i]];
    }
    for ( int i = m; i >= 1; -- i ) sum2[i] += sum2[i + 1];
    REP(i, 1, m - 1) ret += size[Root[i]] * (sum2[i + 1] + sum1[i + 1]) + sum[Root[i]] * sum3[i + 1];
    ans = max(ans, ret);
    // printf("%lld\n", ret);

    // REP(i, 1, m) printf("%lld ", Root[i]); puts("");
    // REP(i, 1, m) printf("%lld ", sum[Root[i]]); puts("");
    // REP(i, 1, m) printf("%lld ", size[Root[i]]); puts(""); 

    int val = 0, w = 0;
    REP(i, 2, m) 
    {
        val += (i - 1) * size[Root[i]];
        w += (m - i + 1) * size[Root[i]];
    }
    // printf("%lld %lld\n", val, w);

    REP(i, 1, m - 1)
    {
        ret = ret + size[Root[i]] * (w - val);
        val = val - sum_size + m * size[Root[i]];
        w = w - m * size[Root[i + 1]] + sum_size;
        // printf("%lld %lld %lld\n", val, w, ret);
        ans = min(ans, ret);
    }
    printf("%lld\n", ans);
    return 0;
}
