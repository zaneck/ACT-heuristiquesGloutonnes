#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#include<unistd.h>
#include<string.h>
#include<math.h>
#include<time.h>

#include "binpack.h"

/* le but est de proposer plusieur mode de verification pour le probleme Binpack
 * mode verification, l'utilisateur saisi son certificat
 * mode "non-deterministe" calcul un certificat au hasard et le verifie
 * mode British Museum, enumeration de tous les certificats arret au permier certificat correcte
 */


void
lectureData(certificat_t cer){
  int i, n, k;
  
  printf("nombre d'objets?\n");
  scanf("%d", &n);
  cer->nombreObjets=n;

  cer->objets=(int*)calloc((size_t)n, sizeof(int));

  for(i=0; i<n; i++){
    printf("poid de l'objet numero %d\n", i);
    scanf("%d", &cer->objets[i]);
  }

  printf("nombre de sacs?\n");
  scanf("%d", &k);
  cer->nombreSacs=k;

  printf("Capacité des sacs?\n");
  scanf("%d", &cer->capaciteSac);
  
  /*tab de n*k*/
  cer->tabRes=(int**)calloc((size_t)n, sizeof(int*));
  for(i=0; i<n; i++){
    cer->tabRes[i]=(int*)calloc((size_t)k, sizeof(int));
  }
  
  return;
}

void
freeCertificat(certificat_t cer){
  int i;
  
  free(cer->objets);
  for(i=0; i<cer->nombreObjets; i++){
    free(cer->tabRes[i]);
  }
  free(cer->tabRes);
  free(cer);
}


void
certificatNext(certificat_t cer){
  int i,j;

  i=0;
  j=0;

  cer->tabRes[i][j]++;

  while(cer->tabRes[i][j]>1 && (i<cer->nombreObjets)){
    cer->tabRes[i][j]=0;
    j++;
    if(j==cer->nombreSacs){
      j=0;
      i++;
    }
    cer->tabRes[i][j]+=1;
  }
  
  return;
}


void
certificatAlea(certificat_t cer){
  int i, j;
  for(i=0; i<cer->nombreObjets; i++){
    for(j=0; j<cer->nombreSacs; j++){
      if(random()%2 ==1){
	cer->tabRes[i][j]=1;
      }
      else{
	cer->tabRes[i][j]=0;
      }
    }
  }
}

int
certificatChargement(certificat_t cer){
  int n,s;
  char string[5];
  
  while(1){
    printf("objets?\n");
    scanf("%d", &n);
    printf("sacs?\n");
    scanf("%d", &s);

    cer->tabRes[n][s]=1;

  
    printf("voulez vous encore rentrer un objets? (non)\n");
    scanf("%s", string);
    if(strcmp("non",string)==0){
      break;
    }
  }
  
  return 1;
}

int
sommeLigne(certificat_t cer, int ligne){
  int retour, i;

  retour=0;
  
  for(i=0; i<cer->nombreSacs; i++){
    retour+= cer->tabRes[ligne][i];
  }

  return retour;
}

int
sommeColone(certificat_t cer, int col){
  int retour, i;

  retour=0;
  
  for(i=0; i<cer->nombreObjets; i++){
    if(cer->tabRes[i][col]==1){
      retour += cer->objets[i];
    }
  }

  return retour;
}

/* correcte si somme ligne = 1*/
/* somme colone pondéré des poids colone */
int
isCorrectCertificats(certificat_t cer){
  int i;

  for(i=0; i< cer->nombreObjets; i++){
    if(sommeLigne(cer, i) != 1){
      return -1;
    }
  }

  for(i=0; i<cer->nombreSacs; i++){
    if(sommeColone(cer, i)>cer->capaciteSac){
      return -1;
    }
  }
  
  return 1;
}

void
british(certificat_t cer){
  unsigned long i, k;
  int r;

  k=(int)pow((double)2,(double)cer->nombreObjets * cer->nombreSacs)-1;
  
  for(i=0; i< k; i++){
    r = isCorrectCertificats(cer);
    if(r==1){
      printfCer(cer);
      printf("One certificat found\n");
      return;
    }
    else{
      certificatNext(cer);
    }
  }
  printfCer(cer);
  printf("No certificat found\n");
}

void
verif(certificat_t cer){
  int r;
  
  certificatChargement(cer);
  r = isCorrectCertificats(cer);

  if(r==1){
    printfCer(cer);
    printf("One certificat found\n");
    return;
  }
  return;
}

void
nonDeter(certificat_t cer, int nbNonDeter){
  int r, i;

  srand((unsigned int)time(NULL));
  
  for(i=0; i<nbNonDeter; i++){
    certificatAlea(cer);
    r = isCorrectCertificats(cer);

    if(r==1){
      printfCer(cer);
      printf("One certificat found\n");
      return;
    }
  }
  printf("No certificat found\n");
  return;
}

void
printfCer(certificat_t cer){
  int i, j;
  
  printf("nombre d'objets %d\n",cer->nombreObjets);

  for(i=0; i<cer->nombreObjets; i++){
    printf("poid de l'objet numero %d, %d\n", i, cer->objets[i]);
  }

  printf("nombre de sacs %d\n", cer->nombreSacs);

  printf("Capacité des sacs %d\n",cer->capaciteSac);
 
  for(i=0; i< cer->nombreObjets; i++){
    printf("<%d> ", cer->objets[i]);
    for(j=0; j< cer->nombreSacs; j++){
      printf("%d ",cer->tabRes[i][j]);
    }
    printf("\n");
  }

}
