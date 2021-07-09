/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年09月21日 星期六 14时53分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;

int n, ans;
struct node
{
    int val, pos;
    bool operator < (const node &a) const { return val > a.val; }
} a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i].val), a[i].pos = i;
    sort(a + 1, a + n + 1);
    REP(i, 1, n)
    {
        ans += a[i].val * (i - 1) + 1;
    }
    printf("%d\n", ans);
    REP(i, 1, n) printf("%d ", a[i].pos); puts("");
    return 0;
}
