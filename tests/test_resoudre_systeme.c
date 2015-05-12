#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_resoudre_systeme()
{
  int result = 1;

  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 0 );
    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 0, 'b', 2 );
    ajouter_transition( automate, 2, 'a', 2 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 1);
    ajouter_etat_final( automate, 2);

    Systeme tab = systeme(automate);   
    tab = resoudre_systeme(tab, 3);

    TEST(
	 1
	 && tab[0][0] == NULL
	 && tab[0][1] == NULL
	 && tab[0][2] == NULL
	 && tab[1][0] == NULL
	 && tab[1][1] == NULL
	 && tab[1][2] == NULL
	 && tab[2][0] == NULL
	 && tab[2][1] == NULL
	 && tab[2][2] == NULL
	 && get_etiquette(tab[2][3]) == CONCAT
	 , result
	 );
  }
  /*
  {
    
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'a', 1 );
    ajouter_transition( automate, 1, 'b', 0 );

    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);
    ajouter_etat_final( automate, 1);

    Systeme tab = systeme(automate);   
    tab = resoudre_systeme(tab, 2);

    TEST(
	 1
	 && tab[0][0] == NULL
	 && tab[0][1] == NULL
	 && tab[0][2] == NULL
	 && tab[1][0] == NULL
	 && tab[1][1] == NULL
	 && tab[1][2] == NULL
	 && tab[2][0] == NULL
	 && tab[2][1] == NULL
	 && tab[2][2] == NULL
	 && get_etiquette(tab[2][3]) == CONCAT
	 , result
	 );
  }
  *//*
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 0 );
    ajouter_transition( automate, 0, 'b', 0 );
    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 1, 'a', 3 );
    ajouter_transition( automate, 1, 'b', 3 );
    ajouter_transition( automate, 3, 'a', 0 );
    
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 2);

    Systeme tab = systeme(automate);   
    tab = resoudre_systeme(tab, 4);

    TEST(
	 1
	 && tab[0][0] == NULL
	 && tab[0][1] == NULL
	 && tab[0][2] == NULL
	 && tab[1][0] == NULL
	 && tab[1][1] == NULL
	 && tab[1][2] == NULL
	 && tab[2][0] == NULL
	 && tab[2][1] == NULL
	 && tab[2][2] == NULL
	 && get_etiquette(tab[2][3]) == UNION
	 , result
	 );


  }
    *//*
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'a', 1 );
    ajouter_transition( automate, 1, 'b', 2 );
    ajouter_transition( automate, 1, 'c', 3 );
    ajouter_transition( automate, 3, 'a', 2 );
    
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 2);
    ajouter_etat_final( automate, 3);
    
    Systeme tab = systeme(automate);   
    tab = resoudre_systeme(tab, 4);

    TEST(
	 1
	 && tab[0][0] == NULL
	 && tab[0][1] == NULL
	 && tab[0][2] == NULL
	 && tab[1][0] == NULL
	 && tab[1][1] == NULL
	 && tab[1][2] == NULL
	 && tab[2][0] == NULL
	 && tab[2][1] == NULL
	 && tab[2][2] == NULL
	 && get_etiquette(tab[2][3]) == CONCAT
	 , result
	 );


  }
      */
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_resoudre_systeme() )
    return 1; 
   
  return 0;
}
