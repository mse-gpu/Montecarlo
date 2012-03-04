#include <stdlib.h>
#include <time.h>
#include "montecarlo.h"


double MonteCarlo::random(double a, double b)
{
    double n = (double) rand() / RAND_MAX;
    return n * (b - a) + a;
}


int MonteCarlo::processNextPoint(double a, double b, double m)
{
    return this->func.isBelowCurve(
            this->random(a, b),
            this->random(0, m));
}


long long MonteCarlo::loop(long long n)
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


double MonteCarlo::approximate(long long n)
{
    long long nb;

    srand(time(NULL));

    nb = this->loop(n);

    double r = (double) nb / n;

    r *= this->func.getRangeTo() - this->func.getRangeFrom();
    r *= this->func.getUpperLimit();

    return this->func.postprocess(r);
}
