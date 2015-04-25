#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_systeme()
{
  int result = 1;
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'b', 0 );
    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 2, 'a', 2 );
    ajouter_etat_initial( automate, 1);
    ajouter_etat_final( automate, 2);

    Systeme tab = systeme(automate);

    TEST(
	 1
	 && get_lettre(tab[0][0]) == 'b'
	 && get_lettre(tab[0][1]) == 'a'
	 && tab[0][2] == NULL
	 && tab[0][3] == NULL
	 
	 && tab[1][0] == NULL
	 && tab[1][1] == NULL
	 && get_lettre(tab[1][2]) == 'a'
	 && tab[1][3] == NULL
	 
	 && tab[2][0] == NULL
	 && tab[2][1] == NULL
	 && get_lettre(tab[2][2]) == 'a'
	 && get_etiquette(tab[2][3]) == EPSILON

	 , result
	 );
  }
   
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 0 );
    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'b', 1 );
    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 1, 'b', 2 );
    ajouter_transition( automate, 2, 'a', 2 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);
    ajouter_etat_final( automate, 1);
    ajouter_etat_final( automate, 2);
	
    Systeme tab = systeme(automate);

    TEST(
	 1
	 && get_lettre(tab[0][0]) == 'a'
	 && get_lettre(tab[0][1]) == 'a'
	 && tab[0][2] == NULL
	 && get_etiquette(tab[0][3]) == EPSILON
	 
	 && tab[1][0] == NULL
	 && get_lettre(tab[1][1]) == 'b'
	 && get_etiquette(tab[1][3]) == EPSILON
	 
	 && tab[2][0] == NULL
	 && tab[2][1] == NULL
	 && get_lettre(tab[2][2]) == 'a'
	 && get_etiquette(tab[2][3]) == EPSILON
	 , result
	 );
  }
  
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 0, 'b', 2 );
    ajouter_transition( automate, 0, 'a', 3 );
    ajouter_transition( automate, 1, 'a', 3 );
    ajouter_transition( automate, 1, 'b', 0 );
    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 2, 'a', 0 );
    ajouter_transition( automate, 2, 'b', 3 );
    ajouter_transition( automate, 2, 'b', 1 );
    ajouter_transition( automate, 3, 'a', 1 );
    ajouter_transition( automate, 3, 'b', 2 );
    ajouter_transition( automate, 3, 'b', 0 );

    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);
    ajouter_etat_final( automate, 3);
    Systeme tab = systeme(automate);

    TEST(
	 1
	 && tab[0][0] == NULL
	 && get_lettre(tab[0][1]) == 'a'
	 && get_lettre(tab[0][2]) == 'b'
	 && get_lettre(tab[0][3]) == 'a'
	 && get_etiquette(tab[0][4]) == EPSILON
	 
	 && get_lettre(tab[1][0]) == 'b'
	 && tab[1][1] == NULL
	 && get_lettre(tab[1][2]) == 'a'
	 && get_lettre(tab[1][3]) == 'a'
	 && tab[1][4] == NULL
	 
	 && get_lettre(tab[2][0]) == 'a'
	 && get_lettre(tab[2][1]) == 'b'
	 && tab[2][2] == NULL
	 && get_lettre(tab[2][3]) == 'b'
	 && tab[2][4] == NULL
	 
	 && get_lettre(tab[3][0]) == 'b'
	 && get_lettre(tab[3][1]) == 'a'
	 && get_lettre(tab[3][2]) == 'b'
	 && tab[3][3] == NULL
	 && get_etiquette(tab[3][4]) == EPSILON
	 , result
	 );
    
  }
  
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_systeme() )
    return 1; 
   
  return 0;
}
