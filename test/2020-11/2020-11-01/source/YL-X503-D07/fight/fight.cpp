#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long u64;
#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int p=1145141923;
const int Mod = 1145141923;

int a[10000005],b[10000005];
int n,m,q,w;
u64 seed;

u64 rnd()
{
	u64 x = seed;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return seed = x;
}

signed main(){
	freopen("fight.in","r",stdin);
	freopen("fight.out","w",stdout);
	scanf("%lld%lld%lld%llu%lld",&n,&m,&q,&seed,&w);
	for(int i=0;i<=n;++i)a[i]=rnd()%w;
	for(int i=0;i<=m;++i)b[i]=rnd()%w;
    REP(i, 1, m) b[i] = (b[i] + b[i - 1]) % Mod;
	int l,r;
    REP(o, 1, q)
    {
		scanf("%lld%lld", &l, &r);
        int ans = 0; 
        REP(i, 0, n)
        {
            int L = max(0ll, l - i), R = min(m, r - i);
            if ( L <= R ) ans = (ans + a[i] * (b[R] - (L >= 1 ? b[L - 1] : 0))) % Mod;
        }
        printf("%lld\n", (ans + Mod) % Mod);
	}
	return 0;
}
