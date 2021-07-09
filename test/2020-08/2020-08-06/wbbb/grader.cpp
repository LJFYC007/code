#include <bits/stdc++.h>
#include "wbbb.h"

using namespace std;

namespace Work
{
    inline void main()
    {
        int n = 720; 
        init();
        srand(time(0));
        for ( int i = 1; i <= 10; ++ i ) 
        {
            int x = rand() % n + 1, y = rand() % n + 1; 
            while ( x == y ) y = rand() % n + 1;
            int k = helpAlice(x, y);
            int op = rand() % 2;
            if ( op == 0 ) 
            {
                if ( helpBob(x, k) != 1 ) { printf("WA %d %d\n", x, y); return ; }
            }
            else 
            {
                if ( helpBob(y, k) != 0 ) {  printf("WA %d %d\n", x, y); return ; }
            }
        }
        puts("skydogli AK IOI!!");
    }
}

int main()
{
    Work :: main();
    return 0;
}
