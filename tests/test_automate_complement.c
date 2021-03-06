#include "automate.h"
#include "outils.h"
#include "rationnel.c"

int test_automate_complement(){

  int result = 1;

  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 2, 'b', 3 );
    ajouter_transition( automate, 3, 'b', 4 );
    ajouter_transition( automate, 4, 'a', 5 );
    ajouter_etat_initial( automate, 1);
    ajouter_etat_final( automate, 5);



    Automate * comp = creer_automate_complement( automate );

    TEST(
	 1
	 && comp
	 && le_mot_est_reconnu( comp, "" )
	 && le_mot_est_reconnu( comp, "a" )
	 && le_mot_est_reconnu( comp, "ab" )
	 && le_mot_est_reconnu( comp, "abb" )
	 && ! le_mot_est_reconnu( comp, "abba" )
	 , result
	 );
    liberer_automate( automate );
    liberer_automate( comp );
  }
  
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 0 );
    ajouter_transition( automate, 0, 'b', 0 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);

    Automate * comp = creer_automate_complement(automate );

    TEST(
	 1
	 && comp
	 && ! le_mot_est_reconnu( comp, "" )
	 && ! le_mot_est_reconnu( comp, "a" )
	 && ! le_mot_est_reconnu( comp, "ab" )
	 , result
	 );
    liberer_automate( automate );
    liberer_automate( comp );
  }

  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'b', 1 );
    ajouter_transition( automate, 1, 'a', 0 );
    ajouter_transition( automate, 0, 'b', 2 );
    ajouter_transition( automate, 2, 'a', 0 );
    ajouter_transition( automate, 2, 'b', 0 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);
    
    Automate * comp = creer_automate_complement( automate );

    TEST(
	 1
	 && comp
	 && ! le_mot_est_reconnu( comp, "" )
	 && ! le_mot_est_reconnu( comp, "abba" )
	 && ! le_mot_est_reconnu( comp, "aba" )
	 && le_mot_est_reconnu( comp, "a" )
	 && le_mot_est_reconnu( comp, "ab" )
	 , result
	 );
    liberer_automate( automate );
    liberer_automate( comp );
  }
  return result;
}



int main(){

	if( ! test_automate_complement() ){ return 1; }

	return 0;
}
