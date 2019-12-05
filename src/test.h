#ifndef __TEST_H__
#define __TEST_H__

#include "bmp.h"
#include "couleur.h"
#include "json.h"
#include "validateur.h"
#include "taxo.h"

 /* @brief
  * Termine un processus de PID.
  *
  * @params
  * pid : PID du processus a arreter.
  */
void kill_pid(
    int pid
);

#endif
