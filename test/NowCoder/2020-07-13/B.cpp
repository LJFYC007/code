/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 14时08分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 2010;
const double eps = 1e-12;

int n, m, ans = 1;
pii a[maxn], t[maxn];

inline pii Get(pii x) { return pii(-x.second, x.first); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%lf%lf", &a[i].first, &a[i].second); 
    REP(i, 1, n)
    {
        m = 0;
        REP(j, 1, n)
        {
            if ( i == j ) continue ;
            double X = a[i].first * a[j].second, Y = a[j].first * a[i].second;
            if ( X >= Y - eps && X <= Y + eps ) continue ;
            pii a1 = pii(a[i].first / 2, a[i].second / 2), a2 = pii(a[j].first / 2, a[j].second / 2);
            pii n1 = Get(a1), n2 = Get(a2);
            double k1 = -(-n2.y * a1.x + n2.y * a2.x + n2.x * a1.y - n2.x * a2.y) / (n2.x * n1.y - n2.y * n1.x);
            double k2 = -(-n1.y * a1.x + n1.y * a2.x + n1.x * a1.y - n1.x * a2.y) / (n2.x * n1.y - n2.y * n1.x);
            // if ( i == 3 && j == 1 ) 
            // {
                // printf("%lf %lf\n", k1, k2);
                // printf("%lf %lf\n", a1.first, a1.second);
                // printf("%lf %lf\n", a2.first, a2.second);
            // }
            t[++ m] = pii(a1.x + n1.x * k1, a1.y + n1.y * k1);
        }
        sort(t + 1, t + m + 1);
        // REP(j, 1, m) printf("%lf %lf ;", t[j].first, t[j].second); puts("");
        if ( !m ) continue ; 
        int num = 1;
        REP(j, 2, m)
        {
            if ( t[j].first - eps <= t[j - 1].first && t[j - 1].first <= t[j].first + eps 
              && t[j].second - eps <= t[j - 1].second && t[j - 1].second <= t[j].second + eps 
                    ) ++ num;
            else { ans = max(ans, num + 1); num = 1; }
        }
        ans = max(ans, num + 1);
    }
    printf("%d\n", ans);
    return 0;
}
