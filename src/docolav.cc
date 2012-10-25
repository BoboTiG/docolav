
/* =============================================================== */
/*  $Author: BoboTiG <bobotig@gmail.com> $                         */
/*  $Id: docolav $                                                 */
/*  $Revision: 4 $, $Date: 2012/10/25 $                            */
/*  $Source: http://www.bobotig.fr $, $Date: 2012/01/31 $          */
/*                                                                 */
/*  docolav détermine la couleur moyenne dominante d'une image.    */
/* =============================================================== */


#include "docolav.h"
using namespace cimg_library;


// C'est parti mon kiki !
int main(int argc, char *argv[]) {
	unsigned int width = 0, height = 0, total = 0;
	size_t r = 0, g = 0, b = 0;
	char filename[MAX_FILENAME_LEN], format[MAX_FORMAT_LEN];
	
	if ( argv[1] ) {
		if ( ! strncmp(argv[1], "-h", 2) || ! strncmp(argv[1], "--help", 6) ) {
			help();
			return 0;
		} else if ( ! strncmp(argv[1], "-v", 2) || ! strncmp(argv[1], "--version", 9) ) {
			version();
			return 0;
		} else {
			if ( argv[2] ) {
				strncpy(format, argv[1], MAX_FORMAT_LEN);
				strncpy(filename, argv[2], MAX_FILENAME_LEN);
			} else {
				usage();
				return 1;
			}
		}
	} else {
		usage();
		return 0;
	}
	
	// Chargement de l'image et récupérations des infos
	try {
		CImg<unsigned char> picture(filename);
		width = picture.width();
		height = picture.height();
		// Récupération des pixels
		if ( picture.spectrum() == 1 ) {
			cimg_forXY ( picture, x, y ) {
				unsigned char *t = picture.data(x, y, 0, 0);
				r += t[0];
				g += t[1];
				b += t[2];
			}
		} else {
			cimg_forXY ( picture, x, y ) {
				r += picture(x, y, 0, 0);
				g += picture(x, y, 0, 1);
				b += picture(x, y, 0, 2);
			}
		}
	} catch ( CImgIOException &e ) {
		printf("Impossible de charger l'image : %s\n", filename);
		return 1;
	}
	// This is it !
	total = width * height;
	r /= total;
	g /= total;
	b /= total;
	printf(format, r, g, b);
	return 0;
}

void help() {
	printf("Copyright (C) 2012 by BoboTiG.\n\
\n\
docolav comes with ABSOLUTELY NO WARRANTY.\n\
This is free software, and you are welcome to redistribute it under\n\
certain conditions. See the GNU General Public Licence for details.\n\
\n\
docolav détermine la couleur moyenne dominante d'une image.\n\
\n\
Usage : docolav FORMAT FICHIER\n\
\n\
Où FORMAT est une chaîne de caractères passée à printf().\n\
3 arguments sont valables, dans l'ordre : R, G puis B.\n\
\n\
Voici quelques exemples :\n\
	docolav \"R=%%d G=%%d B=%%d\" image.jpg\n\
	docolav \"HEX(%%02X,%%02X,%%02X)\" image.jpg\n\
\n\
Options :\n\
 -h,  --help      affiche ce message\n\
 -v,  --version   affiche les versions du programme et de CImg\n\
\n\
Contact : bobotig (@) gmail (.) com\n");
}

void usage() {
	printf("Usage : docolav FORMAT FICHIER\n");
}

void version() {
	printf("docolav v%s\n", DOCOLAV_VERSION);
	printf(" CImg.h v%d.%d.%d\n",
		(cimg_version / 100), (cimg_version % 100 / 10), (cimg_version % 10));
}
