#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#include "ClassA.h"

using namespace std;

void DemoDouble()
{
	const int R = 3, C = 3;

	srand((unsigned)time(nullptr));

	Matrix<double> m1(R, C);
	m1.FillRandom([]() { return (double)(rand() % 20 - 5); });

	Matrix<double> m2(R, C);
	m2.FillRandom([]() { return (double)(rand() % 10 + 1); });

	cout << "\nMatrix m1:" << endl;
	m1.Print();

	cout << "\nMatrix m2:" << endl;
	m2.Print();

	cout << "\nm1 + m2:" << endl;
	cout << m1 + m2;

	cout << "\nm1 - m2:" << endl;
	cout << m1 - m2;

	cout << "\nm1 * m2:" << endl;
	cout << m1 * m2;

	cout << "\nm1 / m2:" << endl;
	cout << m1 / m2;

	cout << "\nMax of m1 = " << m1.FindMax() << endl;
	cout << "Min of m1 = " << m1.FindMin() << endl;

	Matrix<double> m3 = m1;
	cout << "\nCopy of m1 (m3):" << endl;
	m3.Print();
}

void DemoClassA()
{
	const int R = 2, C = 2;

	srand((unsigned)time(nullptr) + 1);

	Matrix<A> ma(R, C);
	ma.FillRandom([]() { return A((double)(rand() % 10 + 1)); });

	Matrix<A> mb(R, C);
	mb.FillRandom([]() { return A((double)(rand() % 10 + 1)); });

	cout << "\nMatrix ma:" << endl;
	ma.Print();

	cout << "\nMatrix mb:" << endl;
	mb.Print();

	cout << "\nma + mb:" << endl;
	cout << ma + mb;

	cout << "\nma - mb:" << endl;
	cout << ma - mb;

	cout << "\nma * mb:" << endl;
	cout << ma * mb;

	cout << "\nma / mb:" << endl;
	cout << ma / mb;

	cout << "\nMax of ma = " << ma.FindMax() << endl;
	cout << "Min of ma = " << ma.FindMin() << endl;
}

void DemoKeyboard()
{
	Matrix<double> mk(2, 2);
	mk.FillFromKeyboard();
	cout << "\nYou entered:" << endl;
	mk.Print();
	cout << "Max = " << mk.FindMax() << "  Min = " << mk.FindMin() << endl;
}

int main()
{
	DemoDouble();
	DemoClassA();
	DemoKeyboard();

	system("pause");
	return 0;
}
