#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 5e6 + 10;

int n, m, a[maxn], b[maxn], N, ans;

inline bool Check(int x)
{
	int t = sqrt(x);
	return t * t == x;
}

int main()
{
	freopen("library.in", "r", stdin);
	freopen("library1.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { int x; scanf("%d", &x); ++ a[x]; N = max(N, x); } 
	REP(i, 1, m) { int x; scanf("%d", &x); ++ b[x]; N = max(N, x); } 
	REP(i, 1, N) 
	{
		for ( int j = i; j <= N; j += i ) 
			for ( int k = i; k <= N; k += i ) 
				if ( __gcd(j, k) >= 1 && Check(j * k / i) ) 
					ans += a[j] * b[k];
	}
	printf("%d\n", ans);
	return 0;
}
