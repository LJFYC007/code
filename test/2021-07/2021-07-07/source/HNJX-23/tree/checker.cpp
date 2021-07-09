#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

void readOthers(InStream &s) { while (!s.seekEof()) s.readToken(); }
const int N(205), M(N * N);
struct edge { int x, y; };
std::set<std::pair<int, int> > E;
std::vector<edge> G, t1, t2, t;
std::set<int> S[N];
int n, m;

int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	n = inf.readInt(), m = inf.readInt();
	for (int i = 1, x, y, f1, f2; i <= m; i++)
	{
		x = inf.readInt(1, n), y = inf.readInt(1, n), f1 = inf.readInt(0, 1), f2 = inf.readInt(0, 1);
		if (x > y) std::swap(x, y); edge e = (edge) {x, y}; E.emplace(x, y);
		G.push_back(e); if (f1) t1.push_back(e); if (f2) t2.push_back(e);
	}
	readOthers(inf);
	for (auto e : t1) S[e.x].insert(e.y), S[e.y].insert(e.x);
	auto outs = ouf.readToken(), anss = ans.readToken();
	ouf.ensuref(outs == anss, "Wrong Answer [1]");
	readOthers(ans);
	int st = ouf.readInt(0, 1e9);
	for (int i = 1; i <= st; i++)
	{
		int x = ouf.readInt(1, n), y = ouf.readInt(1, n);
		ouf.ensuref(x != y, "Wrong Answer [2]");
		if ( S[x].size() != 1 ) 
		{
			cout << i << endl;
		}
		ouf.ensuref(S[x].size() == 1, "Wrong Answer [3]");
		int z = *S[x].begin(), u = x, v = y; if (u > v) std::swap(u, v);
		ouf.ensuref(E.find(std::make_pair(u, v)) != E.end(), "Wrong Answer [4]");
		S[x].erase(z), S[z].erase(x), S[x].insert(y), S[y].insert(x);
	}
	readOthers(ouf);
	for (int i = 1; i <= n; i++)
		for (auto j : S[i]) if (i < j) t.push_back((edge) {i, j});
	std::sort(t.begin(), t.end(), [] (edge x, edge y) { return std::make_pair(x.x, x.y) < std::make_pair(y.x, y.y); });
	std::sort(t2.begin(), t2.end(), [] (edge x, edge y) { return std::make_pair(x.x, x.y) < std::make_pair(y.x, y.y); });
	for (int i = 0; i < (int) t.size(); i++) ouf.ensuref(t[i].x == t2[i].x && t[i].y == t2[i].y, "Wrong Answer [5]");
	quitf(_ok, "Accepted!");
	return 0;
}
