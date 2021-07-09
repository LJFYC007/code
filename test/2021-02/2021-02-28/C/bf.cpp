#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, ans, Stack[maxn], tot;
char s[maxn];

inline bool Check()
{
	tot = 0;
	REP(i, 1, n) 
		if ( tot && s[i] == Stack[tot] ) -- tot;
		else Stack[++ tot] = s[i];
	return tot == 0;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, n - 1) REP(j, i + 1, n) if ( s[i] != s[j] ) 
	{
		swap(s[i], s[j]);
		if ( Check() ) ++ ans;
		swap(s[i], s[j]);
	}
	printf("%d\n", ans);
	return 0;
}
