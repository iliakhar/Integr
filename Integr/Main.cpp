#include <iostream>
#include "Integration.h"

double FuncForIntegr(double x) {
	double val;
	val = sqrt(x);
	return val;
}

int main() {
	
	Graphic graph(0, 10, 0.1, FuncForIntegr);
	Integration integr({ 2, 12 }, 0.2, FuncForIntegr);
	double answ = integr.Trap();
	std::cout << "\n\n";
	integr.Simp();
	std::cout << "\n\n";
	integr.Kotes();
}