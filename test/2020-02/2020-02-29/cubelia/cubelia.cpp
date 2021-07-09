#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<LL, LL>
typedef long long LL;

const LL maxn = 2e6 + 10;
const LL Mod = 998244353;

LL n, q, a[maxn], b[maxn], suf[maxn], pre[maxn], sum[maxn], Log[maxn], s1[maxn], s2[maxn];
LL st1[maxn][22], st2[maxn][22], ans, Ans;
int S, A, B, P, tp;
struct node { LL val, l, r; node(LL a = 0, LL b = 0, LL c = 0) { val = a; l = b; r = c; } } ;
stack<node> Stack;

inline int Rand()
{
	S = (S * A % P + (B ^ (tp * ans))) % P;
	S = S < 0 ? -S : S;
	return S;
}

inline LL Get(LL l, LL r)
{
	LL len = Log[r - l + 1];
	return st1[l][len] > st1[r - (1 << len) + 1][len] ? st2[l][len] : st2[r - (1 << len) + 1][len];
}

inline LL Solve1(LL l, LL r)
{
	if ( l > r ) return 0;
	return suf[r + 1] * (r - l + 1);
}

inline LL Solve2(LL l, LL r)
{
	if ( l > r ) return 0;
	return pre[l - 1] * (r - l + 1);
}

signed main()
{
	freopen("cubelia.in", "r", stdin);
	freopen("cubelia.out", "w", stdout);
	scanf("%lld%lld", &n, &q);
	REP(i, 1, n) { scanf("%lld", &a[i]); a[i] += a[i - 1]; st1[i][0] = a[i]; st2[i][0] = i; b[i] = b[i - 1] + a[i]; }
	scanf("%d%d%d%d%d", &S, &A, &B, &P, &tp);

	Log[1] = 0; Log[2] = 1; REP(i, 3, n) Log[i] = Log[i >> 1] + 1;
	REP(j, 1, 21) REP(i, 1, n)
	{
		if ( i + (1 << j - 1) > n ) break ;
		st1[i][j] = max(st1[i][j - 1], st1[i + (1 << j - 1)][j - 1]);
		st2[i][j] = st1[i][j - 1] > st1[i + (1 << j - 1)][j - 1] ? st2[i][j - 1] : st2[i + (1 << j - 1)][j - 1];
	}
	for ( LL i = n; i >= 0; -- i ) sum[i] = sum[i + 1] + (n - i + 1) * a[i];
	LL ret = 0;
	for ( LL i = n; i >= 1; -- i )
	{
		while ( !Stack.empty() && a[i] > Stack.top().val )
		{
			ret -= Stack.top().val * (Stack.top().r - Stack.top().l + 1);
			Stack.pop();
		}
		LL L = i, R = Stack.empty() ? n : Stack.top().l - 1;
		ret += a[i] * (R - L + 1); suf[i] = ret;
		s2[i] = s2[i + 1] + suf[i];
		Stack.push(node(a[i], L, R));
	}
	ret = 0; while ( !Stack.empty() ) Stack.pop();
	REP(i, 1, n)
	{
		while ( !Stack.empty() && a[i] > Stack.top().val )
		{
			ret -= Stack.top().val * (Stack.top().r - Stack.top().l + 1);
			Stack.pop();
		}
		LL L = Stack.empty() ? 1 : Stack.top().r + 1, R = i;
		ret += a[i] * (R - L + 1); pre[i] = ret;
		s1[i] = s1[i - 1] + pre[i];
		Stack.push(node(a[i], L, R));
	}

	while ( q -- )
	{
		LL l = Rand() % n + 1, r = Rand() % n + 1;
		if ( l > r ) swap(l, r);
		LL ret = sum[l - 1] - sum[r] - (b[r - 1] - b[l > 1 ? l - 2 : 0]) * (n - r + 1);
		LL pos = Get(l, r);
		ans = (pos - l + 1) * (r - pos + 1) * a[pos];
		ans += s2[l] - s2[pos] + s1[r] - s1[pos];
		ans -= Solve1(l, pos - 1) + Solve2(pos + 1, r);
		ans -= ret;
		Ans = (Ans + ans) % Mod;
	}
	printf("%lld\n", (Ans + Mod) % Mod);
	return 0;
}
