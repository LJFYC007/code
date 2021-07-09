/***************************************************************
	File name: park.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 10时45分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, l[maxn], r[maxn], p[maxn];

namespace Subtask1
{
    bool use[10][10], vis[10];
    int ans = 0x3f3f3f3f;

    inline void DFS(int x, int num)
    {
        if ( num >= ans ) return ;
        if ( x == n + 1 ) { ans = num; return ; }
        REP(i, l[x], r[x])
            if ( !use[i][p[x]] ) 
            {
                use[i][p[x]] = true;
                if ( !vis[i] ) { vis[i] = true; DFS(x + 1, num + 1); vis[i] = false; }
                else DFS(x + 1, num);
                use[i][p[x]] = false;
            }
    }

    inline int main()
    {
        REP(i, 1, n) scanf("%d%d%d", &l[i], &r[i], &p[i]);
        DFS(1, 0); 
        if ( ans == 0x3f3f3f3f ) puts("GG");
        else printf("%d\n", ans);
        return 0;
    }
}

namespace Subtask2
{
    pii q[maxn];
    set<int> Set;

    inline int main()
    {
        int x;
        REP(i, 1, n) scanf("%d%d%d", &q[i].x, &q[i].y, &x);
        sort(q + 1, q + n + 1, [](pii a, pii b) { return a.y < b.y; });
        REP(i, 1, n) Set.insert(i);
        int ans = 0;
        REP(i, 1, n)
        {
            auto it = Set.lower_bound(q[i].x);
            if ( *it > q[i].y ) { puts("GG"); return 0; }
            Set.erase(it); ++ ans;
        }
        printf("%d\n", ans);
        return 0;
    }
}

int main()
{
    freopen("park.in", "r", stdin);
    freopen("park.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if ( n <= 8 ) return Subtask1 :: main();
    return Subtask2 :: main();
}
