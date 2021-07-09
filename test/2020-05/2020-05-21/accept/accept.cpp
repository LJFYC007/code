/***************************************************************
	File name: accept.cpp
	Author: ljfcnyali
	Create time: 2020年05月21日 星期四 13时50分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, num;
long double r;

inline bool Check(int x, int y)
{
    long double t = x, p = (t / y) * num; int q = round(r * num);
    long double g = x * 1.0 / y;
    if ( q == round(p) ) return true;
    return false;
}

signed main()
{
    freopen("accept.in", "r", stdin);
    freopen("accept.out", "w", stdout);
    srand(time(0));
    while ( ~scanf("%lld%Lf", &n, &r) )
    {
        num = 1;
        REP(i, 1, n) num *= 10;
        bool flag = false;
        REP(i, 1, 1000)
        {
            int x = ceil(i * r);
            if ( Check(x, i) ) { printf("%lld\n", i); flag = true; break ; }
            if ( Check(x - 1, i) ) { printf("%lld\n", i); flag = true; break ; }
        }
        if ( flag == true ) continue ;
        int ans = 1000000000;
        REP(i, 1, 50000)
        {
            int N = rand() % (ans - 1) + 1;
            int x = ceil(N * r);
            if ( Check(x, N) ) ans = N; 
            if ( Check(x - 1, N) ) ans = N; 
        }
        printf("%lld\n", ans);
    }
    return 0;
}
