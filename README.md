ACT-heuristiquesGloutonnes
==========================

Auteurs
=======
Valentin Owczarek val.owczarek@gmail.com

Description
===========

tp5 de ACT, université de lille1 Master informatique.

Le but du tp est de resoudre le Probleme du binPack en utilisant des heuristiques.
Cela pour permettre de resoudre le probleme efficacement en terme de temps mais non pas
optimalement.


Fichiers
========
* Gestion du probleme original binpack
    * binpack.c
    * binpack.h

* Gestion des heuristique
    * heuristique.c
    * heuristique.h

* Routine principal
    * mainBinpack.c

* Se simplifier la vie
    * Makefile



How to
======
**Utilisation**

  * Construction de l'executable
    * <code>make</code>
  * Suppresion des objets
    * <code>make clean</code>
  * Suppression des objets et de l'executable
    * <code>make realclean</code>
  * Help
    * <code>./binpack</code>
