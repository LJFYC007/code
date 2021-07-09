/***************************************************************
    File name: J.cpp
    Author: ljfcnyali
    Create time: 2019年05月22日 星期三 08时38分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int Begin[maxn], Next[maxn], To[maxn], e;
long long ans1, ans2;
int tot, low[maxn], dfn[maxn], n, sum[maxn], cut[maxn], num, root;
stack<int> Stack;
vector<int> p[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void Tarjan(int u)
{
    low[u] = dfn[u] = ++ num; Stack.push(u);
    int cnt = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !dfn[v] ) 
        {
            Tarjan(v); ++ cnt;
            low[u] = min(low[u], low[v]);
            if ( (u == root && cnt > 1) || (u != root && dfn[u] <= low[v]) ) cut[u] = 1;
            if ( dfn[u] <= low[v] ) 
            {
                p[++ tot].clear();	
                while ( Stack.top() != v ) 
                {
                    p[tot].push_back(Stack.top()); Stack.pop();
                }
                Stack.pop();
                p[tot].push_back(u);
                p[tot].push_back(v);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int cnt = 0;
    while ( 1 ) 
    {
        ++ cnt;
        scanf("%d", &n); if ( n == 0 ) break ;
        printf("Case %d: ", cnt);
        mem(Begin); e = 0; tot = 0; mem(low); mem(dfn); mem(p); mem(cut); num = 0;
        while ( !Stack.empty() ) Stack.pop();
        ans1 = 0; ans2 = 1;
        int m = 0;
        REP(i, 1, n) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); m = max(m, max(u, v)); }
        REP(i, 1, m) if ( !dfn[i] ) { root = i; Tarjan(i); }
        REP(i, 1, tot)
        {
            int s = 0;
            REP(j, 0, p[i].size() - 1)
                if ( cut[p[i][j]] == 1 ) ++ s;
            if ( s == 0 ) { ans1 += 2; ans2 *= (p[i].size() - 1) * p[i].size() / 2; }
            else if ( s == 1 ) { ++ ans1; ans2 *= (p[i].size() - 1); }
//			printf("%d %d %d\n", s, ans1, ans2);
        }
        printf("%lld %lld\n", ans1, ans2);
//		REP(i, 1, m) printf("%d ", cut[i]); puts("");
    }
    return 0;
}
