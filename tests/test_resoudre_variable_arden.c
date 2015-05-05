#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_resoudre_variable_arden()
{
  int result = 1;

  {
    Automate * automate = creer_automate();

    ajouter_transition( automate, 0, 'a', 1 );
    ajouter_transition( automate, 1, 'b', 2 );
    ajouter_transition( automate, 2, 'a', 2 );
    ajouter_transition( automate, 2, 'a', 0 );
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);
    ajouter_etat_final( automate, 2);

    Systeme tab = systeme(automate);   
    Rationnel **res = resoudre_variable_arden(tab[2],2,3);
  
    TEST(
	 1
	 && get_lettre(res[0]) == 'a'
	 && res[1] == NULL
	 && res[2] == NULL
	 && get_etiquette(res[3]) == STAR	 
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
    Rationnel **res = resoudre_variable_arden(tab[2],2,3);
    
    TEST(
	 1
	 && res[0] == NULL
	 && res[1] == NULL
	 && res[2] == NULL
	 && get_etiquette(res[3]) == STAR
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
    Rationnel **res = resoudre_variable_arden(tab[0],0,3);
    
    TEST(
	 1
	 && res[0] == NULL
	 && get_lettre(res[1]) == 'a'
	 && res[2] == NULL
	 && get_etiquette(res[3]) == STAR
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
    Rationnel **res = resoudre_variable_arden(tab[1],1,3);

    TEST(
	 1
	 && res[0] == NULL
	 && res[1] == NULL
	 && get_etiquette(res[2]) == UNION
	 && get_etiquette(res[3]) == STAR			      
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
    ajouter_transition( automate, 3, 'a', 3 );
    
    ajouter_etat_initial( automate, 0);
    ajouter_etat_final( automate, 0);
    ajouter_etat_final( automate, 3);
   
    Systeme tab = systeme(automate);
    Rationnel **res = resoudre_variable_arden(tab[3],3,4);

    TEST(
	 1
	 && get_lettre(res[0]) == 'b'
	 && get_lettre(res[1]) == 'a'
	 && get_lettre(res[2]) == 'b'
	 && res[3] == NULL
	 && get_etiquette(res[4]) == STAR
	 , result
	 );   
  }

  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_resoudre_variable_arden() )
    return 1; 
   
  return 0;
}

