#include <iostream>
#include <stdlib.h>



/**
 * Base class for functions to be run using the montecarlo
 * approximation method.
 *
 * Subclasses have to implement at least constructor which has to
 * set the correct values for the simulation range and the
 * calculation logic used to compute the y-value for a given point
 * on the x axis.
 */
class Function
{
	protected:
		/**
		* Calculation range definition [x_from, x_to] x [0, m].
		*/
		double x_from;
		double x_to;
		double m;

		/**
		* Protected constructor to be used by subclasses.
		*/
		Function(double a, double b, double m) : x_from(a), x_to(b), m(m) {};

	public:
		double getRangeFrom()
		{
			return x_from;
		}
		double getRangeTo()
		{
			return x_to;
		};
		double getUpperLimit()
		{
			return m;
		};

		/**
		 * Subclasses have to provide their own 'calculate' function.
		 */
		virtual double calculate(double x) = 0;
		bool isBelowCurve(double x, double y)
		{
			return y < calculate(x);
		};
		virtual double postprocess(double val)
		{
			return val;
		};
};



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

double Montecarlo::random(double a, double b)
{
	double n = rand() * 1.0 / RAND_MAX;
	return n * (b - a) + a;
}

int Montecarlo::processNextPoint(double a, double b, double m)
{
	return this->func.isBelowCurve(
			this->random(a, b),
			this->random(0, m));
}

long long Montecarlo::loop(long long n)
{
	double a = this->func.getRangeFrom();
	double b = this->func.getRangeTo();
	double m = this->func.getUpperLimit();

	int nb = 0;

	while (n) {
		nb += this->processNextPoint(a, b, m);
		n--;
	}

	return nb;
}

double Montecarlo::approximate(long long n)
{
	long long nb;

	srand(time(NULL));
	
	nb = this->loop(n);

	double r = (double) nb / n;

	r *= this->func.getRangeTo() - this->func.getRangeFrom();
	r *= this->func.getUpperLimit();

	return this->func.postprocess(r);
}




class PI : public Function
{
	public:
		PI() : Function(-1, 1, 5) {};
		virtual double calculate(double x)
		{
			return 1./(1+x*x);
		};
		virtual double postprocess(double val)
		{
			return 2 * val;
		};
};

class Sqrt2 : public Function
{
	public:
		Sqrt2() : Function(0, 1, 1) {};
		virtual double calculate(double x)
		{
			return x;
		};
};



int main(void)
{
	PI pi;
	Montecarlo mc(pi);

	std::cout << "Value: " << mc.approximate(99999999L) << std::endl;

	return 0;
}
