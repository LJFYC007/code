#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
#define x1 X1
#define y1 Y1
#define x2 X2
#define y2 Y2
typedef long long LL;

const int maxn = 2e5 + 10;

int n, k, f[maxn];
struct node { int x1, y1, x2, y2; } a[maxn], b[5];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	srand(time(0));
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) scanf("%lld%lld%lld%lld", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
	while ( 1 )
	{
		random_shuffle(a + 1, a + n + 1);
		REP(i, 1, k) b[i] = a[i];
		REP(i, k + 1, n)
		{
			double Max = -1; int pos = 0;
			REP(j, 1, k)
			{
				int sum = (b[j].x2 - b[j].x1) * (b[j].y2 - b[j].y1);
				int X1 = max(b[j].x1, a[i].x1);
				int X2 = min(b[j].x2, a[i].x2);
				int Y1 = max(b[j].y1, a[i].y1);
				int Y2 = min(b[j].y2, a[i].y2);
				if ( X1 > X2 || Y1 > Y2 ) continue ;
				int ret = (X2 - X1) * (Y2 - Y1);
				if ( ret * 1.0 / sum > Max ) { Max = ret * 1.0 / sum; pos = j; }
			}
			if ( pos == 0 ) goto Next ;
			b[pos].x1 = max(b[pos].x1, a[i].x1);
			b[pos].x2 = min(b[pos].x2, a[i].x2);
			b[pos].y1 = max(b[pos].y1, a[i].y1);
			b[pos].y2 = min(b[pos].y2, a[i].y2);
		}
		REP(i, 1, k) printf("%lld %lld\n", b[i].x1, b[i].y1); return 0;
		Next : ;
	}
	return 0;
}
