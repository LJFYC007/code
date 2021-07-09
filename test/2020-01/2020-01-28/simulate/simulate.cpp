#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e7 + 10;

int a[maxn], n, ans[maxn], Stack[maxn], tot;
char s[maxn];

int main()
{
	freopen("simulate.in", "r", stdin);
	freopen("simulate.out", "w", stdout);
	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, n) a[i] = s[i] - '0';
	REP(i, 1, n)
	{
		while ( a[i] >= 2 )
		{
			if ( !tot ) Stack[++ tot] = 0;
			int x = Stack[tot -- ];
			int len = i - x - 1, Min = min(a[i] - 1, len);
			a[i] -= Min; a[i + 1] += Min;
			x += Min;
			if ( a[i] < 2 ) { Stack[++ tot] = x; break ; }
			if ( x == i - 1 ) { a[i] -= 2; ++ a[i + 1]; }
		}
		if ( a[i] == 0 ) Stack[++ tot] = i;
	}
	REP(i, 1, tot) ans[Stack[i]] = -1;
	REP(i, 1, n) s[i] = ans[i] == -1 ? '0' : '1';
	printf("%s\n", s + 1);
	return 0;
}
