#include<iostream>
#include<algorithm>
#include<list>
#include<set>
#include<map>

using namespace std;

map<int, int>mt;
int main() {
	//ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n; scanf("%d", &n);
	int cnt = 1;
	mt[1000000000] = 1;
	map<int, int>::iterator it1, it2;
	while (n--) {
		int x, y; scanf("%d%d", &x, &y);
		it1 = mt.lower_bound(y);
		if (it1 == mt.begin()){
			printf("%d %d\n", x, it1->second);
			//cout << x << " " << it1->second << endl;
		}
		else if (it1 == mt.end()) {
			--it1;
			printf("%d %d\n", x, it1->second);
			//cout<<x<<" "<<it1->second<<endl;
		}
		else {
			int p1, p12;
			int p2, p22;
			p1 = it1->first, p12 = it1->second;
			--it1;
			p2 = it1->first, p22 = it1->second;
			if (p1 - y < abs(p2 - y) ){
				printf("%d %d\n", x, p12);
				//cout << x << " " << p12 << endl;
			}
			else {
                if(p1 - y == abs(p2 - y) ){
                    printf("%d %d\n",x,min(p12,p22));
                }
				else printf("%d %d\n", x, p22);
				//cout << x << " " << p22 << endl;
			}

		}
		if(mt.find(y)!=mt.end()){
            mt[y]=min(mt[y],x);
		}
		else
            mt[y]=x;
	}

}
