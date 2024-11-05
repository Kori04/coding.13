#include <stdio.h>  // Print Commands
#include <stdlib.h> // Basic Commands
#include <sys/time.h> //Used for gettime
#include <unistd.h> // Used To Figure Out PageSize


int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Too Few Arguments Provided\n");
        exit(EXIT_FAILURE);
    }

    long PAGESIZE = sysconf(_SC_PAGESIZE);
    int jump = PAGESIZE / sizeof(int);
    int pages = atoi(argv[1]);
    int trials = atoi(argv[2]);

    if (pages < 0 || trials < 0){
        printf("Incorrect Input\n");
        exit(EXIT_FAILURE);
    }

    int *a = calloc(pages, PAGESIZE);


    int trialnum = 0;
    int i = 0;
    int trialst = 0;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (trialnum = 0; trialnum < trials; trialnum++){
        for (i = 0; i < pages * jump; i += jump)
            a[i] += 1;
            a[i] = 0;
    }

    gettimeofday(&end, NULL);

    float microsecstotal = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    float microsecs = microsecstotal / trials;


    printf("Micro Seconds = %f\n", microsecs);
    free(a);
}

// Question 1: clock_gettime (The timing method I decided to use) is percise to the nanosecond, As such I wil likely only have to run the trials once.
// Question 2: See written code 
// Question 5: I did this by having it set each value to 0 to make sure it has to run the process each time
// Question 6: If this isn't done then it could process much faster by having more TLBs avaiable to split pages across resulting in less misses
// Question 7: This would affect my code, however I use calloc instead of malloc to clear everything and make it a 0 before I run the process.