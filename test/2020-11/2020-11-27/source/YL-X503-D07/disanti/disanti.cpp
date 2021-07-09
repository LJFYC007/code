/***************************************************************
	File name: disanti.cpp
	Author: ljfcnyali
	Create time: 2020年11月27日 星期五 11时46分22秒
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
const int INF = 1e18;

int n, C, ans;
pii a[maxn], b[maxn];

inline void print(int pos)
{
    int sum = C, x = n - pos + 1;
    REP(i, pos, n) sum -= a[i].x;
    int d = __gcd(sum, x); sum /= d; x /= d;
    if ( x < 0 ) { x = -x; sum = -sum; }
    REP(i, pos, n) b[a[i].y] = pii(a[i].x * x + sum, x);
    REP(i, 1, n) if ( b[i].y == 0 || b[i].y == 1 ) printf("%lld\n", b[i].x); else printf("%lld/%lld\n", b[i].x, b[i].y);
}

signed main()
{
    freopen("disanti.in", "r", stdin);
    freopen("disanti.out", "w", stdout);
    scanf("%lld%lld", &n, &C);
    REP(i, 1, n) { scanf("%lld", &a[i].x); a[i].y = i; }
    sort(a + 1, a + n + 1);
    int sum = 0;
    a[0].x = -INF;
    for ( int i = n; i >= 1; -- i ) 
    {
        sum += a[i].x;
        int val = C - sum, x = n - i + 1;
        if ( val < 0 && -val > a[i].x * x ) { print(i + 1); return 0; }
        if ( a[i - 1].x < 0 && val > 0 && -a[i - 1].x * x < val ) continue ;
        if ( a[i - 1].x < 0 ) { print(i); return 0; }
    }
    return 0;
}
