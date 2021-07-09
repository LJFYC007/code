/***************************************************************
	File name: anticipate.cpp
	Author: ljfcnyali
	Create time: 2020年07月18日 星期六 10时41分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 51;
const int N = 1e8;
const double eps = 1e-12;

int op, n, l, r, x[maxn], y[maxn], ans[maxn];

signed main()
{
    freopen("anticipate.in", "r", stdin);
    freopen("anticipate.out", "w", stdout);
    srand(time(0));
    scanf("%lld", &op);
    scanf("%lld%lld%lld", &n, &l, &r);
    REP(i, 1, n) scanf("%lld", &x[i]);
    REP(i, 1, n) scanf("%lld", &y[i]);
    int sum = N / n;
    REP(o, 1, sum)
    {
        double pos = l + rand() % ((r - l) * 1000) / 1000.0, t = -1;
        int ret = 0;
        REP(i, 1, n)
        {
            double Time = min((x[i] - l) * (r - l) / (pos - l), (r - x[i]) * (r - l) / (r - pos)) + y[i];
            if ( Time > t ) { ret = i; t = Time; }
        }
        ++ ans[ret];
    }
    REP(i, 1, n) printf("%.9lf\n", ans[i] * 1.0 / sum);
    return 0;
}
