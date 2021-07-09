/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年11月13日 星期五 10时00分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], b[maxn], ans;

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, x, y); int t = x; x = y; y = t - (a / b) * y;
}

int main()
{
    freopen("mode.in", "r", stdin);
    freopen("mode.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { int x; scanf("%d", &x); ++ a[x]; }
    REP(i, 1, n - 1) { int x; scanf("%d", &x); ++ b[x]; }
    int ans = 0;
    REP(o, 1, n - 1)
    {
        int ret = 0;
        REP(i, 1, n - 1)
        {
            int x, y; exgcd(i, n, x, y);
            x *= o; y *= o;
            ret += min(a[i], b[(x % n + n) % n]);
        }
        ans = max(ans, ret);
    }
    printf("%d\n", ans);
    return 0;
}
