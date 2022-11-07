/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, q, g[maxn]; struct node { int x, y; } a[maxn];
char s[maxn];

inline bool cmp(node a, node b)
{
	if ( a.x * b.y != a.y * b.x )
		return a.x * b.y > a.y * b.x;
	return a.y < b.y;
}

namespace Subtask1
{
	char s[maxn]; int a[maxn], b[maxn];
	inline int main(int n, int q)
	{
		while ( q -- ) 
		{
			int op; scanf("%d", &op);
			scanf("%s", s + 1);
			int m = str(s + 1);
			REP(i, 1, m) a[i] = s[i] - '0';
			if ( op == 1 ) 
			{
				reverse(a + 1, a + m + 1);
				REP(i, 1, m) a[i] *= n;
				REP(i, 1, m) 
				{
					if ( i == m && a[i] >= 10 ) a[++ m] = 0;
					a[i + 1] += a[i] / 10;
					a[i] %= 10;
				}
				for ( int i = m; i >= 1; -- i ) printf("%d", a[i]); puts("");
			}
			else
			{
				int now = 0, x = 0;
				REP(i, 1, m)
				{
					x = x * 10 + a[i];
					if ( x >= n || now ) b[++ now] = x / n;
					x %= n;
				}
				if ( x ) puts("inf");
				else { REP(i, 1, now) printf("%d", b[i]); puts(""); }
			}
		}

		return 0;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q);
	scanf("%s", s + 1);
	bool flag = s[n] == '1';
	REP(i, 1, n - 1) if ( s[i] == '1' ) flag = false;
	if ( flag ) 
	{
		return Subtask1 :: main(n, q);
	}
	int num1 = 0, num2 = 0;
	REP(i, 1, 10000)
	{
		REP(j, 1, n)
		{
			++ num2;
			if ( s[j] == '1' ) ++ num1;	
			a[num2] = {num1, num2};
		}
	}
	sort(a + 1, a + 10000 * n + 1, cmp);
	REP(i, 1, 10000 * n + 1) g[a[i].y] = i;
	while ( q -- ) 
	{
		int op, k; scanf("%d%d", &op, &k);
		if ( op == 1 ) printf("%d\n", a[k].y);
		else 
		{
			if ( g[k] <= 10000 ) printf("%d\n", g[k]);
			else printf("inf\n");
		}
	}
    return 0;
}
