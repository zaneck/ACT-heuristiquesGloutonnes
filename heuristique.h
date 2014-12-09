#ifndef HEURISTIQUE
#define HEURISTIQUE


/** 
 * Le principe est simple; on a un sac courant; à chaque objet, on le met dans le sac
 * courant si il y a assez de place. Sinon , on crée un nouveau sac courant et on y met l’objet;
*/
void nextFit(certificat_t cer);

/*
 * Pour chaque objet, on regarde si il rentre dans un des sacs créés: si oui, on le met
 * dans le premier qui convient; sinon, on créee un nouveau sac et on y met l’objet;
 */
void firstFit(certificat_t cer);

/*
 * Pour chaque objet, on regarde si il rentre dans un des sacs créés: si oui, on le met
 * dans le celui qui est le plus rempli parmi ceux qui conviennent. Sinon, on crée un nouveau sac et on y
 * met l’objet.
 */
void bestFit(certificat_t cer);

#endif
