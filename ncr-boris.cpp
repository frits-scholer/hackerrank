#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <vector>

typedef unsigned long long llu;
#define f(i,s,e) for(unsigned int i=s;i<e;++i)
#define fe(i,s,e) for(unsigned int i=s;i<=e;++i)
typedef std::vector<llu> lvector;
lvector* vv;
int main() {

	vv = new lvector[1001];
	vv[0].push_back(1);
	vv[1].push_back(1); vv[1].push_back(1);
	fe(i, 2, 1000) {
		vv[i].push_back(1);
		f(j, 1, vv[i - 1].size()) {
			vv[i].push_back((vv[i - 1][j - 1] + vv[i - 1][j]) % 1000000000);
		}
		vv[i].push_back(1);
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int N;
		scanf("%d", &N);
		printf("%llu", vv[N][0]);
		f(i, 1, vv[N].size()) {
			printf(" %llu", vv[N][i]);
		}
		printf("\n");
	}
}


