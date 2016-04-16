#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

#define SHOWWHOST
#define NRECS 16
#define URSIZE (sizeof(stuct utmp))

static char utmpbuf[NRECS*UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

void show info(struct utmp *);
void showtime(time_t);
int utmp_open( char *);
struct utmp * utmp_next();
void utmp_close();
int utmp_reload();

int main()
{


             struct utmp * utbufp, *utmp_next();

             if( utmp_open( UTMP_FILE ) == -1){ 
                       perror( UTMP_FILE );
                       exit(1);
             }
             while( ( utbufp = utmp_next() ) != NULLUT )
                        show_info( utbufp );
             utmp_close();
             return 0;
}



void show_info( struct utmp 8utbufp ){
        if( utbufp -> ut_type != USER_PROCESS )
                return;
         printf( "%12.12s", utbufp -> ut_name );
         printf( " " );
         printf( "%-8.8s", utbufp -> ut_line );
         printf( "\t" );
         showtime( tubufp -> ut_time );

#ifdef SOWHOST
       if( utbufp -> ut_host[0] != '\0' )
                   printf( " (%s)", utbufp -> ut_host );
#endif

        printf("\n");
}

void showtime ( time_t timeval  ) {
        char *cp;
        struct tm *t;

        cp = ctime( &timeval );
        t = localtime( &timeval );
        printf( "%12.12s", cp + 4 );
}

int utmp_open( char * fileNAme ) {
        fd_utmpmp = open(  fileName, O_RDONLY );
        cur_rec = num_recs = 0;
        return fd_utmp;
}

struct utmp *utmp_next(){
         struct utmp *recp;
      
        if( fd_utmp == -1 )
                 return NULLUT;
        if( cur_rec == num_recs && utmp_reload() == 0 )
               return NULLUT;

       recp = ( struct utmp*)&utmpbuf[cur_rec *UTSIZE];
       cur_rec++;
       return recp;
}

int utmp_reload(){
      int amt_read;
      amr_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
      num_recs = amt_read/UTSIZE;
      cur_rec = 0;
      return num_recs;
}

void utmp_close(){
         if( fd_utmp !=-1)
                close( fd_utmp );
}

