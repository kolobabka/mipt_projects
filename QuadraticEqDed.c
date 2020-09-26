/* Я только начал программировать, и потому еще очень плохо знаю язык. Я понимаю, что всё, что я написал в main необходимо разбить на множество функций, которые должны возвращать
в основную результат, однако делать я этого ещё не умею:( Сейчас читаю главу Прата, посвященную функциям, по окончании изучения которой я полностью переделаю этот код. Но мне
ведь надо с чего-то начинать! */

#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996).

#define NO_ROOTS  0
#define ONE_ROOT  1
#define TWO_ROOTS  2
#define INF_ROOTS  3

int SolvQuad(double a, double b, double c, double* x1, double* x2);
int linequation(double a, double b, double c, double* x1);
int is_zero(double* e);

int main() {

	double a = 0, b = 0, c = 0;

	printf("\n"
		"SolvQuadratic Equation, v 1.0.0\n"
		"Enter coeffs a, b, c for equation ax^2 + bx + c = 0. Enter a:");


	scanf("%lf", &a);
	printf("                                                     Enter b:");
	scanf("%lf", &b);
	printf("                                                     Enter c:");
	scanf("%lf", &c);

	double x1 = 0, x2 = 0;
	if (a == 0) {
		int check_func_1 = linequation(a, b, c, &x1);

		switch (check_func_1)
			{
			case NO_ROOTS:  printf ("No roots!");                   break;

			case ONE_ROOT:  printf ("Only one root, %lf\n", x1);    break;

			case INF_ROOTS: printf ("Infinite number of roots!\n"); break;
			}
	}
	else {
		int check_func_2 = SolvQuad(a, b, c, &x1, &x2);

		switch (check_func_2)
		{
			case NO_ROOTS: printf("No roots!");                     break;

			case ONE_ROOT: printf("Only one root, %lf\n", x1);      break;

			case TWO_ROOTS: printf("Two roots:\n"
				"The first root is x1 = %lf\n"
				"The second root is x2 = %lf\n", x1, x2);           break;

			case INF_ROOTS: printf("Infinite number of roots!\n");  break;
		}
	}

	printf("\n\nThat's all! We've just finished to solve this equation!\n");


	return 0;
}

int SolvQuad(double a, double b, double c, double* x1, double* x2)
{


	if (a != 0) {
		double D = b * b - 4 * a * c;


		if (D == 0) {
			*x1 = -b / (2 * a);
			int ger = is_zero(x1);

			return ONE_ROOT;
		}
		else

		if (D > 0) {
			double sqrt_d = sqrt(D);

			*x1 = (-b + sqrt_d) / (2 * a);
			*x2 = (-b - sqrt_d) / (2 * a);

			return TWO_ROOTS;

		}

		if (D < 0)

			return NO_ROOTS;
	}

}
int linequation(double a, double b, double c, double *x1)
{

		if (b != 0) {
			*x1 = -c / b;

			int ger = is_zero(x1);

			return ONE_ROOT;
		}

		if ((b == 0) && (c != 0))
		{


			return NO_ROOTS;

		}

		if ((b == 0) && (c == 0)) {

			return INF_ROOTS;
		}




}

int is_zero(double* e )
{
		if (fabs(*e) <= 10e-6) *e = 0;
}
