/***************************************************************
	File name: CF666D.cpp
	Author: ljfcnyali
	Create time: 2021年04月28日 星期三 16时58分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5;
const int INF = 0x3f3f3f3f;

int T, ret, now, p[maxn], q[maxn], f[maxn]; pii a[maxn], b[maxn], ans[maxn];
map<int, bool> Mapx, Mapy;

inline void Fuck()
{
	int Minx = INF, Miny = INF, Maxx = -INF, Maxy = -INF;
	REP(i, 1, 4) { Minx = min(Minx, b[p[i]].x); Miny = min(Miny, b[p[i]].y); Maxx = max(Maxx, b[p[i]].x); Maxy = max(Maxy, b[p[i]].y); } 
	int num1 = 0, num2 = 0;
	REP(i, 1, 4) 
	{
		if ( b[i].x == Minx ) ++ num1; if ( b[i].y == Miny ) ++ num2;
		if ( b[i].x != Minx && b[i].x != Maxx ) return ;
		if ( b[i].y != Miny && b[i].y != Maxy ) return ;
	}
	if ( num1 != 2 || num2 != 2 || Maxx - Minx != Maxy - Miny ) return ;
	now = 0;
	REP(i, 1, 4) 
	{
		if ( a[i].x != b[p[i]].x && a[i].y != b[p[i]].y ) return ; 
		if ( a[i].x != b[p[i]].x ) now = max(now, abs(a[i].x - b[p[i]].x));
		if ( a[i].y != b[p[i]].y ) now = max(now, abs(a[i].y - b[p[i]].y));
	}
	if ( now >= ret ) return ; 
	ret = now; REP(i, 1, 4) ans[i] = b[p[i]];
}

inline void Maintain()
{
	REP(i, 1, 4) p[i] = i;
	do { Fuck(); } while ( next_permutation(p + 1, p + 4 + 1) );
}

inline void Solve()
{
	REP(i, 0, (1 << 4) - 1)
	{
		Mapx.clear(); Mapy.clear();
		REP(j, 1, 4) if ( (i >> j - 1) & 1 ) Mapx[a[j].x] = true; else Mapy[a[j].y] = true;
		vector<int> px, py;
		for ( auto it : Mapx ) px.push_back(it.first);
		for ( auto it : Mapy ) py.push_back(it.first);
		if ( px.size() > 2 || py.size() > 2 ) continue ; 
		if ( px.size() == 2 && py.size() == 2 ) 
		{ 
			b[1] = pii(px[0], py[0]); b[2] = pii(px[0], py[1]);
			b[3] = pii(px[1], py[0]); b[4] = pii(px[1], py[1]);
			Maintain();
		} 
		if ( px.size() == 2 && py.size() == 1 ) 
		{
			int x = px[1] - px[0], y = py[0];
			b[1] = pii(px[0], y); b[2] = pii(px[0], y + x);
			b[3] = pii(px[1], y); b[4] = pii(px[1], y + x);
			Maintain();
			b[1] = pii(px[0], y); b[2] = pii(px[0], y - x);
			b[3] = pii(px[1], y); b[4] = pii(px[1], y - x);
			Maintain();
		}
		if ( px.size() == 1 && py.size() == 2 ) 
		{
			int x = px[0], y = py[1] - py[0];
			b[1] = pii(x, py[0]); b[2] = pii(x + y, py[0]);
			b[3] = pii(x, py[1]); b[4] = pii(x + y, py[1]);
			Maintain();
			b[1] = pii(x, py[0]); b[2] = pii(x - y, py[0]);
			b[3] = pii(x, py[1]); b[4] = pii(x - y, py[1]);
			Maintain();
		}
		if ( px.size() == 2 && py.size() == 0 ) 
		{
			int d = px[1] - px[0];		
			REP(i, 1, 4) q[i] = i;
			do
			{
				f[1] = a[q[1]].y; f[2] = a[q[2]].y; f[3] = a[q[3]].y - d; f[4] = a[q[4]].y - d;
				int Min = INF, Max = -INF; REP(i, 1, 4) { Min = min(Min, f[i]); Max = max(Max, f[i]); } 
				int x = (Max + Min) / 2;
				b[1] = pii(px[0], x); b[2] = pii(px[1], x);
				b[3] = pii(px[0], x + d); b[4] = pii(px[1], x + d);
				Maintain();
			} while ( next_permutation(q + 1, q + 4 + 1) );
		}
		if ( px.size() == 0 && py.size() == 2 ) 
		{
			int d = py[1] - py[0];		
			REP(i, 1, 4) q[i] = i;
			do
			{
				f[1] = a[q[1]].x; f[2] = a[q[2]].x; f[3] = a[q[3]].x - d; f[4] = a[q[4]].x - d;
				int Min = INF, Max = -INF; REP(i, 1, 4) { Min = min(Min, f[i]); Max = max(Max, f[i]); } 
				int x = (Max + Min) / 2;
				b[1] = pii(x, py[0]); b[2] = pii(x, py[1]);
				b[3] = pii(x + d, py[0]); b[4] = pii(x + d, py[1]);
				Maintain();
			} while ( next_permutation(q + 1, q + 4 + 1) );
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{ 
		REP(i, 1, 4) scanf("%d%d", &a[i].x, &a[i].y); 
		ret = INF; Solve();	
		if ( ret == INF ) puts("-1");
		else { printf("%d\n", ret); REP(i, 1, 4) printf("%d %d\n", ans[i].x, ans[i].y); }
	}
    return 0;
}
