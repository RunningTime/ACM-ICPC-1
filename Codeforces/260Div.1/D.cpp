#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 101000;
const int Sqrt = 333;
const int NUM = N / Sqrt + 1;
deque<int> que[NUM];
int cnt[NUM][N],n,A[N],m;
int answer;

int main() {
	scanf("%d",&n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d",A+i);
		que[i/Sqrt].push_back(A[i]);
		cnt[i/Sqrt][A[i]] ++;
	}
	scanf("%d",&m);
	while (m--) {
		int op,l,r,v;
		scanf("%d%d%d",&op,&l,&r);
		l = (l+answer-1)%n;
		r = (r+answer-1)%n;
		if (l>r) swap(l,r);
		if (op==1) {
			v = que[r/Sqrt][r%Sqrt];
			que[r/Sqrt].erase(que[r/Sqrt].begin() + r%Sqrt);
			cnt[r/Sqrt][v] --;
			que[l/Sqrt].insert(que[l/Sqrt].begin() + l%Sqrt,v);
			cnt[l/Sqrt][v] ++;
			for (int i = l/Sqrt; i < r/Sqrt; ++ i) {
				if (que[i].size()>Sqrt) {
					v = que[i].back();
					que[i].pop_back();
					cnt[i][v] --;
					que[i+1].push_front(v);
					cnt[i+1][v] ++;
				}
			}
		} else {
			scanf("%d",&v);
			v = (v+answer-1)%n+1;
			answer = 0;
			r ++;
			while (l<r && l%Sqrt) {
				answer += que[l/Sqrt][l%Sqrt]==v;
				l ++;
			}
			while (l<r && r%Sqrt) {
				r --;
				answer += que[r/Sqrt][r%Sqrt]==v;
			}
			for (int i = l/Sqrt; i < r/Sqrt; ++ i) {
				answer += cnt[i][v];
			}
			printf("%d\n",answer);
		}
	}
	return 0;
}
