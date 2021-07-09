#include<bits/stdc++.h>
#include "game.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

int a[21];
set<pii> Set;
vector<int> p;
bool vis[21];

int start_game()
{
	srand(time(0)); Set.clear(); mem(vis);
	REP(i, 1, 20) a[i] = i;
	random_shuffle(a + 1, a + 20 + 1);
	REP(i, 1, 14) REP(j, 1, 4) put(a[i], j);
	REP(i, 1, 20)
	{
		p = query(a[i]);
		int x = p.size();
		if ( unique(p.begin(), p.end()) != p.end() ) vis[a[i]] = true;
		Set.insert(pii(x, a[i]));
	}
	auto it = Set.begin();
	while ( vis[it -> second] ) ++ it;
	int ans = it -> second;
	Set.erase(it);
	REP(i, 77, 99)
	{
		auto it = Set.begin();
		put(it -> second, 1);
		int x = (it -> first) + 1, y = it -> second;
		Set.erase(it);
		Set.insert(pii(x, y));
	}
	return ans;
}
