/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 20时04分32秒
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
pii a[maxn], b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, (1 << n)) { scanf("%d", &b[i].first); b[i].second = i; }
    for ( int i = n; i >= 1; -- i ) 
    {
        REP(j, 1, (1 << i)) a[j] = b[j];
        REP(j, 1, (1 << i - 1))
        {
            if ( a[j * 2 - 1].first < a[j * 2].first ) 
                b[j] = a[j * 2];
            else b[j] = a[j * 2 - 1];
        }
    }
    cout << (a[1].first < a[2].first ? a[1].second : a[2].second) << endl;
    return 0;
}
