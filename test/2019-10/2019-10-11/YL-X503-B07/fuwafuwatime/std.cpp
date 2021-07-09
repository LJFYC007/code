#ifndef K_ON
#define K_ON
#endif

#include <bits/stdc++.h>

using namespace std;

#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define fst first
#define snd second
#define SZ(u) ((int) (u).size())
#define ALL(u) (u).begin(), (u).end()

inline void proc_status()
{
	ifstream t("/proc/self/status");
	cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>()) << endl;
}

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T> inline T read()
{
	register T sum(0), fg(1);
	register char ch(getchar());
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') fg = -1;
	for(;  isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ '0');
	return sum * fg;
}

typedef long long LL;
typedef pair<int, int> pii;

const int MOD = 9990017;

LL n, m, B;

inline void input()
{
	n = read<LL>(), m = read<LL>(), B = read<LL>();
}

inline int fpm(int x, int y)
{
	int res = 1;
	for(; y; y >>= 1, x = (LL) x * x % MOD) if(y & 1) res = (LL) res * x % MOD;
	return res;
}

const int MAXN = (int) pow(1e10, 2.0 / 3);

int fac[MOD], ifac[MOD];
int pre_f0[MAXN + 5];

inline int C0(LL N, LL M) { return N < M ? 0 : (LL) fac[N] * ifac[N - M] % MOD * ifac[M] % MOD; }
inline int C(LL N, LL M) { return N < M ? 0 : (LL) C0(N % MOD, M % MOD) * (N >= MOD ? C(N / MOD, M / MOD) : 1) % MOD; }

inline void MATH_init()
{
	fac[0] = 1;
	for(int i = 1; i < MOD; ++i) fac[i] = (LL) fac[i - 1] * i % MOD;
	ifac[MOD - 1] = fpm(fac[MOD - 1], MOD - 2);
	for(int i = MOD - 2; i >= 0; --i) ifac[i] = (LL) ifac[i + 1] * (i + 1) % MOD;

	for(int i = 1; i <= MAXN; ++i) pre_f0[i] = C(i, B);
	for(int i = 1; i <= MAXN; ++i)
		for(int j = i * 2; j <= MAXN; j += i)
			(pre_f0[j] -= pre_f0[i]) %= MOD;

	for(int i = 1; i <= MAXN; ++i) (pre_f0[i] += pre_f0[i - 1]) %= MOD;
}

unordered_map<LL, int> pre_f;

inline int S(LL N)
{
	if(N <= MAXN) return pre_f0[N];
	if(pre_f.count(N)) return pre_f[N];
	int res = C(N + 1, B + 1);
	for(LL i = 2, j; i <= N; i = j + 1)
	{
		j = N / (N / i);
		res -= (LL) S(N / i) * (j - i + 1) % MOD;
		res = res < 0 ? res + MOD : res;
	}
	return pre_f[N] = res;
}

inline void solve()
{
	MATH_init();

	int ans = 0;
	for(LL i = 1, j; i <= min(n, m); i = j + 1)
	{
		j = min(n / (n / i), m / (m / i));
        printf("%d %d\n", S(j), S(i - 1));
		(ans += (LL) (S(j) - S(i - 1)) % MOD * (n / i) % MOD * (m / i) % MOD) %= MOD;
	}
	printf("%d\n", (ans + MOD) % MOD);
}

int main()
{
#ifdef K_ON
	freopen("fuwafuwatime.in", "r", stdin);
	freopen("fuwafuwatime.ans", "w", stdout);
#endif

	input();
	solve();

	return 0;
}


