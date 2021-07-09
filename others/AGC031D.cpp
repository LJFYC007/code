/***************************************************************
	File name: AGC031D.cpp
	Author: ljfcnyali
	Create time: 2021年03月05日 星期五 21时37分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m;
vector<int> p, q, ans;

vector<int> operator *(vector<int> a, vector<int> b) { vector<int> c(n + 1); REP(i, 1, n) c[i] = a[b[i]]; return c; } 
vector<int> Inv(vector<int> a) { vector<int> b(n + 1); REP(i, 1, n) b[a[i]] = i; return b; }

inline vector<int> power(vector<int> a, int b)
{
	if ( !b ) { vector<int> r(n + 1); REP(i, 1, n) r[i] = i; return r; } 
	vector<int> r = a; -- b;
	while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
	return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); p.resize(n + 1); q.resize(n + 1);
	REP(i, 1, n) scanf("%d", &p[i]); REP(i, 1, n) scanf("%d", &q[i]);
	int k = (m - 1) / 6, now = k * 6;	
	vector<int> a = power(q * Inv(p) * Inv(q) * p, k);
	p = a * p * Inv(a); q = a * q * Inv(a);
	if ( now + 1 == m ) ans = p;
	else if ( now + 2 == m ) ans = q;
	else 
	{
		REP(i, now + 3, m) { vector<int> h = q * Inv(p); p = q; q = h; }
		ans = q;
	}
	REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
