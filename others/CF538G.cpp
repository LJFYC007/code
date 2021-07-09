/***************************************************************
	File name: CF538G.cpp
	Author: ljfcnyali
	Create time: 2021年01月20日 星期三 09时07分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int INF = 8e18;
const double eps = 1e-12;

int n, l; 
struct node { int A, B, C; } ;
struct HAHAHAHA
{
    int ans[maxn]; node a[maxn];

    inline void Solve()
    {
        a[0] = {0, 0, 0}; a[n + 1] = {-1, l, 0};
        sort(a, a + n + 1, [](node &a, node &b) { return a.B < b.B; });
        int L = -INF, R = INF;
        REP(i, 1, n + 1)
        {
            long double k = a[i - 1].A - a[i].A; int b = a[i].C - a[i - 1].C, t = a[i].B - a[i - 1].B;
            if ( k == 0 && (-b > 0 || t - b < 0) ) { puts("NO"); exit(0); }
            if ( k == 0 ) continue ; 
            long double l = -b / k, r = (t - b) / k; if ( l > r ) swap(l, r);
            L = max(L, (int)ceil(l - eps)); R = min(R, (int)floor(r + eps));
        }
        if ( L > R ) { puts("NO"); exit(0); }

        int sn = L, now = 0, pos = 0;
        REP(i, 1, n + 1) 
        {
            int x = a[i].C - a[i].A * sn;
            while ( now < a[i].B ) 
            { 
                ++ now; 
                if ( pos < x ) { ans[now] = 1; ++ pos; }
                else ans[now] = -1;
            }
            if ( pos != x ) { puts("NO"); exit(0); }
        }
    }
} A, B;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &l);
    REP(i, 1, n) 
    { 
        int t, x, y; scanf("%lld%lld%lld", &t, &x, &y); 
        if ( (x + y + t) % 2 != 0 ) { puts("NO"); exit(0); }
        if ( (x - y + t) % 2 != 0 ) { puts("NO"); exit(0); }
        A.a[i] = {t / l, t % l, (x + y + t) / 2}; B.a[i] = {t / l, t % l, (x - y + t) / 2}; 
    }
    A.Solve(); B.Solve();
    REP(i, 1, l) 
    {
        if ( A.ans[i] == 1 && B.ans[i] == 1 ) putchar('R');
        if ( A.ans[i] == -1 && B.ans[i] == 1 ) putchar('D');
        if ( A.ans[i] == 1 && B.ans[i] == -1 ) putchar('U');
        if ( A.ans[i] == -1 && B.ans[i] == -1 ) putchar('L');
    }
    puts("");
    return 0;
}

