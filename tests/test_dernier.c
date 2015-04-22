#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

int test_dernier(){
  int result = 1;
  	
  {
    Rationnel * rat;
    rat = expression_to_rationnel("a*.b*");
    numeroter_rationnel(rat);
    Ensemble * e = dernier(rat);
       
    TEST(
	 1
	 && est_dans_l_ensemble(e, 1)
	 && est_dans_l_ensemble(e, 2)
	 , result);
  }
  
  {
    Rationnel * rat;
    rat = expression_to_rationnel("(a+b)*");
    numeroter_rationnel(rat);
    Ensemble * e = dernier(rat);
       
    TEST(
	 1
	 && est_dans_l_ensemble(e, 1)
	 && est_dans_l_ensemble(e, 2)
	 , result);
  }
  
  {
    Rationnel * rat;
    rat = expression_to_rationnel("(a.a)*.(b+c*).(a.b*)");
    numeroter_rationnel(rat);
    Ensemble * e = dernier(rat);
 
    TEST(
	 1
	 && ! est_dans_l_ensemble(e, 1)
	 && ! est_dans_l_ensemble(e, 2)
	 && ! est_dans_l_ensemble(e, 3)
	 && ! est_dans_l_ensemble(e, 4)
	 && est_dans_l_ensemble(e, 5)
	 && est_dans_l_ensemble(e, 6)
	 , result);
  }
  
  {
    Rationnel * rat;
    rat = expression_to_rationnel("(a.a)*.(b+c*).a.b*");
    numeroter_rationnel(rat);
    Ensemble * e = dernier(rat);
 
    TEST(
	 1
	 && ! est_dans_l_ensemble(e, 1)
	 && ! est_dans_l_ensemble(e, 2)
	 && ! est_dans_l_ensemble(e, 3)
	 && ! est_dans_l_ensemble(e, 4)
	 && est_dans_l_ensemble(e, 5)
	 && est_dans_l_ensemble(e, 6)
	 , result);
  }
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_dernier() )
    return 1; 
   
  return 0;
}
