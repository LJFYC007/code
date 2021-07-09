/***************************************************************
    File name: s.cpp
    Author: ljfcnyali
    Create time: 2021年04月06日 星期二 11时18分25秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 4e5 + 10;
 
int n, m, ans, sum1, sum2, a[maxn], f[maxn], val, Max[maxn], Min[maxn], size[maxn], Maxx;
 
inline pii find(int x) 
{ 
    if ( x == f[x] ) return pii(x, a[x]);
    pii t = find(f[x]); return pii(t.first, t.second + a[x]);
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("s.in", "r", stdin);
    freopen("s.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { f[i] = i; size[i] = 1; } 
    REP(i, 1, m) 
    {
        int s, t, v, w; scanf("%lld%lld%lld%lld", &s, &t, &v, &w);
        pii x = find(s), y = find(t);
        if ( x.first == y.first )
        {
            if ( x.second + v * w != y.second ) { printf("%lld\n", i); return 0 ; } 
            continue ; 
        }
        if ( size[x.first] < size[y.first] ) 
        {
            int ret = -x.second + y.second - v * w;
            a[x.first] += ret; Min[x.first] += ret; Max[x.first] += ret;
            f[x.first] = y.first; size[y.first] += size[x.first];
            Max[y.first] = max(Max[y.first], Max[x.first]);
            Min[y.first] = min(Min[y.first], Min[x.first]);
        }
        else
        {
            int ret = x.second + v * w - y.second;
            a[y.first] += ret; Min[y.first] += ret; Max[y.first] += ret;
            f[y.first] = x.first; size[x.first] += size[y.first];
            Max[x.first] = max(Max[x.first], Max[y.first]);
            Min[x.first] = min(Min[x.first], Min[y.first]);
        }
        int pos = find(s).first;
        if ( find(s).first == find(1).first && find(s).first == find(n).first ) val = Max[pos] - Min[pos];
        else Maxx = max(Maxx, Max[pos] - Min[pos]);
        if ( val && Maxx >= val ) { printf("%lld\n", i); return 0; } 
        if ( n == 39743 && m == 195729 && i == 70090 ) 
			cout << s << " " << t << " " << v << " " << w << " " << find(s).second << " " << find(t).second << " " << find(1).second << endl;
    }
    printf("%lld\n", -val);
    return 0;
}
