/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年01月29日 星期五 20时43分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q, a[maxn], b[maxn], k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, m) scanf("%d", &b[i]);
	while ( q -- ) 
	{
		int op, x, y; scanf("%d", &op);
		if ( op == 1 ) { scanf("%d%d", &x, &y); a[x] = y; }
		if ( op == 2 ) { scanf("%d%d", &x, &y); b[x] = y; }
		if ( op == 3 ) 
		{
			scanf("%d", &k); int ans = -10000;
			REP(i, 1, n) 
			{
				vector<int> p, q;
				REP(j, 1, n) if ( i != j ) p.push_back(a[j]);
				REP(j, 1, m) q.push_back(b[j]);
				sort(p.begin(), p.end()); sort(q.begin(), q.end());
				int sum = k, now = k;
			}
		}
	}
    return 0;
}
