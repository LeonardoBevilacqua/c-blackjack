#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat(const char* str_1, const char* str_2, const char* separator)
{
    const size_t len_1 = strlen(str_1);
    const size_t len_2 = strlen(str_2);
    const size_t len_3 = strlen(separator);

    char* result = malloc(len_1 + len_2 + len_3 + 1);

    memcpy(result, str_1, len_1);
    memcpy(result + len_1, separator, len_3);
    memcpy(result + len_1 + len_3, str_2, len_2 + 1);

    return result;
}

int main()
{
    char* names = NULL;
    char* separator = ", ";

    names = concat("foo", "bar", separator);
    printf("NAMES: %s\n", names);
    names = concat(names, "baz", separator);
    printf("NAMES: %s\n", names);
    return 0;
}
