#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int a[maxn];

int main()
{
	freopen("bubble.in", "w", stdout);
	srand(time(0));
	int n = 100, m = 100;
	printf("%d %d\n", n, m);
	REP(i, 1, n) a[i] = i;
	random_shuffle(a + 1, a + n + 1);
	REP(i, 1, n) printf("%d ", a[i]); puts("");
	REP(i, 1, m)
	{
		int t = rand() % 2 + 1;
		int x = rand() % n;
		if ( t == 1 ) printf("%d %d\n", t, x == 0 ? 1 : x);
		else printf("%d %d\n", t, x);
	}
	return 0;
}
