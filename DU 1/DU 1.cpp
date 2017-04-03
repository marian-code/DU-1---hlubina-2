// DU 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

int main()
{
	vector<double> ln_rho;
	const int n = 10000;
	int i, j;
	const double rho_0 = 10E-5;
	double rho_n, rho_n_plus;

	cout.precision(5);
	cout.setf(std::ios::fixed, std::ios::floatfield);

	random_device rand_dev;
	mt19937 generator(rand_dev());
	uniform_real_distribution<double>  uniform(-1.0, 1.0);

	for (i = 1; i < n; i++)
	{
		rho_n = rho_0;

		for (j = 0; j < i; j++)
		{
			rho_n_plus = rho_n + rho_0 + 2 * rho_0*rho_n + 2 * sqrt(rho_0*rho_n*(1 + rho_n)*(1 + rho_0))*uniform(generator);
			rho_n = rho_n_plus;
		}
		ln_rho.push_back(log(rho_n_plus));
		if (n % i == 1000)
		{
			cout << "n: " << i << endl;
			cout << "ln_rho: " << ln_rho[i-1] << endl;
		}
	}
	
	ofstream outfile1;
	outfile1.open("ln_rho2.csv");
	
	for (i = 0; i < ln_rho.size(); i++)
	{
		if (i < ln_rho.size() - 1) outfile1 << ln_rho[i] << ",";
		else outfile1 << ln_rho[i];
	}
	
	outfile1.close();

    return 0;
}

