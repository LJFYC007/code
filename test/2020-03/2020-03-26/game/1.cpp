#include<bits/stdc++.h>
#include "game.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

int a[21], b[100];
set<pair<pii, int> > Set;

int start_game()
{
	srand(time(0));
	REP(i, 1, 20) a[i] = i;
	REP(i, 1, 99) b[i] = i;
	random_shuffle(a + 1, a + 20 + 1);
	int m = 100;
	REP(i, 1, 14) REP(j, 1, 4) put(a[i], b[-- m]);
	REP(i, 1, 20)
	{
		int x = query(a[i]).size();
		Set.insert(make_pair(pii(x, rand()), a[i]));
	}
	int ans = Set.begin() -> second;
	Set.erase(Set.begin());
	REP(i, 77, 99)
	{
		auto it = Set.begin();
		put(it -> second, b[-- m]);
		int x = it -> first.first + 1, y = it -> second;
		Set.erase(it);
		Set.insert(make_pair(pii(x, rand()), y));
	}
	return ans;
}
