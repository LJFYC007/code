#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

typedef long long LL;
const int mod = 1e9 + 7, maxn = 5e6 + 10, maxk = 60;
using namespace std;

__gnu_pbds::cc_hash_table<LL, int> F;
int k; LL m;

LL read()
{
	LL x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = 0; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return f ? x : -x;
}

void proc_status()
{
	ifstream t("/proc/self/status");
	cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>()) << endl;
}

void add(int &x, int y)
{
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
}

int Pow(int x, int p)
{
	int r = 1;
	while(p)
	{
		if(p & 1) r = (LL)x * r % mod;
		x = (LL)x * x % mod; p >>= 1;
	}
	return r;
}

int f[maxn], vis[maxn], lim, mi[maxn], pri[maxn], cnt, y[maxk];
void init(int N)
{
	lim = N; cnt = 0;
	vis[1] = 1; f[1] = 1;
	for(int i = 2; i <= N; ++i)
	{
		if(!vis[i]) pri[++cnt] = i, mi[cnt] = Pow(i, k), f[i] = mi[cnt] - 1;
		for(int j = 1; j <= cnt && pri[j] * i <= N; ++j)
		{
			vis[pri[j] * i] = 1;
			if(i % pri[j] == 0) { f[i * pri[j]] = (LL)f[i] * mi[j] % mod; break; }
			f[i * pri[j]] = (LL)f[i] * f[pri[j]] % mod;
		}
	}
	for(int i = 2; i <= N; ++i) add(f[i], f[i - 1]);
	for(int i = 1; i <= k + 2; ++i) y[i] = 0, add(y[i], Pow(i, k)), add(y[i], y[i - 1]);
	F.clear();
}

int top, sta[maxn];
vector<pair<int, int> > vec;
void dfs(int dep, int now, int mu, int N)
{
	if(dep > top)
	{
		vec.push_back(make_pair(now, mu));
		return ;
	}
	dfs(dep + 1, now * sta[dep], -mu, N);
	dfs(dep + 1, now, mu, N);
}

void init_g(LL N)
{
	top = 0;
	for(int i = 1; (LL)pri[i] * pri[i] <= N; ++i)
		if(N % pri[i] == 0)
		{
			sta[++top] = pri[i];
			while(N % pri[i] == 0) N /= pri[i];
		}
	if(N != 1) sta[++top] = N;
	vec.clear(); dfs(1, 1, 1, N); sort(vec.begin(), vec.end());
}

int calc_g(LL N)
{
	int Ans = 0;
	for(int i = 0; i < vec.size(); ++i)
	{
		if(vec[i].first > N) break;
		add(Ans, (vec[i].second > 0) ? (N / vec[i].first) % mod : mod - (N / vec[i].first) % mod);
	}
	return Ans;
}

int pre[maxk], suf[maxk], inv[maxk], fac[maxk], ifac[maxk];
int lagrange(LL x, int N)
{
	pre[0] = suf[N + 1] = 1;
	for(int i = 1; i <= N; ++i) pre[i] = (LL)pre[i - 1] * ((x - i) % mod) % mod;
	for(int i = N; i >= 1; --i) suf[i] = (LL)suf[i + 1] * ((x - i) % mod) % mod;

	int ans = 0;
	for(int i = 1; i <= N; ++i)
	{
		int s1 = (LL)pre[i - 1] * suf[i + 1] % mod * y[i] % mod;
		int s2 = (LL)ifac[i - 1] * ifac[N - i] % mod;
		s2 = ((N - i) & 1 ? mod - s2 : s2);
		add(ans, (LL)s1 * s2 % mod);
	}
	return (ans + mod) % mod;
}

int calc(LL N)
{
	if(N <= lim) return f[N];
	if(F.find(N) != F.end()) return F[N];
	int ans = lagrange(N, k + 2);
	for(LL i = 2, j; i <= N; i = j + 1)
	{
		j = N / (N / i);
		add(ans, mod - (LL)(j - i + 1) * calc(N / i) % mod);
	}
	return F[N] = ans;
}

int main()
{
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);

	inv[0] = inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for(int i = 2; i <= 52; ++i)
	{
		fac[i] = (LL)fac[i - 1] * i % mod;
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
		ifac[i] = (LL)ifac[i - 1] * inv[i] % mod;
	}

	int T = 1;
	for(int Case = 1; Case <= T; ++Case)
	{
		k = 0;
		int n = read(); m = read(); int g = 0;
		for(int i = 1; i <= n; ++i)
		{
			int x = read();
			if(x == -1) ++k;
			else g = __gcd(x, g);
		}

		init(min(m, (LL)(5e6))); 

		int ans = 0, lst = 0;
		if(g == 0) { ans = calc(m); goto nxt; }
		init_g(g);
		for(LL i = 1, j; i <= m; i = j + 1)
		{
			j = m / (m / i); int now = calc(j);
			add(ans, (LL)(now - lst) * calc_g(m / i) % mod);
			lst = now;
		}
		nxt:;
		printf("%d\n", ans);
	}
//	proc_status();

	return 0;
}
