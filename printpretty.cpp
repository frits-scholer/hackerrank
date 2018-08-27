#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;
	/* Enter your code here */
		cout << left << nouppercase << showbase << hex << (long) A << endl;
		cout.precision(2);
		cout <<  showpos << setw(0xf) << right << setfill('_') << fixed << B << endl;
		cout.precision(9);
		cout << noshowpos << scientific << uppercase << C << endl;
	}
	return 0;
}
