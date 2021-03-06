#include "Integration.h"

double Integration::TakeIntegral(char typeInegr, double e) {
	double (Integration::*IntegrationFunc)(double x);
	double eMultiplier(0);
	try {
		switch (typeInegr) {
		case 'T': IntegrationFunc = &Integration::TrapWithoutE;
			eMultiplier = 3;
			break;
		case 'S': IntegrationFunc = &Integration::SimpWithoutE;
			eMultiplier = 15;
			break;
		case 'K': return Kotes();
		default:
			throw std::string("\n\nERORR ERROR ERROR ERROR\n");
		}
	}
	catch(std::string strError) {
		std::cout << strError;
		exit(1);
	}
	
	double h, answerH1, answerH2;
	h = lim.second - lim.first;
	setNewValues(h);
	answerH2 = (this->*IntegrationFunc)(h);
	h = (lim.second - lim.first) / 2;
	do{
		std::cout << "\nh = " << h << "\n";
		setNewValues(h);
		answerH1 = answerH2;
		answerH2 = (this->*IntegrationFunc)(h);
		h /= 2;
		std::cout << "\n" << answerH1 << " - " << answerH2 << " = " << answerH1 - answerH2 << "  (" << eMultiplier * e << ")\n";
	} while (abs(answerH1 - answerH2) >= eMultiplier * e);
	return answerH2;
}

double Integration::TrapWithoutE(double h) {
	double answer(0);
	std::cout << "TrapIntegral(" << lim.first << "; " << lim.second << ") = ( ";
	for (int i(0); i < storageOfData.size() - 1; i++) {
		answer += (storageOfData[i].second + storageOfData[i + 1].second) / 2;
		std::cout << " + (" << storageOfData[i].second + storageOfData[i + 1].second << ")/2";
	}
	answer *= h;
	std::cout << " ) * " << h << " = " << answer;
	return answer;
}

double Integration::SimpWithoutE(double h) {
	double even(0), uneven(0), answer(0);
	answer = storageOfData[0].second + storageOfData[storageOfData.size() - 1].second;
	std::cout << "SimpIntegral(" << lim.first << "; " << lim.second << ") = ( " << storageOfData[0].second <<
		") + (" << storageOfData[storageOfData.size() - 1].second << ") + 4*(";
	for (int i(1); i < storageOfData.size() - 1; i += 2) {
		uneven += storageOfData[i].second;
		std::cout << " + (" << storageOfData[i].second << ")";
	}
	std::cout << " + 2*(";
	for (int i(2); i < storageOfData.size() - 1; i += 2) {
		even += storageOfData[i].second;
		std::cout << " + (" << storageOfData[i].second << ")";
	}
	answer = (answer + 4 * uneven + 2 * even) * h / 3;
	std::cout << ") * " << h << "/3 = " << answer;
	return answer;
}

long double Integration::Kotes() {
	long double answer(0), hVal;
	std::cout << "NewtonKotesIntegral(" << lim.first << "; " << lim.second << ") = ( ";
	for (int i(0); i < storageOfData.size(); i++) {
		hVal = getH(i);
		answer += storageOfData[i].second * hVal;
		std::cout << " + (" << storageOfData[i].second << " ) * " << hVal;
	}
	answer *= (lim.second - lim.first);
	std::cout << " ) * ( " << lim.second << " - " << lim.first << " ) = " << answer;
	return answer;
}

long double Integration::getH(int elemInd) {
	int size(storageOfData.size());
	std::vector<long double>expression(size + 1);
	std::vector<long double>tmp(size + 1);
	int k = 0;
	long double exprVal, answ;
	for (int i(0); i < expression.size(); i++)
		expression[i] = 0;
	expression[0] = elemInd == 0 ? -1 : 0;
	expression[1] = 1;
	for (int i(abs(expression[0]) + 1); i < size; i++)
		if (i != elemInd) {
			tmp = expression;
			expression[0] *= -i;
			for (int j(1); j < k + 3; j++)
				expression[j] = tmp[j] * (-i) + tmp[j - 1];
			k++;
		}
	tmp = expression;
	expression[0] = 0;
	for (int i(0); i < expression.size() - 1; i++)
		expression[i + 1] = tmp[i] / (i + 1);
	exprVal = CalculateExpression(expression, size - 1);
	answ = exprVal / (size - 1);
	for (int i(2); i <= elemInd; i++)
		answ /= i;
	for (int i(2); i < size - elemInd; i++)
		answ /= i;
	answ = (size - 1 - elemInd) % 2 == 0 ? answ : -answ;
	return answ;
}

double Integration::CalculateExpression(std::vector<long double>& expression, double val) {
	long double answ(0);
	double degree = val;
	for (int i(1); i < expression.size(); i++) {
		answ += degree * expression[i];
		degree *= val;
	}
	return answ;
}

void Integration::setNewValues(double h) {
	int size((lim.second - lim.first) / h + 1);
	//input >> size;
	storageOfData.resize(size);
	double step(lim.first);
	for (int i(0); i < size; i++) {
		storageOfData[i].first = step;
		storageOfData[i].second = FuncForIntegr(storageOfData[i].first);
		step += h;
	}
}