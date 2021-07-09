#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<set>
#define N 4000005 
#define ll long long
#define mod 998244353
using namespace std;
int n,len=1,L,g,ng,li,ri,la,ans;
set<int>si;
int s[N],fc[N],ny[N],f[N],R[N],cal[N];
int po(int a,int b){
	int an=1;
	while(b!=0){
		if(b&1) an=(ll)an*a%mod;
		a=(ll)a*a%mod;b=(b>>1);
	}
	return an;
}
int C(int a,int b){
	if(a<0||b<a) return 0;
	return (ll)fc[b]*ny[a]%mod*ny[b-a]%mod;
}
void dft(int *e,int op){
	for(int i=0;i<len;i++)
		if(i<R[i]) swap(e[i],e[R[i]]);
	for(int i=1;i<len;i<<=1){
		int wn=po((op>0)?g:ng,(mod-1)/(i<<1));
		for(int j=0;j<len;j+=(i<<1))
			for(int k=0,w=1;k<i;k++,w=(ll)w*wn%mod){
				int t1=e[j+k],t2=(ll)w*e[j+k+i]%mod;
				e[j+k]=(t1+t2)%mod;e[j+k+i]=(t1-t2+mod)%mod;
			}
	}
	if(op<0){
		int ni=po(len,mod-2);
		for(int i=0;i<len;i++) e[i]=(ll)e[i]*ni%mod;
	}
}
int get_num(int a,int b){
	int sum=0;
	for(int i=0;i<=b;i++) sum=(sum+(ll)cal[i]*cal[a-i]%mod)%mod;
	return sum;
}
void push_la(){
	while(la!=n){
		auto it=si.lower_bound(la+1);
		if((*it)==la+1) la++;
		else break;
	}
}
void get_int(){li=la+1;auto it=si.lower_bound(li);ri=(*it)-1;}
int main()
{
//	freopen("stacktwo.in","r",stdin);
//	freopen("stacktwo.out","w",stdout);
	scanf("%d",&n);g=3,ng=(mod+1)/3;
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	fc[0]=ny[0]=1;for(int i=1;i<=4*n;i++) fc[i]=(ll)fc[i-1]*i%mod,ny[i]=po(fc[i],mod-2);
	while(len<=2*n) len=(len<<1),L++;
	cal[0]=f[0]=1;for(int i=1;i<len/2;i++) cal[i]=f[i]=(C(i,2*i)-C(i-1,2*i)+mod)%mod;
	for(int i=1;i<=n;i++) f[i]=f[i+1];
	/*for(int i=0;i<len;i++) R[i]=((R[i>>1]>>1)|((i&1)<<(L-1)));
	dft(f,1);for(int i=0;i<len;i++) f[i]=(ll)f[i]*f[i]%mod;
	dft(f,-1);*/si.insert(0);si.insert(n+1);la=0;int mul=f[n-1];
//	for(int i=0;i<len;i++) cout<<f[i]<<" ";cout<<endl;
	for(int i=1;i<=n;i++){
		get_int();if(s[i]>ri) break;
		if(i==n){ans++;break;}
		int tmp=(ll)mul*po(f[ri-li],mod-2)%mod;
//		cout<<tmp<<" "<<mul<<endl;
		int rem=ri-s[i],tp=0;
//		cout<<rem<<endl;
		if(rem<ri-li-rem) tp=get_num(ri-li,rem-1);
		else tp=(f[ri-li]-get_num(ri-li,ri-li-rem)+mod)%mod;
//		cout<<tp<<" - "<<ri-li<<" - "<<ri-li-rem<<endl;
		ans=(ans+(ll)tp*tmp%mod)%mod;
		mul=(ll)tmp*f[max(0,rem-1)]%mod*f[max(0,ri-li-rem-1)]%mod;
		si.insert(s[i]);push_la();	
	}
	printf("%d\n",ans);
	return 0;
}
