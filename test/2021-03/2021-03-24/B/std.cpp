#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

const int maxn = 1e6 + 10;
const int INF = 1e9;
const int N = 1e9;

int n, m, q, ans[maxn], c[maxn];
struct node 
{ 
	int x, y, w, op; 
	bool operator < (const node &a) const { return y < a.y; } 
} a[maxn], b[maxn], Q[maxn];
map<int, int> Map;
vector<node> p;

char buf[10000010],*cur=buf+10000010;
char getc(){ (cur==buf+10000010)?fread(cur=buf,1,10000010,stdin):0; return *cur++; }
inline void read(int &x)
{
    char c = getc(); x = 0; bool flag = false;
    while ( (c < '0' || c > '9') && c != '-' ) c = getc();
	if ( c == '-' ) { flag = true; c = getc(); }
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getc(); }
	if ( flag ) x = -x;
}

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) c[i] = max(c[i], val); }
inline int query(int pos) { int ret = -INF; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, c[i]); return ret; } 

inline void Solve(int l, int r)
{
	if ( l >= r ) return ;
	int Mid = l + r >> 1; Solve(l, Mid); Solve(Mid + 1, r);
	int Max = -INF, pos = -1;
	REP(i, l, Mid) if ( a[i].op == 0 && Max < a[i].w ) { Max = a[i].w; pos = i; }
	if ( pos != -1 ) { REP(i, Mid + 1, r) if ( a[i].op == 1 ) p.push_back({a[pos].x, a[i].x, a[i].w + Max}); }
	Max = -INF; pos = -1;
	REP(i, Mid + 1, r) if ( a[i].op == 1 && Max < a[i].w ) { Max = a[i].w; pos = i; }
	if ( pos != -1 ) { REP(i, l, Mid) if ( a[i].op == 0 ) p.push_back({a[i].x, a[pos].x, a[i].w + Max}); }
}

inline void calc()
{
	REP(i, 1, m) c[i] = -INF; sort(p.begin(), p.end()); sort(Q + 1, Q + q + 1);
	int now = 1; p.push_back({m + 1, INF + 1, -INF});
	for ( int i = 0; i < p.size(); ++ i ) 
	{
		while ( now <= q && Q[now].y < p[i].y ) 
		{
			ans[Q[now].w] = max(ans[Q[now].w], query(Q[now].x));	
			++ now;
		}
		add(p[i].x, p[i].w);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	read(n); 
	REP(i, 1, n + n) 
	{ 
		read(a[i].x); read(a[i].y); read(a[i].w); 
		if ( i <= n ) { a[i].x = -a[i].x; Map[a[i].x] = true; } else a[i].op = 1;
	}
	read(q); REP(i, 1, q) { read(Q[i].x); read(Q[i].y); Q[i].x = -Q[i].x; ans[i] = -1; Q[i].w = i; Map[Q[i].x] = true; }
	for ( auto it : Map ) Map[it.first] = ++ m;
	REP(i, 1, n) a[i].x = Map[a[i].x]; REP(i, 1, q) Q[i].x = Map[Q[i].x];

	sort(a + 1, a + n + n + 1); Solve(1, n + n); calc(); p.clear();
	REP(i, 1, n + n) 
		if ( a[i].op == 0 ) a[i].x = m - a[i].x + 1; 
		else a[i].x = N - a[i].x + 1;
	REP(i, 1, q) { Q[i].x = m - Q[i].x + 1; Q[i].y = N - Q[i].y + 1; } 
	Solve(1, n + n); calc();

	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
