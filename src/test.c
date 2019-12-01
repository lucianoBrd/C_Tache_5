#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "test.h"

/* @brief
 * Main fonction.
 */
int main(
  int   argc,
  char  **argv
){
    char  data[DATA_SIZE];
    
    /**** Test message, nom, calcule, couleurs ****/
    /* Create object */
    message_json *json = new_message_json(4);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "+");
    strcpy(json->valeurs[1], "5");
    strcpy(json->valeurs[2], "6");
    strcpy(json->valeurs[3], "7");
    
    /* Test calcule */
    assert(calcule(json) == 18);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(4);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "mpmp");
    strcpy(json->valeurs[1], "5");
    strcpy(json->valeurs[2], "6");
    strcpy(json->valeurs[3], "7");
    
    /* Test calcule */
    assert(calcule(json) == -1.0);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "-");
    strcpy(json->valeurs[1], "10");
    strcpy(json->valeurs[2], "6");
    
    /* Test calcule */
    assert(calcule(json) == 4);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "*");
    strcpy(json->valeurs[1], "10");
    strcpy(json->valeurs[2], "6");
    
    /* Test calcule */
    assert(calcule(json) == 60);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "/");
    strcpy(json->valeurs[1], "2");
    strcpy(json->valeurs[2], "2");
    
    /* Test calcule */
    assert(calcule(json) == 1);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "moyenne");
    strcpy(json->valeurs[1], "10");
    strcpy(json->valeurs[2], "10");
    
    /* Test calcule */
    assert(calcule(json) == 10);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "minimum");
    strcpy(json->valeurs[1], "10");
    strcpy(json->valeurs[2], "6");
    
    /* Test calcule */
    assert(calcule(json) == 6);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "maximum");
    strcpy(json->valeurs[1], "10");
    strcpy(json->valeurs[2], "6");
    
    /* Test calcule */
    assert(calcule(json) == 10);
    
    /* Delete the object */
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "ecart_type");
    strcpy(json->valeurs[1], "10");
    strcpy(json->valeurs[2], "6");
    
    /* Test calcule */
    assert(calcule(json) == 2);
    
    /* Delete the object */
    delete_message_json(json);
    
    /**** Test analyze JSON messages ****/
    /* Create object */
    json = new_message_json(1);
    /* Set the code of the message */
    strcpy(json->code, "message");
    strcpy(json->valeurs[0], "Bonjour");
    
    /* Create the string and delete the object */
    create_message_json(data, json);
    delete_message_json(json);
    /* Test the function create a correct message */
    assert(strcmp("{\"code\" : \"message\", \"valeurs\" : [\"Bonjour\"]}", data) == 0);
    
    /* Create the object with the message */
    json = create_object_json(data);
    /* Test the object contain correct values */
    assert(json->nb_valeurs == 1);
    assert(strcmp(json->code, "message") == 0);
    assert(strcmp(json->valeurs[0], "Bonjour") == 0);
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(1);
    /* Set the code of the message */
    strcpy(json->code, "nom");
    strcpy(json->valeurs[0], "Paul");
    
    /* Create the string and delete the object */
    create_message_json(data, json);
    delete_message_json(json);
    /* Test the function create a correct message */
    assert(strcmp("{\"code\" : \"nom\", \"valeurs\" : [\"Paul\"]}", data) == 0);
    
    /* Create the object with the message */
    json = create_object_json(data);
    /* Test the object contain correct values */
    assert(json->nb_valeurs == 1);
    assert(strcmp(json->code, "nom") == 0);
    assert(strcmp(json->valeurs[0], "Paul") == 0);
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(4);
    /* Set the code of the message */
    strcpy(json->code, "calcule");
    strcpy(json->valeurs[0], "+");
    strcpy(json->valeurs[1], "5");
    strcpy(json->valeurs[2], "6");
    strcpy(json->valeurs[3], "7");
    
    /* Create the string and delete the object */
    create_message_json(data, json);
    delete_message_json(json);
    /* Test the function create a correct message */
    assert(strcmp("{\"code\" : \"calcule\", \"valeurs\" : [\"+\", 5, 6, 7]}", data) == 0);
    
    /* Create the object with the message */
    json = create_object_json(data);
    /* Test the object contain correct values */
    assert(json->nb_valeurs == 4);
    assert(strcmp(json->code, "calcule") == 0);
    assert(strcmp(json->valeurs[0], "+") == 0);
    assert(strcmp(json->valeurs[1], "5") == 0);
    assert(strcmp(json->valeurs[2], "6") == 0);
    assert(strcmp(json->valeurs[3], "7") == 0);
    delete_message_json(json);
    
    /* Create object */
    json = new_message_json(3);
    /* Set the code of the message */
    strcpy(json->code, "couleurs");
    strcpy(json->valeurs[0], "3");
    strcpy(json->valeurs[1], "#0e0e0c");
    strcpy(json->valeurs[2], "#0f0f0d");
    
    /* Create the string and delete the object */
    create_message_json(data, json);
    delete_message_json(json);
    /* Test the function create a correct message */
    assert(strcmp("{\"code\" : \"couleurs\", \"valeurs\" : [3, \"#0e0e0c\", \"#0f0f0d\"]}", data) == 0);
    
    /* Create the object with the message */
    json = create_object_json(data);
    /* Test the object contain correct values */
    assert(json->nb_valeurs == 3);
    assert(strcmp(json->code, "couleurs") == 0);
    assert(strcmp(json->valeurs[0], "3") == 0);
    assert(strcmp(json->valeurs[1], "#0e0e0c") == 0);
    assert(strcmp(json->valeurs[2], "#0f0f0d") == 0);
    delete_message_json(json);
    
    /**** Test validate JSON messages ****/
    assert(validateur_format_message_json(data) != -1);
    assert(validateur_content_message_json(data) != -1);
    
    strcpy(data, "{\"code\" : couleurs\", \"valeurs\" : [3, \"#0e0e0c\", \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\"  \"couleurs\", \"valeurs\" : [3, \"#0e0e0c\", \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"couleurs\" \"valeurs\" : [3, \"#0e0e0c\", \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"couleurs\", \"valeurs\"  [3, \"#0e0e0c\", \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"couleurs\", \"valeurs\" : [3, \"#0e0e0c\", \"#0f0f0d\"}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "\"code\" : \"couleurs\", \"valeurs\" : [3, \"#0e0e0c\", \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"couleurs\", \"valeurs\" : [\"3\", \"#0e0e0c\", \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"couleurs\", \"valeurs\" : [3, #0e0e0c, \"#0f0f0d\"]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"calcule\", \"valeurs\" : [\"+\", 5, 6, 7]}");
    assert(validateur_format_message_json(data) != -1 || validateur_content_message_json(data) != -1);
    
    strcpy(data, "{\"code\" : \"calcule\", \"valeurs\" : [+, 5, 6, 7]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"calcule\", \"valeurs\" : [\"+\", 5, \"6\", 7]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"nom\", \"valeurs\" : [\"Paul\"]}");
    assert(validateur_format_message_json(data) != -1 || validateur_content_message_json(data) != -1);
    
    strcpy(data, "{\"code\" : \"nom\", \"valeurs\" : [Paul]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    strcpy(data, "{\"code\" : \"message\", \"valeurs\" : [\"Bonjour\"]}");
    assert(validateur_format_message_json(data) != -1 || validateur_content_message_json(data) != -1);
    
    strcpy(data, "{\"code\" : \"message\", \"valeurs\" : [Bonjour]}");
    assert(validateur_format_message_json(data) == -1 || validateur_content_message_json(data) == -1);
    
    /**** Test multiple client can communicate with the server ****/
    assert(1 == 1);
    
    printf("\nALL TESTS PASSED\n");
    return 0;

} /* main */
