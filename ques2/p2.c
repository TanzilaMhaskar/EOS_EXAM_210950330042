#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>



int *count;
int num;
sem_t s1;
int p1[2];
int p2[2];
pipe(p1);
pipe(p2);
pid_t id;
id =fork;
 

int main()
{
    if(id==0) //child process
    {

    }
    else  //parent process
    {
    open(p1[0],O_RDONLY);
    close(p2[0]);
    int shmd;
    char buff;
    sem_init(&s1,0,1);
    shmd = shm_open("/dictionary.txt",O_RDONLY, S_IRUSR );
    read("dictionary.txt",buff,sizeof(buff));
    ftruncate(shmd, sizeof(int));
    count = (int *)mmap(NULL, sizeof(int), PROT_READ |PROT_WRITE,MAP_SHARED,shmd,0);
    if (buff=="m")
    {
        sem_wait(&s1);
        printf("%s",buff);
        sem_post(&s1);
    }
    
    shm_unlink("/dictionary.txt");
    sem_destroy(&s1);
    }

return 0;
}