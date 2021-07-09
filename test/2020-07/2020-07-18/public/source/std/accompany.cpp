#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
typedef long long ll;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
struct single {vector <ll> a[2]; };
struct info {vector <ll> a[2][2]; };
single dp[MAXN]; vector <pair <int, int>> a[MAXN];
int n, sz[MAXN], son[MAXN], flen[MAXN], father[MAXN];
void dfs(int pos, int fa) {
	sz[pos] = 1;
	for (auto x : a[pos])
		if (x.first != fa) {
			dfs(x.first, pos);
			sz[pos] += sz[x.first];
			father[x.first] = pos;
			flen[x.first] = x.second;
			if (sz[x.first] > sz[son[pos]]) son[pos] = x.first;
		}
}
info merge(info a, info b, int len) {
	info ans;
	for (int i = 0; i <= 1; i++)
	for (int j = 0; j <= 1; j++) {
		for (int k = 0; k <= 1; k++) {
			int inc = 1 - k; vector <ll> res;
			vector <ll> &x = a.a[i][k], &y = b.a[k][j];
			if (x.size() == 0 || y.size() == 0) continue;
			int s = 0, t = 0, ls = x.size() - 1, lt = y.size() - 1;
			if (inc && res.size() == 0) res.push_back(0);
			res.push_back(x[s] + y[t] + inc * len);
			while (s < ls || t < lt) {
				if (s < ls && (t == lt || x[s + 1] - x[s] > y[t + 1] - y[t])) s++;
				else t++;
				res.push_back(x[s] + y[t] + inc * len);
			}
			vector <ll> &to = ans.a[i][j];
			for (unsigned p = 0; p < res.size(); p++)
				if (p < to.size()) chkmax(to[p], res[p]);
				else to.push_back(res[p]);
		}
	}
	return ans;
}
info line(int l, int r, vector <int> &p) {
	if (l == r) {
		info ans; int pos = p[l];
		ans.a[0][1] = ans.a[1][0] = dp[pos].a[0];
		ans.a[1][1] = dp[pos].a[1];
		return ans;
	}
	int mid = (l + r) / 2;
	return merge(line(l, mid, p), line(mid + 1, r, p), flen[p[mid + 1]]);
}
single merge(single a, single b) {
	single ans;
	for (int i = 0; i <= 1; i++)
	for (int j = 0; i + j <= 1; j++) {
		vector <ll> res;
		vector <ll> &x = a.a[i], &y = b.a[j];
		if (x.size() == 0 || y.size() == 0) continue;
		int s = 0, t = 0, ls = x.size() - 1, lt = y.size() - 1;
		res.push_back(x[s] + y[t]);
		while (s < ls || t < lt) {
			if (s < ls && (t == lt || x[s + 1] - x[s] > y[t + 1] - y[t])) s++;
			else t++;
			res.push_back(x[s] + y[t]);
		}
		vector <ll> &to = ans.a[i + j];
		for (unsigned p = 0; p < res.size(); p++)
			if (p < to.size()) chkmax(to[p], res[p]);
			else to.push_back(res[p]);
	}
	return ans;
}
single vertex(int l, int r, vector <int> &p) {
	if (l == r) return dp[p[l]];
	int mid = (l + r) / 2;
	return merge(vertex(l, mid, p), vertex(mid + 1, r, p));
}
void getans(int pos) {
	vector <int> points;
	for (int i = pos; i != 0; i = son[i]) {
		points.push_back(i);
		vector <int> sons;
		for (auto x : a[i])
			if (x.first != father[i] && x.first != son[i]) {
				getans(x.first);
				sons.push_back(x.first);
			}
		if (!sons.size()) {
			dp[i].a[0].push_back(0);
			dp[i].a[1].push_back(0);
		} else dp[i] = vertex(0, sons.size() - 1, sons);
	}
	info tmp = line(0, points.size() - 1, points);
	dp[pos].a[0].clear();
	dp[pos].a[1].clear();
	for (int i = 0; i <= 1; i++) {
		vector <ll> &to = dp[pos].a[i];
		for (int j = 0; j <= 1 - i; j++)
		for (int k = 0; k <= 1; k++) {
			vector <ll> &cur = tmp.a[j][k];
			if (i == 1 && to.size() == 0) to.push_back(0);
			for (unsigned p = 0, q = i; p < cur.size(); p++, q++)
				if (q < to.size()) chkmax(to[q], cur[p] + i * flen[pos]);
				else to.push_back(cur[p] + i * flen[pos]);
		}
	}
	vector <ll> &x = dp[pos].a[0], &y = dp[pos].a[1];
	for (unsigned i = 0; i < x.size(); i++)
		if (i < y.size()) chkmax(y[i], x[i]);
		else y.push_back(x[i]);
}
int main() {
	freopen("accompany.in", "r", stdin);
	freopen("accompany.out", "w", stdout);
	int num, l, r; read(num);
	read(n), read(l), read(r);
	for (int i = 1; i <= n - 1; i++) {
		int x, y, z; read(x), read(y), read(z);
		a[x].emplace_back(y, z);
		a[y].emplace_back(x, z);
	}
	dfs(1, 0);
	getans(1);
	for (int i = l; i <= r; i++)
		if (i < dp[1].a[0].size()) printf("%lld ", dp[1].a[0][i]);
		else printf("- ");
	printf("\n");
	return 0;
}