#include<bits/stdc++.h>

using namespace std;
#define rint register int
#define REP(i, a, b) for ( rint i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)

const double eps = 0.0000000001;
int n, m, k;

namespace Subtask1
{
	const int maxn = 500010;
	
	int y[maxn], c[maxn], a[maxn], s[maxn], z[maxn];
	
	inline void Solve()
	{
		REP(i, 1, m) scanf("%d", &y[i]);
		REP(i, 1, k - 1) scanf("%d", &c[i]);
		REP(i, 1, k) scanf("%d%d%d", &a[i], &s[i], &z[i]);
		int last = 0; double ans = 0;
		REP(i, 1, k)
		{
			double x = y[s[i]];
			if ( last ) x = x * (1 - c[i - last] * 1.0 / 100);
			x = 1 - (x * 1.0) / z[i];
			x = max(x, (double)0); x = 1 - x * x;
			if ( x < 0.64 + eps ) last = i;
			ans += x * a[i];
		}
		printf("%.2lf\n", ans);
	}
}

namespace Subtask2
{
	const int maxn = 110;
	const int maxm = 1100;
	const int INF = 0x3f3f3f3f;
	
	double dp[maxm][maxn][maxn], f[maxm][maxm];
	int x[maxn], y[maxn], c[maxn], a[maxn], ss[maxn], z[maxn];
    template<class T> double maxx(T a, T b) { return a > b ? a : b; }
#define max maxx
	
	inline void Solve()
	{
		REP(i, 1, n) scanf("%d", &x[i]);
		REP(i, 1, m) scanf("%d", &y[i]);
		REP(i, 1, k - 1) scanf("%d", &c[i]);
		REP(i, 1, k) scanf("%d%d%d", &a[i], &ss[i], &z[i]);
		int num = 1 << n;
        REP(s, 0, num - 1)
            for ( rint S = s; ; S = (S - 1) & s)
            {
                f[s][S] = 1;
                REP(j, 1, n)
			        if ( ((1 << (j - 1)) & s) && !((1 << (j - 1)) & S) ) f[s][S] = f[s][S] * (1 + x[j] / 100.0);
                if ( S == 0 ) break ;
            }
        int now = 0;
        REP(i, 0, num - 1) REP(j, 0, k) dp[i][now][j] = -INF;
        dp[0][0][0] = 0;
		REP(i, 1, k)
        {
            now ^= 1;
            REP(j, 0, num - 1) REP(o, 0, k) dp[j][now][o] = -INF;
            for ( rint s = 0; s != num; ++ s )
                for ( rint S = s; ; S = (S - 1) & s)
				{
					double p = y[ss[i]] * f[s][S], tmp = a[i] * 0.64;
                    for ( rint j = 0; j < i; ++ j )
					{
						if ( dp[S][now ^ 1][j] != -0x3f3f3f3f )
                        {
		    				double q = p;
			    			if ( j != 0 ) q = q * (1 - c[i - j] / 100.0);
				    		q = max((double)0, 1 - q / z[i]); q = (1 - q * q) * a[i];
					    	if ( q < tmp ) dp[s][now][i] = max(dp[s][now][i], dp[S][now ^ 1][j] + q);
						    else dp[s][now][j] = max(dp[s][now][j], dp[S][now ^ 1][j] + q);
                        }
					}
					if ( S == 0 ) break ; 
				}
        }
		double ans = 0;
		REP(i, 0, k) ans = max(ans, dp[num - 1][now][i]);
		printf("%.2lf\n", ans);
	}
}

int main()
{
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);	
	if ( n == 0 ) { Subtask1 :: Solve(); return 0; }
	Subtask2 :: Solve();
	return 0;
}

