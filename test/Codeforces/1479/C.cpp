/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月08日 星期一 10时55分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int L, R, s, p[maxn], a[40][40];
struct node { int u, v, w; } ;
vector<node> ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &L, &R);
	
	if ( L == 1 ) s = 1; 
	else { s = 2; ans.push_back({1, 2, L - 1}); R -= L - 1; }
	-- R;

	ans.push_back({s, 32, 1});
	int val = 0;
	for ( int i = 20; i >= 0; -- i ) if ( (R >> i) & 1 ) 
	{
		ans.push_back({s + i + 1, 32, val + 1});
		val = val | (1 << i);
	}
	REP(i, 1, 21) 
	{
		REP(j, 0, i - 2) 
		{
			ans.push_back({s + j, s + i, a[s + j][s + i - 1]});
			a[s + j][s + i] = a[s + j][s + i - 1];
		}
		a[s + i - 1][s + i] = i == 1 ? 1 : 1 << i - 2;
		ans.push_back({s + i - 1, s + i, a[s + i - 1][s + i]});
	}

	puts("YES");
	printf("32 %d\n", ans.size());
	for ( auto it : ans ) printf("%d %d %d\n", it.u, it.v, it.w);
    return 0;
}
