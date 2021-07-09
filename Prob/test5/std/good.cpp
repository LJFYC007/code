#include<bits/stdc++.h>
using namespace std;
int a[10000];
int main(){
	freopen("good.in","r",stdin);
	freopen("good.out","w",stdout);
	int m;
	scanf("%d",&m);
	while(m--){
		int n=0;
		while(1){
			int x;
			scanf("%d",&x);
			if(!x)break;
			a[++n]=x;
		}
		bool flg=0,fl=0,flag=1;
		for(int i=2;i<=n;i++){
			if(a[i]==a[i-1]){
				flag=0;
				break;
			}
			if(a[i-1]<a[i])flg=1;
			if(a[i-1]>a[i])fl=1;
			else if(fl){
				flag=0;
				break;
			}
		}
		if(fl&&flag&&flg)printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
