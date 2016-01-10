
/* =============================================================== */
/*  $Author: Mickaël S. <mickael@jmsinfo.co> $                     */
/*  $Id: docolav $                                                 */
/*  $Revision: 11 $, $Date: 2016/01/10 $                           */
/*  $Source: http://jmsinfo.co $, $Date: 2012/01/31 $              */
/*                                                                 */
/*  docolav détermine la couleur moyenne dominante d'une image.    */
/* =============================================================== */


#include "./docolav.h"
using namespace cimg_library;


// C'est parti mon kiki !
int main(int argc, char *argv[]) {
	// Traitement des arguments
	if ( !argv[1] ) {
		usage();
		return 0;
	}
	std::string format = argv[1];
	if ( format == "-h" || format == "--help" ) {
		help();
		return 0;
	} else if ( format == "-v" || format == "--version" ) {
		version();
		return 0;
	}
	if ( !argv[2] ) {
		usage();
		return 0;
	}
	std::string filename = argv[2];

	// Chargement de l'image et récupération des infos
	try {
		CImg<uint8_t> picture(filename.c_str());
		// Récupération des pixels
		uintptr_t r = 0, g = 0, b = 0;
		if ( picture.spectrum() == 1 ) {
			cimg_forXY ( picture, x, y ) {
				uint8_t *t = picture.data(x, y, 0, 0);
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
		// This is it!
		uintptr_t total = picture.width() * picture.height();
		r /= total;
		g /= total;
		b /= total;
		printf(format.c_str(), r, g, b);
		return 0;
	} catch ( CImgIOException &e ) {
		std::cerr << "Impossible de charger l'image : " << filename << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

void help() {
	std::cout <<
	"docolav détermine la couleur moyenne dominante d'une image.\n\n"
	"Usage : docolav FORMAT FICHIER\n\n"
	"FORMAT est une chaîne de caractères passée à printf().\n"
	"3 arguments sont valables, dans l'ordre : R, G puis B.\n\n"
	"Options :\n"
	" -h,  --help      affiche ce message\n"
	" -v,  --version   affiche les versions du programme et de CImg\n\n"
	"Exemples :\n"
	"$ docolav 'R=%d G=%d B=%d' image.jpg\n"
	"R=25 G=52 B=77\n\n"
	"$ docolav 'HEX(%02X,%02X,%02X)' image.png\n"
	"HEX(19,34,4D)\n";
}

void usage() {
	std::cout << "Usage : docolav FORMAT FICHIER" << std::endl;
}

void version() {
	std::cout << "docolav " << DOCOLAV_VERSION << "\n   "
	cimg_appname << " " << cimg_version/100 << "." << (cimg_version/10)%10 << "." << cimg_version%10 << "\n\n"
	"Copyright (C) 2012-2016 by Mickaël S.\n"
	"docolav comes with ABSOLUTELY NO WARRANTY.\n"
	"This is free software, and you are welcome to redistribute it under\n"
	"certain conditions. See the GNU General Public Licence for details.\n\n"
	"Écrit par Mickaël S. <mickael@jmsinfo.co>.\n";
}
