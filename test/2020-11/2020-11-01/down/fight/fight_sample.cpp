#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const int p=1145141923;
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
int main(){
	freopen("fight.in","r",stdin);
	freopen("fight.out","w",stdout);
	scanf("%d%d%d%llu%d",&n,&m,&q,&seed,&w);
	for(int i=0;i<=n;++i)a[i]=rnd()%w;
	for(int i=0;i<=m;++i)b[i]=rnd()%w;
	int l,r;
	for(int i=1;i<=q;++i){
		scanf("%d%d",&l,&r);
	}
	return 0;
}
