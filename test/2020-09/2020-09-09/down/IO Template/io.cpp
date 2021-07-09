/*
#include <bits/stdc++.h>
using namespace std;
*/
const int MAXBUF=20000005;
char B[MAXBUF],*Si=B,*Ti=B;
inline char getc()
{if (Si==Ti) Ti=(Si=B)+fread(B,1,MAXBUF,stdin);
if (Si==Ti) return 0;
return *Si++;
}
template <class T>
inline void read(T &a)
{static char c;
while ((c=getc())<'0'||c>'9');a=c-'0';
while ((c=getc())>='0'&&c<='9') a=(a<<3)+(a<<1)+c-'0';
}
char Buff[MAXBUF],*sti=Buff;
template <class T>
inline void write(T a)
{if (a==0) {*sti++='0';return;}
int t[21],cnt=0;
while (a) t[++cnt]=a%10,a/=10;
for (int i=cnt;i>=1;i--) *sti++='0'+t[i];
}
/*
int a[1000005];
int main (){
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int i,n;read(n);
	for (i=1;i<=n;i++) read(a[i]);
	for (i=1;i<=n;i++) write(a[i]),*sti++=' ';
	*sti++='-';*sti++='1';*sti++='\n';
	fwrite(Buff,1,sti-Buff,stdout);
	return 0;
}
*/
