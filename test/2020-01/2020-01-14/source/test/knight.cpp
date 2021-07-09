#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <complex>
#include <queue>
#include <stack>

using namespace std;

#define forn(i,n) for (int i = 0; i < (int)n; i ++)
#define ford(i,n) for (int i = n-1; i >= 0; i --)
#define fs first
#define sc second
#define all(a) a.begin(), a.end()
#define last(a) (int)a.size() - 1
#define I (int)
#define pb push_back
#define mp make_pair
#define seta(x,y) memset(x,y,sizeof (x))

typedef long long int64;
typedef long double ldb;
typedef pair <int, int> pii;

const int inf = (1 << 30) - 1;
const int64 inf64 = (1LL << 62) - 1;
const ldb eps = 1e-9;
const ldb pi = 3.1415926535897932384626433832795;
const string task = "knight";
int const n = 8;
int const VMAX = 70;
int const NMAX = n;

template <class T> T sqr (const T &a) {return a*a;}

int const dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int const dy[8] = {-2, 2, -1, 1, -2, 2, -1, 1};

char s[NMAX][NMAX + 2];
int num[NMAX][NMAX], now;
int S, T, prev[VMAX], dist[VMAX];
char ans1[VMAX], ans2[VMAX];
vector <int> v, w, u, c, f, para;
vector <pii> tmp_ans, best_ans;
bool used[VMAX];

bool may(int x, int y)
{
	if (x >=0 && x < n && y >= 0 && y < n) return true;
	else return false;
}

bool kon(int q)
{
	return used[q];
}

void add(int V, int U, int C, int W)
{
	v.pb(V);
	u.pb(U);
	c.pb(C);
	w.pb(W);
	f.pb(0);
	para.pb(I v.size());

	para.pb(I v.size() - 1);
	v.pb(U);
	u.pb(V);
	c.pb(0);
	w.pb(-W);
	f.pb(0);
}

void make_graph(int x)
{
	f.clear();
	c.clear();
	w.clear();
	para.clear();
	v.clear();
	u.clear();

	S = 0, T = 65;
	forn(i, n)
		forn(j, n)
		{
			forn(f, 8)
				if (may(i + dx[f], j + dy[f]))
					add(num[i][j], num[i + dx[f]][j + dy[f]], 100000, 1);

			if (s[i][j] == 'N' && ((i + j) & 1) == x) continue;

			if (s[i][j] == 'N') add(S, num[i][j], 1, 0);
			else add(S, num[i][j], 0, 0);
			if (((i + j) & 1) == x) 
				add(num[i][j], T, 1, 0);
			//else add(num[i][j], T, 0, 0);
		}
}

void way(int T)
{
	if (T == 0) return;
	way(v[prev[T]]);
	f[prev[T]]++;
	f[para[prev[T]]]--;
}

int num1;

bool flow()
{
	forn(i, VMAX)
		dist[i] = 1000000;
	dist[0] = 0;
	forn(i, VMAX)
	{
		bool flag = 0;
		forn(j, num1)
			if (c[j] - f[j] > 0 && dist[u[j]] > dist[v[j]] + w[j])
			{
				dist[u[j]] = dist[v[j]] + w[j];
				prev[u[j]] = j;
				flag = 1;
			}
		if (!flag) break;
	}
	if (dist[T] < 1000000) 
	{
		way(T);
		return true;
	}
	return false;
}

void dfs(int q, bool may)
{
	if (q == T) return;
	forn(i, v.size())
		if (v[i] == q && f[i] > 0)
		{
			if (kon(u[i]))
			{
				if (v[i] == S)
				{
					used[u[i]] = false;
					dfs(u[i], true);
				}
				else dfs(u[i], false);
				if (v[i] != S && u[i] != T)
					tmp_ans.pb(mp(v[i], u[i]));
				f[i]--;
				f[para[i]]++;
				return;
			}
			if (u[i] != T) tmp_ans.pb(mp(v[i], u[i]));
			if (u[i] == T) used[q] = true;
			dfs(u[i], true);
			f[i]--;
			f[para[i]]++;
			return;
		}
}

void solve()
{
	now = 1;
	forn(i, n)
		forn(j, n)
		{
			num[i][j] = now;
			ans1[now] = (char) ('a' + j);
			ans2[now++] = (char) ('8' - i);
		}

	best_ans.resize(10000);

	make_graph(0);
	num1 = v.size();
	seta(used, 0);
	forn(i, n)
		forn(j, n)
			if (s[i][j] == 'N') used[num[i][j]] = true;
	tmp_ans.clear();
	while (flow()) {}
	forn(i, 32)
		dfs(S, true);
	if (best_ans.size() > tmp_ans.size()) best_ans = tmp_ans;

	make_graph(1);
	num1 = v.size();
	seta(used, 0);
	forn(i, n)
		forn(j, n)
			if (s[i][j] == 'N') used[num[i][j]] = true;
	tmp_ans.clear();
	while (flow()) {}
	forn(i, 32)
		dfs(S, true);
	if (best_ans.size() > tmp_ans.size()) best_ans = tmp_ans;

	cout << best_ans.size() << endl;
//	forn(i, best_ans.size())
//		printf("%c%c-%c%c\n", ans1[best_ans[i].fs], ans2[best_ans[i].fs], ans1[best_ans[i].sc], ans2[best_ans[i].sc]);
}

int main ()
{
//	freopen ((task+".in").data(), "r", stdin);
//	freopen ((task+".out").data(), "w", stdout);

	while (scanf("%s", s[0]) != EOF)
	{
		for (int i = 1; i < n; i++)
			scanf("%s", s[i]);
		solve();
		cout << endl;
	}

	return 0;
}

