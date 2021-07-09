#include <bits/stdc++.h>

#define x first
#define y second
#define y1 Y1
#define y2 Y2
#define mp make_pair
#define pb push_back
#define DEBUG(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long LL;
typedef pair <int, int> pii;

template <typename T> inline int Chkmax (T &a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline int Chkmin (T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline T read ()
{
	T sum = 0, fl = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
	return sum * fl;
}

inline void proc_status ()
{
	ifstream t ("/proc/self/status");
	cerr << string (istreambuf_iterator <char> (t), istreambuf_iterator <char> ()) << endl;
}

const int Maxn = 1e5 + 100, Maxm = 2e5 + 100;
const int Mod = 1e9 + 7;

int N, M, S, T;
int LIM = 1e5 + 80;
int pw2[Maxn];
int e, Begin[Maxn], To[Maxm << 1], Next[Maxm << 1], W[Maxm << 1];

inline void add_edge (int x, int y, int z)
{
	To[++e] = y;
	Next[e] = Begin[x];
	Begin[x] = e;
	W[e] = z;
}

namespace SEG
{
#define mid ((l + r) >> 1)
#define ls(x) node[x].ch[0]
#define rs(x) node[x].ch[1]
#define lson ls(o), l, mid
#define rson rs(o), mid + 1, r
	struct info
	{
		int ch[2], val;
	} node[Maxn * 100];
	int node_cnt;

	inline void push_up (int o, int l, int r)
	{
		node[o].val = (node[ls(o)].val + (LL) node[rs(o)].val * pw2[mid - l + 1] % Mod) % Mod;
	}

	int flag;

	inline void insert (int pre, int &o, int l, int r, int x)
	{
		o = ++node_cnt, node[o] = node[pre];

		if (l == r)
		{
			if (!node[o].val) node[o].val = 1, flag = 1;
			else node[o].val = 0;
			return ;
		}

		if (x <= mid)
		{
			insert (node[pre].ch[0], lson, x);
			if (!flag) x = mid + 1;
		}
		if (x > mid) insert (node[pre].ch[1], rson, x);

		push_up (o, l, r);
	}

	inline int compare (int x, int y, int l, int r)
	{
		if (l == r) return node[x].val < node[y].val;
		if (node[x].val == node[y].val) return x < y;
		if (node[rs(x)].val == node[rs(y)].val) return compare (ls(x), ls(y), l, mid); 
		return compare (rs(x), rs(y), mid + 1, r);
	}
	
#undef mid
}

inline int cmp (int x, int y) { return SEG :: compare (x, y, 0, LIM); }

struct info
{
	int x, id;
	inline bool operator < (const info &rhs) const { return !cmp (id, rhs.id); }
};

int Root[Maxn], Vis[Maxn];

inline void Init ()
{
	pw2[0] = 1;
	for (int i = 1; i <= LIM; ++i) pw2[i] = (LL) pw2[i - 1] * 2 % Mod;

	for (int i = 1; i <= N; ++i)
		if (i != S)
		{
			SEG :: flag = 0;
			SEG :: insert (0, Root[i], 0, LIM, LIM);
		}
}

inline void Solve ()
{
	Init ();

	static priority_queue <info> Q;
	Q.push ((info){S, Root[S]});
	while (!Q.empty())
	{
		int x = Q.top().x; Q.pop();
		if (Vis[x]) continue;
		Vis[x] = 1;
		if (x == T) break;

		for (int i = Begin[x]; i; i = Next[i])
		{
			int y = To[i], now = 0;
			SEG :: flag = 0;
			SEG :: insert (Root[x], now, 0, LIM, W[i]);
			if (cmp (now, Root[y]))
			{
				Root[y] = now;
				Q.push ((info){y, Root[y]});
			}
		}
	}

	if (!Vis[T]) puts("-1");
	else printf("%d\n", SEG :: node[Root[T]].val);
}


inline void Input ()
{
	read<int>();
	N = read<int>(), M = read<int>(), S = read<int>(), T = read<int>();
	for (int i = 1; i <= M; ++i)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add_edge (x, y, z);
		add_edge (y, x, z);
	}
}

int main()
{

#ifndef ONLINE_JUDGE
//	freopen("physics.in", "r", stdin);
//	freopen("physics.out", "w", stdout);
#endif

	Input ();
	Solve ();

	return 0;
}

