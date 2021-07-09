/***************************************************************
	File name: rhombus.cpp
	Author: ljfcnyali
	Create time: 2019年09月17日 星期二 18时48分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 3010;

int a[maxn][maxn], n, m, h, ty;
int l[maxn][maxn], r[maxn][maxn], ans = -10000000000000;
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn];

namespace Data_Maker
{
	int Seed,A,b,c,MOD;
	int Random() {
		c++;
		Seed=(Seed*A+b*c)%MOD;
		return Seed;
	}
	int Random_int() {
		int tmp=Random();
		if(Random()&1)tmp*=-1;
		return tmp;
	}
	void MAKE(){
		scanf("%lld%lld%lld%lld%lld",&Seed,&A,&b,&c,&MOD);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			    a[i][j]=Random_int();
    }
}

inline int DFS(int x, int y, int X, int Y)
{
    // cerr << x << " " << y << " " << X << " " << Y << endl;
    int sum = a[x][y];
    REP(i, 0, 3)
    {
        int u = x + dt[i][0], v = y + dt[i][1];
        if ( u < 1 || v < 1 || u > n || v > m || vis[u][v] ) continue ;
        if ( abs(u - X) + abs(v - Y) >= h ) continue ;
        vis[u][v] = true; sum += DFS(u, v, X, Y);
    }
    return sum;
}

signed main()
{
    freopen("rhombus.in", "r", stdin);
    freopen("rhombus.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &h, &ty);
    if ( ty == 1 ) Data_Maker :: MAKE();
    else REP(i, 1, n) REP(j, 1, m) scanf("%lld", &a[i][j]);
    // REP(i, 1, n) { REP(j, 1, m) printf("%lld ", a[i][j]); puts(""); }
    REP(i, h, m)
    {
        int x = 1, y = i; l[1][i] = a[x][y];
        REP(j, 1, h - 1) { ++ x; -- y; l[1][i] += a[x][y]; }
    }
    REP(i, 2, n - h + 1)
    {
        REP(j, h, m - 1) l[i][j] = l[i - 1][j + 1] - a[i - 1][j + 1] + a[i + h - 1][j - h + 1];
        int x = i, y = m; l[x][y] = a[x][y];
        REP(j, 1, h - 1) { ++ x; -- y; l[i][m] += a[x][y]; }
    }
    // REP(i, 1, n) { REP(j, 1, m) printf("%lld ", l[i][j]); puts(""); }
    REP(i, 1, m - h + 1)
    {
        int x = 1, y = i; r[1][i] = a[x][y];
        REP(j, 1, h - 1) { ++ x; ++ y; r[1][i] += a[x][y]; }
    }
    REP(i, 2, n - h + 1)
    {
        REP(j, 2, m - h + 1) r[i][j] = r[i - 1][j - 1] - a[i - 1][j - 1] + a[i + h - 1][j + h - 1];
        int x = i, y = 1; r[x][y] = a[x][y];
        REP(j, 1, h - 1) { ++ x; ++ y; r[i][1] += a[x][y]; }
    }
    // puts("");
    // REP(i, 1, n) { REP(j, 1, m) printf("%lld ", r[i][j]); puts(""); }
    vis[h][h] = true; int sum1 = DFS(h, h, h, h), sum2;
    REP(i, h, n - h + 1)
    {
        if ( i > h ) 
        {
            int x = i - 1, y = h;
            sum1 = sum1 - l[x - h + 1][y] - r[x - h + 1][y] + r[x + 1][y - h + 1] + l[x + 1][y + h - 1];
            sum1 = sum1 + a[x - h + 1][y] - a[x + h][y];
        }
        ans = max(ans, sum1); sum2 = sum1;
        // printf("%lld %lld %lld %lld\n", i, h, sum1, a[i][h] + DFS(i, h, i, h));
        REP(j, h, m - h)
        {
            int x = i, y = j;
            sum2 = sum2 - l[x - h + 1][y] + r[x - h + 1][y + 1] - r[x][y - h + 1] + l[x][y + h];
            sum2 = sum2 + a[x][y - h + 1] - a[x][y + h];
            ans = max(ans, sum2);
            // printf("%lld %lld %lld %lld\n", i, j + 1, sum2, a[i][j + 1] + DFS(i, j + 1, i, j + 1));
        }
    }
    printf("%lld\n", ans);
    return 0;
}
