#include "../headers/utility_functions.h"

#include <stdlib.h>
#include <string.h>


char* concat(const char *s1, const char *s2)
{
    /* TODO @kswierzy: when program flow is so designed that s1 and s2 can not be null place ASSERT macros/function to document that:
        assert(s1 != NULL);
        assert(s2 != NULL);
        Assert macros/functions will be replaced with an empty statement, when program is compiled in release mode with NDEBUG defined. */
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    /* TODO @kswierzy: what if malloc retrns NULL, because allocation failed? */
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}