#include "extrafile.h"
#include <fstream>
#include <climits>
#include <random>
#include <algorithm>
#include <cmath> 
using namespace std;

void loadHeader(ifstream& file, tgaFile::Header& header) { //give it a Header object to populate
	
	//Char
	file.read(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
	file.read(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
	file.read(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));

	//Shorts
	file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
	file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));

	//Char
	file.read(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));

	//Shorts
	file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
	file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
	file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
	file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));

	//Char
	file.read(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
	file.read(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));
}

void loadImage(ifstream& file, tgaFile::Header& header, tgaFile::Image& image) { //given a header AND image object populate the pixel information
	

	//Set amount of pixels from the Image object
	image.amountOfPixels = header.width * header.height;

	//Read the pixel data
	image.allPixelsInImg.reserve(image.amountOfPixels); // Reserve space for efficiency

	for (unsigned int i = 0; i < (image.amountOfPixels); i++) {


		//Start assigning the data to the pixelObject
		file.read(reinterpret_cast<char*>(&image.pixel.blueData), sizeof(image.pixel.blueData));
		file.read(reinterpret_cast<char*>(&image.pixel.greenData), sizeof(image.pixel.greenData));
		file.read(reinterpret_cast<char*>(&image.pixel.redData), sizeof(image.pixel.redData));

		//Send the current object to a vector of pixels
		image.allPixelsInImg.push_back(image.pixel);


	}
}


tgaFile loadtgaFile(const string& pathname) { //load a newly created tgaFile object with information read from the path. Return this object
	tgaFile newFile;
	ifstream file(pathname, ios::binary);

	loadHeader(file, newFile.header); //load the header of the tgaFile
	loadImage(file, newFile.header, newFile.image); //load the Image of the tgaFile

	file.close();
	return newFile;

}


void writeHeader(ofstream& file, tgaFile::Header& header) {
	//write the header

	//Char
	file.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
	file.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
	file.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));

	//Shorts
	file.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
	file.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));

	//Char
	file.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));

	//Shorts
	file.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
	file.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
	file.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
	file.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));

	//Char
	file.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
	file.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));


}

void writeImage(ofstream& file, tgaFile::Image& image) {

	//write the image data
	for (auto& pixel : image.allPixelsInImg) {
		file.write(reinterpret_cast<char*>(&pixel.blueData), sizeof(pixel.blueData));
		file.write(reinterpret_cast<char*>(&pixel.greenData), sizeof(pixel.greenData));
		file.write(reinterpret_cast<char*>(&pixel.redData), sizeof(pixel.redData));

	}


}


void writetgaFile(const string& pathname, tgaFile& filename)
{
	ofstream file(pathname, ios::binary);
	writeHeader(file, filename.header);
	writeImage(file, filename.image);

	file.close();
}



void allPixelsRed(const string& pathname, tgaFile& filename)
{

	
	for (auto& pixel : filename.image.allPixelsInImg) { //maxes out red pixels while minimizing the blue and green. Does this for every pixel
		pixel.blueData = 0;
		pixel.greenData = 0;
		pixel.redData = 255;

	}


	writetgaFile(pathname,filename);
	

}

uint8_t randomNumber(mt19937& gen) {
	uniform_int_distribution<> dis(0, 255);
	return static_cast<uint8_t>(dis(gen));
}

void randomColors(const string& pathname, tgaFile& filename, mt19937 &gen) {

	for (auto& pixel : filename.image.allPixelsInImg) { //randomizes the pixel color intensity on each channel for every pixel.
		pixel.blueData = randomNumber(gen);
		pixel.greenData = randomNumber(gen);
		pixel.redData = randomNumber(gen);

	}

	writetgaFile(pathname, filename);

}

void createnewFile(const string& pathname, tgaFile& filename){
	
	for (auto& pixel : filename.image.allPixelsInImg) { //changes every pixel to black
		pixel.blueData = 0;
		pixel.greenData = 0;
		pixel.redData = 0;

	}

	writetgaFile(pathname, filename);

}

//Task 1 


tgaFile multiply(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname) {
	
	//initialize the TGA file structure, especially the header.
	tgaFile tempFile = loadtgaFile(pathname);

	//Iterate through each pixel in the images.
	for (size_t i = 0; i < topLayerFile.image.amountOfPixels; i++) { //we use topLayerFile for formality,bottomLayerFile could also be used since both are same dimension
		//Refers to the current pixel of each image(top layer, bottom layer, and temp file).This avoids unecessary copying by doing referencing
		auto& topPixel = topLayerFile.image.allPixelsInImg[i];
		auto& bottomPixel = bottomLayerFile.image.allPixelsInImg[i];
		auto& tempPixel = tempFile.image.allPixelsInImg[i];

		//Perform multiplication using rounding and min. Casting ensures that the data matches what we're using to store it in the struct (unsigned char)
		tempPixel.blueData = static_cast<unsigned char>(round(min(255.0, (topPixel.blueData / 255.0) * (bottomPixel.blueData / 255.0) * 255.0)));
		tempPixel.greenData = static_cast<unsigned char>(round(min(255.0, (topPixel.greenData / 255.0) * (bottomPixel.greenData / 255.0) * 255.0)));
		tempPixel.redData = static_cast<unsigned char>(round(min(255.0, (topPixel.redData / 255.0) * (bottomPixel.redData / 255.0) * 255.0)));
	}

	return tempFile;
}



tgaFile subtract(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname)
{
	tgaFile tempFile = loadtgaFile(pathname);
	for (size_t i = 0; i < topLayerFile.image.amountOfPixels; i++) {
		auto& topPixel = topLayerFile.image.allPixelsInImg[i];
		auto& bottomPixel = bottomLayerFile.image.allPixelsInImg[i];
		auto& tempPixel = tempFile.image.allPixelsInImg[i];


		//Perform the subtraction and clamp the result to the range [0, 255]
		tempPixel.blueData = max(0, bottomPixel.blueData - topPixel.blueData);
		tempPixel.greenData = max(0,  bottomPixel.greenData - topPixel.greenData);
		tempPixel.redData = max(0,  bottomPixel.redData - topPixel.redData);

	}


	return tempFile;
}


tgaFile screen(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname) {
	tgaFile tempFile = loadtgaFile(pathname);
	for (size_t i = 0; i < topLayerFile.image.amountOfPixels; i++) {
		auto& topPixel = topLayerFile.image.allPixelsInImg[i];
		auto& bottomPixel = bottomLayerFile.image.allPixelsInImg[i];
		auto& tempPixel = tempFile.image.allPixelsInImg[i];

		//Normalize color values to [0, 1], perform the screen operation, and then scale back to [0, 255]
		//Using round for rounding
		tempPixel.blueData = static_cast<unsigned char>(round(255.0 * (1.0 - (1.0 - topPixel.blueData / 255.0) * (1.0 - bottomPixel.blueData / 255.0))));
		tempPixel.greenData = static_cast<unsigned char>(round(255.0 * (1.0 - (1.0 - topPixel.greenData / 255.0) * (1.0 - bottomPixel.greenData / 255.0))));
		tempPixel.redData = static_cast<unsigned char>(round(255.0 * (1.0 - (1.0 - topPixel.redData / 255.0) * (1.0 - bottomPixel.redData / 255.0))));
	}

	return tempFile;
}


tgaFile overlay(tgaFile& topLayerFile, tgaFile& bottomLayerFile, const string& pathname) {
	tgaFile tempFile = loadtgaFile(pathname);
	for (size_t i = 0; i < topLayerFile.image.amountOfPixels; i++) {
		auto& topPixel = topLayerFile.image.allPixelsInImg[i];
		auto& bottomPixel = bottomLayerFile.image.allPixelsInImg[i];
		auto& tempPixel = tempFile.image.allPixelsInImg[i];

		//Normalize color values to [0, 1]
		double topBlue = topPixel.blueData / 255.0;
		double topGreen = topPixel.greenData / 255.0;
		double topRed = topPixel.redData / 255.0;
		double bottomBlue = bottomPixel.blueData / 255.0;
		double bottomGreen = bottomPixel.greenData / 255.0;
		double bottomRed = bottomPixel.redData / 255.0;

		//Apply overlay blend mode for blue channel
		if (bottomBlue < 0.5) {
			tempPixel.blueData = static_cast<unsigned char>(round(2 * topBlue * bottomBlue * 255.0));
		}
		else {
			tempPixel.blueData = static_cast<unsigned char>(round(255.0 * (1 - 2 * (1 - topBlue) * (1 - bottomBlue))));
		}

		//Apply overlay blend mode for green channel
		if (bottomGreen < 0.5) {
			tempPixel.greenData = static_cast<unsigned char>(round(2 * topGreen * bottomGreen * 255.0));
		}
		else {
			tempPixel.greenData = static_cast<unsigned char>(round(255.0 * (1 - 2 * (1 - topGreen) * (1 - bottomGreen))));
		}

		//Apply overlay blend mode for red channel
		if (bottomRed < 0.5) {
			tempPixel.redData = static_cast<unsigned char>(round(2 * topRed * bottomRed * 255.0));
		}
		else {
			tempPixel.redData = static_cast<unsigned char>(round(255.0 * (1 - 2 * (1 - topRed) * (1 - bottomRed))));
		}

	}//end of for loop

	return tempFile;
}


tgaFile increaseGreen(tgaFile& topLayerFile, const string& pathname) {
	tgaFile tempFile = loadtgaFile(pathname);
	for (size_t i = 0; i < topLayerFile.image.amountOfPixels; i++) {
		auto& pixel = topLayerFile.image.allPixelsInImg[i];
		auto& tempPixel = tempFile.image.allPixelsInImg[i];

		//Calculate new green value
		int newGreen = pixel.greenData + 200;
		//Clamp the green value to the range [0, 255] and assign to tempPixel
		if (newGreen > 255) {
			tempPixel.greenData = 255;
		}
		else {
			tempPixel.greenData = newGreen;
		}

		//Copy the red and blue values from the original pixel to tempPixel
		tempPixel.redData = pixel.redData;
		tempPixel.blueData = pixel.blueData;
	}

	return tempFile;
}



tgaFile multiChannelTransform(tgaFile& topLayerFile, const string& pathname) {
	tgaFile tempFile = loadtgaFile(pathname);
	for (size_t i = 0; i < topLayerFile.image.amountOfPixels; i++) {
		auto& pixel = topLayerFile.image.allPixelsInImg[i];
		auto& tempPixel = tempFile.image.allPixelsInImg[i];

		//Scale the red channel by 4 and clamp to the range [0, 255]
		int newRed = pixel.redData * 4;
		if (newRed > 255) {
			tempPixel.redData = 255;
		}
		else {
			tempPixel.redData = newRed;
		}

		//Set the blue channel to 0
		tempPixel.blueData = 0;

		//Keep the green channel as it is
		tempPixel.greenData = pixel.greenData;
	}

	return tempFile;
}


vector<tgaFile> separateColorLoad(const string& pathname) {
	tgaFile originalFile = loadtgaFile(pathname);
	vector<tgaFile> separateColorVector; //allows us to deliver multiple channels with one output
	//Create 3 new tgaFile objects for red, green, and blue channels
	tgaFile redChannelFile = originalFile;
	tgaFile greenChannelFile = originalFile;
	tgaFile blueChannelFile = originalFile;

	for (size_t i = 0; i < originalFile.image.amountOfPixels; i++) {
		auto& pixel = originalFile.image.allPixelsInImg[i];


		//For the blue channel file, set red and green the blue data info [blue,blue,blue]
		blueChannelFile.image.allPixelsInImg[i].redData = blueChannelFile.image.allPixelsInImg[i].blueData;
		blueChannelFile.image.allPixelsInImg[i].greenData = blueChannelFile.image.allPixelsInImg[i].blueData;
		

		//For the green channel file, set red and blue to the green data info [green,green,green]
		greenChannelFile.image.allPixelsInImg[i].redData = greenChannelFile.image.allPixelsInImg[i].greenData;
		greenChannelFile.image.allPixelsInImg[i].blueData = greenChannelFile.image.allPixelsInImg[i].greenData;
		

		//For the red channel file, set green and blue to the red data info [red,red,red]
		redChannelFile.image.allPixelsInImg[i].greenData = redChannelFile.image.allPixelsInImg[i].redData;
		redChannelFile.image.allPixelsInImg[i].blueData = redChannelFile.image.allPixelsInImg[i].redData;
		

		
	}

	//Send the completed channels to the vector for delivery
	separateColorVector.push_back(blueChannelFile);
	separateColorVector.push_back(greenChannelFile);
	separateColorVector.push_back(redChannelFile);

	return separateColorVector;
}


tgaFile combinedLayers(const tgaFile& blueLayer, const tgaFile& greenLayer, const tgaFile& redLayer, const string& baseFilename) {
	//Using the blue layer's structure as the base for the combined image (could be any of them as long as all dimensions are same)
	tgaFile combinedImage = loadtgaFile(baseFilename);

	for (size_t i = 0; i < combinedImage.image.amountOfPixels; i++) {
		//Send only the blue data in the blueLayer channel to the blue data in the combined image and so on for the other colors
		combinedImage.image.allPixelsInImg[i].blueData = blueLayer.image.allPixelsInImg[i].blueData;
		combinedImage.image.allPixelsInImg[i].greenData = greenLayer.image.allPixelsInImg[i].greenData;
		combinedImage.image.allPixelsInImg[i].redData = redLayer.image.allPixelsInImg[i].redData;
	}

	return combinedImage;
}

tgaFile rotate180deg(const tgaFile& original, const string& baseFilename) {
	tgaFile rotatedImage = loadtgaFile(baseFilename); 

	//Reverse the order of the pixels
	reverse(rotatedImage.image.allPixelsInImg.begin(), rotatedImage.image.allPixelsInImg.end());

	return rotatedImage;
}




//Testing 
bool areHeadersIdentical(const tgaFile::Header& header1, const tgaFile::Header& header2) {
	
	//Assume they are equal
	bool identical = true;


	//Sequence of tests to check if they are not equal
	if (header1.idLength != header2.idLength) {
		cout << "idLength differs: " << static_cast<int>(header1.idLength) << " vs " << static_cast<int>(header2.idLength) << endl;
		identical = false;
	}
	if (header1.colorMapType != header2.colorMapType) {
		cout << "colorMapType differs: " << static_cast<int>(header1.colorMapType) << " vs " << static_cast<int>(header2.colorMapType) << endl;
		identical = false;
	}
	if (header1.dataTypeCode != header2.dataTypeCode) {
		cout << "dataTypeCode differs: " << static_cast<int>(header1.dataTypeCode) << " vs " << static_cast<int>(header2.dataTypeCode) << endl;
		identical = false;
	}
	if (header1.colorMapOrigin != header2.colorMapOrigin) {
		cout << "colorMapOrigin differs: " << header1.colorMapOrigin << " vs " << header2.colorMapOrigin << endl;
		identical = false;
	}
	if (header1.colorMapLength != header2.colorMapLength) {
		cout << "colorMapLength differs: " << header1.colorMapLength << " vs " << header2.colorMapLength << endl;
		identical = false;
	}
	if (header1.colorMapDepth != header2.colorMapDepth) {
		cout << "colorMapDepth differs: " << static_cast<int>(header1.colorMapDepth) << " vs " << static_cast<int>(header2.colorMapDepth) << endl;
		identical = false;
	}
	if (header1.xOrigin != header2.xOrigin) {
		cout << "xOrigin differs: " << header1.xOrigin << " vs " << header2.xOrigin << endl;
		identical = false;
	}
	if (header1.yOrigin != header2.yOrigin) {
		cout << "yOrigin differs: " << header1.yOrigin << " vs " << header2.yOrigin << endl;
		identical = false;
	}
	if (header1.width != header2.width) {
		cout << "width differs: " << header1.width << " vs " << header2.width << endl;
		identical = false;
	}
	if (header1.height != header2.height) {
		cout << "height differs: " << header1.height << " vs " << header2.height << endl;
		identical = false;
	}
	if (header1.bitsPerPixel != header2.bitsPerPixel) {
		cout << "bitsPerPixel differs: " << static_cast<int>(header1.bitsPerPixel) << " vs " << static_cast<int>(header2.bitsPerPixel) << endl;
		identical = false;
	}
	if (header1.imageDescriptor != header2.imageDescriptor) {
		cout << "imageDescriptor differs: " << static_cast<int>(header1.imageDescriptor) << " vs " << static_cast<int>(header2.imageDescriptor) << endl;
		identical = false;
	}

	return identical;
}



bool areImagesIdentical(const tgaFile::Image& image1, const tgaFile::Image& image2) {
	
	//Note: Images are equal if they have the same count of pixels and all pixels are the same. Additionally they must be ordered the same but we don't need to check that since theyre ordered in the vector and visual inspection

	//Check they have the same pixel count before continuing (in case if they have all the same pixels but maybe one doesn't have enough equal pixels)
	if (image1.amountOfPixels != image2.amountOfPixels) {
		cout << "Image sizes differ: " << image1.amountOfPixels << " vs " << image2.amountOfPixels << endl;
		return false;
	}

	//iterate through each pixel in the both images
	for (size_t i = 0; i < image1.amountOfPixels; i++) {
		const auto& pixel1 = image1.allPixelsInImg[i];
		const auto& pixel2 = image2.allPixelsInImg[i];

		//If either blue, green, or red data are mismatching then the pixels are not identical. They all must be equal.
		if (pixel1.blueData != pixel2.blueData ||
			pixel1.greenData != pixel2.greenData ||
			pixel1.redData != pixel2.redData) {

			//Describes the details of where and which pixels were differing
			cout << "Pixel difference found at index " << i << ": "
				<< "Pixel1 (BGR) = (" << static_cast<int>(pixel1.blueData) << ", "
				<< static_cast<int>(pixel1.greenData) << ", "
				<< static_cast<int>(pixel1.redData) << ") vs "
				<< "Pixel2 (BGR) = (" << static_cast<int>(pixel2.blueData) << ", "
				<< static_cast<int>(pixel2.greenData) << ", "
				<< static_cast<int>(pixel2.redData) << ")" << endl;

			return false;
		}
	}

	//If no difference was detected through our checks, return true
	return true;
}


bool areFilesIdentical(const string& filePath1, const string& filePath2) {
	tgaFile file1 = loadtgaFile(filePath1);
	tgaFile file2 = loadtgaFile(filePath2);

	return areHeadersIdentical(file1.header, file2.header) && areImagesIdentical(file1.image, file2.image);
}

