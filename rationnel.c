/*
 *   Ce fichier fait partie d'un projet de programmation donné en Licence 3 
 *   à l'Université de Bordeaux.
 *
 *   Copyright (C) 2015 Giuliana Bianchi, Adrien Boussicault, Thomas Place, Marc Zeitoun
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rationnel.h"
#include "ensemble.h"
#include "automate.h"
#include "parse.h"
#include "scan.h"
#include "outils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int yyparse(Rationnel **rationnel, yyscan_t scanner);

Rationnel *rationnel(Noeud etiquette, char lettre, int position_min, int position_max, void *data, Rationnel *gauche, Rationnel *droit, Rationnel *pere)
{
   Rationnel *rat;
   rat = (Rationnel *) malloc(sizeof(Rationnel));

   rat->etiquette = etiquette;
   rat->lettre = lettre;
   rat->position_min = position_min;
   rat->position_max = position_max;
   rat->data = data;
   rat->gauche = gauche;
   rat->droit = droit;
   rat->pere = pere;
   return rat;
}

Rationnel *Epsilon()
{
   return rationnel(EPSILON, 0, 0, 0, NULL, NULL, NULL, NULL);
}

Rationnel *Lettre(char l)
{
   return rationnel(LETTRE, l, 0, 0, NULL, NULL, NULL, NULL);
}

Rationnel *Union(Rationnel* rat1, Rationnel* rat2)
{
   // Cas particulier où rat1 est vide
   if (!rat1)
      return rat2;

   // Cas particulier où rat2 est vide
   if (!rat2)
      return rat1;
   
   return rationnel(UNION, 0, 0, 0, NULL, rat1, rat2, NULL);
}

Rationnel *Concat(Rationnel* rat1, Rationnel* rat2)
{
   if (!rat1 || !rat2)
      return NULL;

   if (get_etiquette(rat1) == EPSILON)
      return rat2;

   if (get_etiquette(rat2) == EPSILON)
      return rat1;
   
   return rationnel(CONCAT, 0, 0, 0, NULL, rat1, rat2, NULL);
}

Rationnel *Star(Rationnel* rat)
{
   return rationnel(STAR, 0, 0, 0, NULL, rat, NULL, NULL);
}

bool est_racine(Rationnel* rat)
{
   return (rat->pere == NULL);
}

Noeud get_etiquette(Rationnel* rat)
{
   return rat->etiquette;
}

char get_lettre(Rationnel* rat)
{
   assert (get_etiquette(rat) == LETTRE);
   return rat->lettre;
}

int get_position_min(Rationnel* rat)
{
   return rat->position_min;
}

int get_position_max(Rationnel* rat)
{
   return rat->position_max;
}

void set_position_min(Rationnel* rat, int valeur)
{
   rat->position_min = valeur;
   return;
}

void set_position_max(Rationnel* rat, int valeur)
{
   rat->position_max = valeur;
   return;
}

Rationnel *fils_gauche(Rationnel* rat)
{
   return rat->gauche;
}

Rationnel *fils_droit(Rationnel* rat)
{
   return rat->droit;
}

Rationnel *fils(Rationnel* rat)
{
   return rat->gauche;
}

Rationnel *pere(Rationnel* rat)
{
   return rat->pere;
}

void print_rationnel(Rationnel* rat)
{
   if (rat == NULL)
   {
      printf("∅");
      return;
   }
   
   switch(get_etiquette(rat))
   {
      case EPSILON:
         printf("ε");         
         break;
         
      case LETTRE:
         printf("%c", get_lettre(rat));
         break;

      case UNION:
         printf("(");
         print_rationnel(fils_gauche(rat));
         printf(" + ");
         print_rationnel(fils_droit(rat));
         printf(")");         
         break;

      case CONCAT:
         printf("[");
         print_rationnel(fils_gauche(rat));
         printf(" . ");
         print_rationnel(fils_droit(rat));
         printf("]");         
         break;

      case STAR:
         printf("{");
         print_rationnel(fils(rat));
         printf("}*");         
         break;

      default:
         assert(false);
         break;
   }
}

Rationnel *expression_to_rationnel(const char *expr)
{
    Rationnel *rat;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    // Initialisation du scanner
    if (yylex_init(&scanner))
        return NULL;
 
    state = yy_scan_string(expr, scanner);

    // Test si parsing ok.
    if (yyparse(&rat, scanner)) 
        return NULL;
    
    // Libération mémoire
    yy_delete_buffer(state, scanner);
 
    yylex_destroy(scanner);
 
    return rat;
}

void rationnel_to_dot(Rationnel *rat, char* nom_fichier)
{
   FILE *fp = fopen(nom_fichier, "w+");
   rationnel_to_dot_aux(rat, fp, -1, 1);
}

int rationnel_to_dot_aux(Rationnel *rat, FILE *output, int pere, int noeud_courant)
{   
   int saved_pere = noeud_courant;

   if (pere >= 1)
      fprintf(output, "\tnode%d -> node%d;\n", pere, noeud_courant);
   else
      fprintf(output, "digraph G{\n");
   
   switch(get_etiquette(rat))
   {
      case LETTRE:
         fprintf(output, "\tnode%d [label = \"%c-%d\"];\n", noeud_courant, get_lettre(rat), rat->position_min);
         noeud_courant++;
         break;

      case EPSILON:
         fprintf(output, "\tnode%d [label = \"ε-%d\"];\n", noeud_courant, rat->position_min);
         noeud_courant++;
         break;

      case UNION:
         fprintf(output, "\tnode%d [label = \"+ (%d/%d)\"];\n", noeud_courant, rat->position_min, rat->position_max);
         noeud_courant = rationnel_to_dot_aux(fils_gauche(rat), output, noeud_courant, noeud_courant+1);
         noeud_courant = rationnel_to_dot_aux(fils_droit(rat), output, saved_pere, noeud_courant+1);
         break;

      case CONCAT:
         fprintf(output, "\tnode%d [label = \". (%d/%d)\"];\n", noeud_courant, rat->position_min, rat->position_max);
         noeud_courant = rationnel_to_dot_aux(fils_gauche(rat), output, noeud_courant, noeud_courant+1);
         noeud_courant = rationnel_to_dot_aux(fils_droit(rat), output, saved_pere, noeud_courant+1);
         break;

      case STAR:
         fprintf(output, "\tnode%d [label = \"* (%d/%d)\"];\n", noeud_courant, rat->position_min, rat->position_max);
         noeud_courant = rationnel_to_dot_aux(fils(rat), output, noeud_courant, noeud_courant+1);
         break;
         
      default:
         assert(false);
         break;
   }
   if (pere < 0)
      fprintf(output, "}\n");
   return noeud_courant;
}

Rationnel* numerotation_rationnel(Rationnel* rat, int valeur){
  
  if(get_etiquette(rat) == LETTRE)
    {
      set_position_min (rat, ++valeur );
      set_position_max (rat,valeur);
      return rat;
    }

  if(fils_gauche (rat) != NULL)
    {
      if(get_etiquette(rat) == STAR)
	{
	  Rationnel* minmax = numerotation_rationnel(fils(rat),valeur);      
	  set_position_min (rat, get_position_min(minmax));
	  set_position_max (rat, get_position_max(minmax));
	  valeur = get_position_max(minmax);
	}
      else
	{
	  Rationnel* rat_min = numerotation_rationnel(fils_gauche(rat), valeur);
	  set_position_min(rat,get_position_min(rat_min));
	  valeur = get_position_max(rat_min);
	}
    }

  if(fils_droit (rat) != NULL)
    {
      Rationnel* rat_max = numerotation_rationnel(fils_droit(rat), valeur);
      set_position_max(rat,get_position_max(rat_max));
      valeur = get_position_max(rat_max);
    }

  return rat;
}

void numeroter_rationnel(Rationnel *rat)
{  
  numerotation_rationnel(rat,0);
}

bool contient_mot_vide(Rationnel *rat)
{
    if(!rat)
    return false;
 
    if(get_etiquette(rat) == EPSILON || get_etiquette(rat) == STAR)
      return true;
    
    if(fils_gauche (rat) != NULL)  
      if(fils_droit (rat) != NULL)
	return contient_mot_vide(fils_gauche(rat)) || contient_mot_vide(fils_droit(rat));
    
    return false;
}

void trouver_premier(Ensemble * e, Rationnel * rat){
  if(!rat)
    return;  
  switch(get_etiquette(rat))
    {
    case EPSILON:
      break;
      
    case LETTRE:     
      ajouter_element(e,(intptr_t)get_position_min(rat));
      break;
      
    case UNION:
      trouver_premier(e,fils_gauche(rat));
      trouver_premier(e,fils_droit(rat));
      break;

    case CONCAT:
      if(contient_mot_vide(fils_gauche(rat)))
	  trouver_premier(e,fils_droit(rat));
	    
      trouver_premier(e,fils_gauche(rat));
      break;
      
    case STAR:
      trouver_premier(e,fils(rat));
      break;    
    }  
}

Ensemble *premier(Rationnel *rat)
{
  Ensemble * e = creer_ensemble(NULL,NULL,NULL);
  trouver_premier(e, rat);
  return e;
}


void trouver_dernier(Ensemble * e, Rationnel * rat){
  if(!rat)
    return;
  
  switch(get_etiquette(rat))
    {
    case EPSILON:
      break;
      
    case LETTRE:     
      ajouter_element(e,(intptr_t)get_position_min(rat));
      break;
      
    case UNION:
      trouver_dernier(e,fils_droit(rat));
      trouver_dernier(e,fils_gauche(rat));
      break;

    case CONCAT:
      if(contient_mot_vide(fils_droit(rat)))
	  trouver_dernier(e,fils_gauche(rat));
	    
      trouver_dernier(e,fils_droit(rat));
      break;
      
    case STAR:
      trouver_dernier(e,fils(rat));
      break;    
    }  
}

Ensemble *dernier(Rationnel *rat)
{
   Ensemble * e = creer_ensemble(NULL,NULL,NULL);
  trouver_dernier(e, rat);
  return e;
}

void trouver_suivant(Ensemble * e, Rationnel * rat, int positon){
  if(!rat)
    return;
  
  switch(get_etiquette(rat))
    {
    case EPSILON:
      break;
      
    case LETTRE:     
      break;
      
    case UNION:
      break;

    case CONCAT:
      break;
      
    case STAR:
      break;    
    }  
}

Ensemble *suivant(Rationnel *rat, int position)
{
  Ensemble * e = creer_ensemble(NULL,NULL,NULL);
  trouver_suivant(e, rat, position);
  return e; 
}

Automate *Glushkov(Rationnel *rat)
{
   A_FAIRE_RETURN(NULL);
}

bool meme_langage (const char *expr1, const char* expr2)
{
  /*Rationnel *rat1 = expression_to_rationnel(expr1);
  numeroter_rationnel(rat1);
  Automate *auto1 = Glushkov(rat1);
  Automate *auto_deter1 = creer_automate_deterministe(auto1);
  Automate *auto_mini1 =  creer_automate_minimal(auto_deter1);
  rat1 = Arden(auto_mini1);

  Rationnel *rat2 = expression_to_rationnel(expr2);
  numeroter_rationnel(rat2);
  Automate *auto2 = Glushkov(rat2);
  Automate *auto_deter2 = creer_automate_deterministe(auto2);
  Automate *auto_mini2 =  creer_automate_minimal(auto_deter2);
  rat2 = Arden(auto_mini2);
  
  return(rat1 == rat2); // il existe surement une fonction qui pour comparer 2 rat*/
  return false;
}

Systeme systeme(Automate *automate)
{
   A_FAIRE_RETURN(NULL);
}

void print_ligne(Rationnel **ligne, int n)
{
   for (int j = 0; j <=n; j++)
      {
         print_rationnel(ligne[j]);
         if (j<n)
            printf("X%d\t+\t", j);
      }
   printf("\n");
}

void print_systeme(Systeme systeme, int n)
{
   for (int i = 0; i <= n-1; i++)
   {
      printf("X%d\t= ", i);
      print_ligne(systeme[i], n);
   }
}

Rationnel **resoudre_variable_arden(Rationnel **ligne, int numero_variable, int n)
{
   A_FAIRE_RETURN(NULL);
}

Rationnel **substituer_variable(Rationnel **ligne, int numero_variable, Rationnel **valeur_variable, int n)
{
   A_FAIRE_RETURN(NULL);
}

Systeme resoudre_systeme(Systeme systeme, int n)
{
   A_FAIRE_RETURN(NULL);
}

Rationnel *Arden(Automate *automate)
{
   A_FAIRE_RETURN(NULL);
}

