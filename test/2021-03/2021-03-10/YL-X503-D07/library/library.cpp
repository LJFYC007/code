#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;

int n, m, a[maxn], b[maxn], N, s[maxn], prime[maxn], tot, f[maxn], num[maxn], miu[maxn];
long long ans;
bool vis[maxn];
char buf[10000010],*cur=buf+10000010;

char getc(){
    (cur==buf+10000010)?fread(cur=buf,1,10000010,stdin):0;
    return *cur++;
}

inline void read(int &x)
{
	char c = getc(); x = 0;
	while ( c < '0' || c > '9' ) c = getc();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getc(); }
}

signed main()
{
	freopen("library.in", "r", stdin);
	freopen("library.out", "w", stdout);
	read(n); read(m);
	REP(i, 1, n) { int x; read(x); ++ a[x]; N = max(N, x); } 
	REP(i, 1, m) { int x; read(x); ++ b[x]; N = max(N, x); } 

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
	REP(i, 1, N) f[i] = i / f[i];

	REP(d, 1, N) if ( miu[d] ) for ( int t = d; t <= N; t += d ) 
	{
		REP(i, 1, N / t) s[f[i * d]] += a[i * t];
		if ( miu[d] == 1 ) for ( int i = t; i <= N; i += t ) ans += 1ll * b[i] * s[f[i]];
		else for ( int i = t; i <= N; i += t ) ans -= 1ll * b[i] * s[f[i]];
		REP(i, 1, N / t) s[f[i * d]] -= a[i * t];
	}
	printf("%lld\n", ans);
	return 0;
}
