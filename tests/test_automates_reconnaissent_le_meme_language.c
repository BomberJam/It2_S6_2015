/*
 *   Ce fichier fait partie d'un projet de programmation donné en Licence 3 
 *   à l'Université de Bordeaux
 *
 *   Copyright (C) 2015 Adrien Boussicault
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "automate.h"
#include "outils.h"
#include "ensemble.h"
#include <stdarg.h>

int test_automates_reconnaissent_le_meme_language(){
  int resultat = 1;
  /*
  {
    Automate* automate1 = creer_automate();
    ajouter_etat_initial( automate1, 0 );
    ajouter_etat_final( automate1, 1 );
    ajouter_transition( automate1, 0, 'a', 1 );

    Automate* automate2 = creer_automate();
    ajouter_etat_initial( automate2, 0 );
    ajouter_etat_final( automate2, 1 );
    ajouter_transition( automate2, 0, 'b', 1 );

    int test=automates_reconnaissent_le_meme_language(automate1, automate2); 

    TEST(
	 1
	 && ! test
	 , resultat
	 );

    liberer_automate( automate1 );
    liberer_automate( automate2 );
  }

  {
    Automate* automate1 = creer_automate();
    ajouter_etat_initial( automate1, 0 );
    ajouter_etat_final( automate1, 1 );
    ajouter_transition( automate1, 0, 'a', 1 );

    Automate* automate2 = creer_automate();
    ajouter_etat_initial( automate2, 0 );
    ajouter_etat_final( automate2, 1 );
    ajouter_transition( automate2, 0, 'a', 1 );

    int test=automates_reconnaissent_le_meme_language(automate1, automate2); 

    TEST(
	 1
	 && test
	 , resultat
	 );

    liberer_automate( automate1 );
    liberer_automate( automate2 );
  }
  */
  {
    Automate* automate1 = creer_automate();
    ajouter_etat_initial( automate1, 0 );
    ajouter_etat_final( automate1, 3 );
    ajouter_transition( automate1, 0, 'a', 1 );
    ajouter_transition( automate1, 0, 'a', 3 );
    ajouter_transition( automate1, 1, 'b', 2 );
    ajouter_transition( automate1, 2, 'a', 1 );
    ajouter_transition( automate1, 2, 'a', 3 );

    Automate* automate2 = creer_automate();
    ajouter_etat_initial( automate2, 0 );
    ajouter_etat_final( automate2, 1 );
    ajouter_etat_final( automate2, 3 );
    ajouter_transition( automate2, 0, 'a', 1 );
    ajouter_transition( automate2, 1, 'b', 2 );
    ajouter_transition( automate2, 2, 'a', 3 );
    ajouter_transition( automate2, 3, 'b', 2 );

    int test=automates_reconnaissent_le_meme_language(automate1, automate2); 

    TEST(
	 1
	 && test
	 , resultat
	 );

    liberer_automate( automate1 );
    liberer_automate( automate2 );
  }
  
  {
    Automate* automate1 = creer_automate();
    ajouter_etat_initial( automate1, 0 );
    ajouter_etat_final( automate1, 3 );
    ajouter_transition( automate1, 0, 'a', 1 );
    ajouter_transition( automate1, 0, 'a', 3 );
    ajouter_transition( automate1, 1, 'b', 2 );
    ajouter_transition( automate1, 2, 'a', 1 );
    ajouter_transition( automate1, 2, 'a', 3 );

    Automate* automate2 = creer_automate();
    ajouter_etat_initial( automate2, 0 );
    ajouter_etat_final( automate2, 1 );
    ajouter_etat_final( automate2, 3 );
    ajouter_transition( automate2, 0, 'b', 1 );
    ajouter_transition( automate2, 1, 'a', 2 );
    ajouter_transition( automate2, 2, 'b', 3 );
    ajouter_transition( automate2, 3, 'a', 2 );

    int test=automates_reconnaissent_le_meme_language(automate1, automate2); 

    TEST(
	 1
	 && ! test
	 , resultat
	 );

    liberer_automate( automate1 );
    liberer_automate( automate2 );
  }
  
  return resultat;
}

int main(){

  if( ! test_automates_reconnaissent_le_meme_language() ){ return 1; }

  return 0;
}
