#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 100010;

int Begin[maxn], Next[maxn], To[maxn], e, n, m;
int dfn[maxn], low[maxn], Index, Stack[maxn], top, ans;
bool vis[maxn];
priority_queue<int, vector<int>, greater<int> > DAG;

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ Index;
    vis[u] = true;
    Stack[++ top] = u;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( !dfn[v] ) 
        {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if ( vis[v] ) low[u] = min(low[u], low[v]);
    }
    if ( dfn[u] == low[u] ) 
    {
        int sum = 0, t = top, Min = u;
        while ( Stack[t + 1] != u ) 
        {
            Min = min(Min, Stack[t]);
            vis[Stack[t]] = false;
            -- t; ++ sum;
        }
        // printf("%d %d\n", u, sum);
        if ( sum > ans || ( sum == ans && DAG.top() > Min ) ) 
        {
            while ( !DAG.empty() ) DAG.pop();
            while ( Stack[top + 1] != u )
            {
                DAG.push(Stack[top]); top --;
            } 
            ans = sum;
        }
        else while ( Stack[top + 1] != u ) -- top;
    }
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
        int u, v, x; scanf("%d%d%d", &u, &v, &x);
        add(u, v);
        if ( x == 2 ) add(v, u);
    }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i, 0);
    printf("%d\n", ans);
    while ( !DAG.empty() ) { printf("%d ", DAG.top()); DAG.pop(); }
    puts("");
    return 0;
}
