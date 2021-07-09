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
const int INF = 1e9;

int nowx, nowy, ax, ay, bx, by, px, py, n, tot, a[maxn], c[maxn], b, d;
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
	REP(i, 1, min(n, m))
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
	Insert(min(px, py));
	memset(a, -1, sizeof(a)); memset(c, -1, sizeof(c));
	while ( a[nowx] == -1 ) { a[nowx] = b; ++ b; nowx = (nowx * ax + bx) % px; } b = b - a[nowx]; 
	while ( c[nowy] == -1 ) { c[nowy] = d; ++ d; nowy = (nowy * ay + by) % py; } d = d - c[nowy];
	int tx = a[nowx], ty = c[nowy];

	// cout << tx << " " << ty << endl;
	// REP(i, 0, px - 1) cout << a[i] << " "; cout << endl;
	REP(i, 0, px - 1) if ( a[i] >= tx && ty > a[i] ) a[i] += max(0ll, (ty - a[i] - 1) / b + 1) * b;
	REP(i, 0, py - 1) if ( c[i] >= ty && tx > c[i] ) c[i] += max(0ll, (tx - c[i] - 1) / d + 1) * d;
	REP(i, 0, px - 1) cout << a[i] << " "; cout << endl;
	REP(i, 0, py - 1) cout << c[i] << " "; cout << endl;

	int x0, y0, D = __gcd(b, d); b /= D; d /= D; exgcd(b, d, x0, y0); 
	cout << x0 << " " << y0 << " " << b << " " << d << endl;
	x0 = (x0 % d + d) % d; y0 = (y0 % b + b) % b;

	REP(i, 0, px - 1) if ( a[i] >= tx ) 
	{
		int Min = INF, Max = -INF;
		REP(j, 0, py - 1) if ( c[j] >= ty && c[j] >= a[i] ) 
		{
			if ( (a[i] - c[j]) % D != 0 ) continue ; 
			int t = b * x0 * (c[j] - a[i]) + a[i];
			if ( i == 0 && j == 1 ) cout << t << endl;
			if ( t < n ) { Min = min(Min, j); Max = max(Max, j); }
		}
		if ( Min != INF ) p.push_back(pii(i, Min));
		if ( Max != -INF ) p.push_back(pii(i, Max));
		cout << i << " " << Min << " " << Max << endl;
	}
	
	REP(i, 0, py - 1) if ( c[i] >= ty ) 
	{
		int Min = INF, Max = -INF;
		REP(j, 0, px - 1) if ( a[j] >= tx && a[j] >= c[i] ) 
		{
			if ( (a[i] - c[j]) % D != 0 ) continue ; 
			int t = d * y0 * (a[j] - c[i]) + c[i];
			// if ( i == 1 && j == 0 ) cout << t << endl;
			if ( t < n ) { Min = min(Min, j); Max = max(Max, j); }
		}
		if ( Min != INF ) p.push_back(pii(Min, i));
		if ( Max != -INF ) p.push_back(pii(Max, i));
		cout << i << " " << Min << " " << Max << endl;
	}

	Solve(p);
    return 0;
}
