#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_substituer_variable()
{
  int result = 1;

  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 1 );   
    ajouter_transition( automate, 0, 'b', 2 );
    ajouter_transition( automate, 1, 'b', 2 );
    ajouter_transition( automate, 2, 'a', 0 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 1);
    ajouter_etat_final( automate, 2);
    
    Systeme tab = systeme(automate);
    Rationnel **res = substituer_variable(tab[1],2,tab[2],3);
    print_ligne(res,3);
    TEST(
	 1
	 && get_etiquette(res[0]) == CONCAT
	 && res[1] == NULL
	 && res[2] == NULL
	 && get_etiquette(res[3]) == UNION
	 , result
	 );
  }
  
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'b', 0 );
    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 2, 'a', 2 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 2);

    Systeme tab = systeme(automate);
    Rationnel **res = substituer_variable(tab[0],1,tab[1],3);

    TEST(
	 1
	 && get_lettre(res[0]) == 'b'
	 && res[1] == NULL
	 && get_etiquette(res[2]) == CONCAT
	 && res[3] == NULL
	 , result
	 );
  }
  
  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'b', 0 );
    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'a', 2 );
    ajouter_transition( automate, 2, 'a', 2 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 2);

    Systeme tab = systeme(automate);
    Rationnel **res = substituer_variable(tab[1],2,tab[2],3);

    TEST(
	 1
	 && res[0] == NULL
	 && res[1] == NULL
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
    Rationnel **res = substituer_variable(tab[1],2,tab[2],3);

    TEST(
	 1
	 && res[0] == NULL
	 && get_lettre(res[1]) == 'b'
	 && res[2] == NULL
	 && get_etiquette(res[3]) == UNION
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
    Rationnel **res = substituer_variable(tab[1],2,tab[2],4);


    TEST(
	 1
	 && get_etiquette(res[0]) == UNION
	 && get_etiquette(res[1]) == CONCAT
	 && res[2] == NULL
	 && get_etiquette(res[3]) == UNION
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
    Rationnel **res = substituer_variable(tab[2],3,tab[3],4);
    
    TEST(
	 1
	 && get_etiquette(res[0]) == UNION
	 && get_etiquette(res[1]) == UNION
	 && get_etiquette(res[2]) == CONCAT
	 && res[3] == NULL
	 && get_lettre(res[4]) == 'b'
	 , result
	 );   
  }
  
  return result;
}


int main(int argc, char *argv[])
{
  if( ! test_substituer_variable() )
    return 1; 
   
  return 0;
}
