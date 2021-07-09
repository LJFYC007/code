#include <bits/stdc++.h>

using namespace std;

struct dsu_t {
	vector<int> dsu;
	dsu_t(int size){
		dsu.resize(size + 1);
		for (int i = 1; i <= size; ++i) {
			dsu[i] = i;
		}
	}
	int find(int u){
		return dsu[u] == u ? u : dsu[u] = find(dsu[u]);
	}
	bool check_border(int op, int len){
		assert(dsu.size() >= len + op);
		for (int i = 1; i <= len; ++i) {
			if (find(dsu.size() - i) != find(len - i + op + 1)) {
				return false;
			}
		}
		return true;
	}
	void make_border(int op, int len){
		assert(dsu.size() >= len + op);
		for (int i = 1; i <= len; ++i) {
			int u = find(dsu.size() - i);
			int v = find(len - i + op + 1);
			if (u != v) dsu[max(u, v)] = min(u, v);
		}
	}
	int size(){
		int res = 0;
		for (int i = 1; i < dsu.size(); ++i) if (dsu[i] == i) ++res;
		return res;
	}
} ;

using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;

const int mod = 1e9 + 7;
const int N = 45;

int add(int a, int b){
	return (a += b) < mod ? a : a - mod;
}
int sub(int a, int b){
	return (a -= b) < 0 ? a + mod : a;
}
int mul(int a, int b){
	return i64(a) * b % mod;
}

int n, s, pow_s[N], ans;

namespace part1 {
	vector<int> cur;
	u64 mask;
	int res;
	void init(){
		mask = res = 0;
		cur.clear();
		cur.push_back(0);
	}
	int f[N], g[N], coef[N], s_coef[N];
	int calc(vector<int> border){
		if (border.size() == 1) return 0;
		int res = 0, m = border.back(), x, y;
		u64 mask = 0;
		for (x = 0; x < border.size(); ++x) {
			mask |= u64(1) << border[x];
		}
		for (x = 1; x <= n; ++x) {
			s_coef[x] = coef[x] = x < m ? (mask >> (m - x) & 1) : pow_s[x - m];
			for (y = 1; y < x; ++y) {
				s_coef[x] = sub(s_coef[x], mul(coef[y], s_coef[x - y]));
			}
		}
		for (x = m; x <= n; ++x) {
			f[x] = pow_s[x - m], g[x] = 0;
			for (y = m; y < x; ++y) {
				f[x] = sub(f[x], mul(f[y], coef[x - y]));
				if (y > m) {
					g[x] = add(g[x], mul(add(f[y], g[y]), s_coef[x - y]));
				}
			}
		}
		for (x = m + 1; x <= n; ++x) {
			res = add(res, mul(g[x], pow_s[n - x]));
			for (y = x + 1; y <= n; ++y) {
				res = sub(res, mul(mul(g[x], s_coef[y - x]), pow_s[n - y]));
			}
		}
		return res;
	}
	vector<int> dfs(int ways){
		ans = add(ans, mul(ways, calc(cur)));
		int last = cur.back(), x, y, nways;
		vector<int> sum(n);
		for (x = last + 1; x < n; ++x) {
			if (x >= last * 2 || (mask >> (2 * last - x) & 1)) {
				cur.push_back(x);
				mask ^= u64(1) << x;
				nways = ways;
				if (x >= last * 2) {
					nways = mul(nways, pow_s[x - last * 2]);
				}
				nways = sub(nways, sum[x]);
				if (nways > 0) {
					vector<int> coef = dfs(nways);
					for (y = 0; y < n; ++y) sum[y] = add(sum[y], coef[y]);
				}
				cur.pop_back();
				mask ^= u64(1) << x;
			}
		}
		sum[last] = add(sum[last], ways);
		return sum;
	}
	int solve(){
		init();
		dfs(1);
		return res;
	}
}

namespace part2 {
	struct node {
		u128 border;
		int ways, coef;
		bool operator > (const node &rhs) const {
			return border > rhs.border;
		}
	} ;
	vector<node> res;
	int len;
	void init(){
		res.clear();
	}
	int f[N], g[N], h[N], coef[N], s_coef[N], t_coef[N], r_coef[N];
	int calc(u128 mask){
		int res = 0, m = len, x, y;
		u64 mask_0 = 0, mask_1 = 0;
		for (x = 1; x <= m; ++x) {
			mask_0 |= (mask >> (x * 2 - 1) & 1) << x;
			mask_1 |= (mask >> (x * 2 - 2) & 1) << x;
		}
		for (x = 1; x <= n; ++x) {
			s_coef[x] = coef[x] = x < m ? (mask_1 >> (m - x) & 1) : pow_s[x - m];
			r_coef[x] = t_coef[x] = x < m - 1 ? (mask_0 >> (m - 1 - x) & 1) : pow_s[x - m + 1];
			for (y = 1; y < x; ++y) {
				s_coef[x] = sub(s_coef[x], mul(t_coef[y], s_coef[x - y]));
				r_coef[x] = sub(r_coef[x], mul(t_coef[y], r_coef[x - y]));
			}
		}
		h[m - 1] = 1; 
		for (x = m; x <= n; ++x) {
			f[x] = pow_s[x - m], g[x] = 0, h[x] = pow_s[x - m + 1];
			for (y = m - 1; y < x; ++y) {
				h[x] = sub(h[x], mul(h[y], t_coef[x - y]));
				f[x] = sub(f[x], mul(h[y], coef[x - y]));
				g[x] = add(g[x], mul(add(f[y], g[y]), s_coef[x - y]));
			}
		}
		for (x = m; x <= n; ++x) {
			res = add(res, mul(g[x], pow_s[n - x]));
			for (y = x + 1; y <= n; ++y) {
				res = sub(res, mul(mul(g[x], r_coef[y - x]), pow_s[n - y]));
			}
		}
		return res;
	}
	void dfs(int pos, u128 mask, dsu_t cur){
		if (pos > 2 * len - 3) {
			node now;
			now.border = mask;
			now.ways = pow_s[cur.size()];
			now.coef = calc(mask);
			res.push_back(now);
			return ;
		}
		if (!cur.check_border(pos & 1, (pos >> 1) + 1)) {
			dfs(pos + 1 + (pos & 1), mask, cur);
		}
		cur.make_border(pos & 1, (pos >> 1) + 1);
		for (int reject = 0; reject < pos; ++reject) {
			if ((~mask >> reject & 1) && cur.check_border(reject & 1, (reject >> 1) + 1)) {
				return ;
			}
		}
		dfs(pos + 1, mask | u128(1) << pos, cur);
	}
	int solve(){
		int sum = 0, x, y;
		for (len = 2; len < n; ++len) {
			init();
			dfs(0, 0, dsu_t(len));
			sort(res.begin(), res.end(), greater<node>());
			for (x = 0; x < res.size(); ++x) {
				for (y = 0; y < x; ++y) {
					if ((res[x].border | res[y].border) == res[y].border) {
						res[x].ways = sub(res[x].ways, res[y].ways);
					}
				}
				sum = add(sum, mul(res[x].ways, res[x].coef));
			}
		}
		return sum;
	}
}

int main(){
	int T, x;
	for (scanf("%d", &T); T; --T) {
		scanf("%d%d", &n, &s);
		for (x = pow_s[0] = 1; x <= n; ++x) {
			pow_s[x] = mul(pow_s[x - 1], s);
		}
		ans = 0;
		ans = add(ans, mul(pow_s[n], n + 1));
		ans = add(ans, part1::solve());
		ans = sub(ans, part2::solve());
		printf("%d\n", ans);
	}
}

