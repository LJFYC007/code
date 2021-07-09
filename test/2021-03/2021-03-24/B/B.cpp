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

const int maxn = 1e5 + 10;
const int INF = 1e9 + 10;
const int NN = 1e9;

int n, m, q, N, ans[maxn], c[maxn], tot = 0, p[maxn], Root[maxn];
struct node 
{ 
	int x, y, w; 
	bool operator < (const node &a) const { return x < a.x; } 
} a[maxn], b[maxn], Q[maxn];
map<int, int> Map;
pii d[maxn];
struct Node { int lson, rson, Max; } Tree[maxn << 4];

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int val) { for ( int i = pos; i <= N; i += lowbit(i) ) c[i] = max(c[i], val); }
inline int query(int pos) { int ret = -INF; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, c[i]); return ret; } 

inline int NewNode() { ++ tot; ls(tot) = rs(tot) = 0; Tree[tot].Max = -INF; return tot; }

inline int Modify(int now, int l, int r, int pos, int val)
{
	int root = NewNode(); Tree[root] = Tree[now]; 
	Tree[root].Max = max(Tree[root].Max, val);
	if ( l == r ) return root;
	int Mid = l + r >> 1; 
	if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos, val);
	else rs(root) = Modify(rs(root), Mid + 1, r, pos, val);
	return root;
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( !root ) return -INF; 
	if ( L <= l && r <= R ) return Tree[root].Max;
	int Mid = l + r >> 1, ret = -INF;
	if ( L <= Mid ) ret = max(ret, Query(ls(root), l, Mid, L, R));
	if ( Mid < R ) ret = max(ret, Query(rs(root), Mid + 1, r, L, R));
	return ret;
}

inline void Solve()
{
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1); sort(Q + 1, Q + q + 1);
	int B = 120, now = 0; tot = 0; REP(i, 1, N) c[i] = -INF; p[m + 1] = -INF;
	REP(i, 1, m) d[i] = pii(-1, -1);
	REP(i, 1, n) d[b[i].x] = pii(b[i].y, b[i].w);

	for ( int i = m; i >= 1; -- i ) 
		if ( d[i].x == -1 ) Root[i] = Root[i + 1];
		else Root[i] = Modify(Root[i + 1], 1, N, d[i].x, d[i].y);

	for ( int l = 1, r = min(B, n); l <= n; l += B, r = min(r + B, n) )
	{
		for ( int i = m; i >= 1; -- i ) 
			if ( d[i].x == -1 ) p[i] = p[i + 1];
			else p[i] = max(p[i + 1], query(d[i].x) + d[i].y);
		
		REP(i, l, r)
		{
			add(a[i].y, a[i].w);
			while ( now < q && Q[now + 1].x < a[i + 1].x )
			{
				++ now;
				if ( Q[now].x > a[i].x ) 
				{
					ans[Q[now].w] = max(ans[Q[now].w], p[Q[now].y]);
					REP(j, l, i) ans[Q[now].w] = max(ans[Q[now].w], Query(Root[Q[now].y], 1, N, a[j].y + 1, N) + a[j].w);
				}
			}
		}
	}
}

char buf[10000010],*cur=buf+10000010;
 
char getc(){
    (cur==buf+10000010)?fread(cur=buf,1,10000010,stdin):0;
    return *cur++;
}
 
inline void read(int &x)
{
    char c = getc(); x = 0; bool flag = false;
    while ( (c < '0' || c > '9') && c != '-' ) c = getc();
	if ( c == '-' ) { flag = true; c = getc(); }
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getc(); }
	if ( flag ) x = -x;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	read(n); if ( n > 50000 ) return 0;
	REP(i, 1, n) { read(a[i].x); read(a[i].y); read(a[i].w); }
	REP(i, 1, n) { read(b[i].x); read(b[i].y); read(b[i].w); }
	read(q);
	REP(i, 1, q) { read(Q[i].x); read(Q[i].y); Q[i].w = i; ans[i] = -1; } 

	REP(i, 1, n) Map[a[i].y] = Map[b[i].y] = true; 
	for ( auto it : Map ) Map[it.first] = ++ N;
	REP(i, 1, n) { a[i].y = Map[a[i].y]; b[i].y = Map[b[i].y]; } 
	
	Map.clear();
	REP(i, 1, n) Map[b[i].x] = true; REP(i, 1, q) Map[Q[i].y] = true;
	for ( auto it : Map ) Map[it.first] = ++ m;
	REP(i, 1, n) b[i].x = Map[b[i].x]; REP(i, 1, q) Q[i].y = Map[Q[i].y];

 	Solve(); 
	REP(i, 1, n) { a[i].x = -NN - a[i].x - 1; b[i].x = m - b[i].x + 1; } 
	REP(i, 1, m) { Q[i].x = -NN - Q[i].x - 1; Q[i].y = m - Q[i].y + 1; }
	Solve();

	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
