
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
        /**
        * Getters for the different range measures.
        */
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

        /**
         * Utility method to check if a given y value is below the function
         * curve for any given x.
         */
        bool isBelowCurve(double x, double y)
        {
            return y < calculate(x);
        };

        /**
         * Function called by the montecarlo algorithm runner once the random
         * points have been placed and the result calculated. Allows to
         * postprocess the result in order to apply an additional mathematical
         * operation (e.g. divide it by 2 in the case of PI calculation).
         *
         * The default implementation simply returns the value unchanged.
         */
        virtual double postprocess(double val)
        {
            return val;
        };
};
