#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, num[4], pos, m;
char s[maxn], t[maxn];
vector<int> ans;

inline void go(int x) 
{ 
	if ( pos == x ) return ; 
	swap(s[pos], s[x]); swap(s[pos + 1], s[x + 1]);
	ans.push_back(x); pos = x; 
}

inline void Check()
{
	pos = 0; n = m; REP(i, 1, n) if ( t[i] == '_' ) { pos = i; break ; }
	for ( auto it : ans ) 
	{
		if ( t[it] == '_' || t[it + 1] == '_' ) { cerr << " Fuck u ____ " << endl; exit(0); } 
		swap(t[pos], t[it]); swap(t[pos + 1], t[it + 1]);
		pos = it;
	}
	int num = 0; REP(i, 1, n) if ( t[i] == 'A' ) ++ num;
	REP(i, 1, n)
	{
		if ( t[i] == 'A' ) -- num;
		if ( t[i] == 'B' && num ) { cerr << " Wrong !!! " << endl; exit(0); } 
	}
	cerr << "AC ~~~ HA ~~ HA ~~ " << endl;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1); REP(i, 1, n) t[i] = s[i]; m = n;
	REP(i, 1, n)
		if ( s[i] == 'A' ) ++ num[i & 1];
		else ++ num[2 + (i & 1)];
	if ( !(num[0] == num[1] || num[0] == num[1] - 1) ) { puts("-1"); return 0; } 
	if ( abs(num[0] + num[2] - num[1] - num[3]) > 1 ) { puts("-1"); return 0; } 
	REP(i, 1, n) if ( s[i] == '_' ) { pos = i; break ; }

	while ( s[n] == 'B' ) -- n;
	for ( int i = n - 3; i >= 1; -- i )  if ( s[i] == 'B' && s[i + 1] == 'B' ) 
	{ 
		go(n - 1); go(i);
		while ( s[n] == 'B' ) -- n;
	}

	int val = num[0] + num[1]; bool flag = true;
	REP(i, 1, n) 
	{
		if ( s[i] == 'A' ) -- val;
		if ( s[i] == 'B' && val ) flag = false;
	}
	int now = n - 2, num = 0;
	if ( flag ) goto Next ;

	REP(i, 1, n) printf("%c", s[i]); puts("");
	go(n - 1);
	REP(i, 1, n - 3) if ( s[i] == 'A' && s[i + 1] == 'A' ) { go(i); go(n - 3); now = n - 4; num = n; break ; } 
	while ( now >= 2 ) 
	{
		if ( s[now - 1] == 'A' && s[now] == 'B' ) { go(num - 1); go(now - 1); -- num; -- now; }
		-- now;
	}
	if ( s[1] == 'B' && s[2] == 'A' ) { go(1); go(num - 1); go(2); } 

Next : ; 
	printf("%d\n", ans.size());
	for ( auto it : ans ) printf("%d ", it); puts("");

	Check();
	return 0;
}
