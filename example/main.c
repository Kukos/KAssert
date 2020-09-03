#include <stdio.h>
#include <assert.h>

/* We want to use KASSERT(cond) instead of assert */
#define KASSERT_EVERYWHERE
#include <kassert/kassert.h>

static int get41(void);

static void example1(void);
static void example2(void);

/* To shows that we can use functions like variables in KASSERT */
static int get41(void)
{
    return 41;
}

/* Please note, that KASSERT terminates program, so comment assert to see another */
static void example1(void)
{
    double a = 5.0;
    double b = 4.0;

    /* You can pass 2 variables with the same type */
    KASSERT_EQ(a, b);

    int c = 100;
    int d = 100;
    KASSERT_NEQ(c, d);

    /* You can pass variable with normal value but be aware of promotion is C */
    char e = 'E';
    KASSERT_GT(e, (char)'K');

    /* You can pass variable and function which returns the same type */
    int f = 100;
    KASSERT_GEQ(get41(), f);

    KASSERT_LT(200, get41());

    /* You can pass expressions but type must be the same */
    KASSERT_LEQ(get41() + 1, get41());
}

/* Please note, that KASSERT terminates program, so comment assert to see another */
static void example2(void)
{
    int* ptr = NULL;
    /* this assert is in fact KASSERT due to KASSERT_EVERYWHERE */
    assert(ptr != NULL);

    /* You can pass here all you want, like to normal assert */
    KASSERT(ptr != NULL && *ptr != 0);
}

int main(void)
{
    example1();
    example2();

    return 0;
}
