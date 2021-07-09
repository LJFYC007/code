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

#define ctz __builtin_ctz
#define bcnt __builtin_popcount

template<typename T> inline bool chkmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

#define getc() (getchar())

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

const int maxn = 10, maxla = 510, maxl = 1010;

int n;
string a[maxn + 5];
string b;
int blen;

struct table
{
	int f[maxl + 5][maxl + 5];

	table() { memset(f, 0, sizeof f); }
	table(const string &x) 
	{
		static int dp[maxla + 5][maxl + 5];
		int lx = SZ(x);
		REP(i, 0, blen + 1)
		{
			memset(dp, 0, sizeof dp);
			REP(j, 0, lx + 1)
			{
				REP(k, i, blen + 1)
				{
					if (j > 0) chkmax(dp[j][k], dp[j - 1][k]);
					if (k > i) chkmax(dp[j][k], dp[j][k - 1]);
					if (j > 0 && k > i && x[j - 1] == b[k - 1])
						chkmax(dp[j][k], dp[j - 1][k - 1] + 1);
				}
			}
			REP(k, i, blen + 1)
				f[i][k] = dp[lx][k];
		}
	}

	table reverse() 
	{
		table ret;
		REP(i, 0, blen + 1) REP(j, 0, blen + 1)
			ret.f[i][j] = f[j][i];
		return ret;
	}

	friend table merge(const table &x, const table &y)
	{
		static int best[maxn + 5][maxn + 5];
		table ans;
//		REP(k, 0, blen + 1) REP(i, 0, k + 1) REP(j, k, blen + 1)
//			chkmax(ans.f[i][j], x.f[i][k] + y.f[k][j]);
//		return ans;
		for (int i = blen; i >= 0; --i)
		{
			best[i][i] = i;
			ans.f[i][i] = 0;
			REP(j, i + 1, blen + 1)
			{
				ans.f[i][j] = -1;
				REP(k, best[i][j - 1], best[i + 1][j] + 1)
					if (chkmax(ans.f[i][j], x.f[i][k] + y.f[k][j])) best[i][j] = k;
			}
		}
		return ans;
	}

	friend int query(const table &x, const table &y, int u, int v)
	{
		int ret = -1;
		REP(k, u, v + 1)
			chkmax(ret, x.f[u][k] + y.f[v][k]); // reversed table y to make it more cache-friendly
		return ret;
	}

	void print() const
	{
		REP(i, 0, blen + 1)
		{
			REP(j, 0, blen + 1)
				debug("%d ", f[i][j]);
			debug("\n");
		}
		debug("\n");
	}

};

table single[maxn + 5], single_reversed[maxn + 5];
table le[(1 << (maxn >> 1)) + 5];
table ri[(1 << (maxn >> 1)) + 5];
int qn;

int main()
{
//#ifdef LOCAL
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//#endif
	static char s[1000];
	Read(n);
	REP(i, 0, n)
	{
		scanf("%s", s), a[i] = s;
	}
	scanf("%s", s), b = s;
	blen = SZ(b);

	REP(i, 0, n) single[i] = table(a[i]);
	int half = n >> 1;
	REP(i, 1, 1 << half)
	{
		le[i] = merge(single[ctz(i & (-i))], le[i ^ (i & (-i))]);
	}
	REP(i, 1, 1 << ((n - half)))
		ri[i] = merge(single[half + ctz(i & (-i))], ri[i ^ (i & (-i))]);

	REP(i, 0, 1 << ((n - half)))
		ri[i] = ri[i].reverse(); // reverse ri[i] for faster queries (optional)

	Read(qn);
	REP(i, 0, qn)
	{
		int m, x, y;
		Read(m);
		Read(x);
		Read(y);
		--x;
		printf("%d\n", query(le[m & ((1 << half) - 1)], ri[(m >> half) & ((1 << (n - half)) - 1)], x, y));
	}
	return 0;
}
