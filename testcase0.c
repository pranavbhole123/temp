#include "types.h"
#include "stat.h"
#include "user.h"

char mem[4096];
int main() {
    
    printf(1, "Parent writes to shared memory\n");
    mem[0] = 'A';
	int initial = getNumFreePages();
    if (fork() == 0) {
        if(fork() == 0)
        {	
            printf(1, "Free Memory Page Count: %d\n", initial-getNumFreePages());
            *mem = 'C';
            printf(1, "Child - 2 writes: %c\n", *mem);
            printf(1, "Free Memory Page Count: %d\n", initial-getNumFreePages());
            exit(); 
        }
        else
        {
            wait();
            printf(1, "Child - 1 reads: %c\n", *mem);
            printf(1, "Free Memory Page Count: %d\n",initial- getNumFreePages());
            *mem = 'B';
            printf(1, "Child - 1 writes: %c\n", *mem);
            printf(1, "Free Memory Page Count: %d\n",initial- getNumFreePages());
        }
        exit();
        
    } else {
        wait();
        printf(1, "Parent reads: %c\n", *mem);
        printf(1, "Free Memory Page Count: %d\n",initial- getNumFreePages());
        *mem = 'X';
        printf(1, "Parent writes: %c\n", *mem);
        printf(1, "Free Memory Page Count: %d\n",initial- getNumFreePages());
    }

	exit();
}