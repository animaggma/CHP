// GCD խնդրի լուծում
#include <iostream> 
#include <cmath>
using namespace std;

int GcdOfNumbers(int a, int b) {
	a = abs(a);
	b = abs(b);
	
	while ( b!= 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;

}

int main() {
	int a, b;
	cout << "Input two numbers: " << endl;
	cin >> a >> b;
	cout<< "GCD of "<< a << " and "<< b << " is " << GcdOfNumbers(a, b);

}
