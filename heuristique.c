#include <stdio.h>
#include <stdlib.h>

#include "binpack.h"

void
nextFit(certificat_t cer){
  int i,n, sacC, capa, sommeSac;

  sacC=0;
  capa=cer->capaciteSac;
  n=cer->nombreObjets;

  /*Pour tous les objets*/
  for(i=0; i<n; i++){
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

}
