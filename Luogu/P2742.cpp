/***************************************************************
	File name: P2742.cpp
	Author: ljfcnyali
	Create time: 2021年04月07日 星期三 11时06分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e9;

int n, tot;
double ans;
pii a[maxn], Stack[maxn];

inline pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); } 
inline pii operator - (pii a, pii b) { return pii(a.x - b.x, a.y - b.y); } 
inline double operator * (pii a, pii b) { return a.x * b.y - a.y * b.x; } 
inline double len(pii a) { return sqrt(a.x * a.x + a.y * a.y); }

inline bool cmp(pii a, pii b) { return a * b > 0 || (a * b == 0 && len(a) < len(b)); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); pii t = pii(INF, INF);
	REP(i, 1, n) { scanf("%lf%lf", &a[i].x, &a[i].y); if ( a[i].x < t.x ) t = a[i]; } 
	REP(i, 1, n) a[i] = a[i] - t;	
	sort(a + 1, a + n + 1, cmp);
	REP(i, 1, n)
	{
		while ( tot >= 2 && (a[i] - Stack[tot - 1]) * (Stack[tot] - Stack[tot - 1]) >= 0 ) -- tot;
		Stack[++ tot] = a[i];
	}
	REP(i, 1, tot) ans += len(Stack[i] - Stack[i == 1 ? tot : i - 1]);
	printf("%.2lf\n", ans);
    return 0;
}
