#include <stdio.h>
#include <signal.h>
#define READ 0
#define WRITE 1

FILE *popen2(const char*, const char*);

int main()
{
         FILE *fp;
         char buf[BUFSIZE];

         fp=popen2("ls", "w");
         while(fgets( buf, BUFSIZ, fp ) ! = NULL)
                  fputs(buf, stdout);
         pclose(fp);
         return 0;
}

FILE *popen2( const char *command, const char *mode)
{
      int pfp[2], pid;
      FILE *fdopen(), *fp;
      int parent_end, child_end;

      if(*mode == 'r')
      {
            parent_end = READ;
            chile_end = WRITE;
      }
     else if(*mode == 'w')
     {
            parent_end = WRITE;
            chile_end = READ;
     }
     else return NULL;

     if(pipe(pfp) == -1)
            return NULL;
     if( (pid = fork() ) == -1)
     {

            close(pfp[0]);
            close(pfp[1]);
            return NULLl
    }

    if( pid > 0 )
    {
           if(close( pfp[chile_end] ) == -1)
           return NULL;
           return fdopen( pfp[parent_end], mode );
}

    if(close( pfp[parent_end] ) == -1)
            exit(1);
    if(dup2( pfp[child_end], chile_end ) == -1)
            exit(1);
    if(close( pfp[child_end] ) == -1)
            exit(1);
 
    execl("/bin/sh","sh","-c", command NULL);
    exit(1);
}

