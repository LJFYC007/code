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

inline void DFS(int x)
{
	int val = 0; bool flag = true; REP(i, 1, n) if ( s[i] == 'A' ) ++ val;
	REP(i, 1, n)
	{
		if ( s[i] == 'A' ) -- val;
		if ( s[i] == 'B' && val ) flag = false;
	}
	if ( flag ) 
	{
		printf("%d\n", ans.size());
		for ( auto it : ans ) printf("%d ", it); puts("");
		exit(0);
	}
	if ( x == n + 1 ) return ;
	
	REP(i, 1, n - 1) if ( s[i] != '_' && s[i + 1] != '_' ) 
	{
		int tt = pos; swap(s[i], s[pos]); swap(s[i + 1], s[pos + 1]); pos = i; ans.push_back(i);
		DFS(x + 1);
		pos = tt; swap(s[i], s[pos]); swap(s[i + 1], s[pos + 1]); ans.pop_back();
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1); REP(i, 1, n) t[i] = s[i]; m = n;
	REP(i, 1, n) if ( s[i] == '_' ) { pos = i; break ; }
	DFS(1);		
	puts("-1");
//	Check();
	return 0;
}
