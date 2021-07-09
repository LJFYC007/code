/***************************************************************
	File name: array.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 11时00分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 300010;

int n, k, p[maxn], q[maxn];

namespace Subtask1
{
    int a[maxn], b[maxn], t1[maxn], t2[maxn];

    inline void Check()
    {
        int ret = 0;
        REP(i, 1, n) REP(j, 1, n) if ( a[i] + b[j] < 0 ) ++ ret;
        if ( ret != k ) return ;
        puts("Yes");
        REP(i, 1, n) printf("%d ", a[i]); puts("");
        REP(i, 1, n) printf("%d ", b[i]); puts("");
        exit(0);
    }

    inline void DFS(int x, int X)
    {
        if ( x == 2 * n + 1 ) { Check(); return ; }
        if ( x == n + 1 ) X = -n; 
        if ( x <= n ) REP(i, X, n) { a[t1[x]] = i; DFS(x + 1, i); }
        else REP(i, X, n) { b[t2[x - n]] = i; DFS(x + 1, i); }
    }

    inline int main()
    {
        REP(i, 1, n) { t1[p[i]] = i; t2[q[i]] = i; }
        DFS(1, -n);
        puts("No");
        return 0;
    }
}

namespace Subtask2
{
    inline int main()
    {
        puts("Yes");
        REP(i, 1, n) printf("%d ", p[i]); puts("");
        REP(i, 1, n) printf("%d ", q[i]); puts("");
        return 0;
    }
}

namespace Subtask3
{
    inline void Solve()
    {
        int x = rand() % (n + 1), y = rand() % (n + 1), ret = 0;
        REP(i, 1, n) p[i] = i <= x ? -abs(p[i]) : abs(p[i]);
        REP(i, 1, n) q[i] = i <= y ? -abs(q[i]) : abs(q[i]);
        REP(i, 1, n) REP(j, 1, n) if ( p[i] + q[j] < 0 ) { ++ ret; if ( ret > k ) break ; }
        if ( ret != k ) return ;
        puts("Yes");
        REP(i, 1, n) printf("%d ", p[i]); puts("");
        REP(i, 1, n) printf("%d ", q[i]); puts("");
        exit(0);
    }

    inline int main()
    {
        int x = sqrt(k);
        if ( x * x == k ) 
        {
            puts("Yes");
            REP(i, 1, n) if ( i <= x ) printf("%d ", -i); else printf("%d ", i); puts("");
            REP(i, 1, n) if ( i <= x ) printf("%d ", -i); else printf("%d ", i); puts("");
        }
        else puts("No");
        return 0;
        if ( n <= 500 ) REP(i, 1, 1000) Solve();
        else REP(i, 1, 300) Solve();
        puts("No");
        return 0;
    }
}

int main()
{
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d", &p[i]);
    REP(i, 1, n) scanf("%d", &q[i]);
    if ( n <= 4 ) return Subtask1 :: main();
    if ( k == 0 ) return Subtask2 :: main();
    return Subtask3 :: main();
}
