/***************************************************************
	File name: CF1242E.cpp
	Author: ljfcnyali
	Create time: 2021年03月31日 星期三 21时22分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;

int n, k;
vector<int> ans[maxn];
deque<int> p;
pii a[maxn];

inline vector<int> Maintain(int y, int num)
{
	vector<int> q;
	REP(i, 1, y - num) { q.push_back(p.back()); p.pop_back(); } p.push_back(q.back());
	REP(i, 1, num) { q.push_back(++ k); p.push_back(k); } p.push_back(q.front());
	p.push_front(p.back()); p.pop_back();
	return q;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i].first); a[i].second = i; } 
	sort(a + 1, a + n + 1);
	REP(i, 1, a[n].first) { p.push_back(++ k); ans[a[n].second].push_back(k); }
	for ( int i = n - 1; i >= 2; -- i ) 
	{
		if ( p.size() - a[i].first + 2 >= a[i - 1].first ) ans[a[i].second] = Maintain(a[i].first, 0);
		else
		{
			int num = 0, x = p.size() - a[i].first + 2;
			while ( x < a[i - 1].first ) { x += 2; ++ num; } 
			ans[a[i].second] = Maintain(a[i].first, num);
		}
	}
	if ( n > 1 ) ans[a[1].second] = Maintain(a[1].first, p.size() == a[1].first);
	printf("%d\n", k);
	REP(i, 1, n) { for ( auto it : ans[i] ) printf("%d ", it); puts(""); } 
    return 0;
}
