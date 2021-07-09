#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 5e6 + 10;

int n, m, a[maxn], b[maxn], N, ans, s[maxn];
int prime[maxn], tot, f[maxn], num[maxn], miu[maxn];
bool vis[maxn];

inline bool Check(int x)
{
	int t = sqrt(x);
	return t * t == x;
}

int main()
{
	freopen("library.in", "r", stdin);
	freopen("library.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { int x; scanf("%d", &x); ++ a[x]; N = max(N, x); } 
	REP(i, 1, m) { int x; scanf("%d", &x); ++ b[x]; N = max(N, x); } 

	f[1] = miu[1] = 1;
	REP(i, 2, N)
	{
		if ( !vis[i] ) { prime[++ tot] = i; f[i] = num[i] = 1; miu[i] = -1; } 
		for ( int j = 1; j <= tot && i * prime[j] <= N; ++ j ) 
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) 
			{ 
				f[i * prime[j]] = f[i] * (num[i] & 1 ? prime[j] * prime[j] : 1); 
				num[i * prime[j]] = num[i] + 1; miu[i * prime[j]] = 0;
				break ; 
			} 
			f[i * prime[j]] = f[i]; num[i * prime[j]] = 1; miu[i * prime[j]] = -miu[i];
		}
	}

	REP(d, 1, N)
	{
		for ( int i = d; i <= N; i += d ) 
		{		
			int x = i / f[i];
			if ( __gcd(x, d / i) != 1 ) continue ; 
			
		}
	}
	printf("%d\n", ans);
	return 0;
}
