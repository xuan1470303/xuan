#include<iostream>
using namespace std;
int A(int m, int n)
{
	if (m == 0) { return n + 1; }
	else if (n == 0) { return A(m - 1, 1); }
	else { return A(m - 1, A(m, n - 1)); }
}

int main()
{
	int m, n;
	cout << "請輸入二整數m,n --> A(m,n)" << endl;
	cin >> m >> n;
	cout << A(m, n);
}