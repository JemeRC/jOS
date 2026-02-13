#ifndef MATH_H_
#define MATH_H_

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.43429448190325182765   // log10(e)
#define M_LN2      0.69314718055994530942   // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.78539816339744830962   // pi/4
#define M_1_PI     0.31830988618379067154   // 1/pi
#define M_2_PI     0.63661977236758134308   // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.70710678118654752440   // 1/sqrt(2)


// Functii Trigonometrice

double cos(double x);               // Cosinus
double sin(double x);               // Sinus
double tan(double x);               // Tangenta
double acos(double x);              // Arccosinus
double asin(double x);              // Arcsinus
double atan(double x);              // Arctangenta
double atan2(double y, double x);   // Arctangenta (cu 2 parametri, gestionează cadranele)


// Functii Hiperbolice

double cosh(double x);   // Cosinus hiperbolic
double sinh(double x);   // Sinus hiperbolic
double tanh(double x);   // Tangenta hiperbolica


// Exponentiali si Logaritmi

double exp(double x);                       // e la puterea x
double frexp(double value, int *exp);       // Desparte numarul in mantisa si exponent 
double ldexp(double x, int exp);            // x * (2 la puterea exp) - opusul lui frexp
double log(double x);                       // Logaritm natural (ln)
double log10(double x);                     // Logaritm in baza 10
double modf(double value, double *iptr);    // Desparte in parte intreaga si fractionara
double pow(double x, double y);             // x la puterea y
double sqrt(double x);                      // Radical 


// Puteri / Rotunjiri / Absolut

double ceil(double x);              // Rotunjire în sus 
double fabs(double x);              // Valoarea absoluta
double floor(double x);             // Rotunjire in jos 
double fmod(double x, double y);    // Restul impartirii in virgula mobila

#endif