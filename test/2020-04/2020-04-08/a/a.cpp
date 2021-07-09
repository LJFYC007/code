#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int n, m, k, a[maxn], last = 1, tot = 1, f[maxn], ans;
struct node { int Next[26], len, fa; } Tree[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int x)
{
	int L = Tree[Tree[x].fa].len, R = Tree[x].len;
	return (f[R] - f[L]) % Mod;
}

inline void Expand(int c)
{
	int cur = ++ tot; Tree[cur].len = Tree[last].len + 1;
	int p = last; last = cur;
	while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
	if ( !p ) { Tree[cur].fa = 1; ans = (ans + Get(cur)) % Mod; return ; }
	int q = Tree[p].Next[c];
	if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; ans = (ans + Get(cur)) % Mod; return ; }
	int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
	while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
	Tree[q].fa = Tree[cur].fa = clone;
	ans = (ans + Get(cur)) % Mod;
}

signed main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	scanf("%s", s + 1);
	REP(i, 0, k) scanf("%lld", &a[i]);
	REP(i, 1, m + str(s + 1))
	{
		f[i] = (n - i + 1) * power(power(26, i), Mod - 2) % Mod;
		int sum = 0, x = 1;
		REP(j, 0, k)
		{
			sum = (sum + a[j] * x) % Mod;
			x = x * i % Mod;
		}
		f[i] = f[i] * sum % Mod;
		if ( i > n ) f[i] = 0;
		f[i] = (f[i] + f[i - 1]) % Mod;
	}
	REP(i, 1, str(s + 1)) Expand(s[i] - 'a');
	printf("%lld\n", ((ans + Mod) % Mod) * 10000 % Mod);
	REP(i, 1, m)
	{
		scanf("%s", s + 1);
		Expand(s[1] - 'a');
		printf("%lld\n", ((ans + Mod) % Mod) * 10000 % Mod);
	}
	return 0;
}
