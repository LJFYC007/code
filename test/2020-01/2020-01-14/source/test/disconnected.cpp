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
const string task = "disconnected";

template <class T> T sqr (const T &a) {return a*a;}

const int nmax = 16384 ;
const int emax = 100100;

vector<pii> g[nmax];
vector<bool> bad[nmax];
vector<pii> zap[emax];
pii e[emax];
int n, m, tst;
int dep[nmax], pr[nmax];
bool used[nmax];
vector<int> w;
int l[nmax], r[nmax], pos[nmax];
pii t[nmax*2];
bool res[nmax];

void update(int v, int l, int r, int x, int c){
	if (l > x || r < x) return;
	if (l == r){
		t[v] = mp(c, 0);
		return;
	}
	int m = (l + r) / 2;
	update(v*2, l, m, x, c);
	update(v*2+1, m + 1, r, x, c);
	t[v] = min(t[v*2], t[v*2+1]);
}

void push(int v){
	if (v >= nmax) return;
	t[v*2].sc = t[v*2+1].sc = t[v].sc;
}

int get(int v, int l, int r, int l1, int r1){
	push(v);
	if (l > r1 || r < l1) return I 1e9;
	if (l1 <= l && r <= r1){
		if (t[v].sc == 1) return I  1e9;
		t[v].sc = 1;
		return t[v].fs;
	}
	int m = (l + r) / 2;
	int f1 = get(v*2, l, m, l1, r1);
	int f2 = get(v*2+1, m + 1, r, l1, r1);
	return min(f1,f2);
}

bool ls(pii a, pii b){
	return r[a.fs] - l[a.fs] < r[b.fs] - l[b.fs];
}

bool check(vector<pii> &a){
	t[1].sc = 0;
	forn(i,a.size()){
		if (dep[a[i].fs] < dep[a[i].sc])
			swap(a[i].fs, a[i].sc);
		if (pr[a[i].fs] != a[i].sc){
			forn(k,5)
				if (k <  I g[a[i].fs].size() && g[a[i].fs][k].sc == a[i].sc){
					bad[a[i].fs][k] = 1;
					break;
				}
		}
	}
	forn(i,a.size()){
		int res =  I 1e9;
		forn(k,5)
			if (k <  I g[a[i].fs].size() && !bad[a[i].fs][k]){
				res = g[a[i].fs][k].fs;
				break;
			}
		update(1, 1, nmax, pos[a[i].fs] + 1, res);
		forn(k,5)
			if (k <  I g[a[i].fs].size())
				bad[a[i].fs][k] = 0;
	}
	
	sort(all(a), ls);

	forn(i,a.size())
		if (pr[a[i].fs] == a[i].sc){
			int f = get(1, 1, nmax, l[a[i].fs]+1, r[a[i].fs]+1);
			if (f >= dep[a[i].fs]) return 0;
		}
	return 1;
}

void go(int v, int d, int p){
	used[v] = 1;
	pr[v] = p;
	dep[v] = d;
	w.pb(v);
	l[v] =  I w.size();
	forn(i,g[v].size()){
		if (g[v][i].sc == p){
			swap(g[v][i], g[v][g[v].size()-1]);
			g[v].pop_back();
		}
		if (i >= g[v].size()) continue;
		if (!used[g[v][i].sc])
			go(g[v][i].sc, d+1, v);
		else
			g[v][i].fs = dep[g[v][i].sc];
	}
	r[v] =  I w.size()-1;
}


void pre_calc(){
	seta(t, 0);
	seta(used, 0);
	go(0, 0, -1);
	forn(i,n){
		sort(all(g[i]));
		bad[i].resize(g[i].size());
	}
	forn(i,w.size()){
		pos[w[i]] = i;
		if (g[w[i]].size() > 0)
			update(1, 1, nmax, i+1, g[w[i]][0].fs);
		else
			update(1, 1, nmax, i+1,  I 1e9);
	}
}

void solve(){
	pre_calc();
	forn(i,n)
		res[i] = check(zap[i]);
}

void read(){
	scanf("%d %d", &n, &m);
	forn(i,m){
		int u,v;
		scanf("%d %d", &u, &v);
		u--; v--;
		g[u].pb(mp( I 1e9,v));
		g[v].pb(mp( I 1e9,u));
		e[i] = mp(u,v);
	}
	scanf("%d", &tst);
	forn(i,tst){
		int k, x;
		scanf("%d", &k);
		forn(j,k){
			scanf("%d", &x);
			zap[i].pb(e[x-1]);
		}
	}
}

void write(){
	forn(i,tst)
		if (res[i])
			puts("Connected");
		else
			puts("Disconnected");
}


int main ()
{
	freopen ((task+".in").data(), "r", stdin);
	freopen ((task+".out").data(), "w", stdout);

	read();
	solve();
	write();

	return 0;
}
