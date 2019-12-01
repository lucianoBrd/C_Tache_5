#ifndef __VALIDATEUR_H__
#define __VALIDATEUR_H__

#include "json.h"

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

#endif
