#include <utils.h>

#include <ctype.h>
#include <string.h>

unsigned char hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return 0;
}

int strcincmp ( const char * first, const char * last, size_t count )
{
        if (!count)
                return(0);

        while (--count && *first && 
            (*first == *last || toupper(*first) == toupper(*last))) {
                first++;
                last++;
        }

        return( toupper(*first) - toupper(*last) );
}

