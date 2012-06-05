#include "string.h"

int isalnum(char c)
{
        return (isalpha(c) || isdigit(c));
}

int isalpha(char c)
{
        if ((c >= 'A' && c <= 'z'))
                return (1);
        else
                return (0);
}

int iscntrl(char c)
{
        if (c < '0') {
                return 1;
        } else {
                return 0;
        }
}


int islower(char c)
{
        if ((c >= 'a' && c <= 'z'))
                return (1);
        else
                return (0);
}

int isspace(char c)
{
        if ((c >= 0x09 && c <= 0x0d) || (c == 0x20))
                return (1);
        return (0);
}

int isupper(char c)
{
        if ((c >= 'A' && c <= 'Z'))
                return (1);
        else
                return (0);
}

char toupper(char c)
{
        if (c >= 'a' && c <= 'z')
                return (c - 'a' + 'A');
        else
                return (c);
}

char tolower(char c)
{
        if (c >= 'A' && c <= 'Z')
                return (c - 'A' + 'a');
        else
                return (c);
}



int isnumber(char c, int base)
{
        char *digits = "0123456789ABCDEF";
        if ((c >= '0' && c <= digits[base - 1]))
                return (1);
        else
                return (0);
}

int tonumber(char c)
{
        if (c >= '0' && c <= '9')
                return (c - '0');
        else if (c >= 'A' && c <= 'F')
                return (c - 'A' + 10);
        else if (c >= 'a' && c <= 'f')
                return (c - 'a' + 10);
        else
                return (c);
}

char todigit(int c)
{
        if (c >= 0 && c <= 9)
                return (c + '0');
        else if (c >= 10 && c <= 15)
                return (c + 'A' - 10);
        else
                return (c);
}

int isxdigit(char c)
{
        if ((c >= '0' && c <= 'F') || (c >= 'a' && c <= 'f'))
                return (1);
        else
                return (0);
}

int isdigit(char c)
{
        if ((c >= '0' && c <= '9'))
                return (1);
        else
                return (0);
}

/*
FUNCTION
	<<strlen>>---character string length

DESCRIPTION
	The <<strlen>> function works out the length of the string
	starting at <<*<[str]>>> by counting chararacters until it
	reaches a <<NULL>> character.

RETURNS
	<<strlen>> returns the character count.
*/
int strlen(char *str) {
  const char *start = str;
  while (*str)
    str++;
  return str - start;
}


/*
FUNCTION
	<<strcat>>---concatenate strings

DESCRIPTION
	<<strcat>> appends a copy of the string pointed to by <[src]>
	(including the terminating null character) to the end of the
	string pointed to by <[dst]>.  The initial character of
	<[src]> overwrites the null character at the end of <[dst]>.

RETURNS
	This function returns the initial value of <[dst]>
*/
char *strcat(char *s1, const char *s2) {
  char *s = s1;

  while (*s1)
    s1++;

  while (*s1++ = *s2++)
    ;
  return s;
}

/*
FUNCTION
	<<strcmp>>---character string compare

DESCRIPTION
	<<strcmp>> compares the string at <[a]> to
	the string at <[b]>.

RETURNS
	If <<*<[a]>>> sorts lexicographically after <<*<[b]>>>,
	<<strcmp>> returns a number greater than zero.  If the two
	strings match, <<strcmp>> returns zero.  If <<*<[a]>>>
	sorts lexicographically before <<*<[b]>>>, <<strcmp>> returns a
	number less than zero.
*/
int strcmp (char *s1, char *s2) {
  while (*s1 != '\0' && *s1 == *s2)
    {
      s1++;
      s2++;
    }

  return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}

/*
FUNCTION
	<<strcpy>>---copy string

DESCRIPTION
	<<strcpy>> copies the string pointed to by <[src]>
	(including the terminating null character) to the array
	pointed to by <[dst]>.

RETURNS
	This function returns the initial value of <[dst]>.
*/

char *strcpy(char *dst0, char *src0) {
  char *s = dst0;

  while (*dst0++ = *src0++)
    ;

  return s;
}

/*
FUNCTION
<<bzero>>---initialize memory to zero

DESCRIPTION
<<bzero>> initializes <[length]> bytes of memory, starting at address
<[b]>, to zero.

RETURNS
<<bzero>> does not return a result.
*/

void bzero(void *b, int length) {
  char *ptr = (char *)b;
  while (length--)
    *ptr++ = 0;
}

// print a string. Difference to Write is, you don't need to specify size.
int print(OpenFileId id, char *buffer) {
    return Write(id, buffer,strlen(buffer));
}

// print a string with newline
int println(OpenFileId id, char *buffer) {
    int retValue = Write(id, buffer,strlen(buffer));
    return (retValue + Write(id, "\n",1));
}

// read a string from the console
int readLine(char *buf, int len) {
	int i;
	char c;
	
	for (i = 0; i < len-1; i++) {		
		Read(ConsoleInput, &c, 1);		
		if (c == '\n') break;
		if (c == 8 && i > 0) 
		    i -= 2; 
		else 
		    buf[i] = c;
	}
	
	buf[i] = 0;
	return i;
}

// print an integer value
extern void printInt(OpenFileId id, int n) {
	
        int i, sign;
        char buffer[15];        

        if ((sign = n) < 0)     /* record sign */
                n = -n;         /* make n positive */
        
        i = 15;			
        buffer[i] = 0;
        
        do {                    /* generate digits in reverse order */
                buffer[--i] = n % 10 + '0';  /* get next digit */
        } while ((n /= 10) > 0);        /* delete it */
        
        if (sign < 0)
                buffer[--i] = '-';
                
        print(id, &buffer[i]);
}

/*
    Parses string interpreting its content as an integer value until a character
    that can not be interpreted is found, and returns a long int value.

    Parameters.

    s
    String representing an integer number. The number is considered until a
    non-numeric character is found (only the digits from 0 to radix-1 are
    considered valid numeric characters, signs are considered valid numeric
     characters for this parameter). The format used is:
    [whitespaces][+|-][0|0x][nnnnn]
    (where whitespaces are any tab or space character and nnnnn is a sequence
    of valid numbers following the specified radix)

    scan_end
    Address of a pointer. This is filled by the function with the address
    where scan has ended. Serves to determine where there is the first
    non-numerical character in the string.

    base
    Numeral radix in which the number to be interpreted.
    Must be 0 or be between 2 and 36. If it is 0 the radix of the string is
    determined by the initial characters of the string:
    initial chars          Interpreted by strol as
    0x                     hexadecimal: radix 16
    0                      octal: radix 8
    any number from 1 to 9 decimal: radix 10

    Return Value.
      The converted long int value from the input string.
      If conversion would cause overflow the result is LONG_MAX or LONG_MIN.
      If an error occurs or no conversion can be made 0 is returned.
*/

long int strtoi(char *s, int base, char **scan_end)
{
        int sign, value, overflow=0;
        long int result=0, oldresult;
        /* Evaluate sign */
        if (*s == '-') {
                sign = -1;
                s++;
        } else if (*s == '+') {
                sign = 1;
                s++;
        } else
                sign = 1;
        /* Skip trailing zeros */
        while (*s == '0')
                s++;
        /* Convert number */
        while (isnumber(*s, base)) {
                value = tonumber(*s++);
                if (value > base || value < 0)
                        return (0);
                oldresult = result;
                result *= base;
                result += value;
                /* Detect overflow */
                if (oldresult > result)
                        overflow = 1;
        }
        if (scan_end != 0L)
                *scan_end = s;
        if (overflow)
                result = INT_MAX;
        result *= sign;
        return (result);
}

// convert string to int
int atoi(const char *nptr){
        return strtoi(nptr, 10, NULL);
}
// write a character on ConsoleOutput
int  putchar (int character )
{
    return Write(ConsoleOutput, &character,1);
}

