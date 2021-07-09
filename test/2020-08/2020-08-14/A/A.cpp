/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年08月14日 星期五 08时50分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, l, r, a[maxn], f[maxn];
struct node { int lson, rson, Max, ; } Tree[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &l, &r);
    REP(i, 1, n) { scanf("%d", &a[i]); a[i] += a[i - 1]; }
    REP(i, 1, n)
    {
        int L = i - r + 1, R = i - l + 1;
        if ( L > 1 ) Delete(L - 1);
    }
    return 0;
}
