#include <iostream>
#include <complex>
#include <vector>

#define PI 3.14159265359
typedef unsigned int uint;
typedef std::vector<std::complex<double>> vec;

vec fastFourierTransform(vec& a)
{
	uint s = a.size();
	if (s == 1) {
		return a;
	}


	vec val(a.size());
	for (uint i = 0; i < s; i++) {
		std::complex<double>c(cos(2.0 * PI * i / s), sin(2.0 * PI * i / s));
		val[i] = c;
	}

	vec odd(s / 2), nodd(s / 2);
	for (uint i = 0; i < s/2; i++) {
		odd[i] = a[i * 2];
		nodd[i] = a[i * 2 + 1];
	}

	vec odref = fastFourierTransform(odd);
	vec nodref = fastFourierTransform(nodd);

	vec res(s);

	for (int k = 0; k < s / 2; k++) {
		res[k] = odref[k] + (val[k] * nodref[k]);
		res[k + s / 2] = odref[k] - (val[k] * nodref[k]);
	}
	return res;
}

vec inverseFastFourierTransform(vec& vecz) {
	vec::iterator it;
	vec test;
	for (it = vecz.begin(); it != vecz.end(); ++it) {
		*it = std::conj(*it);
	}
	
	test = vecz;
	test = fastFourierTransform(vecz);

	for (it = test.begin(); it != test.end(); ++it) {
		*it = std::conj(*it);
	}

	for (it = test.begin(); it != test.end(); ++it) {
		*it /= test.size();
	}

	return test;
};

int main()
{
	int ammount;
	std::cin >> ammount;
	std::complex<double> c;
	vec V;
	double x, y;
	for (uint i = 0; i < ammount; i++) {
		std::cin >> x >> y;
		std::complex<double>c(x, y);
		V.push_back(c);
	}

	vec result;
	result = fastFourierTransform(V);
	std::cout << "FFT RESULT:\n";
	for (uint i = 0; i < ammount; ++i)
	{
		std::cout << result[i] << std::endl;
	}

	std::cout << "\nIFFT RESULT:\n";
	V.clear();
	V.resize(ammount);
	V = inverseFastFourierTransform(result);
	for (uint i = 0; i < ammount; ++i)
	{
		std::cout << V[i] << std::endl;
	}
	system("pause");
	return 0;
}