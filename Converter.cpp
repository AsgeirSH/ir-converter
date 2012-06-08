/******************
  Image-converter

	Program for å gjøre om data lagret fra IR-kamera eller annet en-farget kamera til et bilde.

	Skrevet av Asgeir Stavik Hustad.
	Version: 0.5
	Still in development.

*******************/

#ifndef VERSION
	#define VERSION 0.5
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector> // Bruk i stedet for arrays.
using std::vector;
#include "stdlib.h"
#include "conio.h"

using namespace std;

#include "CImg.h"
using namespace cimg_library;

/*** Prototypes ***/
void hello();
float map(float, float, float, float, float);

/*** HOVEDFUNKSJON ***/
int main(int argc, char *argv[]) {
    int width, height, lineNumber, i;
	vector<vector<int> > image;
    string line;
	ifstream reader;
	string input;
	char *filename;
	char *origFilename;
	
	// Print hei-funksjonen
	hello();

	// Sjekk etter argumenter
	if (argc > 1) {
		// Hvis fil er droppet på programmet.
		printf("\x87pner fil %s.\n", argv[1]);
		reader.open(argv[1]);
		origFilename = argv[1];
		 
		if (!reader.is_open()) {
			printf("Error opening file.\n");
			_getch();
			return 1;
		}
	}
	else {
		// Fil
		/*
		printf("Tast inn filbanen til filen: \n");
		scanf("%s", origFilename);
		reader.open(origFilename);
		*/ // TODO: Krasjer her!!
		printf("Dette programmet bruker du ved \x86 dra filen med dataene over filikonet.");
		printf("Les gjerne readme.txt for informasjon om hvordan filen med dataene må se ut.");
		_getch();
		return 0;	
	}

    // Hent bredde på arrayet.
    getline(reader, line);
    width = atoi(line.c_str());

    // Hent høyde til arrayet. (Antall linjer.)
    getline(reader, line);
    height = atoi(line.c_str());
                
    // Initialiser bilde-array.
	image.resize(height);
	for (i = 0; i < height; ++i) {
		image[i].resize(width);
	}

	cout << "Width: " << width << "\nHeight: " << height << ".\n";
                
    /** Begynn å les arrayet. **/
    // Hent linje
	for (lineNumber = 0; lineNumber < height; lineNumber++) {
		// DEBUG:
		//system("PAUSE");
		//cout << "\nLinjenr: " << lineNumber << ".\n\t";
		getline(reader, line);
		// Hent hvert tall på linja.
		int startPos = 0, endPos = 0, number = 0;
		for (i = 0; i < width; i++) {
			endPos = startPos+4;
			number = atoi(line.substr(startPos, endPos).c_str());
			image[lineNumber][i] = number;
			// DEBUG:
			//cout << "\n Teller: " << i << ": " << number << " ";
			//system("PAUSE");

			startPos = startPos+5;
		}
	}

	/*** Lag bilde ***/
	CImg<float> CImage(width, height, 1, 1, 0);

	int x = 0,y = 0;
	printf("Creating image...\n");
	/*cimg_forX(CImage, x) {
		cimg_forY(CImage, y) {
			printf("Y = %d, X = %d\n", y, x);
			printf(" Value: %d, new value: %.2f\n", image[x][y], map(image[x][y], 0, 1024, 0.0, 1.0));
			CImage(x,y,1) = map(image[x][y], 0, 1024, 0.0, 1.0);
		}
	}*/
	/* cimg_for(CImage, ptr, float) {
		*ptr = map(image[x][y], 0, 1400, 0.0, 1.0);
	}*/
	for ( x = 0; x < width; x++) {
		for ( y = 0; y < height; y++) {
			CImage(x,y) = map(image[y][x], 0, 1400, 255,0 ); 
			// Må disse mappes motsatt vei? Høy verdi er jo tross alt lite lys...
		}
	}

	
	printf("\nSaving image\n");
	
	filename = new char[strlen(origFilename+4)];
	strcpy(filename, origFilename);
	strcat(filename, ".bmp");
	CImage.save(filename);
	// Preview image
	printf("Image is saved as %s.\n\n", filename);
	printf("To preview image (with incorrect colors), press p. Otherwise press Enter.\n\n");
	input = _getch();
	if (input.compare("p") == 0) {
		CImage.display("Rendered image");
	}
}

void hello() {

	char headerText[8][51] = { 
		"*********************************************\n",
		"\tImage-converter\n\n",
		"Dette er et program for \x86 gj\x9Bre om data\n",
		"lagret fra IR-kamera eller annet en-farget\n",
		"kamera til et bilde. \n\n",
		"Skrevet av Asgeir Stavik Hustad. \n",
		"Version 0.5\nStill in development.\n",
		"*********************************************\n\n"
	};

	system("cls");
	for (int i = 0; i < 8; i++) {
		printf("%s", headerText[i]);
	}

	return;
}

float map( float x, float in_min, float in_max, float out_min, float out_max) {
	return (x-in_min) *(out_max - out_min) / (in_max - in_min) + out_min;
}