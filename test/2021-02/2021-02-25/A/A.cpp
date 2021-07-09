#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define int long long
#define pii pair<int, int>
 
const int maxn = 1e5 + 10;
 
int n, q, block, t = 180;
vector<int> p[210][210];
pii x[maxn], y[maxn];
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &q); block = 1000000000 / t; ++ t;
    REP(i, 1, n) 
	{
		scanf("%lld%lld%lld%lld", &x[i].x, &y[i].x, &x[i].y, &y[i].y);
		double k = (y[i].y - y[i].x) * 1.0 / (x[i].y - x[i].x);
		double b = y[i].x - k * x[i].x;
		if ( x[i].x == x[i].y ) 
		{
			int pos = (x[i].x - 1) / block + 1;
			REP(j, 1, t) p[pos][j].push_back(i);
			continue ; 
		}
		REP(j, 1, t)
		{
			int L = (j - 1) * block + 1, R = j * block;
			int l = ceil(k * L + b), r = floor(k * R + b);
			if ( l > r ) swap(l, r);
			int t1 = (l - 1) / block + 1;
			int t2 = (r - 1) / block + 1;
			REP(k, max(1ll, t1), min(t, t2)) p[j][k].push_back(i);
		}
	}
    REP(i ,1, q)
    {
        int a, b, ans = 0; scanf("%lld%lld", &a, &b);
		int X = (a - 1) / block + 1, Y = (b - 1) / block + 1;
		for ( int o = 0; o < p[X][Y].size(); ++ o ) 
        {
			int j = p[X][Y][o];
            int ret = a * (y[j].y - y[j].x) - x[j].x * y[j].y + x[j].y * y[j].x - b * (x[j].y - x[j].x);
            if ( ret == 0 ) ++ ans;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
