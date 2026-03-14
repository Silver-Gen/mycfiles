#include <unistd.h>             // Needed for System calls
#include <stdarg.h>

/*  Utility Functions 
 *  strlen()    <- To count the number of characters in the strin
 *  puts()      <- Puts on single string for debugging and stuff
 *  putchar()   <- Put single character on the screen
 *  chardup()   <- Will take one argument
 */




#define putchar(x)  write(1, chardup(x), 1)

char *chardup(const char c) {
    static char buff[2];
    char *p;
    p = buff;
    *p++ = c;
    *p-- = 0;

    return buff;
}


unsigned int mystrlen(const char *str){
    unsigned int n;
    const char *p;
    for (p=str, n=0; *p; p++, n++);

    return n;
}


int puts(const char *str){
    unsigned int n;
    n = mystrlen(str);
    if(n < 1)
        return -1;
    return write(1, str, n);
}


int myprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const char *p = fmt;
    while (*p) {
        if (*p == '%' && *(p + 1) != '\0') {
            p++;
            switch (*p) {
                case 's': {
                    const char *str = va_arg(args, const char *);
                    puts(str);
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    /* basic int printing */
                    if (num < 0) { write(1, "-", 1); num = -num; }
                    char tmp[12];
                    int i = 0;
                    if (num == 0) { write(1, "0", 1); break; }
                    while (num > 0) { tmp[i++] = '0' + (num % 10); num /= 10; }
                    while (i-- > 0) write(1, chardup(tmp[i+1 > 0 ? i+1 : 0]), 1);
                    /* simplified — extend as needed */
                    break;
                }
                case '%': write(1, "%", 1); break;
                default:  write(1, chardup(*p), 1); break;
            }
        } else {
            write(1, chardup(*p), 1);
        }
        p++;
    }

    va_end(args);
    return 1;
}



int main(){
    myprintf("%s\n", "ARG 2\n");
    
    return 0;
}

