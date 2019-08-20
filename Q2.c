#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


void  printing (char * filename, int typ)
{
    char * toprint;
    int len;
    if (typ == 1)
    {
        toprint = "newfile: ";
        len = 9;
    }
    else if (typ == 2)
    {
        toprint = "oldfile: ";
        len = 9;
    }
    else 
    {
        toprint = "directory: ";
        len = 11;
    }
        struct stat details ;
        int statint = stat(filename,&details);
        if (statint < 0 )
            perror ("Error");
        else {
        write (1,"User has read permissions on ",29);
        write(1,toprint,len);
        if (details.st_mode & S_IRUSR)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"User has write permissions on ",30);
        write(1,toprint,len);
        if (details.st_mode & S_IWUSR)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"User has execute permissions on ",32);
        write(1,toprint,len);
        if (details.st_mode & S_IXUSR)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"\nGroup has read permissions on ",31);
        write(1,toprint,len);
        if (details.st_mode & S_IRGRP)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"Group has write permissions on ",31);
        write(1,toprint,len);
        if (details.st_mode & S_IWGRP)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"Group has Execute permissions on ",33);
        write(1,toprint,len);
        if (details.st_mode & S_IXGRP)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"\nOthers have read permissions on ",33);
        write(1,toprint,len);
        if (details.st_mode & S_IROTH)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"Others have write permissions on ",33);
        write(1,toprint,len);
        if (details.st_mode & S_IWOTH)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        write (1,"Others have execute permissions on ",35);
        write(1,toprint,len);
        if (details.st_mode & S_IXOTH)
            write(1,"Yes\n",4);
        else 
            write(1,"No\n",3) ;
        
    }
}




int main (int argc , char * argv[])
{
    int readin2,reading;
    if (argc<3)
    {
        write (1,"Provide Complete Inputs\n",24);
        exit(1);
    }
    else 
    {
        char * newfile = argv[1];
        char * oldfile = argv[2];
        char * directry = argv[3];
        struct stat k;
        int var = stat (directry,&k);
        write (1,"Directory is created: ",22);
        int flag =0;
        if (var == -1 )
        {
            write(1,"No\n\n",4);
            flag++;
        }
        else if (var ==0 && S_ISDIR(k.st_mode)) 
            write (1,"Yes\n\n",5);
        else 
            write(1,"No, it is a file\n\n",18);
        
        write (1,"NEWFILE\n",8);
        printing (newfile,1);
        write (1,"\nOLDFILE\n",9);
        printing (oldfile,2);
        if (!flag)
        {
            write (1,"\nDirectory\n",11);
            printing (directry,3);
        }
        else 
            write (1,"\nNo Directory Created\n",22);
    
    int fd1,fd2;    
    long long int offset; 
    fd1 = open(newfile, O_RDONLY);      

    if (fd1 < 0)
    {
        perror("Error");
        write(1,"Open error\n",11);
        exit(1);
    }
    fd2 = open(oldfile , O_RDONLY );   //open file to write with rw-------

    if(fd2 < 0)
    {
        perror("Error");
        write(1, "Open error\n",11);
        exit(1);
    }

    offset = lseek(fd1, 0, SEEK_END);    //go to the end of the file
    long long int chunk = offset/100;
    int start = lseek(fd1,-chunk, SEEK_CUR);
    char *hell = (char * )malloc (chunk * sizeof(char));
    char *hellrev = (char * )malloc (chunk * sizeof(char));
    char *c = (char * )malloc (chunk * sizeof(char));        
//    offset +=1;
//    int nchunk;
    int yoogs=start;
//    printf ("hi %lld %d %lld\n",offset,start,chunk );
    int per=0;
    lseek(fd2,0,SEEK_SET);
    int finalflag =0;
    while (offset > 0 )      //while it is not the beginning of the file
    {
        per++;
        if (per>100)
            per=100;
        reading = read(fd1, c, chunk);  //read a char
        if (reading<0)
            perror("Error");
        int chunktemp = chunk-1;
        /*
        for (int i=0;i<chunk;i++)
        {
            hell[i]=c[chunktemp];
            chunktemp--;
        }
        */
// **       printf ("read  %s\n",c);
        readin2 = read(fd2, hellrev, chunk);  
        if (readin2<0)
            perror("Error");
        for (int i=0;i<chunk;i++)
        {
            hell[i]=c[chunktemp];
            if (c[chunktemp]!=hellrev[i])
            {
//                write(1,"No\n",3);
                finalflag++;
            }
            chunktemp--;
        }
// **       printf("rev of read == %s\n",hell);
// **       printf("helrev == %s\n",hellrev);
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
//          printf("%lld\n",offset);
        offset-= chunk;     //track the current offset
//        if (offset < chunk )
//        {
//            nchunk = offset-1;
//            flag =0;
//        }
    }
    write (1,"\nis newfile reverse of oldfile :",32);
    if (finalflag || fd1<0 || fd2<0 )
        write(1,"No\n",3);
    else 
        write(1,"Yes\n",4);

    free(hell);
    free(hellrev);
    free(c);

    int bk = close(fd1);
    if (bk < 0 )
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

        
    }
}
