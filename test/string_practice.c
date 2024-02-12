#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char dest1[50] = "0987654321"; // Initial value, with enough space for the string and a null terminator
    char *src = "12345";

    char *dest2 = strcat(dest1, src); // Overwrite dest1 with src
    


    printf("dest1: %p %s %p %s\n", dest1, dest1, ++dest2, dest2);

    return 0;
}
