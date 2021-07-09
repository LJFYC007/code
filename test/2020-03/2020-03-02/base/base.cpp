#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, k, num[4];
char s[maxn], t[maxn];
bool vis[maxn][4];
bitset<maxn> S, T;
set<int> ans;

inline int get(char c)
{
	if ( c == 'Z' ) return 0;
	if ( c == 'P' ) return 1;
	if ( c == 'S' ) return 2;
	if ( c == 'B' ) return 3;
}

int main()
{
	freopen("base.in", "r", stdin);
	freopen("base.out", "w", stdout);
	scanf("%d", &k);
	scanf("%s", s); n = str(s);
	scanf("%s", t); m = str(t);
	REP(i, 0, k - 1) ++ num[get(s[i])];
	REP(i, 0, n - 1)
	{
		if ( i + k < n ) ++ num[get(s[i + k])];
		REP(j, 0, 3) if ( num[j] ) vis[i][j] = true; else vis[i][j] = false;
		if ( i - k >= 0 ) -- num[get(s[i - k])];
	}
	REP(i, 0, n - m) ans.insert(i);
	REP(i, 0, 3)
	{
		S.reset(); T.reset();
		REP(j, 0, n - 1) if ( !vis[j][i] ) S.set(j);
		REP(j, 0, m - 1) if ( get(t[j]) == i ) T.set(j);
		if ( T.none() ) continue ;
		int last = 0;
		auto it = ans.begin();
		while ( it != ans.end() )
		{
			S >>= *it - last;
			if ( S.none() ) break ;
			last = *it;
			if ( (S & T).any() ) { auto j = it; ++ it; ans.erase(j); }
			else ++ it;
		}
	}
	printf("%d\n", ans.size());
	return 0;
}
