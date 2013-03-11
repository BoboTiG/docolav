
/*!
 * \file docolav.h
 * \brief Part of docolav.
 * \author BoboTiG
 * \date 2013.03.11
 */

#ifndef DOCOLAV_H_
#define DOCOLAV_H_


// Constantes
#define DOCOLAV_VERSION      "0.3.2"
#define MAX_FILENAME_LEN     256
#define MAX_FORMAT_LEN       32
#define cimg_verbosity       0  // Non verbeux
#define cimg_display         0  // Désactiver les possibilités d'affichage
#ifndef _WIN32
	#define cimg_no_system_calls 1
#endif

// La bibliothèque
#include "./CImg.h"

// Prototypes
void help();
void usage();
void version();


#endif  // DOCOLAV_H_
