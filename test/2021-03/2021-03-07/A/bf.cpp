/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年03月07日 星期日 10时17分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

map<vector<int>, int> Map;
vector<int> a;
bool vis[maxn];

inline void Check(vector<int> a)
{
	if ( Map.count(a) ) return ; 
	vector<int> b;
	REP(i, 1, a[0] - 1) { b = a; b[0] -= i; if ( !Map.count(b) ) Check(b); }
	b.clear(); for ( int i = 1; i < a.size(); ++ i ) b.push_back(a[i]); if ( !Map.count(b) ) Check(b); 

	REP(i, 0, 20) vis[i] = false;
	REP(i, 1, a[0] - 1) { b = a; b[0] -= i; vis[Map[b]] = true; }
	b.clear(); for ( int i = 1; i < a.size(); ++ i ) b.push_back(a[i]); vis[Map[b]] = true;
	REP(i, 0, 20) if ( !vis[i] ) { Map[a] = i; break ; } 

	// if ( a.size() != 4 ) return ; 
	// printf("%d:", Map[a]);
	// for ( auto it : a ) printf("%d ", it); puts("");
}

inline void DFS(int x, int lst)
{
	if ( x > 1 ) Check(a);
	if ( x == n + 1 ) return ; 
	REP(i, lst, 5) { a.push_back(i); DFS(x + 1, i); a.pop_back(); } 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	vector<int> a; Map[a] = 0;
	DFS(1, 1);	
    return 0;
}
