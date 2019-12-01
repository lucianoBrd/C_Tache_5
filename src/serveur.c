#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "serveur.h"

/* @brief
 * Affiche les couleurs sous forme de graphique.
 *
 * @params
 * client_socket_fd : Socket du client.
 * json : Objet contenant les couleurs.
 *
 * @return
 * EXIT_FAILURE en cas d'erreur.
 */
int plot(
  int 	       client_socket_fd,
  message_json *json
){
  //Extraire le compteur et les couleurs RGB
  FILE          *p  = popen("gnuplot -persist", "w"),
                *fp = fopen("save.txt", "a+");
  int           i   = 0,
                data_size,
		n   = json->nb_valeurs - 1;
  char          save[DATA_SIZE],
                *tmp;
  message_json  *json_save;

  /* Set parameters */
  fprintf(p, "set xrange [-15:15]\n");
  fprintf(p, "set yrange [-15:15]\n");
  fprintf(p, "set style fill transparent solid 0.9 noborder\n");
  fprintf(p, "set title 'Top %d colors'\n", n);
  fprintf(p, "plot '-' with circles lc rgbcolor variable\n");

  for(i; i < n; i++){
      tmp = json->valeurs[i];
      tmp++;

      /* Print the color and compute his position (with a cercle of 360°) */
      fprintf(p, "0 0 10 %lf %lf 0x%s\n", (float)(i)*(float)(360/(float)n), (float)(i + 1)*(float)(360/(float)n), tmp);

      /* Put the color into the file */
      fputs(json->valeurs[i], fp);
      fputs("\n", fp);

  } /* Foreach colors */

  fprintf(p, "e\n");
  pclose(p);
  fclose(fp);

  /* New object to create a message to return to the client */
  json_save = new_message_json(1);

  strcpy(json_save->code, "couleurs");
  strcpy(json_save->valeurs[0], "Couleurs_enregistrées");

  create_message_json(save, json_save);
  delete_message_json(json_save);
  
  /* Test the message */
  if(validateur_format_message_json(save) == -1 || validateur_content_message_json(save) == -1){
    printf("Message à envoyer incorrect.\n");
    return 0;
      
  }

  data_size = write(client_socket_fd, (void *) save, strlen(save));

  if(data_size < 0){
    perror("erreur ecriture");
    return(EXIT_FAILURE);

  } /* Error write */

} /* plot */

/* @brief
 * Renvoie un message JSON au client.
 *
 * @params
 * client_socket_fd : Socket du client.
 * json : Objet contenant le message.
 *
 * @return
 * EXIT_FAILURE en cas d'erreur.
 */
int renvoie_message(
  int           client_socket_fd,
  message_json  *json
){
  char  data[DATA_SIZE];
  int   data_size;

  /* Create a message to return to the client */
  create_message_json(data, json);
  
  /* Test the message */
  if(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1){
    printf("Message à envoyer incorrect.\n");
    return 0;
      
  }
  
  data_size = write(client_socket_fd, (void *) data, strlen(data));

  if(data_size < 0){
    perror("erreur ecriture");
    return(EXIT_FAILURE);

  } /* Error write */

} /* renvoie_message */

/* @brief
 * Renvoie un message JSON avec le nom du client.
 *
 * @params
 * client_socket_fd : Socket du client.
 * data : String contenant le message JSON.
 *
 * @return
 * EXIT_FAILURE en cas d'erreur.
 */
int renvoie_nom_client(
  int 	client_socket_fd,
  char 	*data
){
  /* Test the message */
  if(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1){
    printf("Message à envoyer incorrect.\n");
    return 0;
      
  }
  
  int data_size = write (client_socket_fd, (void *) data, strlen(data));

  if(data_size < 0){
    perror("erreur ecriture");
    return(EXIT_FAILURE);

  } /* Error write */

} /* renvoie_nom_client */

/* @brief
 * Renvoie le resultat du calcule au client.
 *
 * @params
 * client_socket_fd : Socket du client.
 * json : Objet contenant les nombres et l'opérande du calcule.
 *
 * @return
 * EXIT_FAILURE en cas d'erreur.
 */
int recois_numero_calcule(
  int 	       client_socket_fd,
  message_json *json
){
  int 	        data_size,
		i 	      = 1;
  char 	        *operation    = json->valeurs[0],
                save[DATA_SIZE];
  float         result        = 0.0;
  message_json  *json_save;

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

  /* New object to create a message to return to the client */
  json_save = new_message_json(1);
  strcpy(json_save->code, "calcule");

  if (  strstr(json->valeurs[1], ".") 	!= NULL ||
        strstr(json->valeurs[2], ".") 	!= NULL ||
        strcmp(operation, "/")  	== 0.0  ||
	strcmp(operation, "moyenne")  	== 0.0  ||
	strcmp(operation, "ecart_type") == 0.0  ){
    /* Number float */
    printf("Le resultat du %s vaut %.2f\n", json->code, result);
    sprintf(json_save->valeurs[0], "%.2f", result);

  } else {
    /* Number int */
    printf("Le resultat du %s vaut %d\n", json->code, (int)result);
    sprintf(json_save->valeurs[0], "%d", (int)result);

  }

  create_message_json(save, json_save);
  delete_message_json(json_save);
  
  /* Test the message */
  if(validateur_format_message_json(save) == -1 || validateur_content_message_json(save) == -1){
    printf("Message à envoyer incorrect.\n");
    return 0;
      
  }

  data_size = write (client_socket_fd, (void *) save, strlen(save));

  if(data_size < 0){
    perror("erreur ecriture");
    return(EXIT_FAILURE);

  } /* Error write */

} /* recois_numero_calcule */

 /* @brief
  * Accepter la nouvelle connection d'un client et lire les données
  * envoyées par le client. En suite, le serveur envoie un message
  * en retour.
  *
  * @params
  * socketfd : Socket du client.
  *
  * @return
  * 0 si tout va bien ou -1 en cas d'erreur.
  */
int recois_envoie_message(
  int socketfd
){
  struct sockaddr_in client_addr;

  char          data[DATA_SIZE];
  int           client_addr_len = sizeof(client_addr),
                client_socket_fd,
                data_size;
  message_json  *json;

  /* New connection of the client */
  client_socket_fd = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
  if(client_socket_fd < 0 ){
    perror("accept");
    return(EXIT_FAILURE);

  } /* Error accept */

  memset(data, 0, sizeof(data));

  /* Read client data */
  data_size = read(client_socket_fd, (void *) data, sizeof(data));

  if(data_size < 0){
    perror("erreur lecture");
    return(EXIT_FAILURE);

  } /* Error read */
  
  /* Test the message */
  if(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1){
    printf("Message recu incorrect.\n");
    return 0;
      
  }

  /* Print the message of the client */
  printf("Message recu :\n");
  json = create_object_json(data);
  print_message_json(json);

  if(strcmp(json->code, "message") == 0){
    /* Case code 'message' */

    /* Ask the user what message he wants to return to the client */
    message_json *json_return = new_message_json(1);
    printf("Votre message (max 100 caracteres): ");
    fgets(json_return->valeurs[0], VALEURS_SIZE, stdin);

    strcpy(json_return->code, "message");

    renvoie_message(client_socket_fd, json_return);

  } else if(strcmp(json->code, "nom") == 0){
    /* Case code 'nom' */
    renvoie_nom_client(client_socket_fd, data);

  } else if(strcmp(json->code, "calcule") == 0){
    /* Case code 'calcule' */
    recois_numero_calcule(client_socket_fd, json);

  } else if(strcmp(json->code, "couleurs") == 0){
    /* Case code 'couleurs' */
    /* Plot the image */
    plot(client_socket_fd, json);

  }
  delete_message_json(json);

  /* Close the socket */
  close(socketfd);

} /* recois_envoie_message */

/* @brief
 * Main fonction.
 */
int main(){

  int socketfd,
      bind_status,
      client_addr_len,
      option = 1;

  struct sockaddr_in server_addr, client_addr;

  /* Create the socket */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if(socketfd < 0){
    perror("Unable to open a socket");
    return -1;

  }

  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  /* Put parameters */
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind_status = bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if(bind_status < 0){
    perror("bind");
    return(EXIT_FAILURE);

  } /* Error bind */

  listen(socketfd, 10);
  recois_envoie_message(socketfd);

  return 0;

} /* main */
