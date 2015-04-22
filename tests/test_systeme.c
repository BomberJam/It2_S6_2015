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
   /*
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 0 );
    ajouter_transition( automate, 0, 'b', 0 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);

    Systeme tab = systeme(automate);

    TEST(
	 1
	 && comp
	 && 
	 &&
	 &&
	 , result
	 );
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
    
    Systeme tab = systeme(automate);

    TEST(
	 1
	 && 
	 && 
	 && 
	 && 
	 && 
	 , result
	 );
    }*/
  
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_systeme() )
    return 1; 
   
  return 0;
}
