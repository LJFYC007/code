#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define pdd pair<double, double>
#define x first
#define y second

const int maxn = 1e5 + 10;
const double eps = 1e-12;

int n; double C; pdd a[maxn];

inline double Dis(pdd a, pdd b) { return sqrt((double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))); }
inline double Fucku(double x) { return x >= C / 2 ? x - C / 2 : x + C / 2; }
inline int nxt(int x) { return x == n ? 1 : x + 1; }
inline double cross(pdd a, pdd b) { return a.x * b.y - a.y * b.x; } 

inline pdd Get(double len, int &x)
{
	x = 1; while ( len > Dis(a[x], a[nxt(x)]) ) { len -= Dis(a[x], a[nxt(x)]); x = nxt(x); } 
	double d = Dis(a[x], a[nxt(x)]);
	return pdd(a[x].x + len / d * (a[nxt(x)].x - a[x].x), a[x].y + len / d * (a[nxt(x)].y - a[x].y));
}

inline double calc(vector<pdd> p)
{
	double ret = 0;
	for ( int i = 0; i < p.size(); ++ i ) 
		ret += cross(p[i], i == 0 ? p.back() : p[i - 1]);
	return ret;
}

inline double Solve(double len)
{
	int id1, id2; pdd x = Get(len, id1), y = Get(Fucku(len), id2);
	vector<pdd> p; p.push_back(x); 
	int now = id1; while ( now != id2 ) { now = nxt(now); p.push_back(a[now]); } p.push_back(y);
	double ans = calc(p);
	p.clear(); p.push_back(y); 
	now = id2; while ( now != id1 ) { now = nxt(now); p.push_back(a[now]); } p.push_back(x);
	return ans - calc(p);
}

signed main()
{
	freopen("cut.in", "r", stdin);
	freopen("cut.out", "w", stdout);
	scanf("%lld", &n); REP(i, 1, n) scanf("%lf%lf", &a[i].x, &a[i].y);
	REP(i, 1, n) C += Dis(a[i], a[nxt(i)]);
	cout << Solve(1.98) << " " << Solve(1.99) << " " << Solve(2.01) << " " << Solve(2.02) << endl;
	double l, r; if ( Solve(0) < 0 ) l = C / 2, r = C; else l = 0, r = C / 2;
	REP(i, 1, 100)
	{
		double Mid = (l + r) / 2.0;
		if ( Solve(Mid) >= 0 ) l = Mid; else r = Mid;
	}
	int ccc;
	printf("%.9lf %.9lf ", Get(l, ccc).first, Get(l, ccc).second);
	printf("%.9lf %.9lf\n", Get(Fucku(l), ccc).first, Get(Fucku(l), ccc).second);
	return 0;
}
