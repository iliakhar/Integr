#include <iostream>
#include "Integration.h"

double FuncForIntegr(double x) {
	double val;
	if (x != 0)
		val = 1 / x;
	else val = 0;
	return val;
}

int main() {
	
	Graphic graph(1, 6, 0.1, FuncForIntegr);
	Integration integr({ 1, 2 }, FuncForIntegr);
	integr.TakeIntegral('T', 0.001);
	std::cout << "\n\n";
	integr.TakeIntegral('S', 0.001);
	std::cout << "\n\n";
	integr.TakeIntegral('K');
}