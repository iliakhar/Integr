#pragma once
#include<vector>
#include<fstream>
#include<iostream>
#include<cmath>

using ValueAndAnswer = std::pair<double, double>;
class Graphic {
protected:
	std::vector<ValueAndAnswer> storageOfData;
	void OutputDataValue(double x, double y) {
		std::fstream myfile("../example.csv", std::ios::app);
		myfile << x << "; " << y << "\n";
	}
public:
	Graphic(double startX, double endY, double h, double (*FuncForIntegr)(double x)) {
		std::ofstream myfile("../example.csv");
		myfile.close();
		int size = (abs(startX) + abs(endY)) / h;
		int k(0);
		OutputDataValue(size, 0);
		storageOfData.resize(size);
		for (double xValue(startX); xValue + h*0.1 < endY; xValue +=h) {
			storageOfData[k].first = xValue;
			storageOfData[k].second = FuncForIntegr(storageOfData[k].first);
			OutputDataValue(storageOfData[k].first, storageOfData[k].second);
			k++;
		}
	}
};

class Integration {
protected:
	std::pair<double, double> lim;
	std::vector<ValueAndAnswer> storageOfData;
	double CalculateExpression(std::vector<long double>& expression, double val);
	long double getH(int elemInd);
	double (*FuncForIntegr)(double x);
	void setNewValues(double h);
public:
	Integration(std::pair<double, double>interval, double (*MyFuncForIntegr)(double x)):lim(interval){
		std::ofstream myfile("../integ.csv");
		myfile.close();
		std::fstream mycsv("../integ.csv", std::ios::app);
		mycsv << lim.first << "; " << lim.second << "\n";
		FuncForIntegr = MyFuncForIntegr;
	}

	double TakeIntegral(char typeInegr, double e = 0.001);
	long double Kotes();
	double TrapWithoutE(double h);
	double SimpWithoutE(double h);
};