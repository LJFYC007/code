/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年12月18日 星期三 10时50分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int N = 1e6;

int n, m, a[maxn], sum[maxn], c[maxn][2], ans;
string s;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val, int opt)
{
    for ( int i = pos; i <= N; i += lowbit(i) ) c[i][opt] += val;
}

inline int query(int pos, int opt)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i][opt];
    return sum;
}

namespace Subtask1
{
    inline int main()
    {
        int k; cin >> s >> k;
        if ( s == "A" ) return 0;
        REP(i, 1, n)
        {
            ans += min(k, query(a[i], 0));  
            add(a[i], 1, 0);
        }
        printf("%d\n", ans);
        return 0;
    }
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    scanf("%d", &m);
    int sum = 0;
    REP(i, 1, 1)
        for (int j = n; j >= 2; -- j)
            if ( a[j] < a[j - 1] ) { ++ sum; swap(a[j], a[j -1]); }
    printf("%d\n", sum);
    return 0;
}
