#ifndef __TAXO_H__
#define __TAXO_H__

#include "json.h"

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
);

#endif
