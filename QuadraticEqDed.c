#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "UnTst.md"

#define NO_ROOTS  0
#define ONE_ROOT  1
#define TWO_ROOTS  2
#define INF_ROOTS  3

//..........................................................

void check_func_2(double a, double b, double c, double x1, double x2);
void check_func_1(double b, double c, double x1);
void Quadeq_Test();
int choice();
void Lineq_Test();
void UNIT_TESTS();
int SolvQuad(double a, double b, double c, double* x1, double* x2);
int linequation(double b, double c, double* x1);
int is_zero(double* e);

//..........................................................

int main()
{
  UNIT_TESTS();
	choice();

	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

	printf("\n"
	       "SolvQuadratic Equation, v 2.0.0 (updated)\n"
	       "Enter coeffs a, b, c for equation ax^2 + bx + c = 0. Enter a:");


	int check = scanf("%lf", &a);
	assert( check == 1);

	printf("                                                     Enter b:");

	check = scanf("%lf", &b);
	assert( check == 1);

	printf("                                                     Enter c:");

	check = scanf("%lf", &c);
	assert( check == 1);

	if (a == 0)
  	check_func_1(b, c, x1);

	else
  	check_func_2(a, b, c, x1, x2);

	printf("\n\nThat's all! We've just finished to solve this equation!\n\n");

	return 0;
}

//..........................................................

int SolvQuad(double a, double b, double c, double* x1, double* x2)
{

	if (a != 0)
	{
		double D = b * b - 4 * a * c;


		if (D == 0)
		{
			*x1 = -b / (2 * a);
			 int ger = is_zero(x1);

			return ONE_ROOT;
		}
		else

		if (D > 0)
		{
			double sqrt_d = sqrt(D);

			*x1 = (-b + sqrt_d) / (2 * a);
			*x2 = (-b - sqrt_d) / (2 * a);
			int ger = is_zero(x1);
			is_zero(x2);

			return TWO_ROOTS;

		}

		if (D < 0)

			return NO_ROOTS;
	}

}

//..........................................................

int linequation(double b, double c, double *x1)
{

		if (b != 0)
		{
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

//..........................................................

int is_zero(double* e )
{
	if (fabs(*e) <= 10e-6) *e = 0;
}

//..........................................................

int choice()
{
	char c = '0';
	//while ((c = getchar()) != '\n');
	c = getchar();

	if ( c == 'Y' || c == 'y')
	{
		Lineq_Test();
		Quadeq_Test();
		printf("\n\t\t\t<<<<We've finished to test our, thank you>>>>\n\n");
		return 0;
	}

	if ( c == 'N'|| c == 'n')
	{
		printf("Ok,Goodbye,my friend!!!\n\n");
		return 0;
	}

  if (c == '\n')
  {
    printf("Ok, I believe silience is a sign of an agreement:)\n\n");
    Lineq_Test();
    Quadeq_Test();
    printf("\n\t\t\t<<<<We've finished to test our, thank you>>>>\n\n");
    return 0;
  }

	printf("Sorry, I'm a stupid robot and I don't understand this command :(\n"
	       "Try again!\n\n");

	choice();
}

//..........................................................

void check_func_1(double b, double c, double x1)
{
  int value = linequation(b, c, &x1);

  switch (value)
    {
    case NO_ROOTS:  printf ("No roots!\n");                 break;

    case ONE_ROOT:  printf ("Only one root, %lf\n", x1);    break;

    case INF_ROOTS: printf ("Infinite number of roots!\n"); break;
    }
}

//..........................................................

void check_func_2(double a, double b, double c, double x1, double x2)
{
  int value = SolvQuad(a, b, c, &x1, &x2);

  switch (value)
  {
    case NO_ROOTS: printf("No roots!");                     break;

    case ONE_ROOT: printf("Only one root, %lf\n", x1);      break;

    case TWO_ROOTS: printf("Two roots:\n"
            "The first root is x1 = %lf\n"
            "The second root is x2 = %lf\n", x1, x2);       break;

    case INF_ROOTS: printf("Infinite number of roots!\n");  break;
  }
}
