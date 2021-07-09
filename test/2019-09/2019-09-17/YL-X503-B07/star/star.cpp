/***************************************************************
	File name: star.cpp
	Author: ljfcnyali
	Create time: 2019年09月17日 星期二 20时42分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask1
{
    struct node
    {
        int s, t;
    } q[maxn];

    inline void Solve()
    {
        REP(i, 1, m) scanf("%d%d", &q[i].s, &q[i].t);

    }
}

namespace Subtask2
{
    inline void Solve()
    {
    }
}

int main()
{
    freopen("star.in", "r", stdin);
    freopen("star.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) scanf("%d", &a[i]);
    bool flag = true;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); if ( u != v - 1 ) flag = false; }
    if ( flag == true ) Subtask1 :: Solve();
    else Subtask2 :: Solve();
    return 0;
}
