/***************************************************************
	File name: onmyodo.cpp
	Author: ljfcnyali
	Create time: 2020年10月29日 星期四 11时09分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, k, sum, ans, a[maxn * 10];
vector<int> val;

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( (c < '0' || c > '9') && c != '-' ) c = getchar();
    bool flag = false;
    if ( c == '-' ) { flag = true; c = getchar(); }
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
    if ( flag ) x = -x;
}

signed main()
{
	freopen("input.txt", "r", stdin);
    read(n);
    REP(i, 1, n)
    {
        read(k); REP(j, 1, k) { read(a[j]); sum += a[j]; }
		if ( k % 2 == 1 ) ans += a[(k + 1) / 2];
		else { ans += min(a[k / 2], a[k / 2 + 1]); val.push_back(max(a[k / 2], a[k / 2 + 1]) - min(a[k / 2], a[k / 2 + 1])); }
    }
	sort(val.begin(), val.end());
	reverse(val.begin(), val.end());
	cout << ans << endl;
	cerr << val.size() << endl;
    int op = 0;
	for ( auto it : val ) 
    {
		if ( !op ) ans += it;
		op ^= 1;
    }
    printf("%lld\n", ans);
    return 0;
}
