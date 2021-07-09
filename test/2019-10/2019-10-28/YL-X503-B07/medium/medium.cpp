/***************************************************************
	File name: medium.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 09时01分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int INF = 2147483647;
const int maxn = 2010;

int n, m, h[maxn], T, ans, ret, num;

inline void Solve(int now)
{
    while ( h[now] == h[now - 1] ) -- now;
    ret = h[now] * (n - now + 1);
    REP(i, now + 1, n) h[i] -= h[now];
    h[now] = 0;
    n = n - now + 1;
    REP(i, 1, n) h[i] = h[i + now - 1];
    REP(i, 0, m)
    {
        if ( i > 0 && h[i] != h[i - 1] ) ret += (h[i] - h[i - 1]) * (n - i + 1);
        num = 0;
        REP(j, 1, m - i) num += h[n - j + 1] - h[i];
        ans = min(ans, ret + num);
    }
}

int main()
{
    freopen("medium.in", "r", stdin);
    freopen("medium.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        REP(i, 1, n) scanf("%d", &h[i]);
        sort(h + 1, h + n + 1);
        ans = INF; ret = 0;
        REP(i, 0, m)
        {
            if ( i > 0 && h[i] != h[i - 1] ) ret += (h[i] - h[i - 1]) * (n - i + 1);
            num = 0;
            REP(j, 1, m - i) num += h[n - j + 1] - h[i];
            ans = min(ans, ret + num);
        }
        Solve(m);
        printf("%d\n", ans);
    }
    return 0;
}
