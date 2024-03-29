#include <vector>
#include <iostream>
#include <string>
using namespace std;

void changeOne(string* t, int changeR, bool* checked);
void changeTwo(string* t, int changeR, bool* checked);
void changeThr(string* t, int changeR, bool* checked);
void changeFr(string* t, int changeR, bool* checked);

string sChange(string a) {// 시계방향으로 회전
	string result = a;
	result[0] = a[a.size() - 1];
	for (int i = 0; i < a.size() - 1; i++) {
		result[i + 1] = a[i];
	}
	return result;
}
string bChange(string a) {// 반시계방향으로 회전
	string result = a;
	result[a.size() - 1] = a[0];
	for (int i = 0; i < a.size() - 1; i++) {
		result[i] = a[i + 1];
	}
	return result;
}

void changeOne(string* t, int changeR, bool* checked) {
	if (checked[0] == 0) {
		checked[0] = 1;
		if (changeR == 1) {// 시계방향
			if (t[0][2] != t[1][6])
				changeTwo(t, -1, checked);
			t[0] = sChange(t[0]);

		}
		else {// 반시계
			if (t[0][2] != t[1][6])
				changeTwo(t, 1, checked);
			t[0] = bChange(t[0]);
		}
	}
}

void changeTwo(string* t, int changeR, bool* checked) {
	if (checked[1] == 0) {
		checked[1] = 1;
		if (changeR == 1) {
			if (t[0][2] != t[1][6])
				changeOne(t, -1, checked);
			if (t[1][2] != t[2][6])
				changeThr(t, -1, checked);
			t[1] = sChange(t[1]);
		}
		else {
			if (t[0][2] != t[1][6])
				changeOne(t, 1, checked);
			if (t[1][2] != t[2][6])
				changeThr(t, 1, checked);
			t[1] =bChange(t[1]);
		}
	}
}

void changeThr(string* t, int changeR, bool* checked) {
	if (checked[2] == 0) {
		checked[2] = 1;

		if (changeR == 1) {
			if (t[2][2] != t[3][6])
				changeFr(t, -1, checked);
			if (t[1][2] != t[2][6])
				changeTwo(t, -1, checked);
			t[2] = sChange(t[2]);
		}
		else {
			if (t[2][2] != t[3][6])
				changeFr(t, 1, checked);
			if (t[1][2] != t[2][6])
				changeTwo(t, 1, checked);
			t[2] = bChange(t[2]);
		}
	}
}

void changeFr(string* t, int changeR, bool* checked) {
	if (checked[3] == 0) {
		checked[3] = 1;
		if (changeR == 1) {// 시계방향
			if (t[2][2] != t[3][6])
				changeThr(t, -1, checked);
			t[3] = sChange(t[3]);

		}
		else {// 반시계
			if (t[2][2] != t[3][6])
				changeThr(t, 1, checked);
			t[3] = bChange(t[3]);
		}
	}
}

int main() {
	string t[4];
	int result = 0;
	bool checked[4] = { 0, };// 이미 한 번 돌았는지 확인하기 위한 bool
	int n, buf, buf2;
	// 입력 및 초기화
	for (int i = 0; i < 4; i++)
		cin >> t[i];
	cin >> n;
	int *changeNum = new int[n];// 회전할 애
	int *changeR = new int[n];// 회전 방향
	for (int i = 0; i < n; i++) {
		cin >> changeNum[i] >> changeR[i];
	}

	for (int i = 0; i < n; i++) // 회전
	{	// 처음 회전한 톱니바퀴 기준 회전 시작
		// 회전 시작 후 영향을 준다면, 계속해서 함수에 들어가서 회전시킬 것
		// 한 번 이상의 회전은 안되기 때문에 checked

		// 실패 이유 : 함수로 관리하지 않아 복잡해졌고, 헷갈리면서 오류가 난 것 같음
		// 앞으로 발전 방향 : 시계/반시계 방향 회전을 좀 더 깔끔하게 만들 수 있을 것 같음 ex. 벡터 사용
		if (changeNum[i] == 1) {
			changeOne(t, changeR[i], checked);
		}
		else if (changeNum[i] == 2) {
			changeTwo(t, changeR[i], checked);
		}
		else if (changeNum[i] == 3) {
			changeThr(t, changeR[i], checked);
		}
		else {// changeNum==4
			changeFr(t, changeR[i], checked);
		}

		// 초기화
		for (int j = 0; j < 4; j++)
			checked[j] = 0;
	}
	// 각 결과를 더함
	if (t[0][0] == '1') result += 1;
	if (t[1][0] == '1') result += 2;
	if (t[2][0] == '1') result += 4;
	if (t[3][0] == '1') result += 8;

	cout << result << '\n';
	return 0;
}
