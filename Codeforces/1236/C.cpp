#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 50010;

int n, Stack[maxn], tot;
struct node
{
	int id, a, b, c;
	bool flag;
	bool operator < (const node &x) { return c < x.c || (c == x.c && (b < x.b || (b == x.b && a < x.a))); }
} a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c); a[i].id = i; a[i].flag = false; }
	sort(a + 1, a + n + 1);
	for ( int i = 1; i <= n; ++ i )
	{
		int L = i, R = i;
		while ( a[R + 1].c == a[i].c && R + 1 <= n ) ++ R;
		for ( int j = L; j <= R; ++ j )
		{
			int l = j, r = j;
			while ( a[r + 1].b == a[j].b && r < R ) ++ r;
			for ( int k = l; k < r; k += 2 )
			{
				a[k].flag = a[k + 1].flag = true;
				printf("%d %d\n", a[k].id, a[k + 1].id);
			}
			j = r;
		}
		tot = 0;
		REP(j, L, R)
		{
			if ( !a[j].flag ) Stack[++ tot] = j;
			if ( tot >= 2 )
			{
				a[Stack[tot - 1]].flag = true;
				a[Stack[tot]].flag = true;
				printf("%d %d\n", a[Stack[tot - 1]].id, a[Stack[tot]].id);
				tot -= 2;
			}
		}
		i = R;
	}
	tot = 0;
	REP(i, 1, n)
	{
		if ( !a[i].flag ) Stack[++ tot] = a[i].id;
		if ( tot >= 2 ) { printf("%d %d\n", Stack[tot - 1], Stack[tot]); tot -= 2; }
	}
	return 0;
}
