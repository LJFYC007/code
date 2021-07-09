/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 09时49分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, h[maxn];

int main()
{
    freopen("relics.in", "r", stdin);
    freopen("relics1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &h[i]);
    REP(i, 1, m)
    {
        int l, r; scanf("%d%d", &l, &r);
        int ans = 0;
        REP(i, l, r) 
        {
            int Min = INF;
            REP(j, i, r) 
            {
                Min = min(Min, h[j]);
                ans = max(ans, Min * (j - i + 1));
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
