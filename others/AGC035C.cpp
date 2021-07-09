/***************************************************************
	File name: AGC035C.cpp
	Author: ljfcnyali
	Create time: 2021年02月07日 星期日 16时35分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n;
vector<pii> ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	int x = 1; REP(i, 1, 18) { if ( n == x ) { puts("No"); return 0; } x *= 2; }
	puts("Yes");
	ans.push_back(pii(1, n + 2));
	ans.push_back(pii(n + 2, 3));
	ans.push_back(pii(3, n + 1));
	ans.push_back(pii(n + 1, 2));
	ans.push_back(pii(2, n + 3));
	for ( int i = 4; i < n; i += 2 ) 
	{
		ans.push_back(pii(i, n + 1)); ans.push_back(pii(i + 1, n + 1));
		ans.push_back(pii(n + i, i + 1)); ans.push_back(pii(n + i + 1, i));
	}
	if ( n > 3 && !(n & 1) ) 
	{
		int x = n - 2, y = (n ^ x) ^ 1;	
		ans.push_back(pii(n, x));
		ans.push_back(pii(n + n, y));
	}
	for ( auto it : ans ) printf("%d %d\n", it.first, it.second);
    return 0;
}
