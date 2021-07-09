/***************************************************************
  File name: A.cpp
Author: ljfcnyali
Create time: 2021年03月21日 星期日 09时01分29秒
 ***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, num[41];
char s[maxn];
map<vector<int>, int> Map[41][7][7];
bool vis[maxn];

inline void DFS1(int x)
{
	if ( x * 2 <= n ) { vis[x * 2] = true; ++ num[m]; DFS1(x * 2); return ; }
	bool flag = false;
	REP(i, 1, n) if ( !vis[i] ) { vis[i] = true; flag = true; ++ num[++ m]; DFS1(i); return ; }
}

inline int DFS(int x, vector<int> a, int lst1, int lst2)
{
	if ( x == n ) return 1;	
	if ( Map[x][lst1][lst2].count(a) ) return Map[x][lst1][lst2][a];
	int ret = 0;
	if ( s[x] == '0' ) REP(i, 1, 6)				
	{
		if ( a[i] ) 
		{
			vector<int> b = a; -- b[i]; 
			REP(j, 1, i) 
			{
				++ b[lst1]; ++ b[lst2];
				ret = (ret + 1ll * a[i] * DFS(x + 1, b, j - 1, i - j)) % Mod;
				-- b[lst1]; -- b[lst2];
			}
		}
		if ( i == lst1 ) 
		{
			vector<int> b = a;
			REP(j, 2, i) { ++ b[lst2]; ret = (ret + DFS(x + 1, b, j - 1, i - j)) % Mod; -- b[lst2]; }
		}
		if ( i == lst2 ) 
		{
			vector<int> b = a;
			REP(j, 2, i) { ++ b[lst1]; ret = (ret + DFS(x + 1, b, j - 1, i - j)) % Mod; -- b[lst1]; }
		}
	}
	else
	{
		if ( lst1 ) 
		{
			vector<int> b = a; ++ b[lst2];	
			ret = (ret + DFS(x + 1, b, lst1 - 1, 0)) % Mod;
		}
		if ( lst2 ) 
		{
			vector<int> b = a; ++ b[lst1];	
			ret = (ret + DFS(x + 1, b, lst2 - 1, 0)) % Mod;
		}
	}
	Map[x][lst1][lst2][a] = ret; return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1); s[0] = '0';
	vis[1] = true; ++ num[++ m]; DFS1(1);
	vector<int> a(7); REP(i, 1, m) ++ a[num[i]];
	printf("%d\n", DFS(0, a, 0, 0));
	return 0;
}
