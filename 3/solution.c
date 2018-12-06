#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 24
#define LINE_COUNT 1233

/* How many square inches of fabric are within two or more claims? */

struct Claim
{
    int id;
    int left;
    int top;
    int width;
    int height;
};

struct Claim string_to_claim(char * line)
{
    /*
    A claim like #123 @ 3,2: 5x4 means that 
    claim ID 123 specifies a rectangle 
    3 inches from the left edge, 
    2 inches from the top edge, 
    5 inches wide, and 
    4 inches tall.
    */
    struct Claim c;
    if (sscanf(line, "#%d @ %d,%d: %dx%d", &c.id, &c.left, &c.top, &c.width, &c.height) != 5)
    {
        perror("error converting claim");
        exit(1);
    }
    return c;
}

void print_claim(struct Claim c)
{
    printf("#%d @ %d,%d: %dx%d\n", c.id, c.left, c.top, c.width, c.height);
}

int main()
{
    /* convert file into array of strings */
    FILE *input_file;
    input_file = fopen("input", "r");
    
    if (!input_file) {
        perror("error opening input");
        return 1;
    }

    char line_buffer[LINE_LENGTH];
    char lines[LINE_COUNT][LINE_LENGTH];
    int current_line_index = 0;

    while (fgets(line_buffer, LINE_LENGTH, input_file) != NULL)
    {
        strcpy(lines[current_line_index], line_buffer);
        current_line_index++;
    }
    fclose(input_file);

    /* array of Claims */
    struct Claim claims[LINE_COUNT];
    for (int i = 0; i < LINE_COUNT; ++i)
    {
        claims[i] = string_to_claim(lines[i]);
    }

    /* size of whole fabric */
    int max_height = 0;
    int max_width = 0;
    int right_edge;
    int bottom_edge;
    for (int i = 0; i < LINE_COUNT; ++i)
    {
        right_edge = claims[i].left + claims[i].width;
        bottom_edge = claims[i].top + claims[i].height;
        
        if (right_edge > max_width)
        {
            max_width = right_edge;
        }

        if (bottom_edge > max_height)
        {
            max_height = bottom_edge;
        }
    }

    int fabric[max_width][max_height];

    /* zero out fabric */
    for (int i = 0; i < max_width; ++i)
    {
        for (int j = 0; j < max_height; ++j)
        {
            fabric[i][j] = 0;
        }
    }

    /* apply claims to fabric */
    for (int l = 0; l < LINE_COUNT; ++l)
    {
        for (int i = claims[l].left; i < claims[l].width + claims[l].left; ++i)
        {
            for (int j = claims[l].top; j < claims[l].height + claims[l].top; ++j)
            {
                fabric[i][j]++;
            }
        }
    }
    
    /* count overlaps */
    int overlaps = 0;
    for (int i = 0; i < max_width; ++i)
    {
        for (int j = 0; j < max_height; ++j)
        {
            if (fabric[i][j] > 1)
            {
                overlaps++;
            }
        }
    }

    printf("number of overlaps: %d\n", overlaps);

    /* What is the ID of the only claim that doesn't overlap? */
    int has_overlap = 0;
    for (int l = 0; l < LINE_COUNT; ++l)
    {
        for (int i = claims[l].left; i < claims[l].width + claims[l].left; ++i)
        {
            for (int j = claims[l].top; j < claims[l].height + claims[l].top; ++j)
            {
                if (fabric[i][j] > 1)
                {
                    has_overlap = 1;
                    break;
                }
            }
            if (has_overlap == 1)
            {
                break;
            }
        }
        if (has_overlap == 0)
        {
            printf("claim id #%d has no overlaps\n", claims[l].id);
            break;
        }
        has_overlap = 0;
    }

    return 0;
}