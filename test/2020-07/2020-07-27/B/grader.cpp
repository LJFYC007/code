#include <bits/stdc++.h>
#include "recover.h"

// if c++11 is not enabled, use vector< pair<int, int> > instead of vector<pair<int, int>> to avoid compile error

using namespace std;

namespace workspace {

vector<pair<int, int>> E;
int n, m, k, qcnt;

pair<int, int> query(vector<int> S){
	++qcnt;
	vector<char> vis(n + 1);
	for (int i = 0; i < S.size(); ++i) {
		vis[S[i]] = 1;
	}
	for (int i = 0; i < E.size(); ++i) {
		if (vis[E[i].first] && vis[E[i].second]) {
			return E[i];
		}
	}
	return make_pair(-1, -1);
}

void main(){
	cin >> n >> m >> k;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		if (u > v) swap(u, v);
		E.push_back(make_pair(u, v));
	}
	sort(E.begin(), E.end());
	vector<pair<int, int>> W = recover(n);
	for (int i = 0; i < W.size(); ++i) {
		if (W[i].first > W[i].second) {
			swap(W[i].first, W[i].second);
		}
	}
	sort(W.begin(), W.end());
	if (E == W) {
		cout << "OK\n";
	} else {
		cout << "WA\n";
	}
	cout << qcnt << "\n";
}

}

pair<int, int> query(vector<int> S){
	return workspace::query(S);
}
int main(){
    freopen("recover.in", "r", stdin);
	workspace::main();
}
