#include<bits/stdc++.h>
using namespace std; 
const int N=1e5+5;
int n,a[N],m,s;
bitset<N>f,g;
int main(){
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout); 
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",a+i);
	sort(a+1,a+n+1);
	if(a[1]!=a[2])printf("%d\n",a[1]),exit(0);
	m=unique(a+1,a+n+1)-a-1;
	s=a[n];
	f[0]=1;
	for(i=s,j=m;i>=1;i--){
		if(a[j]==i){
			f[i]=1;
			for(k=a[j];k<=s;k+=a[j])g[k]=1;
			--j;
		}else if(((f>>i)&g).any())f[i]=1;
	}
	for(i=a[1]-1;!f[i];--i);
	printf("%d\n",i);
}

