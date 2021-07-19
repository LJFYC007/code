/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 10时52分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, p[maxn], ans[maxn], b[maxn], k;
struct node { int l, a[3]; } a[maxn];

int main()
{
    freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);	
	REP(i, 1, n) { scanf("%d", &a[i].l); REP(j, 1, a[i].l) scanf("%d", &a[i].a[j]); }
    freopen("output.txt", "r", stdin);
	REP(i, 1, n) scanf("%d", &p[i]);
	REP(i, 1, n) scanf("%d", &ans[i]);
	REP(i, 1, n) assert(p[i] != 0);
	REP(i, 1, n) 
		if ( ans[i] == 0 ) REP(j, 1, a[p[i]].l) b[++ k] = a[p[i]].a[j];
		else for ( int j = a[p[i]].l; j >= 1; -- j ) b[++ k] = a[p[i]].a[j];
	// cout << a[p[1]].a[1] << " " << a[p[1]].a[2] << endl;
	freopen("ansput.txt", "w", stdout);
	// REP(i, 1, k) printf("%d ", b[i]); puts("");
	REP(i, 1, k) 
	{
		if ( b[i] != b[k - i + 1 ] ) 
		{
			puts("NO");
			return 0;
		}
		assert(b[i] == b[k - i + 1]);
	}
	puts("YES");
    return 0;
}
