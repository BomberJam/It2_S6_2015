#include <automate.h>
#include <rationnel.h>
#include <ensemble.h>
#include <outils.h>
#include <parse.h>
#include <scan.h>

#include <stdio.h>

int test_numerotation()
{
  const char *expr = "a.(a.b+a)*.b";
  Rationnel* rat = expression_to_rationnel(expr);
  numeroter_rationnel(rat);

  //printf("Valeur min : %d\nValeur Max : %d\n",get_position_min(rat),get_position_max(rat));

  return(get_position_min(rat) == 1 && get_position_max(rat) == 5);
} 

int main(int argc, char *argv[])
{
  if( ! test_numerotation() )
    return 1; 
   
  return 0;
}
