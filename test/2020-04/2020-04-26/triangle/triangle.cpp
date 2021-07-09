/***************************************************************
	File name: triangle.cpp
	Author: ljfcnyali
	Create time: 2020年04月28日 星期二 19时17分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e3 + 10;

int n, ans;
pii a[maxn], b[maxn];

inline bool cmp(pii x, pii y) { return x.y < y.y; }

inline bool cmp1(pii x, pii y) { return acos(x.first, x.second) < acos(y.first, y.second); }

int main()
{
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1, cmp); 
    REP(i, 3, n)
    {
        REP(j, 1, i - 1) b[j] = pii(a[j].first - a[i].first, a[j].second - a[i].second);
        sort(b + 1, b + i, cmp1);
        pii sum = pii(b[1].first, b[1].second);
        REP(j, 2, i - 1)
        {
            ans += sum.first
        }
    }
    return 0;
}
