/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2020年11月21日 星期六 09时45分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, Begin[2][maxn], Next[2][maxn], To[2][maxn], e[2], T, s, t, val[2];
bool vis[2][maxn];
priority_queue<int, vector<int>, greater<int> > Q[2];

inline void add(int op, int u, int v) { To[op][++ e[op]] = v; Next[op][e[op]] = Begin[op][u]; Begin[op][u] = e[op]; }

inline bool Check(int Mid)
{
    REP(i, 1, n) vis[0][i] = vis[1][i] = false;
    while ( !Q[0].empty() ) Q[0].pop(); 
    while ( !Q[1].empty() ) Q[1].pop();
    val[0] = s; val[1] = t; Q[0].push(s); Q[1].push(t);
    
    int op = 0, cnt = 0;
    while ( 1 ) 
    {
        if ( val[0] == 1 && val[1] == 1 ) return true;
        int x = val[op];
        while ( !Q[op].empty() && Q[op].top() + val[op ^ 1] <= Mid ) 
        {
            int u = Q[op].top(); Q[op].pop(); val[op] = min(val[op], u); 
            vis[op][u] = true;
            for ( int i = Begin[op][u]; i; i = Next[op][i] )
                if ( !vis[op][To[op][i]] ) Q[op].push(To[op][i]);
        }
        if ( x == val[op] ) ++ cnt;
        if ( cnt > 2 ) return false;
        op ^= 1;
    }
    return true;
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n); e[0] = e[1] = 0; REP(i, 1, n) Begin[0][i] = Begin[1][i] = 0;
        REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(0, u, v); add(0, v, u); }
        REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(1, u, v); add(1, v, u); }
        scanf("%d%d", &s, &t);
        
        int L = s + t, R = 2 * n, ans;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( Check(Mid) ) { ans = Mid; R = Mid - 1; }
            else L = Mid + 1;
        }

        printf("%d\n", ans);
    }
    return 0;
}
