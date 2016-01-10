
/*!
 * \file docolav.h
 * \brief Part of docolav.
 * \author Mickaël S.
 * \date 2016.01.10
 */

#pragma once

// Constantes
#define DOCOLAV_VERSION "0.3.3"
#define cimg_verbosity 0  // Non verbeux
#define cimg_display 0    // Désactiver les possibilités d'affichage
#ifndef _WIN32
	#define cimg_no_system_calls 1
#endif

// La bibliothèque
#include <cstdint>
#include <string>
#include <iostream>
#include "./CImg.h"

// Prototypes
void help();
void usage();
void version();
