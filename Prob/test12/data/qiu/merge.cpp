#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MN 100005
int n,a[MN],b[MN];
int work(int l,int r){
	if(l==r)return 0;
	int mid=(l+r)>>1;
	int res=work(l,mid)+work(mid+1,r);	
	for(int j=l;j<=r;++j)b[j]=a[j];
	int p1=l,p2=mid+1;
	for(int j=l;j<=r;++j){
		if(p1<=mid&&(b[p1]<=b[p2]||p2==r+1)){
			a[j]=b[p1++];
		}
		else{
			a[j]=b[p2++];
			res+=(mid-p1+1);
		}
	}
	return res;
}
signed main(){
	freopen("data5.in","r",stdin);
	freopen("data5.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	printf("%lld\n",work(1,n));
	return 0;
}
