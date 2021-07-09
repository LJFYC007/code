#include<bits/stdc++.h>
typedef long long ll;
const int maxn = 170, maxk = 15;
int n, m, q;
int ok[maxn][maxn];
int low, up;
struct Mat {
	int a[maxn][maxn][maxk];
	inline Mat operator * (Mat b) const {
		Mat ret;
		for(int i = 0;i < maxn;++i) for(int j = 0;j < i;++j)
			std::swap(b.a[i][j], b.a[j][i]);
		struct node { int x, y, z, val; };
		struct cmp { inline int operator () (const node & x, const node & y) const { return x.val > y.val; } };

		for(int i = low;i <= up;++i) for(int j = 0;j < n;++j) {
			const auto get = [&](const node & x){ return a[i][x.x][x.y] + b.a[j][x.x][x.z]; };
			static node heap[maxn + maxk];
			for(int k = 0;k < n;++k) heap[k] = {k, 0, 0, a[i][k][0] + b.a[j][k][0]};
			int tot = n;
			std::make_heap(heap, heap + tot, cmp());
			for(int k = 0;k < maxk;++k) {
				node x = * heap;  ret.a[i][j][k] = x.val;
				if(x.val > 1e9) {
					std::fill(ret.a[i][j] + k, ret.a[i][j] + maxk,  1e9);
					break;
				}
				if(k != maxk - 1) {
					std::pop_heap(heap, heap + tot, cmp()), -- tot;
					const auto push = [&](node x) {
						x.val = get(x); int pos = tot ++;
						for(;pos && heap[pos - 1 >> 1].val > x.val;pos = pos - 1 >> 1)
							heap[pos] = heap[pos - 1 >> 1]; heap[pos] = x;
					};
					push({x.x, x.y, x.z + 1});
					if(x.z == 0)  push({x.x, x.y + 1, x.z});
				}
			}
		}
		return ret;
	}
} a[30], ans, empty;
std::vector<int> v[maxn][maxn];
int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m >> q;
	for(int i = 1, x, y, z;i <= m;++i) {
		std::cin >> x >> y >> z;
		v[x - 1][y - 1].push_back(z);
	}
	for(int i = 0;i < n;++i) for(int j = 0;j < n;++j) {
		std::sort(v[i][j].begin(), v[i][j].end());
		for(;v[i][j].size() < 15;) v[i][j].push_back(1e9);
		for(int l = 0;l < 15;++l) a -> a[i][j][l] = v[i][j][l];
	}
	up = n;
	for(int i = 1;i < 20;++i) {
		a[i] = a[i - 1] * a[i - 1];
	}
	for(int i = 1, s, t, a, k;i <= q;++i) {
		std::cin >> s >> t >> a >> k;
		low = up = 0, ans = empty;
		for(int j = 0;j < n;++j) {
			std::fill(ans.a[0][j], ans.a[0][j] + maxk, 1e9);
		}
		ans.a[0][s - 1][0] = 0;
		for(int j = 0;j < 20;++j) if(a >> j & 1)
			ans = ans * ::a[j];
		int o = ans.a[0][t - 1][k - 1];
		std::cout << (o > 9e8 ? -1 : o) << '\n';
	}
}
