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

const int maxn = 1e6 + 10;
const int maxm = 2e5 + 10;
const int INF = 1e9;

int nowx, nowy, ax, ay, bx, by, px, py, n, tot, a[maxn], c[maxn], b, d, Min[maxn][61], Max[maxn][61];
pii Stack[maxn];

inline pii operator -(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); } 
inline int operator *(pii a, pii b) { return a.x * b.y - a.y * b.x; }
inline int len(pii a) { return a.x * a.x + a.y * a.y; } 

inline bool cmp(pii a, pii b)
{
	if ( a.x == 0 && b.x == 0 )
	{
		if ( a.y < 0 && b.y > 0 ) return true;
		if ( a.y > 0 && b.y < 0 ) return false;
		return len(a) < len(b);
	}
	return a * b > 0 || (a * b == 0 && len(a) < len(b));
}

inline void Solve(vector<pii> a)
{
	n = a.size(); pii t = a[0];
	REP(i, 0, n - 1) if ( a[i].x < t.x ) t = a[i];
	REP(i, 0, n - 1) a[i] = a[i] - t;
	sort(a.begin(), a.end(), cmp);
	REP(i, 0, n - 1)
	{
		while ( tot >= 2 && (a[i] - Stack[tot - 1]) * (Stack[tot] - Stack[tot - 1]) >= 0 ) -- tot;
		Stack[++ tot] = a[i];
	}
	int ans = 0; REP(i, 1, tot) ans += abs(Stack[i] * Stack[i == 1 ? tot : i - 1]);
	printf("%lld\n", ans);
}

inline void exgcd(int a, int b, int &x, int &y)
{
	if ( !b ) { x = 1; y = 0; return ; } 
	exgcd(b, a % b, x, y); int t = x; x = y; y = t - a / b * y;
}

vector<pii> p; 
inline void Insert(int m)
{
	int x = nowx, y = nowy; p.push_back(pii(x, y));
	REP(i, 1, min(n, m) - 1)
	{
		x = (x * ax + bx) % px;
		y = (y * ay + by) % py;
		p.push_back(pii(x, y));
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	cin >> nowx >> nowy >> ax >> ay >> bx >> by >> px >> py >> n;
	// if ( n <= 200000 ) { Insert(n); Solve(p); return 0; } 
	Insert(min(px, py));
	memset(a, -1, sizeof(a)); memset(c, -1, sizeof(c));
	while ( a[nowx] == -1 ) { a[nowx] = b; ++ b; nowx = (nowx * ax + bx) % px; } b = b - a[nowx]; 
	while ( c[nowy] == -1 ) { c[nowy] = d; ++ d; nowy = (nowy * ay + by) % py; } d = d - c[nowy];
	int tx = a[nowx], ty = c[nowy];
	
	REP(i, 0, d - 1) { Min[i][0] = INF; Max[i][0] = -INF; } 
	REP(i, 0, py - 1) if ( c[i] >= ty && c[i] < n ) 
	{
		Min[c[i] % d][0] = min(Min[c[i] % d][0], i);
		Max[c[i] % d][0] = max(Max[c[i] % d][0], i);
	}
	REP(j, 1, 60) REP(i, 0, d - 1) 
	{
		Min[i][j] = min(Min[i][j - 1], Min[(i + (1ll << j - 1) % d * b) % d][j - 1]);
		Max[i][j] = max(Max[i][j - 1], Max[(i + (1ll << j - 1) % d * b) % d][j - 1]);
	}

	REP(i, 0, px - 1) if ( a[i] >= tx && a[i] < n ) 
	{
		int pos = a[i] % d, Minn = INF, Maxx = -INF;
		for ( int j = 60; j >= 0; -- j ) 
		{
			__int128 w = (1ll << j); w = w * b + a[i] - b;
			if ( w < n ) 
			{
				Minn = min(Minn, Min[pos][j]); Maxx = max(Maxx, Max[pos][j]);
				a[i] += (1ll << j) * b;
				pos = (pos + (1ll << j) % d * b) % d;
			}
		}
		if ( Minn != INF ) p.push_back(pii(i, Minn)); 
		if ( Maxx != -INF ) p.push_back(pii(i, Maxx));
	}

	Solve(p);
    return 0;
}
