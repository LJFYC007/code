/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 08时36分33秒
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
const int INF = 1e18;

int n, m, k, h[maxn], a[maxn];

inline int get(int x)
{
	int sum = 0;
	REP(i, 1, x) sum += a[i];
	return sum;
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree1.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	REP(i, 1, n) { scanf("%lld", &h[i]); a[i] = h[i] - h[i - 1]; }
	while ( m -- ) 
	{
		int op, l, r, c; scanf("%lld%lld%lld", &op, &l, &r);
		if ( op == 1 ) 
		{
			int sum = 0;
			REP(i, l, r) REP(j, 1, i) sum += a[j];
			printf("%lld\n", sum);
		}
		if ( op == 2 ) 
		{
			scanf("%lld", &c);
			a[l] += c; a[r + 1] -= c;
		}
		if ( op == 3 ) 
		{
			REP(i, l + 1, r)	
			{
				int j = i + 1;
				while ( a[i] > k ) 
				{
					int x = min(a[i] - k, j <= r ? k - a[j] : INF);
					if ( x > 0 ) { a[i] -= x; a[j] += x; }
					++ j;
				}
				j = i - 1;
				while ( a[i] < -k ) 
				{
					int x = min(-k - a[i], j > l ? a[j] + k : INF);
					if ( x > 0 ) { a[i] += x; a[j] -= x; }
					-- j;
				}
			}
		}
	}
    return 0;
 }
