#include <stdio.h>
#include <stdlib.h>

#include "binpack.h"

#define debug 0

void
nextFit(certificat_t cer){
  int i,n, sacC, capa, sommeSac;

  sacC=0;
  capa=cer->capaciteSac;
  n=cer->nombreObjets;

  /*Pour tous les objets*/
  for(i=0; i<n; i++){
    if(debug==1){
      printfCer(cer);
    }
    /*on essaye de le mettre dans le sacC*/
    sommeSac= sommeColone(cer, sacC) + cer->objets[i];
    if(sommeSac<= capa){
      /*On l'ajoute*/
      cer->tabRes[i][sacC]=1;
    }
    /*sinon on essaye un autre sac, si il en reste*/
    else{
      sacC++;
      
      if(sacC >= cer->nombreSacs){
	return;
      }

      /*si l'objet est trop grand pour le sac...*/
      /*le probleme a pas de solution*/
      cer->tabRes[i][sacC]=1;
    }
  }
  return;
}


void
firstFit(certificat_t cer){
  int i,n, sacC, capa, sommeSac;

  capa=cer->capaciteSac;
  n=cer->nombreObjets;

  /*Pour tous les objets*/
  for(i=0; i<n; i++){
    if(debug==1){
      printfCer(cer);
    }
    sacC=0;
    while(sacC !=-1){
      /*on essaye de le mettre dans le sacC*/
      sommeSac= sommeColone(cer, sacC) + cer->objets[i];
      if(sommeSac <= capa){
	cer->tabRes[i][sacC]=1;
	sacC=-1;
      }
      else{/*sinon on passe au sac suivant*/
	sacC++;
	if(sacC >= cer->nombreSacs){/*si ça passe pas.. echec*/
	  return;
	}
      }
    }
  }
  return;
}


void
bestFit(certificat_t cer){
  int i, j, n, capa, sommeSac;
  int nbSacC, sacSelect, plusRempli;
  
  capa=cer->capaciteSac;
  n=cer->nombreObjets;
  nbSacC=1;

  /*Pour chaque objets*/
  for(i=0; i<n; i++){
    if(debug==1){
      printfCer(cer);
    }
    plusRempli=0;
    sacSelect=-1;
    /*pour tous les sacs créé*/
    for(j=0; j<nbSacC; j++){
      sommeSac= sommeColone(cer, j) + cer->objets[i];
      if(sommeSac <= capa && sommeSac > plusRempli){
	sacSelect=j;
	plusRempli= sommeSac;
      }
    }
    /*sacSelect indique si il y a un sac qui correspond ou non*/
    if(sacSelect != -1){
      cer->tabRes[i][sacSelect]=1;
    }
    else if(++nbSacC > cer->nombreSacs){/*il y a plus de sac dispo*/
      return;
    }
    else{/*on met l'objets dans ce sacs*/
      cer->tabRes[i][nbSacC-1]=1;
    }
  }
  return;
}

static int
comp(const void* a, const void* b){
  if(*(const int *)a==*(const int *)b){
    return 0;
  }
  else if( *(const int *)a>*(const int *)b){
    return 1;
  }
  else{
    return 0;
  }
}

void
offlineObjet(certificat_t cer){
  qsort(cer->objets, (size_t)cer->nombreObjets,sizeof(int), comp);
}
