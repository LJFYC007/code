#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 2147483647;

int n, a[maxn], b[maxn];

inline void print()
{
    int ans = INF;
    REP(i, 1, n - 1) ans = min(ans, abs(b[i] - b[i + 1]));
    printf("%d\n", ans);
}

int main()
{
	freopen("sequence10.in", "r", stdin);
	freopen("sequence10.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);

    sort(a + 1, a + n + 1);
    if ( n % 2 == 0 ) 
    {
        REP(i, 1, n / 2) b[i + i] = a[i];
        REP(i, 1, n / 2) b[i + i - 1] = a[n / 2 + i];
        print();
        return 0;
    }

    int len = n / 2;
    int pos = 0, Min = INF;
    REP(i, 1, n)
    {
        if ( i + len > n ) break ; 
        int val = a[i + len] - a[i];
        if ( val < Min ) { Min = val; pos = i; } 
    }
    int x = 1;
    REP(i, pos, pos + len) { b[x] = a[i]; x += 2; }
    x = 2;
    REP(i, pos + len + 1, n) { b[x] = a[i]; x += 2; }
    REP(i, 1, pos - 1) { b[x] = a[i]; x += 2; } 
    print();
    return 0;
}
