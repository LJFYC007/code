/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2021年04月08日 星期四 08时52分43秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;
 
const int maxn = 5e6 + 10;
const int INF = 1e9;
 
int x[maxn], y[maxn], ax, ay, bx, by, px, py, n, tot, yMin[maxn], yMax[maxn];
pii Stack[maxn];
 
inline pii operator -(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); } 
inline int operator *(pii a, pii b) { return a.x * b.y - a.y * b.x; }
inline int len(pii a) { return a.x * a.x + a.y * a.y; } 
 
inline void Solve(vector<pii> a)
{
    n = a.size(); pii t = a[0];
    REP(i, 0, n - 1) if ( a[i].x < t.x ) t = a[i];
    REP(i, 0, n - 1) a[i] = a[i] - t;
    sort(a.begin(), a.end(), [](const pii &a, const pii &b) { return a * b > 0 || (a * b == 0 && len(a) < len(b)); });
    REP(i, 0, n - 1)
    {
        while ( tot >= 2 && (a[i] - Stack[tot - 1]) * (Stack[tot] - Stack[tot - 1]) >= 0 ) -- tot;
        Stack[++ tot] = a[i];
    }
    int ans = 0; REP(i, 1, tot) ans += abs(Stack[i] * Stack[i == 1 ? tot : i - 1]);

	REP(i, 1, tot) 
	{
		Stack[i] = pii(Stack[i].x + t.x, Stack[i].y + t.y);
		// cout << Stack[i].first << " " << Stack[i].second << endl;
	}
    printf("%lld\n", ans);
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    cin >> x[0] >> y[0] >> ax >> ay >> bx >> by >> px >> py >> n;
    REP(i, 1, n - 1) { x[i] = (x[i - 1] * ax + bx) % px; y[i] = (y[i - 1] * ay + by) % py; }
	REP(i, 0, px - 1) yMin[i] = INF, yMax[i] = -INF;
	REP(i, 0, n - 1) yMin[x[i]] = min(yMin[x[i]], y[i]), yMax[x[i]] = max(yMax[x[i]], y[i]);
	REP(i, 0, px - 1) if ( yMin[i] != INF ) cout << i << " " << yMin[i] << " " << yMax[i] << endl;
	REP(i, 0, n - 1) printf("%lld ", x[i]); puts("");
	REP(i, 0, n - 1) printf("%lld ", y[i]); puts("");
    vector<pii> p; REP(i, 0, n - 1) p.push_back(pii(x[i], y[i])); Solve(p);
    return 0;
}
