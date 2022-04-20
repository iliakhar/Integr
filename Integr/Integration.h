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
		int size = (startX + endY) / h;
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
	double h;
	double CalculateExpression(std::vector<long double>& expression, double val);
	long double getH(int elemInd);
public:
	Integration(std::pair<double, double>interval, double newH, double (*FuncForIntegr)(double x)):lim(interval), h(newH) {
		std::ofstream myfile("../integ.csv");
		myfile.close();
		std::fstream mycsv("../integ.csv", std::ios::app);
		mycsv << lim.first << "; " << lim.second << "\n";
		//std::ifstream input(filename);
		int size((interval.second - interval.first) / h + 1);
		//input >> size;
		storageOfData.resize(size);
		double step(interval.first);
		for (int i(0); i < size; i++) {
			storageOfData[i].first = step;
			storageOfData[i].second = FuncForIntegr(storageOfData[i].first);
			step += h;
		}
	}

	double Trap();
	double Simp();
	long double Kotes();
};