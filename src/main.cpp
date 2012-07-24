
/* =============================================================== */
/*	$Author: BoboTiG <bobotig@gmail.com> $                         */
/*	$Id: docolav $                                                 */
/*	$Revision: 1 $, $Date: 2012/02/06 $                            */
/*	$Source: http://www.bobotig.fr $, $Date: 2012/01/31 $          */
/*                                                                 */
/*	docolav is a tool to get the dominant color average of a pic.  */
/* =============================================================== */


#include <cstdio>
#include <iostream>
#include <string>
#include <opencv/highgui.h>
using namespace std;


// Constantes
#define VERSION "0.1"


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
	} else if ( arg1 == "-v" || arg1 == "--version" ) {
		version();
	} else if ( arg1 == "-of" || arg1 == "--output-format" ) {
		of = 1;
		if ( argc != 4 ) {
			usage();
			return EXIT_FAILURE;
		}
		format = argv[2];
		if ( format != "rgb" && format != "hex" && format != "html" ) {
			cout << "Available ofrmats are rgb, hex and html." << endl;
			return EXIT_FAILURE;
		}
		img = argv[3];
	} else {
		img = arg1;
	}
	
	// Load the picture and get its informations
	picture = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	if ( ! picture ) {
		cout << "Could not load picture file: " << img << endl;
		return EXIT_FAILURE;
	}
	
	// Affichage de la bête
	/*cvNamedWindow("une_window");
	cvShowImage("une_window", picture);
	cvWaitKey();
	cvDestroyWindow("une_window");
	return 0;
	//*/
	
	// Get all pixels values
	height = picture->height;
	width  = picture->width;
	for ( unsigned int x = 0; x < width; ++x) {
		for ( unsigned int y = 0; y < height; ++y) {
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
		cout << "File      : " << img << endl;
		cout << "Dimensions: " << width << " * " << height << " px" << endl;
		cout << "Dominant color average" << endl;
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
docolav is a tool to get the dominant color average of a picture.\n\
\n\
Usage : docolav [OPTION [VALUE]] FILE\n\
\n\
Options :\n\
 -h,  --help			display this message\n\
 -of, --output-format	output format: rgb, hex or html\n\
 -v,  --version			print tools version\n\
\n\
Report bugs, suggestions and comments to <bobotig@gmail.com>." << endl;
}


void usage() {
	cout << "Usage : docolav [OPTION [VALUE]] FILE" << endl;
}


void version() {
	cout << "docolav v" << VERSION << "." << endl;
	cout << "OpenCV library v" << CV_VERSION << "." << endl;
}
