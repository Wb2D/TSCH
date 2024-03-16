#ifndef GLOBAL_H
#define GLOBAL_H

#include "ErrorTracker/errortracker.h"




/*!
 * \details Единица трансляции, используемая для предотвращения множественного
 * использования глобальных переменных.
*/

extern ErrorTracker G_ERROR;


#endif // GLOBAL_H
