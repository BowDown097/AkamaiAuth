#define MEASUREEXECTIME
#define PATHNAME "/services/MediaGenerator/mgid:arc:video:nickelodeonplay.com:51161a24-38f1-11e9-a442-0e40cf2fc285?ep=745e8724"
#define USECURRTIME

#include "akamaiauth.h"
#if defined(USECURRTIME) || defined(MEASUREEXECTIME)
    #include <time.h>
#endif

int main()
{
    #ifdef MEASUREEXECTIME
        clock_t t;
        t = clock();
    #endif

    printf("Using pathname '%s'\n", PATHNAME);
    #ifdef USECURRTIME
        long exp = time(0) + 14400;
        printf("Using current time for expiration ~ time %ld (Unix time + 14400)\n", exp);
        printf("%s\n", generateGDAToken(PATHNAME, exp, "", ""));
    #else
        printf("NOT using current time for expiration ~ time 14400\n");
        printf("%s\n", generateGDAToken(PATHNAME, 14400, "", ""));
    #endif

    #ifdef MEASUREEXECTIME
        t = clock() - t;
        double elapsed = ((double)t) / CLOCKS_PER_SEC;
        printf("Generating Akamai GDA token took %f seconds\n", elapsed);
    #endif

    return 0;
}