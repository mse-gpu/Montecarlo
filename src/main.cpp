#include <iostream>
#include "montecarlo.h"


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
    MonteCarlo mc(pi);

    std::cout << mc.approximate(99999999L) << std::endl;

    return 0;
}
