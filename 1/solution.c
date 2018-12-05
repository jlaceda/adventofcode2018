#include <stdio.h>

int main()
{
    FILE *input_file;
    input_file = fopen("input", "r");
    if (!input_file) {
        perror("error opening input");
        return 1;
    }

    const int input_buffer_size = 1048;
    const int line_buffer_size = 16;
    const int max_iterations = 1000;

    int results[input_buffer_size * max_iterations];
    char line_buffer[line_buffer_size];
    int input_number;
    
    int freq, counter, found_dupe, run_number = 0;
    
    results[counter] = 0;

    while (!found_dupe) 
    {
        while (fgets(line_buffer, line_buffer_size, input_file) != NULL && found_dupe == 0)  
        {
            counter += 1;
            sscanf(line_buffer, "%d", &input_number);
            freq += input_number;
            results[counter] = freq;
            
            for (int i = 0; i < counter; ++i)
            {
                if (freq == results[i])
                {
                    printf("First duplicate frequency (%d) found during run number %d.\n", freq, run_number);
                    found_dupe = 1;
                    break;
                }
            }
            
        }
        if (run_number == 0)
        {
            printf("Resulting frequency after 1 run: %d.\n", freq);
        }
        
        run_number += 1;
        if (run_number > max_iterations)
        {
            break;
        }
        rewind(input_file);
    }

    fclose (input_file);
    return 0;
}