#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <random>
#include <cmath> 
using namespace std;


struct tgaFile {
	struct Header {

		//part 1 of the .tga file, the stuff before the chunk of pixel data
		char idLength = 0;
		char colorMapType = 0;
		char dataTypeCode = 0;
		short colorMapOrigin = 0;
		short colorMapLength = 0;
		char colorMapDepth = 0;
		short xOrigin = 0;
		short yOrigin = 0;
		short width = 0;
		short height = 0;
		char bitsPerPixel = 0;
		char imageDescriptor = 0;


	};

	struct Image {
		struct Pixel {

			unsigned char blueData = 0;
			unsigned char greenData = 0;
			unsigned char redData = 0;

		};
		unsigned int amountOfPixels = 0;

		//part 2 of the .tga file, the chunk of pixel data that is the visual picture 
		vector<Pixel> allPixelsInImg;
		Pixel pixel;
	};

	Header header;
	Image image;


};

//Functions for loading and writing images 
void loadHeader(ifstream& file, tgaFile::Header& header);
void loadImage(ifstream& file, tgaFile::Header& header, tgaFile::Image& image);
tgaFile loadtgaFile(const string& pathname);

void writeHeader(ofstream& file, tgaFile::Header& header);
void writeImage(ofstream& file, tgaFile::Image& image);
void writetgaFile(const string& pathname,  tgaFile& filename);


//Ramping Up Activities
void allPixelsRed(const string& pathname, tgaFile& filename);
uint8_t randomNumber(mt19937& gen);
void randomColors(const string& pathname, tgaFile& filename, mt19937& gen);
void createnewFile(const string& pathname, tgaFile& filename);


//Functions to complete Tasks 

tgaFile multiply(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname);


tgaFile subtract(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname);


tgaFile screen(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname);


tgaFile overlay(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname);


tgaFile increaseGreen(tgaFile& topLayerFile, const string& pathname);


tgaFile multiChannelTransform(tgaFile& topLayerFile, const string& pathname);


vector<tgaFile> separateColorLoad(const string& pathname);


tgaFile combinedLayers(const tgaFile& blueLayer, const tgaFile& greenLayer, const tgaFile& redLayer, const string& baseFilename);


tgaFile rotate180deg(const tgaFile& original, const string& baseFilename);


//Functions for Testing
bool areHeadersIdentical(const tgaFile::Header& header1, const tgaFile::Header& header2);

bool areImagesIdentical(const tgaFile::Image& image1, const tgaFile::Image& image2);

bool areFilesIdentical(const string& filePath1, const string& filePath2);