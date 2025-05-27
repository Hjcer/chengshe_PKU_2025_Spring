
#include<getopt.h>
#include<stdio.h>
#include<stdlib.h>


int str2int(char * a)
{
    int res = 0;
    for(int i = 0; a[i] != '\0'; i++)
    {
        res = res * 10 + a[i] - '0';
    }
    return res;
}

void mystrcpy(char * ini, char * b)
{
    int i = 0;
    for(;ini[i] != '\0'; i++)
    {
        b[i] = ini[i];
    }
}


int main(int argc, char *argv[])
{
    int isv = 0;
    int s = 0;
    int E = 0;
    int b = 0;

    char * t = (char *) malloc(sizeof(char) * 50);
    
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\nOptions:\n  -h         Print this help message.\n  -v         Optional verbose flag.\n  -s <num>   Number of set index bits.\n  -E <num>   Number of lines per set.\n  -b <num>   Number of block offset bits.\n  -t <file>  Trace file.\n\nExamples:\n  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace");
                goto END;
                break;
            case 's':
                s = str2int(optarg);
                break;
            case 'E':
                E = str2int(optarg);
                break;
            case 'b':
                b = str2int(optarg);
                break;
            case 't':
                mystrcpy(optarg, t);

        }
    }
    


    printSummary(0, 0, 0);
END:
    return 0;
}
