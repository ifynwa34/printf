#include "main.h"

/**
 * print_with_precision - Helper function to print with precision.
 * @specifier: The conversion specifier ('d', 's', etc.).
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
static int print_with_precision(char specifier, va_list list, char buffer[],
    int flags, int width, int precision, int size)
{
    int printed_chars = 0;
    switch (specifier)
    {
        case 'd':
            printed_chars += print_int(list, buffer, flags, width, precision, size);
            break;
        case 's':
            printed_chars += print_string(list, buffer, flags, width, precision, size);
            break;
        case 'c':
        case '%':
        case 'i':
        case 'b':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'p':
        case 'S':
        case 'r':
        case 'R':
            printed_chars += fmt_types[i].fn(list, buffer, flags, width, -1, size);
            break;
    }
    return printed_chars;
}

/**
 * handle_print - Prints an argument based on its type.
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Index to keep track of the format string position.
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * Return: Number of characters printed or -1 on error.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[])
{
    int i, unknown_len = 0;
    int printed_chars = 0;

    for (i = 0; fmt_types[i].fmt != '\0'; i++)
    {
        if (fmt[*ind] == fmt_types[i].fmt)
        {
            // Handle precision for %d and %s
            if (fmt[*ind] == 'd' || fmt[*ind] == 's')
            {
                // Check and apply precision
                int precision = -1; // Initialize precision to -1
                if (fmt[*ind] == 'd' || fmt[*ind] == 's')
                {
                    if (fmt[*ind + 1] == '.')
                    {
                        *ind += 2;
                        precision = 0;
                        while (fmt[*ind] >= '0' && fmt[*ind] <= '9')
                        {
                            precision = precision * 10 + (fmt[*ind] - '0');
                            (*ind)++;
                        }
                    }
                }
                printed_chars += print_with_precision(fmt[*ind], list, buffer, flags, width, precision, size);
            }
            else
            {
                printed_chars += fmt_types[i].fn(list, buffer, flags, width, -1, size);
            }
            return printed_chars;
        }
    }

    if (fmt_types[i].fmt == '\0')
    {
        if (fmt[*ind] == '\0')
            return (-1);
        unknown_len += write(1, "%%", 1);
        if (fmt[*ind - 1] == ' ')
            unknown_len += write(1, " ", 1);
        else if (width)
        {
            --(*ind);
            while (fmt[*ind] != ' ' && fmt[*ind] != '%')
                --(*ind);
            if (fmt[*ind] == ' ')
                --(*ind);
            return (1);
        }
        unknown_len += write(1, &fmt[*ind], 1);
        return (unknown_len);
    }
    return (printed_chars);
}
