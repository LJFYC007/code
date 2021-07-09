/***************************************************************
	File name: CF605E.cpp
	Author: ljfcnyali
	Create time: 2021年02月20日 星期六 15时59分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const double INF = 1e18;

int n;
double a[maxn][maxn], f[maxn], sum, val1[maxn], val2[maxn], now[maxn];
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) REP(j, 1, n) { scanf("%lf", &a[i][j]); a[i][j] /= 100; }
	sum = 1; vis[n] = true;
	REP(i, 1, n) { val1[i] = 1; val2[i] = a[i][n]; now[i] = 1 - a[i][n]; }
	REP(o, 2, n)
	{
		double Min = INF; int pos = 0;
		REP(i, 1, n) if ( !vis[i] && val1[i] / val2[i] < Min ) { Min = val1[i] / val2[i]; pos = i; } 
	 	vis[pos] = true; f[pos] = Min;
		REP(i, 1, n) if ( !vis[i] ) 
		{
			val1[i] += now[i] * a[i][pos] * f[pos];
			now[i] = now[i] * (1 - a[i][pos]);
			val2[i] = 1 - now[i];
		}
	}
	printf("%.6lf\n", f[1]);
    return 0;
}
