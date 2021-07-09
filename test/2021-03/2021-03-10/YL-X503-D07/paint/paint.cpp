#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second

const int maxn = 1e5 + 10;

int n, p[maxn], m, t[maxn], num;
double ans;
struct node 
{ 
	int x, y, id; 
	bool operator < (const node &a) const { return x < a.x; } 
} a[maxn];

/*
inline double len(int x, int y) { return sqrt((double)((a[x].x - a[y].x) * (a[x].x - a[y].x) + (a[x].y - a[y].y) * (a[x].y - a[y].y))); }

inline int cross(pii a, pii b, pii c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

inline bool Check()
{
	REP(i, 1, m - 1) 
		if ( cross(line[i].x, line[i].y, line[m].x) * cross(line[i].x, line[i].y, line[m].y) < 0 && 
			 cross(line[m].x, line[m].y, line[i].x) * cross(line[m].x, line[m].y, line[i].y) < 0 )
			return false;
	return true;
}

inline void DFS(int x, double ret)
{
	++ num;
	if ( num >= 1000000 ) return ;
	if ( x == n + n + 1 )
	{
		if ( ret > ans ) 
		{
			REP(i, 1, n + n) t[i] = p[i];
			ans = ret;
		}
		return ;
	}
	if ( p[x] ) DFS(x + 1, ret);
	else
	{
		REP(y, n + x, n + n) if ( !p[y] ) 
		{
			p[x] = y; p[y] = x; line[++ m] = {a[x], a[y]};
			if ( Check() ) DFS(x + 1, ret + len(x, y));
			-- m; p[y] = p[x] = 0;
		}
	}
}
*/

int main()
{
	scanf("%d", &n);
	REP(i, 1, n + n) { scanf("%d%d", &a[i].x, &a[i].y); a[i].id = i; } 
	sort(a + 1, a + n + n + 1);
	for ( int i = 1; i <= n + n; i += 2 ) 
	{
		t[a[i].id] = a[i + 1].id;
		t[a[i + 1].id] = a[i].id;
	}
	REP(i, 1, n + n) printf("%d ", t[i]); puts("");
	return 0;
}
