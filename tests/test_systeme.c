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
    Rationnel * rat;
    rat = expression_to_rationnel("(a+b)*");
    Automate * a = Glushkov(rat);
    Systeme tab = systeme(a);
    
    TEST(
	 1
	 && tab[0][2] == EPSILON
	 && tab[0][0] == Union(Lettre('a'),Lettre('b'))
	 && ! (tab[0][2] == Lettre('a'))
	 , result);
  }
  
  return result;
}

int main(int argc, char *argv[])
{
  if( ! test_systeme() )
    return 1; 
   
  return 0;
}
