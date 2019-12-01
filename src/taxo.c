#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "taxo.h"

/* @brief
 * Renvoie le resultat du calcule.
 *
 * @params
 * json : Objet contenant les nombres et l'opérande du calcule.
 *
 * @return
 * Resultat du calcule ou -1 en cas d'erreur.
 */
float calcule(
  message_json *json
){
  int           i 	        = 1;
  char 	        *operation  = json->valeurs[0];
  float         result      = 0.0;

  if(strcmp(operation, "+") == 0.0){
    /* Case + */
    for(i; i < json->nb_valeurs; i++){
      result += atof(json->valeurs[i]);
      
    } /* For each number */

  } else if(strcmp(operation, "-") == 0.0){
    /* Case - */
    result = atof(json->valeurs[1]);
    for(i = 2; i < json->nb_valeurs; i++){
      result -= atof(json->valeurs[i]);
      
    } /* For each number */

  } else if(strcmp(operation, "*") == 0.0){
    /* Case * */
    result = 1;
    for(i; i < json->nb_valeurs; i++){
      result *= atof(json->valeurs[i]);
      
    } /* For each number */

  } else if(strcmp(operation, "/") == 0.0){
    /* Case / */
    result = atof(json->valeurs[1]);
    for(i = 2; i < json->nb_valeurs; i++){
      result /= atof(json->valeurs[i]);
      
    } /* For each number */

  } else if(strcmp(operation, "moyenne") == 0.0){
    /* Case moyenne */
    for(i; i < json->nb_valeurs; i++){
      result += atof(json->valeurs[i]);
      
    } /* For each number */
    result = result / (json->nb_valeurs - 1);

  } else if(strcmp(operation, "minimum") == 0.0){
    /* Case minimum */
    result = atof(json->valeurs[1]);
    for(i; i < json->nb_valeurs; i++){
      if(result > atof(json->valeurs[i]))
	result = atof(json->valeurs[i]);
      
    } /* For each number */

  } else if(strcmp(operation, "maximum") == 0.0){
    /* Case maximum */
    result = atof(json->valeurs[1]);
    for(i; i < json->nb_valeurs; i++){
      if(result < atof(json->valeurs[i]))
	result = atof(json->valeurs[i]);
      
    } /* For each number */

  } else if(strcmp(operation, "ecart_type") == 0.0){
     /* Case moyenne */
     float moy = 0.0;
    for(i; i < json->nb_valeurs; i++){
      moy += atof(json->valeurs[i]);
      
    } /* For each number */
    moy = moy / (json->nb_valeurs - 1);
    
    for(i = 1; i < json->nb_valeurs; i++){
      result += pow(atof(json->valeurs[i]) - moy, 2);
      
    } /* For each number */
    
    result = sqrt(result / (json->nb_valeurs - 1));

  } else {
    /* Case error */
    result = -1.0;

  }
  return result;


} /* calcule */
