#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined (__linux__) || defined (__gnu_linux__)
    #define CLEAR "clear"
#endif

#if defined (_WIN32) || defined (__WIN32__) || defined (_WIN64) || defined (__WINDOWS__)
    #define CLEAR "cls"
#endif

#if defined (__APPLE__) || defined (__MACH__)
    #define CLEAR "clear"
#endif

void saveProgress(int score)
{
    FILE *save_write_fptr = fopen("progress/save.txt", "w");

    if(save_write_fptr == NULL) { exit(1); }

    fprintf(save_write_fptr, "%d", score);
    fclose(save_write_fptr);
}

void loadProgress(int *score)
{
    FILE *save_read_fptr = fopen("progress/save.txt", "r");

    if(save_read_fptr == NULL) { exit(1); }

    fscanf(save_read_fptr, "%d", score);
    fclose(save_read_fptr);
}

void resetProgress(int *score)
{
    FILE *save_reset_fptr = fopen("progress/save.txt", "w");

    if(save_reset_fptr == NULL) { exit(1); }

    fprintf(save_reset_fptr, "%d", 0);

    *score = 0;

    fclose(save_reset_fptr);
}

int main()
{
    char selection;
    char symbols[] = {'A', 'B', 'C', '?'};
    int slot_1 = 3;
    int slot_2 = 3;
    int slot_3 = 3;
    int score = 0;
    int round = 0;

    srand(time(NULL));
    loadProgress(&score);

    while(1)
    {
        if(round >= 1)
        {
            slot_1 = rand() % 3;
            slot_2 = rand() % 3;
            slot_3 = rand() % 3;

            for(int i = 0; i < 3; i++)
            {
                if(slot_1 == i && slot_2 == i && slot_3 == i)
                {
                    score += 3;
                }
            }
        }

        RESET_PROGRESS_START:
        system(CLEAR);
        printf("=============- \x1b[1;34mYour Score: %d\x1b[m\n", score);
        printf("| \x1b[1;31m%c\x1b[m | \x1b[1;31m%c\x1b[m | \x1b[1;31m%c\x1b[m |\n", symbols[slot_1], symbols[slot_2], symbols[slot_3]);
        printf("=============\nS for Spin, Q for Quit R for Reset Progress > ");
        scanf(" %c", &selection);

        round++;

        if(selection == 's' || selection == 'S') { continue; }
        if(selection == 'q' || selection == 'Q') { saveProgress(score); break; }
        if(selection == 'r' || selection == 'R') { resetProgress(&score); goto RESET_PROGRESS_START; }
    }

    return 0;    
}
