#ifndef BINPACK
#define BINPACK

struct certificat_s{
  int** tabRes;

  int* objets;
  
  int nombreObjets;
  int nombreSacs;

  int capaciteSac;
  
};

typedef struct certificat_s * certificat_t;



/**
 * initialise et alloue cer avec les données de la entres standard
 * tabRes prend la valeur du premier certificats
 * un tableau de 0
 *
 * Syntaxe du fichier 
 * n, le nb objets
 * p1
 * P2
 * .
 * .
 * .
 * Pn
 * k , le nb de sacs
 * c , la capacité
 *
  */
void lectureData(certificat_t cer);

/**
 * free une struture cer,
 */
void freeCertificat(certificat_t cer);

/**
 * met a jour le tabRes, ajoute 1 a tab 0,
 * et propagation retenue. 
 */
void certificatNext(certificat_t cer);

/**
 * generation d'un tabRes aleatoire
 * nous supposons une lecture prealable par
 * lectureData
 */
void certificatAlea(certificat_t cer);

/**
 * charge un certificat depuis un fichier
 *
 * return 0 1; erreur de lecture, allclear
 */
int certificatChargement(certificat_t cer);

/**
 * verification d'un certificat
 * return 1, 0: vrai, faux
 *
 */
int isCorrectCertificats(certificat_t cer);


void british(certificat_t cer);
void verif(certificat_t cer);
void nonDeter(certificat_t cer, int nbNonDeter);
void printfCer(certificat_t cer);

#endif
