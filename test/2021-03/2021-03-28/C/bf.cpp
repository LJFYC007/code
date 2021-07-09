/***************************************************************
    File name: C.cpp
    Author: ljfcnyali
    Create time: 2021年03月28日 星期日 09时07分17秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 1e5 + 10;
const int INF = 1e9;
 
int n, a[maxn], b[maxn], ret = INF;
vector<int> ans;
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) scanf("%d", &b[i]);
    REP(x, 0, 2048)
    {
        int sum = 0;
        REP(i, 1, n) sum += abs(a[i] - (b[i] ^ x));
        if ( sum < ret ) { ret = sum; ans.clear(); }
        if ( ret == sum ) ans.push_back(x);
    }
    printf("%d %d\n", ret, ans.size());
    return 0;
}

