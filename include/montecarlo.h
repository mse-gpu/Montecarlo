#include "function.h"


class MonteCarlo
{
    public:
        /**
         * A template could be used instead of passing in a function instance,
         * but doing so would prevent to customize the construction of the
         * function instance with additional parameters.
         */
        MonteCarlo(Function& func) : func(func) {};

        /**
         * Execute the MonteCarlo approximation algorithm by calculating n
         * random points.
         */
        double approximate(long long n);

    private:
        Function& func;

        double random(double a, double b);
        long long loop(long long n);
        int processNextPoint(double a, double b, double m);
};
