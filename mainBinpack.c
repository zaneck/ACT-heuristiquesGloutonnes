#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>

#include"binpack.h"
#include"heuristique.h"
void
usage(void){
  printf("-o ofline mode\n");
  printf("-n nextFit\n");
  printf("-f firstFit\n");
  printf("-bestFit\n");
}


int
main(int argc, char* argv[]){
  int flag; /*0 1 2: next first best*/
  char c;
  int offline;

  certificat_t cer;

  /*debut init*/
  flag=-1;
  offline=0;
  
  while (1) {
    static struct option long_options[] =
      {
	{"offline", no_argument, 0, 'o'},
	{"nextFit", no_argument, 0, 'n'},
	{"firstFit", required_argument, 0, 'f'},
	{"bestFit", no_argument, 0, 'b'},
	{0,0,0,0}
      };
    int option_index = 0;

    c = getopt_long(argc, argv, "onfb", long_options, &option_index);

    if (c == -1) break;

    switch(c){
    case 'o':
      offline=1;
      break;
    case 'n' :
      flag = 0;
      break;
    case 'f' :
      flag = 1;
      break;
    case 'b' :
      flag = 2;
      break;
    case '?' :
      break;
    default :
      usage();
      exit(EXIT_FAILURE);
    }
  }
  /*fin init*/

  if(flag ==-1){
    usage();
    exit(EXIT_FAILURE);
  }
  
  cer= (certificat_t)malloc(sizeof(struct certificat_s));
  lectureData(cer);
  if(offline==1){
    offlineObjet(cer);
  }
  switch(flag){
  case 0:/* next*/
    nextFit(cer);
    break;
    
  case 1:/* first*/
    firstFit(cer);
    break;
    
  case 2:/* best */
    bestFit(cer);
    break;
    
  default:
    usage();
    exit(EXIT_FAILURE);
    break;
  }
  if(isCorrectCertificats(cer)==1){
    printf("Un certificat trouve\n");
    printfCer(cer);
  }
  else{
    printf("Aucun certificat trouve");
  }
  freeCertificat(cer);
  exit(EXIT_SUCCESS);
}
