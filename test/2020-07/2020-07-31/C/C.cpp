/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月31日 星期五 11时02分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;

int N, n, m, W, h[maxn], a[maxn], id[maxn];
pii Q[maxn];
double ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &W);
    while ( n -- ) 
    {
        int op; scanf("%lld", &op);
        if ( op == 1 ) 
        {
            ++ m; id[m] = m;; scanf("%lld%lld", &h[m], &a[m]);
            int x = m - 1;
            while ( x >= 1 ) 
            {
                int val = a[x] * h[x + 1] - W - a[x + 1] * h[x];
                if ( val < 0 ) break ; 
                swap(a[x], a[x + 1]); swap(h[x], h[x + 1]); swap(id[x], id[x + 1]); -- x;
            }
        }
        else { Q[++ N].x = m; scanf("%lld", &Q[N].y); }
    }
    REP(i, 1, N)
    {
        int num = Q[i].y;
        REP(j, 1, m) 
        {
            if ( id[j] <= Q[i].x ) -- num;
            if ( !num ) { printf("%lld %lld\n", h[j], a[j]); break ; }
        }
    }
    return 0;
}
