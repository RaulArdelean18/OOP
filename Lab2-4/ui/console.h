#ifndef OOP_CONSOLE_H
#define OOP_CONSOLE_H

#include "../service/service.h"

/**
 * Tip de date care modeleaza consola aplicatiei
 *
 * campuri:
 * - srv: pointer catre service-ul aplicatiei
 */
typedef struct {
    Service *srv;
} Console;

/**
 * Initializeaza consola cu service-ul dat
 *
 * param ui: pointer la consola care va fi initializata
 * param srv: pointer la service-ul folosit de consola
 */
void init_console(Console *ui, Service *srv);

/**
 * Porneste meniul aplicatiei
 *
 * param ui: pointer la consola
 */
void run(Console *ui);

#endif
