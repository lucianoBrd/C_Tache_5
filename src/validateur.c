#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validateur.h"

/* @brief
 * Vérifie le contenu d'un message.
 * Si le message contient le bon nombre et format de donnée
 * en fonction de son code. Comme par exemple si le code vaut 
 * calcule, le message doit contenir 3 valeurs dont la première 
 * au format string et les deux autres doivent être des nombres
 * corrects.
 * Il est préférable d'éxécuter validateur_format_message_json
 * avant cette fonction car cette fonction ne vérifie pas la forme
 * globale du message (nombre paire de guillemets...).
 * Cette fonction suppose donc que le format global du message est correct.
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * 0 si tout va bien ou -1 en cas d'erreur.
 */
int validateur_content_message_json(
  char *message
){
  message_json *json;
  
  json = create_object_json(message);
  
  if(	strcmp(json->code, "message")  	!= 0 &&
    	strcmp(json->code, "nom") 	!= 0 &&
    	strcmp(json->code, "calcule")  	!= 0 &&
    	strcmp(json->code, "couleurs") 	!= 0 ){
    delete_message_json(json);
    return -1;

  } /* Check if code is correct */
  
  if( strcmp(json->code, "message") == 0 ||
      strcmp(json->code, "nom")     == 0 ){
    if(json->nb_valeurs != 1){
      delete_message_json(json);
      return -1;
      
    }
    if(validateur_string_content_message_json(message) == -1){
        delete_message_json(json);
        return -1;
      
    }
  } /* Message or name case */
  
  if(strcmp(json->code, "calcule") == 0){
    if(json->nb_valeurs < 1){
      delete_message_json(json);
      return -1;
      
    }
    if(json->nb_valeurs > 2){
      int i = 1;
      for(i; i < json->nb_valeurs; i++){
	if(atof(json->valeurs[1]) == 0.0){
	  delete_message_json(json);
	  return -1;
	  
	}
	
      } /* For each number */
      if(validateur_calcule_content_message_json(message) == -1){
	  delete_message_json(json);
	  return -1;
	
      }
    }
    
  } /* Calcule case */
  
  if(strcmp(json->code, "couleurs") == 0){
    if(json->nb_valeurs < 1){
      delete_message_json(json);
      return -1;
      
    }
    if(json->nb_valeurs > 2){
      if(atof(json->valeurs[0]) == 0.0){
	delete_message_json(json);
	return -1;
	
      }
      if(validateur_couleurs_content_message_json(message) == -1){
	  delete_message_json(json);
	  return -1;
	
      }
    }
    
  } /* Couleurs case */
  
  delete_message_json(json);
  return 0;
  
} /* validateur_content_message_json */

/* @brief
 * Vérifie le format global d'un message.
 * Vérifie si le message commence bien par { et se termine
 * par }... En somme, cette fonction vérifie que le message
 * répond aux norme global de format.
 * Il est préférable d'éxécuter cette fonction avant
 * validateur_content_message_json car cette fonction vérifie la forme
 * globale du message (nombre paire de guillemets...).
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * 0 si tout va bien ou -1 en cas d'erreur.
 */
int validateur_format_message_json(
  char *message
){
  int 	i = 0;
  
  if(validateur_guille_format_message_json(message) < 0){
    return -1;
    
  } /* Test there are good number of guillemets */
  
  if(validateur_accolades_format_message_json(message) < 0){
    return -1;
    
  } /* Test there are the accolades */  
  
  /* Test there is the "code" */
  i = validateur_code_format_message_json(message, i);
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is : after "code" */
  i = validateur_char_format_message_json(message, i, ':');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is " after "code" : */
  i = validateur_char_format_message_json(message, i, '"');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is " after "code" : "string */
  i = validateur_char_after_format_message_json(message, i, '"');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is , after "code" : "string" */
  i = validateur_char_format_message_json(message, i, ',');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is the valeurs */
  i = validateur_valeurs_format_message_json(message, i);
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is : after "valeurs" */
  i = validateur_char_format_message_json(message, i, ':');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is [ after "valeurs" : */
  i = validateur_char_format_message_json(message, i, '[');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is ] after "valeurs" : [... */
  if(validateur_char_after_format_message_json(message, i, ']') < 0){
    return -1;
    
  }
  
    
  return 0;
  
} /* validateur_format_message_json */

/* @brief
 * Vérifie qu'il y a un nombre paire de guillemets.
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * Position après ce que l'on vérifie si tout va bien ou -1 en cas d'erreur.
 */
int validateur_guille_format_message_json(
  char *message
){
  int i = 0,
      count = 0;
  /* Count number of " */
  while(message[i] != '\0'){
    if(message[i] == '"'){
      count++;
    
    }
    i++;
  }
  
  if(count%2 != 0){
    return -1;
    
  }
  return i;
  
} /* validateur_guille_format_message_json */

/* @brief
 * Vérifie que le message commence par
 * une accolade et se termine par une 
 * accolade.
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * Position après ce que l'on vérifie si tout va bien ou -1 en cas d'erreur.
 */
int validateur_accolades_format_message_json(
  char *message
){
  char 	accolade_first = ' ', 
	accolade_last;
  int 	accolade_first_c = 0,
	i = 0;
  /* Test there are the accolades */
  while(message[i] != '\0'){
    if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if(accolade_first_c == 0){
	accolade_first = message[i];
	accolade_first_c = 1;
      }
      accolade_last = message[i];
    
    }
    i++;
  }
  
  if(accolade_first != '{' || accolade_last != '}'){
    return -1;
    
  }
  return i;
  
} /* validateur_accolades_format_message_json */

/* @brief
 * Vérifie que le message contient "code" au bon emplacement.
 *
 * @params
 * message : Message JSON à vérifier.
 * i : Position de démarage.
 *
 * @return
 * Position après ce que l'on vérifie si tout va bien ou -1 en cas d'erreur.
 */
int validateur_code_format_message_json(
  char 	*message,
  int	i
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] != '{' && message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if( i > 4				&&
	  message[i]     == 'e' 	&&
	  message[i - 1] == 'd' 	&&
	  message[i - 2] == 'o' 	&&
	  message[i - 3] == 'c' 	&&
	  message[i + 1] == '"' 	&&
	  message[i - 4] == '"' 	){
	valid = 0;
	break;
	
      }
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i = i + 2;
  return i;
  
} /* validateur_code_format_message_json */

/* @brief
 * Vérifie que le message contient un charactere au bon emplacement.
 *
 * @params
 * message : Message JSON à vérifier.
 * i : Position de démarage.
 * char_test : Charactere à vérifier.
 *
 * @return
 * Position après ce que l'on vérifie si tout va bien ou -1 en cas d'erreur.
 */
int validateur_char_format_message_json(
  char 	*message,
  int	i,
  char 	char_test
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if(message[i] == char_test){
        valid = 0;
        break;
	
      } else {
        break;
	
      }
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i++;
  return i;
  
} /* validateur_char_format_message_json */

/* @brief
 * Vérifie que le message contient "valeurs" au bon emplacement.
 *
 * @params
 * message : Message JSON à vérifier.
 * i : Position de démarage.
 *
 * @return
 * Position après ce que l'on vérifie si tout va bien ou -1 en cas d'erreur.
 */
int validateur_valeurs_format_message_json(
  char 	*message,
  int	i
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if(   i > 7 			&&
            message[i]     == 's' 	&&
            message[i - 1] == 'r' 	&&
            message[i - 2] == 'u' 	&&
            message[i - 3] == 'e' 	&&
            message[i - 4] == 'l' 	&&
            message[i - 5] == 'a' 	&&
            message[i - 6] == 'v' 	&&
            message[i + 1] == '"' 	&&
            message[i - 7] == '"' 	){
        valid = 0;
        break;
	
      }
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i = i + 2;
  return i;
  
} /* validateur_valeurs_format_message_json */

/* @brief
 * Vérifie que le message contient un charactere 
 * juste après i (ne prend pas en compte les espaces, retour à la ligne...).
 *
 * @params
 * message : Message JSON à vérifier.
 * i : Position de démarage.
 * char_test : Charactere à vérifier.
 *
 * @return
 * Position après ce que l'on vérifie si tout va bien ou -1 en cas d'erreur.
 */
int validateur_char_after_format_message_json(
  char 	*message,
  int	i,
  char	char_test
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] == char_test){
      valid = 0;
      break;
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i++;
  return i;
  
} /* validateur_char_after_format_message_json */

/* @brief
 * Vérifie que le message contient un string comme valeur.
 * Utile pour vérifier un message dont le code vaut nom ou 
 * message.
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * 0 si tout va bien ou -1 en cas d'erreur.
 */
int validateur_string_content_message_json(
  char 	*message
){
  int i = 0;
    while(message[i] != '\0'){
        if( i > 7 			&&
            message[i]     == 's' 	&&
            message[i - 1] == 'r' 	&&
            message[i - 2] == 'u' 	&&
            message[i - 3] == 'e' 	&&
            message[i - 4] == 'l' 	&&
            message[i - 5] == 'a' 	&&
            message[i - 6] == 'v' 	&&
            message[i + 1] == '"' 	&&
            message[i - 7] == '"' 	){
            break;
        
        }
      
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] == ':'){
            break;
            
        }
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] == '['){
            i++;
            break;
            
        }
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
            break;
            
        }
        i++;
    }
    if(message[i] != '"')
        return -1;
    
    return 0;
  
} /* validateur_string_content_message_json */

/* @brief
 * Vérifie que le message contient un string comme première valeur
 * puis deux nombres.
 * Utile pour vérifier un message dont le code vaut calcule.
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * 0 si tout va bien ou -1 en cas d'erreur.
 */
int validateur_calcule_content_message_json(
  char 	*message
){
  int i = 0;
    while(message[i] != '\0'){
        if( i > 7 			&&
            message[i]     == 's' 	&&
            message[i - 1] == 'r' 	&&
            message[i - 2] == 'u' 	&&
            message[i - 3] == 'e' 	&&
            message[i - 4] == 'l' 	&&
            message[i - 5] == 'a' 	&&
            message[i - 6] == 'v' 	&&
            message[i + 1] == '"' 	&&
            message[i - 7] == '"' 	){
            break;
        
        }
      
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] == ':'){
            break;
            
        }
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] == '['){
            i++;
            break;
            
        }
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
            break;
            
        }
        i++;
    }
    if(message[i] != '"')
        return -1;
    while(message[i] != '\0'){
        if(message[i] == ','){
            i++;
            while(message[i] != '\0'){
                if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
                    if(message[i] == '"')
                        return -1;
                    else 
                        break;
                    
                }
                i++;
            }
            
        }
        i++;
    }
    
    return 0;
  
} /* validateur_calcule_content_message_json */

/* @brief
 * Vérifie que le message contient un nombre comme première valeur
 * puis un string pour toutes les autres valeurs.
 * Utile pour vérifier un message dont le code vaut couleurs.
 *
 * @params
 * message : Message JSON à vérifier.
 *
 * @return
 * 0 si tout va bien ou -1 en cas d'erreur.
 */
int validateur_couleurs_content_message_json(
  char 	*message
){
  int i = 0;
    while(message[i] != '\0'){
        if( i > 7 			&&
            message[i]     == 's' 	&&
            message[i - 1] == 'r' 	&&
            message[i - 2] == 'u' 	&&
            message[i - 3] == 'e' 	&&
            message[i - 4] == 'l' 	&&
            message[i - 5] == 'a' 	&&
            message[i - 6] == 'v' 	&&
            message[i + 1] == '"' 	&&
            message[i - 7] == '"' 	){
            break;
        
        }
      
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] == ':'){
            break;
            
        }
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] == '['){
            i++;
            break;
            
        }
        i++;
    }
    while(message[i] != '\0'){
        if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
            break;
            
        }
        i++;
    }
    if(message[i] == '"')
        return -1;
    while(message[i] != '\0'){
        if(message[i] == ','){
            i++;
            while(message[i] != '\0'){
                if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
                    if(message[i] != '"')
                        return -1;
                    else 
                        break;
                    
                }
                i++;
            }
            
        }
        i++;
    }
    
    return 0;
  
} /* validateur_couleurs_content_message_json */
