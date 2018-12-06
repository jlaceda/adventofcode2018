#include <stdio.h>
#include <string.h>

int main()
{
    FILE *input_file;
    input_file = fopen("input", "r");
    
    if (!input_file) {
        perror("error opening input");
        return 1;
    }

    const int line_buffer_size = 28;
    const int number_of_lines = 250;
    const char letters[26] = "abcdefghijklmnopqrstuvwxyz";

    char line_buffer[line_buffer_size];
    char lines[number_of_lines][line_buffer_size];
    int line_count = 0;

    while (fgets(line_buffer, line_buffer_size, input_file) != NULL)
    {
        strcpy(lines[line_count], line_buffer);
        line_count++;
    }
    fclose(input_file);

    int two_of = 0;
    int three_of = 0;

    for (int line = 0; line < number_of_lines; ++line)
    {
        printf("current line: %s", lines[line]);

        int letters_count[26] = {0};

        for (int i = 0; i < line_buffer_size; ++i)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (lines[line][i] == letters[j])
                {
                    letters_count[j]++;
                    break;
                }
            }
        }

        for (int i = 0; i < 26; ++i)
        {
            printf("letter: %c count: %d\n", letters[i], letters_count[i]);
        }

        int two_of_found = 0;
        int three_of_found = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (letters_count[i] == 2 && two_of_found == 0)
            {
                two_of++;
                two_of_found = 1;
            }
            if (letters_count[i] == 3 && three_of_found == 0)
            {
                three_of++;
                three_of_found = 1;
            }
        }
    }
    printf("2-of count: %d\n3-of count: %d\nchecksum: %d\n", two_of, three_of, three_of * two_of);

    /* part 2 */
    for (int i = 0; i < number_of_lines; ++i)
    {
        for (int j = i + 1; j < number_of_lines; ++j)
        {
            int diffs = 0;
            int diff_index = -1;
            for (int c = 0; c < line_buffer_size - 2; ++c)
            {
                if (lines[i][c] != lines[j][c])
                {
                    diffs++;
                    diff_index = c;
                    if (diffs > 1)
                    {
                        break;
                    }
                }
            }
            if (diffs == 1)
            {
                printf("the 2 target box ids:\n%s%s", lines[i], lines[j]);
                printf("the one diff is %c at string index %d.\n", lines[i][diff_index], diff_index);
                printf("solution:\n");
                for (int k = 0; k < line_buffer_size; ++k)
                {
                    if (k == diff_index)
                    {
                        continue;
                    }
                    printf("%c", lines[i][k]);
                }
                break;
            }
        }
    }
    return 0;
}