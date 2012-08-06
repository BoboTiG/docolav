
/* =============================================================== */
/*  $Author: BoboTiG <bobotig@gmail.com> $                         */
/*  $Id: docolav $                                                 */
/*  $Revision: 2 $, $Date: 2012/08/06 $                            */
/*  $Source: http://www.bobotig.fr $, $Date: 2012/01/31 $          */
/*                                                                 */
/*  docolav détermine la couleur moyenne dominante d'une image.    */
/* =============================================================== */


#include <cstdio>
#include <iostream>
#include <string>
#include <opencv/highgui.h>
using namespace std;


// Constantes
#define VERSION "0.2"


// Prototypes
void help();
void usage();
void version();


// C'est parti mon kiki !
int main(int argc, char *argv[]) {
	IplImage* picture = 0;
	unsigned int of = 0, height = 0, width = 0, total = 0;
	unsigned int r = 0, g = 0, b = 0;
	string arg1 = "", img = "", format = "rgb";
	
	if ( argc < 2 ) {
		usage();
		return EXIT_FAILURE;
	}
	arg1 = argv[1];
	if ( arg1 == "-h" || arg1 == "--help" ) {
		help();
		return EXIT_SUCCESS;
	} else if ( arg1 == "-v" || arg1 == "--version" ) {
		version();
		return EXIT_SUCCESS;
	} else if ( arg1 == "-of" || arg1 == "--output-format" ) {
		of = 1;
		if ( argc != 4 ) {
			usage();
			return EXIT_FAILURE;
		}
		format = argv[2];
		if ( format != "rgb" && format != "hex" && format != "html" ) {
			cout << "Formats disponibles : rgb, hex et html." << endl;
			return EXIT_FAILURE;
		}
		img = argv[3];
	} else {
		img = arg1;
	}
	
	// Chargement de l'image
	picture = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	if ( ! picture ) {
		cout << "Impossible de charger l'image : " << img << endl;
		return EXIT_FAILURE;
	}
	
	// Affichage de la bête
	/*cvNamedWindow("une_fentere");
	cvShowImage("une_fentere", picture);
	cvWaitKey();
	cvDestroyWindow("une_fentere");
	return 0;
	//*/
	
	// Récupération des tous les pixels
	height = picture->height;
	width  = picture->width;
	for ( unsigned int x = 0; x < width; ++x ) {
		for ( unsigned int y = 0; y < height; ++y ) {
			uchar* ptr = cvPtr2D(picture, y, x, NULL);
			r += (int) ptr[2];
			g += (int) ptr[1];
			b += (int) ptr[0];
			++total;
		}
	}
	cvReleaseImage(&picture);
	r /= total;
	g /= total;
	b /= total;
	
	// This is it !
	if ( of ) {
		if      ( format == "rgb" ) printf("RGB(%d,%d,%d)", r, g, b);
		else if ( format == "hex" ) printf("HEX(%02X,%02X,%02X)", r, g, b);
		else                        printf("#%02X%02X%02X", r, g, b);
	} else {
		cout << "Fichier    : " << img << endl;
		cout << "Dimensions : " << width << " * " << height << " px" << endl;
		cout << "Couleur moyenne dominante" << endl;
		printf("    RGB(%d,%d,%d)\n", r, g, b);
		printf("    HEX(%02X,%02X,%02X)\n", r, g, b);
		printf("    #%02X%02X%02X\n", r, g, b);
	}
	return EXIT_SUCCESS;
}


void help() {
	cout << "Copyright (C) 2012 by BoboTiG.\n\
\n\
docolav comes with ABSOLUTELY NO WARRANTY.\n\
This is free software, and you are welcome to redistribute it under \n\
certain conditions. See the GNU General Public Licence for details.\n\
\n\
docolav détermine la couleur moyenne dominante d'une image.\n\
\n\
Usage : docolav [OPTION [VALEUR]] FICHIER\n\
\n\
Options :\n\
 -h,  --help		affiche ce message\n\
 -of, --output-format	format de sortie : rgb, hex ou html\n\
 -v,  --version		affiche les versions du programme et d'OpenCV\n\
\n\
Rapporter erreurs, suggestions et commentaires à <bobotig@gmail.com>." << endl;
}


void usage() {
	cout << "Usage : docolav [OPTION [VALEUR]] FICHIER" << endl;
}


void version() {
	cout << "docolav v" << VERSION << "." << endl;
	cout << "OpenCV v" << CV_VERSION << "." << endl;
}
