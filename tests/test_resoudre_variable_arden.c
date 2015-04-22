#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_resoudre_variable_arden()
{
  int result = 0;

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
  print_ligne(res, 3);
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_resoudre_variable_arden() )
    return 1; 
   
  return 0;
}

