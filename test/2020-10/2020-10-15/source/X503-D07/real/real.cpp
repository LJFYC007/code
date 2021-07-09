/***************************************************************
	File name: real.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 10时08分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const double eps = 1e-9;
const double INF = 1e18;

int n, ans, a[maxn];
char s[maxn];
double f, Min = INF;
struct node { double x, y; int id; } point[maxn];

signed main()
{
    freopen("real.in", "r", stdin);
    freopen("real.out", "w", stdout);
    scanf("%lf", &f);
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) 
    {
        a[i] = a[i - 1] + s[i] - '0';
        point[i].x = i;
        point[i].y = f * i - a[i];
        point[i].id = i;
    }
    sort(point + 1, point + n + 1, [](node &a, node &b) { return a.y < b.y; });
    REP(i, 2, n) 
    {
        double slope = (point[i].y - point[i - 1].y) / (point[i].x - point[i - 1].x);
        if ( abs(slope) < Min - eps ) { Min = abs(slope); ans = min(point[i].id, point[i - 1].id); }
        else if ( abs(slope) < Min + eps ) ans = min(ans, min(point[i].id, point[i - 1].id)); 
    }
    printf("%lld\n", ans);
    return 0;
}
