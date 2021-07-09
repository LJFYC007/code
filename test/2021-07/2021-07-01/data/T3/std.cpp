#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int __buffsize = 100000;
char __buff[__buffsize];
char *__buffs, *__buffe;

#define getc() (__buffs == __buffe ? fread(__buff, 1, __buffsize, stdin), __buffe = __buff + __buffsize, *((__buffs = __buff)++) : *(__buffs++))

template<typename T> inline T &Read(T &x)
{
	static char c;
	while (1) 
	{ 
		c = getc(); 
		if (c == '-' || (c >= '0' && c <= '9')) break; 
	}
	bool flag = c == '-';
	x = flag ? 0 : c - '0';
	while (1)
	{
		c = getc();
		if (c < '0' || c > '9') break;
		(x *= 10) += c - '0';
	}
	if (flag) x = -x;
	return x;
}

#undef getc

const int maxn = 1001000, maxk = 1001000;

int n;
int a[maxn + 5];

vector<int> p[maxn + 5];
int lis[maxn + 5];

int m;
int qn;
int K;

double ans;
double dp[maxn + 5];

double Log[maxn + maxk + 5];

inline double eval(int x, int y)
{
	if (y <= a[x]) return -1e100;
	return dp[x] + Log[y - a[x] + K];
}

inline int intersection(int x, int y)
{
	// dp[x] + log(u - a[x] + K) > dp[y] + log(u - a[y] + K)
	// log(u - a[x] + K) - log(u - a[y] + K) > dp[y] - dp[x]
	// (u - a[x] + K) / (u - a[y] + K) > exp(dp[y] - dp[x])
	// (u - a[x] + K) > (u - a[y] + K) * exp(dp[y] - dp[x])
	// (1 - exp(dp[y] - dp[x])) u > a[x] - K - (a[y] - K) * exp(dp[y] - dp[x]);
	if (dp[y] >= dp[x]) return n;
	double tmp = exp(dp[y] - dp[x]);
	int inter = min((double)n, ((a[x] - K) - (a[y] - K) * tmp) / (1 - tmp)) + .5;
	if (inter == n) return n;
	chkmax(inter, max(a[x], a[y]) + 1);
	return eval(x, inter) > eval(y, inter) ? inter : inter + 1;
}

vector<pair<int, int> > q[maxn + 5];
int cur_best[maxn + 5];

inline void work()
{
	ans = 0;
	vector<pair<int, int> > lst;
	REP(i, 1, n + 1) q[i].clear(), cur_best[i] = 0;
	REP(i, 0, n)
	{
		if (lis[i] > 1)
		{
			while (cur_best[lis[i] - 1] + 1 < SZ(q[lis[i] - 1]) && q[lis[i] - 1][cur_best[lis[i] - 1] + 1].y > a[i]) 
			{
				++cur_best[lis[i] - 1];
			}
			dp[i] = eval(q[lis[i] - 1][cur_best[lis[i] - 1]].x, a[i]);
		}
		else dp[i] = 0;
		if (lis[i] == m) chkmax(ans, dp[i]);

		int tmp = oo;
		while (!q[lis[i]].empty())
		{
			if (q[lis[i]].back().y > (tmp = intersection(q[lis[i]].back().x, i))) break;
			q[lis[i]].pop_back();
		}
		q[lis[i]].pb(mp(i, tmp));
		chkmin(cur_best[lis[i]], SZ(q[lis[i]]) - 1);
	}
}

int main()
{
//#ifdef LOCAL
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//#endif
	REP(i, 0, maxn + maxk + 1)
		Log[i] = log(i);
	Read(n);
	REP(i, 0, n) Read(a[i]), --a[i];
	m = 0;
	REP(i, 0, n)
	{
		int l = 0, r = n - 1;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (p[mid].empty() || a[p[mid].back()] > a[i]) r = mid - 1;
			else l = mid;
		}
		lis[i] = l + 1;
		p[lis[i]].pb(i);
		chkmax(m, lis[i]);
	}
	printf("%d\n", m);
	Read(qn);
	REP(i, 0, qn)
	{
		Read(K);
		work();
		printf("%.15f\n", ans);
	}
	return 0;
}
