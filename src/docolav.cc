
/* =============================================================== */
/*  $Author: BoboTiG <bobotig@gmail.com> $                         */
/*  $Id: docolav $                                                 */
/*  $Revision: 9 $, $Date: 2013/03/11 $                            */
/*  $Source: http://www.bobotig.fr $, $Date: 2012/01/31 $          */
/*                                                                 */
/*  docolav détermine la couleur moyenne dominante d'une image.    */
/* =============================================================== */


#include "./docolav.h"
using namespace cimg_library;


// C'est parti mon kiki !
int main(int argc, char *argv[]) {
	unsigned int width = 0, height = 0, total = 0;
	size_t r = 0, g = 0, b = 0;
	char filename[MAX_FILENAME_LEN + 1], format[MAX_FORMAT_LEN + 1];

	// Traitement des arguments
	if ( !argv[1] ) {
		usage();
		return 0;
	}
	if ( !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") ) {
		help();
		return 0;
	} else if ( !strcmp(argv[1], "-v") || !strcmp(argv[1], "--version") ) {
		version();
		return 0;
	}
	if ( !argv[2] ) {
		usage();
		return 0;
	}
	strncpy(format, argv[1], MAX_FORMAT_LEN);
	format[MAX_FORMAT_LEN] = 0;
	strncpy(filename, argv[2], MAX_FILENAME_LEN);
	filename[MAX_FILENAME_LEN] = 0;
	
	// Chargement de l'image et récupération des infos
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
		fprintf(stderr, "Impossible de charger l'image : %s\n", filename);
		fprintf(stderr, "%s\n", e.what());
		return 1;
	}
	// This is it!
	total = width * height;
	r /= total;
	g /= total;
	b /= total;
	printf(format, r, g, b);
	return 0;
}

void help() {
	printf("Tous droits (C) 2012-2013 par BoboTiG.\n\
\n\
docolav est livré avec ABSOLUMENT AUCUNE GARANTIE.\n\
C'est un programme libre, et vous pouvez le redistribuer sous certaines\n\
conditions. Voir la GNU General Public Licence pour plus de détails.\n\
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
	printf("docolav %s\n", DOCOLAV_VERSION);
	printf(" CImg.h %d.%d.%d\n",
		(cimg_version / 100), (cimg_version % 100 / 10), (cimg_version % 10));
}
