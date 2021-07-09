#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=1000000;
int n,sum[N+5];
void add(int x){
	while(x<=N)sum[x]++,x+=x&(-x);
}
int ask(int x){
	int res=0;
	while(x)res+=sum[x],x-=x&(-x);
	return res;
}
int main(){	
	cin>>n;
	LL res=0;
	for(int i=1;i<=n;++i){
		int a;cin>>a;
		res+=i-1-ask(a);
		add(a);
	}
	printf("%lld\n",res);
	return 0;
}
