#include "main.h"

/**
 * _printf - Custom printf function
 * @format: The format string
 * @...: Variable number of arguments
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int printed_chars = 0;
    int i = 0;

    va_start(args, format);

    while (format && format[i])
    {
        if (format[i] != '%')
        {
            putchar(format[i]);
            printed_chars++;
        }
        else if (format[i + 1])
        {
            i++;
            switch (format[i])
            {
                case 'd':
                    printed_chars += printf("%d", va_arg(args, int));
                    break;
                case 's':
                    printed_chars += printf("%s", va_arg(args, char *));
                    break;
                case 'c':
                    putchar(va_arg(args, int));
                    printed_chars++;
                    break;
                case 'f':
                    printed_chars += printf("%f", va_arg(args, double));
                    break;
                default:
                    putchar('%');
                    putchar(format[i]);
                    printed_chars += 2;
                    break;
            }
        }
        i++;
    }

    va_end(args);
    return (printed_chars);
}

int main(void)
{
    int i = 42;
    char *s = "Hello, world!";
    char c = 'A';
    double f = 3.14159;

    _printf("Integer: %d, String: %s, Char: %c, Float: %f\n", i, s, c, f);

    return (0);
}
