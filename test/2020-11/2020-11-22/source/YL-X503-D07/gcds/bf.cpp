/***************************************************************
	File name: gcds.cpp
	Author: ljfcnyali
	Create time: 2020年11月22日 星期日 09时18分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e4 + 10;

int n, a[maxn], ans;

inline int Solve()
{
    int ret = 0;
    REP(i, 1, n)
    {
        if ( a[i] == 1 ) return 0;
        int x = a[i]; ++ ret;
        REP(j, i + 1, n)
        {
            x = __gcd(x, a[j]);
            if ( x == 1 ) break ; ++ ret;
        }
    }
    if ( ret == 246 ) 
    {
        REP(i, 1, n) printf("%d ", a[i]);
        puts("");
    }
    return ret;
}

int main()
{
    freopen("gcds.in", "r", stdin);
    freopen("gcds1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n)
    {
        int x = a[i];
        REP(j, 1, 5000) { a[i] = j; ans = max(ans, Solve()); }
        a[i] = x;
    }
    printf("%d\n", ans);
    return 0;
}
