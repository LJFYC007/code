/***************************************************************
	File name: math.cpp
	Author: ljfcnyali
	Create time: 2019年10月14日 星期一 08时37分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int INF = 100000000000;
const long double eps = 1e-20;

long double t, ans;
int T, n, m, x, y, sum;
bool flag;

inline void Solve(int X, int Y)
{
    if ( __gcd(X, Y) != 1 ) return ;
    long double p = fabs((long double) X / Y - t);
    if ( fabs(ans - p) < eps ) flag = true;
    else if ( p < ans ) { ans = p; x = X; y = Y; flag = false;} 
}

signed main()
{
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    cin >> T;
    while ( T -- )
    {
        cin >> m >> n >> t;
        ans = INF; flag = false;
        REP(i, 1, n)
        {
            int p = min((int)(i * t), m);
            Solve(p, i);
            if ( p + 1 <= m ) Solve(p + 1, i);
            if ( p - 1 >= 0 ) Solve(p - 1, i);
        }
        if ( flag == true ) puts("hou tou hou tou shi jie yi liu");
        else printf("%lld/%lld\n", x, y);
    }
    return 0;
}
