#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
int rando(){
  int rfile = open("/dev/random", O_RDONLY);
  if(rfile < 0){
    printf("%s\n",strerror(errno));
    return 0;
    //if open fails extra error info is printed
  }
  int *num = malloc(sizeof(int));
  read(rfile,num,sizeof(int));
  close(rfile);
  return *num;
}
int main(){
  int randarr[10];
  printf("Generating Random Numbers:\n");
  for(int x = 0; x < 10; x++){
    randarr[x] = rando();
    printf("\tRandom %d: %d\n", x, randarr[x]);
  }

  printf("Writing numbers to file...\n");
  int wfile = open("writein.txt",O_CREAT | O_WRONLY, 0777);
  if(wfile < 0){
    printf("%s\n",strerror(errno));
    return 0;
  }
  write(wfile,randarr,sizeof(int)*10);

  printf("Reading numbers from file...\n");
  int randarr2[10];
  int rfile = open("writein.txt", O_RDONLY);
  int y = read(rfile,randarr2,sizeof(int)*10);
  if(y < 0){
    printf("%s\n",strerror(errno));
    return 0;
  }
  printf("Verification that written values are the same:\n");
      for (int x = 0; x < 10; x++) {
        printf("\tRandom %d: %d\n", x, randarr2[x]);
      }
  close(wfile);
  close(rfile);
}
