/***************************************************************
	File name: prime.cpp
	Author: ljfcnyali
	Create time: 2020年10月19日 星期一 09时37分49秒
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
const int INF = 1e9;

int n, q;
pii a[maxn];
bool IsPrime[maxn];

inline pii operator +(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
inline pii operator *(pii a, pii b) { return pii(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x); }

inline bool Check(pii x)
{
    if ( x.x <= 1 || x.y != 0 ) return false;
    for ( int i = 2; i * i <= x.x; ++ i )
        if ( x.x % i == 0 ) return false;
    return true;
}

signed main()
{
    freopen("prime.in", "r", stdin);
    freopen("prime1.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) 
    {
        scanf("%lld%lld", &a[i].x, &a[i].y);
        IsPrime[i] = Check(a[i]);
    }
    while ( q -- ) 
    {
        int op, l, r, x, y; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%lld%lld", &x, &y);
            a[l] = pii(x, y); IsPrime[l] = Check(a[l]);
            REP(i, l + 1, r) { a[i] = a[l]; IsPrime[i] = IsPrime[l]; }
        }
        if ( op == 2 ) 
        {
            scanf("%lld%lld", &x, &y);
            REP(i, l, r)
            {
                if ( abs(a[i].x) >= INF || abs(a[i].y) >= INF )
                {
                    a[i].x = a[i].y = INF;
                    IsPrime[i] = false;
                    continue ;
                }
                a[i] = a[i] * pii(x, y); IsPrime[i] = Check(a[i]);
            }
        }
        if ( op == 3 ) 
        {
            int ans = 0;
            REP(i, l, r) ans += IsPrime[i];
            printf("%lld\n", ans);
        }
    }
    return 0;
}
