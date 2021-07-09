/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 14时28分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int INF = 0x3f3f3f3f;

int n, m, h[maxn], f[maxn];

int main()
{
    freopen("medium.in", "r", stdin);
    freopen("medium.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        REP(i, 1, n) scanf("%d", &h[i]);
        sort(h + 1, h + n + 1);
        REP(i, 1, n) f[i] = (n - i + 1) * h[i];
        REP(o, 2, m)
        {
            for ( int i = n; i >= 1; -- i ) 
            {
                f[i] = INF;
                REP(j, 1, i - 1)
                    f[i] = min(f[i], f[j] + (n - i + 1) * (h[i] - h[j]));
            }
        }
        int ans = INF;
        REP(i, 1, n) ans = min(ans, f[i]);
        printf("%d\n", ans);
    }
    return 0;
}

