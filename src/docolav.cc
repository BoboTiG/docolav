
/* =============================================================== */
/*  $Author: BoboTiG <bobotig@gmail.com> $                         */
/*  $Id: docolav $                                                 */
/*  $Revision: 3 $, $Date: 2012/10/24 $                            */
/*  $Source: http://www.bobotig.fr $, $Date: 2012/01/31 $          */
/*                                                                 */
/*  docolav détermine la couleur moyenne dominante d'une image.    */
/* =============================================================== */


#include "docolav.h"
using namespace cimg_library;


// C'est parti mon kiki !
int main(int argc, char *argv[]) {
	unsigned int width = 0, height = 0, of = 0;
	size_t r = 0, g = 0, b = 0, total = 0;
	char filename[512], format[4];
	
	if ( argc < 2 ) {
		usage();
		return 1;
	}
	if ( ! strncmp(argv[1], "-h", 2) || ! strncmp(argv[1], "--help", 6) ) {
		help();
		return 0;
	} else if ( ! strncmp(argv[1], "-v", 2) || ! strncmp(argv[1], "--version", 9) ) {
		version();
		return 0;
	} else if ( ! strncmp(argv[1], "-of", 3) || ! strncmp(argv[1], "--output-format", 16) ) {
		of = 1;
		if ( argc != 4 ) {
			usage();
			return 1;
		}
		strncpy(format, argv[2], 4);
		if (   strncmp(format, "dim", 3) && strncmp(format, "rgb", 3) 
			&& strncmp(format, "hex", 3) && strncmp(format, "html", 4) ) {
			printf("Formats disponibles : dim, rgb, hex et html.\n");
			return 1;
		}
		strncpy(filename, argv[3], 512);
	} else {
		strncpy(filename, argv[1], 512);
	}
	
	// Chargement de l'image et récupérations des infos
	try {
		CImg<unsigned char> picture(filename);
		width = picture.width();
		height = picture.height();
		// Ça ne sert à rien de continuer si on veut seulement les dimensions
		if ( of &&  ! strncmp(format, "dim", 3) ) {
			printf("%dx%d", width, height);
			return 0;
		}
		// Récupération des pixels
		if ( picture.spectrum() == 1 ) {
			cimg_forXY ( picture, x, y ) {
				unsigned char *t = picture.data(x, y, 0, 0);
				//printf("R=%02d G=%02d B=%02d\n", t[0],t[1],t[2]);
				r += t[0];
				g += t[1];
				b += t[2];
			}
		} else {
			cimg_forXY ( picture, x, y ) {
				//printf("R=%02d G=%02d B=%02d\n", picture(x, y, 0, 0),picture(x, y, 0, 1),picture(x, y, 0, 2));
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
	if ( of ) {
		if ( ! strncmp(format, "rgb", 3) ) {
			printf("RGB(%d,%d,%d)", r, g, b);
		} else if ( ! strncmp(format, "hex", 3) ) {
			printf("HEX(%02X,%02X,%02X)", r, g, b);
		} else {
			printf("#%02X%02X%02X", r, g, b);
		}
	} else {
		printf("Fichier    : %s\n", filename);
		printf("Dimensions : %d * %d px\n", width, height);
		printf("Couleur moyenne dominante\n");
		printf("  RGB(%d,%d,%d)\n", r, g, b);
		printf("  HEX(%02X,%02X,%02X)\n", r, g, b);
		printf("  #%02X%02X%02X\n", r, g, b);
	}
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
Usage : docolav [OPTION [VALEUR]] FICHIER\n\
\n\
Options :\n\
 -h,  --help          affiche ce message\n\
 -of, --output-format format de sortie : dim, rgb, hex ou html\n\
 -v,  --version       affiche les versions du programme et de CImg\n\
\n\
Contact : bobotig (@) gmail (.) com\n");
}

void usage() {
	printf("Usage : docolav [OPTION [VALEUR]] FICHIER\n");
}

void version() {
	printf("docolav v%s\n", DOCOLAV_VERSION);
	printf("I'm using the CImg library v%d.%d.%d\n",
		(cimg_version / 100), (cimg_version % 100 / 10), (cimg_version % 10));
}
