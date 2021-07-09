/***************************************************************
	File name: AGC044E.cpp
	Author: ljfcnyali
	Create time: 2021年07月09日 星期五 17时10分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define double long double
#define pdd pair<double, double>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, pos, Stack[maxn], tot; double C[maxn], ans;
pii A[maxn], t[maxn];

pii operator +(pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }
pii operator -(pii a, pii b) { return pii(a.first - b.first, a.second - b.second); }
pii operator *(int a, pii b) { return pii(a * b.first, a * b.second); }
double operator *(pdd a, pdd b) { return a.first * b.second - a.second * b.first; } 
inline pdd get(int a, int b) { return pdd(b - a, C[b] - C[a]); }

signed main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%lld", &n); 
	REP(i, 1, n) { scanf("%lld", &A[i].first); if ( A[i].first > A[pos].first ) pos = i; } 
	REP(i, 1, n) scanf("%lld", &A[i].second);

	if ( A[pos].first == 0 ) { cout << 0 << endl; return 0; }

	REP(i, 1, n) A[i + n] = A[i];
	REP(i, pos + 1, pos + n) A[i - pos] = A[i];

	t[1] = pii(1, 0);
	REP(i, 2, n - 1)
		t[i] = 2 * (pii(0, A[i - 1].second) + t[i - 1]) - t[i - 2];
	pii cur = 2 * (t[n - 1] + pii(0, A[n - 1].second)) - t[n - 2];
	double x = 0; 
	if ( cur.first != 0 ) x = -cur.second * 1.0 / cur.first;
	REP(i, 1, n - 1) C[i] = t[i].first * x + t[i].second;

	REP(i, 1, n - 1) ans += C[i];
	REP(i, 1, n) C[i] = A[i].first - C[i];
	C[0] = C[n];

	Stack[++ tot] = 0; Stack[++ tot] = 1;
	REP(i, 2, n)
	{
		while ( tot >= 2 && get(Stack[tot - 1], Stack[tot]) * get(Stack[tot - 1], i) > 0 ) -- tot;
		Stack[++ tot] = i;
	}

	REP(i, 2, tot)
	{
		pdd a = pdd(Stack[i - 1], C[Stack[i - 1]]), b = pdd(Stack[i], C[Stack[i]]);
		ans += (b.second + a.second) * (b.first - a.first + 1) / 2;
		ans -= a.second;
	}

	printf("%.10Lf\n", ans / n);
    return 0;
}
