#include<bits/stdc++.h>
const int maxn = 15;
const int mod = 12345678;
const int p1 = 233,p2 = mod + 1 - p1;
typedef long long ll;
int f[1 << maxn];
int g[1 << maxn];
int a[maxn],n,m;
int ans[maxn];
inline void reduce(int & x){ x += x >> 31 & mod; }
int main(){
	std::ios::sync_with_stdio(false),std::cin.tie(0);
	std::cin >> n >> m;
	for(int i=0;i<n;++i) std::cin >> a[i],-- a[i];
	for(int i=0;i<n;++i){
		int p = 0;
		for(int j=0;j<n;++j) p |= (a[j] >= i) << j;
		f[p] = 1;
	}
	for(int i=0;i<m;++i) for(int i=0;i + 1 < n;++i) {
		int a = i,b = i + 1;
		for(int i=0;i<1<<n;++i){
			const int x = i >> a & 1,y = i >> b & 1;
			if(x == y){
				reduce(g[i] += f[i] - mod);
			}else{
				const int i2 = i ^ (1 << a) ^ (1 << b);
				if(x == 1 && y == 0){
					g[i] = (g[i] + ll(p1) * f[i]) % mod;
					g[i2] = (g[i2] + ll(p2) * f[i]) % mod;
				}else{
					g[i] = (g[i] + ll(p2) * f[i]) % mod;
					g[i2] = (g[i2] + ll(p1) * f[i]) % mod;
				}
			}
		}
		for(int i=0;i<1<<n;++i) f[i] = g[i],g[i] = 0;
	}
	for(int i=0;i<1<<n;++i) for(int j=0;j<n;++j) if(i >> j & 1)
		reduce(ans[j] += f[i] - mod);
	for(int i=0;i<n;++i) std::cout << ans[i] << ' ';
}
