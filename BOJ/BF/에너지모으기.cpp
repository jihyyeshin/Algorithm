#include <iostream>
#include <vector>
using namespace std;

int go(vector<int> &a) {
	int n = a.size();
	if (n == 2) return 0;// 에너지를 모을 수 있는게 없음
	int ans = 0;
	for (int i = 1; i < n - 1; i++) {
		int energy = a[i - 1] * a[i + 1];// 에너지 모으기
		vector<int> b(a);
		b.erase(b.begin() + i);
		energy += go(b);
		if (ans < energy)
			ans = energy;
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cout << go(a) << '\n';
	return 0;
}