#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int max0 = 310, max1 = 5050;

int n, m, K;
int sum;

pair<pair<int, int>, int> ed_raw[max1 + 5];

double ans = 0;

struct edge
{
    int id, g;
	double w;
	int nxt;
 
    edge() { }
    edge(const int &_id, const int &_g, const double &_w, const int &_nxt): id(_id), g(_g), w(_w), nxt(_nxt) { }
 
};
 
int st[max0 + 5], en = 0;
edge e[max1 + 5];
 
int N;
 
inline void add_edge(const int &x, const int &y, const int &z, const double &w)
{
    e[en] = edge(y, z, w, st[x]), st[x] = en++; 
}
 
inline void add_biedge(int x, int y, int z, const double &w)
{
    if (!z) return;
    add_edge(x, y, z, w);
    add_edge(y, x, 0, -w);
}
 
int S, T;
 
double dis[max0 + 5];
int pre[max0 + 5];

int cnt[max0 + 5];

bool SPFA()
{
    static int q[max0 + 5];
    static bool vis[max0 + 5] = {0};
    int head = 0, rear = 0;
    memset(vis, 0, sizeof(vis[0]) * N);
	REP(i, 0, N) dis[i] = -1e100;
    q[rear++] = S;
    dis[S] = 0;
    while (head != rear)
    {
        const int &x = q[head++];
        vis[x] = 0;
        if (head >= max0 + 1) head -= max0 + 1;
		if (x == T) continue;
        for (int i = st[x]; i != -1; i = e[i].nxt)
        {
            if (!e[i].g) continue;
            const int &y = e[i].id;
            if (chkmax(dis[y], dis[x] + e[i].w))
            {
                pre[y] = i;
                if (!vis[y])
                {
                    vis[y] = 1;
                    q[rear++] = y;
                    if (rear >= max0 + 1) rear -= max0 + 1;
                }
            }
        }
    }
    if (dis[T] <= 0) return 0;
	return 1;
}

bool dij()
{
    static bool vis[max0 + 5] = {0};
	static double old_dis[max0 + 5];
    memset(vis, 0, sizeof(vis[0]) * N);
    memcpy(old_dis, dis, sizeof(old_dis[0]) * N);
	REP(i, 0, N) dis[i] = -1e100;
    dis[S] = 0;
	priority_queue<pair<double, int> > q;
	q.push(mp(dis[S], S));
	while (!q.empty())
	{
		int x = q.top().y; q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		if (x == T) continue;
        for (int i = st[x]; i != -1; i = e[i].nxt)
        {
            if (!e[i].g) continue;
            const int &y = e[i].id;
            if (chkmax(dis[y], dis[x] + e[i].w))
            {
                pre[y] = i;
				q.push(mp(dis[y] - old_dis[y], y));
            }
        }
	}
    if (dis[T] <= 0) return 0;
	return 1;
}

double cur;

inline void augment() 
{
	cur += dis[T];
    int u = T;
    while (u != S)
    {
        --e[pre[u]].g;
        ++e[pre[u] ^ 1].g;
        u = e[pre[u] ^ 1].id;
    }

	int newcomer = e[pre[T] ^ 1].id;
	++cnt[newcomer];
	add_biedge(newcomer, T, 1, n - cnt[newcomer]);
}

inline pair<int, int> calc(const double &x)
{
	memset(st, -1, sizeof st), en = 0;
	N = (n << 1) + 2;
	S = N - 2;
	T = N - 1;
	REP(i, 0, m)
		add_biedge(ed_raw[i].x.x, ed_raw[i].x.y + n, 1, ed_raw[i].y);
	REP(i, 0, n)
	{
		add_biedge(S, i, 1, 0);
		cnt[i] = 0;
		add_biedge(i + n, T, 1, n + x);
	}

	memset(cnt, 0, sizeof cnt);
	cur = 0;
	if (SPFA()) augment();
	while (dij()) augment();

	int num_zero = 0;
	REP(i, 0, n) if (!cnt[i + n]) ++num_zero;
	return mp((int)(cur - (n - num_zero) * x + .5) + sum, num_zero);
}

//set<pair<int, double> > _;

inline double eval(const pair<int, int> &x)
{
	if (K == 1) return (double)x.x / x.y;
//	_.insert(mp(x.y, double((LL)x.x * x.x) / x.y));
	return double((LL)x.x * x.x) / x.y;
}

inline void work(const double &l, const double &r, const pair<int, int> &ansl, const pair<int, int> &ansr) 
{
	chkmax(ans, eval(ansl));
	chkmax(ans, eval(ansr));
	if (ansl == ansr) return;
	double mid = double(ansr.x - ansl.x) / (ansr.y - ansl.y);
	pair<int, int> ans_mid = calc(mid);
	if (ans_mid == ansl || ans_mid == ansr) return;
	work(l, mid, ansl, ans_mid);
	work(mid, r, ans_mid, ansr);
}

int main()
{
//#ifdef LOCAL
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//#endif
	scanf("%d%d%d", &n, &m, &K);
	sum = 0;
	REP(i, 0, n)
	{
		int x;
		scanf("%d", &x);
		sum += x;
	}
	REP(i, 0, m)
	{
		scanf("%d%d%d", &ed_raw[i].x.x, &ed_raw[i].x.y, &ed_raw[i].y);
		--ed_raw[i].x.x;
		--ed_raw[i].x.y;
	}
	work(0, 1e7, calc(0), calc(1e7));
//	for (auto u : _) debug("%d %f\n", u.x, u.y);
	printf("%.15f\n", ans);
	return 0;
}
