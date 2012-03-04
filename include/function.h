
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
