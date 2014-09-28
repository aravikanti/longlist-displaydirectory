       #define _XOPEN_SOURCE 500
       #include <ftw.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <stdint.h>
       #include <pwd.h>
       #include <grp.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <gnu/libc-version.h>
       //static int count = 0;
       static int
       display_info(const char *fpath, const struct stat *sb,
                    int tflag, struct FTW *ftwbuf)
       {
	  if(ftwbuf->level<=1)
	  {
	  //Type
	     printf("%s",
               (tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
               (tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?   "f" :
               (tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
               (tflag == FTW_SLN) ? "sln" : "-");
	  
	  //Type
	  
	  
	  //Permissions
	      //owner
	     if(sb->st_mode & S_IRWXU & S_IRUSR) printf("r"); else printf("-");
	     if(sb->st_mode & S_IRWXU & S_IWUSR) printf("w"); else printf("-");
	     if(sb->st_mode & S_IRWXU & S_IXUSR) printf("x"); else printf("-");
	     //group
	     if(sb->st_mode & S_IRWXG & S_IRGRP) printf("r"); else printf("-");
	     if(sb->st_mode & S_IRWXG & S_IWGRP) printf("w"); else printf("-");
	     if(sb->st_mode & S_IRWXG & S_IXGRP) printf("x"); else printf("-");
	     //every one else
	     if(sb->st_mode & S_IRWXO & S_IROTH) printf("r"); else printf("-");
	     if(sb->st_mode & S_IRWXO & S_IWOTH) printf("w"); else printf("-");
	     if(sb->st_mode & S_IRWXO & S_IXOTH) printf("x"); else printf("-");
	   //Permissions
	   
	   //Link Count
	   printf(" %2ld", (long) sb->st_nlink);
	   //Link Count
	   
	   //uid,gid
	    struct passwd *pw;
	    if ((pw = getpwuid((uid_t)sb->st_uid)) == NULL) {
		printf("\nFAIL: uid %d does not exist\n", sb->st_uid);
		exit(1);
	    }
	    printf(" %2s", pw->pw_name);
	    struct group *gr;
	    gr= getgrgid(pw->pw_gid);
	    if (!gr)
	    {
	      printf ("\nCouldn't find out about group %d.\n", (int) pw->pw_gid);
	      exit (EXIT_FAILURE);
	    }
	    printf(" %2s", gr->gr_name);	   
	   //uid,gid
	   
	   //size
           printf(" %lld",(long long) sb->st_size);
	   //size
	   
	   //date/time
	   char *dmod_time,*amod_time;
	   amod_time=ctime(&sb->st_mtime);
	   dmod_time=amod_time;
	   int length=0;
	   while(*dmod_time!='\n')
	   {
	      length++;
	     dmod_time++;
	   }
	   *dmod_time='\0';
	   printf("   %s", amod_time);
	   
	   //date/time
	   
	   //file name
	   char *fname = NULL;
	   fname=strrchr (fpath, '/');
	   printf(" %s",fname);
	  //file name
	   
	   
	   
	   
	   printf("\n");
	   
	   //if((tflag & FTW_D)  && (tflag & FTW_DNR) && (tflag & FTW_NS) && ftwbuf->level==1)
	   //{
	     //count = 0;
          // return FTW_SKIP_SUBTREE;		/* To tell nftw() to continue */
	   //}
	  }
	   return 0;
	   
       
       }

       int main(int argc, char *argv[])
       {
           int flags = 0;
	   
	   flags |= FTW_PHYS;
	   //flags |= FTW_ACTIONRETVAL;
	   flags |= FTW_MOUNT;
	   
	   if(argc < 2)
	   {
	      if(nftw(".",display_info,20,flags)== -1)
	      {
		perror("nftw");
		exit(EXIT_FAILURE);
	      }
	   }
	   else
	   {
	     for(int i=1;i<argc;i++)
	     {
		if(nftw(argv[i],display_info,20,flags)==-1)
                {
		    perror("nftw");
		    exit(EXIT_FAILURE);
	        }
	      
	     }
	      
	   }
           exit(EXIT_SUCCESS);
       }
