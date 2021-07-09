/***************************************************************
	File name: big.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 10时46分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], ans = -1, sum, suf[maxn];

inline int calc(int x) { return ((x * 2 / (1 << n)) + x * 2) % (1 << n); }

int main()
{
    freopen("big.in", "r", stdin);
    freopen("big.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d", &a[i]);
    for ( int i = m; i >= 1; -- i ) suf[i] = suf[i + 1] ^ a[i];
    REP(x, 0, (1 << n) - 1)
    {
        int Min = INF, now = x;
        REP(i, 1, m)
        {
            Min = min(Min, calc(now) ^ suf[i]);
            now ^= a[i];
        }
        Min = min(Min, calc(now));

        if ( Min > ans ) { ans = Min; sum = 0; }
        if ( Min == ans ) ++ sum;
    }
    printf("%d\n%d\n", ans, sum);
    return 0;
}
