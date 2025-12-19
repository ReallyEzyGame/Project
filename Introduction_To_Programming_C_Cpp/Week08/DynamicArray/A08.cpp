#include <stdio.h>

// Create an empty labs
int **make_system(const int N)
{
    int **labs = new int *[N];

    return labs;
}
// fill the lab with input requirement
void fill_labs(int **labs, const int *values, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        labs[i] = new int[values[i]];
        // Default value
        for (int j = 0; j < values[i]; ++j)
        {
            labs[i][j] = 0;
        }
    }
}

void log_in(int **labs, const int lab, const int station, const int log, const int N, const int M)
{
    if (lab < 0 || N <= lab)
    {
        throw(10);
    }
    if (station < 0 || M <= station)
    {
        throw(10);
    }

    labs[lab][station] = log;
}
void display(int **labs, const int *lab, const int N) {
    for (int r = 0; r < N; ++r) {
        int col = lab[r];

        for (int i = 0; i < col; ++i) {
            printf("%-5d ", labs[r][i]);
        }
        printf("\n");
    }
}
int main()
{
    const int N = 5;
    int array[N] = {10,11,12,13,14};

    int **labs = make_system(N);
    fill_labs(labs, array, N);

    printf("Before Login:\n");
    display(labs, array, N);

    log_in(labs, 1, 2, 12345, N, array[1]);
    printf("After Login:\n");
    display(labs, array, N);

    
    for (int i = 0; i < N; ++i) {
        delete[] labs[i];
    }
    delete[] labs;
}