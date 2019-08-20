#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>



void  tostr ( int k , char str[])
{
    str[0]='\r';
    str[1]= k/10+48;
    str[2]=k%10+48;
    str[3]='\0';
    if (k==100)
    {
        str[0]='\r';
        str[1]='1';
        str[2]='0';
        str[3]='0';
        str[4]='\0';
    }
}

void barprint(int per)
{
    char  bar[53];
    bar[0]=' ';
    bar[1]=' ';
    bar[2]='[';
    for (int i=3;i<53;i++)
    {
        if ((i-3)<per/2)
            bar[i]='=';
        else if ((i-3)==per/2)
            bar[i]='>';
        else 
            bar[i]='.';
    }
    bar[52]=']';
    write(1,bar,53);

}


char * getname (char * path)
{
    int curr=0;
    char * toret ; 
    for (int i=0;path[i]!='\0';i++)
    {   
        if (path[i]=='/')
            curr=i;
    }
    if (curr == 0)
        toret=path;
    else 
        toret=curr+path+1;
    return toret;
}


int main( int argc , char * argv[])
{
    char * fpath ;
    char * filename ;
    if (argc == 1)
    {
        fpath= "";
        write (1,"no argument given\n",18);
        exit(1);
    }
    else
    {
        fpath = argv[1];  
//        printf ("%s \n", argv[1]);
    }
//  printf ("%s",argv[1]);
    char   dirna[100] ;
    char *  chap= "Assignment\0" ;

//    argv[2]="Assignment";
//    if (argc>2)
//        dirna=argv[2];
//    else 
//    {

    for (int i=0;i<11;i++)
    {
        dirna[i]=chap[i];
    }

//  }
//        dirna="Assignment";
    
//    printf ("direcory is %s\n",dirna);
    int fd1,fd2;    //file descriptors
    long long int offset; //current offset
    fd1 = open(fpath, O_RDONLY);      //open file to read
    if (fd1<0)
    {
        perror ("Error");
        write(1,"Open error\n",11);
        exit(1);
    }
    mkdir (dirna,0700);
    filename= getname(fpath);

    char str[4];

//    printf ("filename is %s \n",filename);

    int lencount =0;        
    for (int i=0;dirna[i]!='\0';i++)
    {
//      printf ("%d\n",lencount);
        lencount++;
    }
//  printf ("dirna is 1 %s \n \n ",dirna );
    dirna[lencount]='/';
    lencount++;
//  printf ("dirna is %s \n \n ",dirna );
//  lencount++;
    int k=0;
    while (filename[k]!='\0')
    {
        dirna[k+lencount]=filename [k];
        k++;
    }
    dirna[k+lencount]='\0';

//  printf ("dirna is %s \n \n ",dirna );

    if (fd1 < 0)
    {
        write(1,"Open error\n",11);
    }
    fd2 = open(dirna , O_WRONLY | O_CREAT | O_TRUNC, 0600);   
    
    if(fd2 < 0)
    {
        perror("Error");
        write(1, "Open error\n",11);
        exit(1);
    }

    offset = lseek(fd1, 0, SEEK_END);    //go to the end of the file
    long long int chunk = offset/100;
    if(!chunk) ++chunk;
    int start = lseek(fd1,-chunk, SEEK_CUR);
    char *hell = (char * )malloc (chunk * sizeof(char));     
    char *c = (char * )malloc (chunk * sizeof(char));       
//    char c[3];    
//    offset +=1;
//    int nchunk;
    int yoogs=start;
    start += chunk;
//    printf ("hi %lld %d %lld\n",offset,start,chunk );
    int per=0;
    while (offset > 0 )      //while it is not the beginning of the file 
    {
        tostr(per,str);
        if (per < 100)
        {
            write (1,str,3);
            write (1,"% Done",6);
            barprint(per);
        }
        else
        {
            write (1,"\r100",4);
            write (1,"% Done",7);
        }

        per = ((start - offset) * 100) / start;

//        if (offset < chunk)
//            chunk=offset ;
//        printf("offset = %lld ", offset );
//        int myvar= lseek(fd1,0,SEEK_CUR);
//        printf ("but pointer is %d \n",myvar);
        int reading = read(fd1, c, chunk);  //read a char
        if (reading <0)
        {
            perror("Error");
        }
//        printf ("taken = %s \n", c);
        int chunktemp = chunk-1;
        for (int i=0;i<chunk;i++)
        {
            hell[i]=c[chunktemp];
            chunktemp--;
        }
  //      printf ("printed %s\n",hell);
        int writing = write(fd2, hell, chunk);  //write the char
        if (writing < 0 )
            perror("Error");
        if (yoogs==0) {
//            printf("breaking\n");
            break;
        } if (yoogs<chunk)
        {
            chunk=yoogs;
            yoogs=lseek(fd1,0,SEEK_SET);
//            printf("<chunk\n");
        }
        else 
            yoogs = lseek(fd1, -2*chunk, SEEK_CUR);   

//        printf("%lld\n",offset);
        offset-= chunk;    
//        if (offset < chunk )
//        {
//            nchunk = offset-1;
//            flag =0;
//        }
    }


/*        
        read(fd1, &c, nchunk);  //read a char
        printf ("taken = %s \n", c);
        int chunktemp = nchunk-1;
        for (int i=0;i<nchunk;i++)
        {
            hell[i]=c[chunktemp];
            chunktemp--;
        }
        printf ("printed %s\n",hell);
        write(fd2, &hell, nchunk);  //write the char
//        lseek(fd1, -2*chunk, SEEK_CUR);   //go back 2 spots to the char before the one just read
        printf("%d\n",offset);
  */ 
    free (c);
    free(hell);

    write(1, "\r100% Done\n", 12);
    int bk = close(fd1);  //close the files
    if (bk<0)
    {
        perror("Error");
        exit(1);
    }
    int dk = close(fd2);
    if (dk < 0 )
    {
        perror("Error");
        exit(1);
    }
    return 0;
}
