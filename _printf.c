#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function
 * @format: format string.
 *
 * Return: The number of printed characters.
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0, flags, width, precision, size, buff_ind = 0;
	int printed = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	return (-1);

	va_start(list, format);

	for (i = 0; format[i]; i++)
	{

		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			printed_chars++;

			if (buff_ind == BUFF_SIZE)
			{
				print_buffer(buffer, &buff_ind);
			}
		}
		else
		{

			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			i++;

			printed = handle_print(format, &i, list,
buffer, flags, width, precision, size);
			if (printed == -1)
			return (-1);
			printed_chars += printed;
		}
	}


	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the buffer
 * @buffer: buffer to print.
 * @buff_ind: index of last character in buffer.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
	write(STDOUT_FILENO, buffer, *buff_ind);
	*buff_ind = 0;
	}
}
