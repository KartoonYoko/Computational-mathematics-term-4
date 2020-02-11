#include <iostream>

//using namespace std;

using func = double(*)(double);

// метод Свенна
void svenn(double& x0, double& d, func f, double& a, double& b) {
	double xN;
	double xC = x0;
	double xL = x0 - d;
	double xR = x0 + d;
	while (!((f(xL) > f(xC)) && (f(xR) > f(xC)))) {
		if ((f(xL) > f(xC)) && (f(xC) > f(xR))) {
			xN = xR + 2 * d;
			xL = xC;
			xC = xR;
			xR = xN;
		}
		else
			if ((f(xL) < f(xC)) && (f(xC) < f(xR))) {
				xN = xL - 2 * d;
				xR = xC;
				xC = xL;
				xL = xN;
			}
		d *= 2;
	}
	a = xL;
	b = xR;

}

// метод деления пополам
double methodOfHaldDivide(double a, double b, func f, double eps) {
	double x1, x2, x3;
	while (b - a > 2 * eps) {
		x1 = (3 * a + b) / 4;
		x2 = (a + b) / 2;
		x3 = (a + 3 * b) / 4;
		if ((f(x1) < f(x2)) && (f(x2) < f(x3))) b = x2;
		else
			if ((f(x1) > f(x2)) && (f(x2) > f(x3))) a = x2;
			else {
				a = x1;
				b = x3;
			}
	}

	return (a + b) / 2;
}

// метод золотого сечения
double goldRatio(double a, double b, func f, double eps) {
	double x1, x2, phi;
	phi = (sqrt(5) - 1) / 2;
	while (b - a > 2 * eps) {
		x1 = phi * a + (1 - phi) * b;
		x2 = (1 - phi) * a + phi * b;
		if (f(x1) < f(x2))
			b = x2;
		else
			if (f(x1) > f(x2))
				a = x1;
	}

	return (a + b) / 2;
}



// пассивный поиск
double passiveSearching(double a, double b, func f, double eps) {
	int n = static_cast<int>(b - a) / eps;
	double min = f(a);
	for (int i = 1; i <= n; i++) {
		a += i * (b - a) / eps;
		double buf = f(a);
		if (min < buf)
			min = buf;
	}
	return min;
}






int main()
{
	func f = [](double x)->double {
		return pow(1.4, pow(x, 2) - x - 4);
	};

	double x0 = 0;
	double d = 0.2;
	double a;
	double b;

	svenn(x0, d, f, a, b);
	//std::cout « a « "; " « b « std::endl;
	std::cout << methodOfHaldDivide(a, b, f, 0.01) << "; " << goldRatio(a, b, f, 0.01) <<  "; " << passiveSearching(a, b, f, 0.01) << std::endl;
}