#include "function.h"


class Montecarlo
{
	public:
		/**
		 * A template could be used instead of passing in a function instance,
		 * but doing so would prevent to customize the construction of the
		 * function instance with additional parameters.
		 */
		Montecarlo(Function& func) : func(func) {};
		double approximate(long long n);

	private:
		Function& func;

		double random(double a, double b);
		long long loop(long long n);
		int processNextPoint(double a, double b, double m);
};


