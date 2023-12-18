#include <iostream>
#include "extrafile.h"
#include <random>
#include <cmath> 
using namespace std;

int main()
{
    // Initialize the random number generator
    random_device rd;
    mt19937 gen(rd());

    // Paths
    string layer1_pathname = R"(./input/layer1.tga)";
    string pattern1_pathname = R"(./input/pattern1.tga)";
    string layer2_pathname = R"(./input/layer2.tga)";
    string car_pathname = R"(./input/car.tga)";
    string pattern2_pathname = R"(./input/pattern2.tga)";
    string text_pathname = R"(./input/text.tga)";
    string circles_pathname = R"(./input/circles.tga)";

    string layer_blue_pathname = R"(./input/layer_blue.tga)";
    string layer_green_pathname = R"(./input/layer_green.tga)";
    string layer_red_pathname = R"(./input/layer_red.tga)";
    string text2_pathname = R"(./input/text2.tga)";

    string output_pathname = R"(./output/)";

    cout << "entering task 1" << endl;
    // Task 1
    tgaFile layer1 = loadtgaFile(layer1_pathname); //top layer
    tgaFile pattern1 = loadtgaFile(pattern1_pathname); //bottom layer

    tgaFile multiplyFile = multiply(layer1, pattern1, layer1_pathname);//takes in layer1 and pattern1 and returns a file. Uses layer1 as a base for the header and image data
    writetgaFile(output_pathname + "part1.tga", multiplyFile);

    cout << "entering task 2" << endl;
    // Task 2
    tgaFile layer2 = loadtgaFile(layer2_pathname);
    tgaFile car = loadtgaFile(car_pathname);

    tgaFile subtractFile = subtract(layer2, car, layer2_pathname); //takes in the layers
    writetgaFile(output_pathname + "part2.tga", subtractFile);

    cout << "entering task 3" << endl;
    // Task 3
    tgaFile pattern2 = loadtgaFile(pattern2_pathname);
    tgaFile text = loadtgaFile(text_pathname);

    tgaFile multiplyFile2 = multiply(layer1, pattern2, layer1_pathname); //takes in the layers
    tgaFile screenFile = screen(text, multiplyFile2, text_pathname);
    writetgaFile(output_pathname + "part3.tga", screenFile);

    cout << "entering task 4" << endl;
    // Task 4
    tgaFile circles = loadtgaFile(circles_pathname);
    tgaFile multiplyFile3 = multiply(layer2, circles, layer2_pathname);
    tgaFile subtractfile2 = subtract(pattern2, multiplyFile3, pattern2_pathname);
    writetgaFile(output_pathname + "part4.tga", subtractfile2);

    cout << "entering task 5" << endl;
    // Task 5
    tgaFile overlayFile = overlay(layer1, pattern1, layer1_pathname);
    writetgaFile(output_pathname + "part5.tga", overlayFile);

    cout << "entering task 6" << endl;
    // Task 6
    tgaFile increaseGreenFile = increaseGreen(car, car_pathname);
    writetgaFile(output_pathname + "part6.tga", increaseGreenFile);

    cout << "entering task 7" << endl;
    // Task 7 
    tgaFile multiChannelTransformFile = multiChannelTransform(car, car_pathname);
    writetgaFile(output_pathname + "part7.tga", multiChannelTransformFile);

    cout << "entering task 8" << endl;
    // Task 8
    vector<tgaFile> colorChannels = separateColorLoad(car_pathname);
    string channelNames[3] = { "b", "g","r" };

    for (int i = 0; i < colorChannels.size(); i++) {
        string filename = output_pathname + "part8_" + channelNames[i] + ".tga";
        writetgaFile(filename, colorChannels[i]);
    }

    cout << "entering task 9" << endl;
    // Task 9
    tgaFile layer_blue = loadtgaFile(layer_blue_pathname);
    tgaFile layer_green = loadtgaFile(layer_green_pathname);
    tgaFile layer_red = loadtgaFile(layer_red_pathname);

    tgaFile combinedLayersFile = combinedLayers(layer_blue, layer_green, layer_red, layer_blue_pathname);
    writetgaFile(output_pathname + "part9.tga", combinedLayersFile);

    cout << "entering task 10" << endl << endl;
    // Task 10
    tgaFile text2 = loadtgaFile(text2_pathname);

    tgaFile text2File = rotate180deg(text2, text2_pathname);
    writetgaFile(output_pathname + "part10.tga", text2File);

    // File check 1
    cout << "Test Check 1 " << endl;
    string outputFilePath_part1 = R"(./output/part1.tga)";
    string exampleFilePath_EXAMPLE_part1 = R"(./examples/EXAMPLE_part1.tga)";

    if (areFilesIdentical(outputFilePath_part1, exampleFilePath_EXAMPLE_part1)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile = loadtgaFile(outputFilePath_part1);
        tgaFile exampleFile = loadtgaFile(exampleFilePath_EXAMPLE_part1);

        if (areHeadersIdentical(outputFile.header, exampleFile.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile.image, exampleFile.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    // File check 2
    cout << "Test Check 2 " << endl;
    string outputFilePath_part2 = R"(./output/part2.tga)";
    string exampleFilePath_EXAMPLE_part2 = R"(./examples/EXAMPLE_part2.tga)";

    if (areFilesIdentical(outputFilePath_part2, exampleFilePath_EXAMPLE_part2)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile2 = loadtgaFile(outputFilePath_part2);
        tgaFile exampleFile2 = loadtgaFile(exampleFilePath_EXAMPLE_part2);

        if (areHeadersIdentical(outputFile2.header, exampleFile2.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile2.image, exampleFile2.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    // File check 3
    cout << "Test Check 3 " << endl;
    string outputFilePath_part3 = R"(./output/part3.tga)";
    string exampleFilePath_EXAMPLE_part3 = R"(./examples/EXAMPLE_part3.tga)";

    if (areFilesIdentical(outputFilePath_part3, exampleFilePath_EXAMPLE_part3)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile3 = loadtgaFile(outputFilePath_part3);
        tgaFile exampleFile3 = loadtgaFile(exampleFilePath_EXAMPLE_part3);

        if (areHeadersIdentical(outputFile3.header, exampleFile3.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile3.image, exampleFile3.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 4
    cout << "Test Check 4 " << endl;
    string outputFilePath_part4 = R"(./output/part4.tga)";
    string exampleFilePath_EXAMPLE_part4 = R"(./examples/EXAMPLE_part4.tga)";

    if (areFilesIdentical(outputFilePath_part4, exampleFilePath_EXAMPLE_part4)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile4 = loadtgaFile(outputFilePath_part4);
        tgaFile exampleFile4 = loadtgaFile(exampleFilePath_EXAMPLE_part4);

        if (areHeadersIdentical(outputFile4.header, exampleFile4.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile4.image, exampleFile4.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 5
    cout << "Test Check 5 " << endl;
    string outputFilePath_part5 = R"(./output/part5.tga)";
    string exampleFilePath_EXAMPLE_part5 = R"(./examples/EXAMPLE_part5.tga)";

    if (areFilesIdentical(outputFilePath_part5, exampleFilePath_EXAMPLE_part5)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile5 = loadtgaFile(outputFilePath_part5);
        tgaFile exampleFile5 = loadtgaFile(exampleFilePath_EXAMPLE_part5);

        if (areHeadersIdentical(outputFile5.header, exampleFile5.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile5.image, exampleFile5.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 6
    cout << "Test Check 6 " << endl;
    string outputFilePath_part6 = R"(./output/part6.tga)";
    string exampleFilePath_EXAMPLE_part6 = R"(./examples/EXAMPLE_part6.tga)";

    if (areFilesIdentical(outputFilePath_part6, exampleFilePath_EXAMPLE_part6)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile6 = loadtgaFile(outputFilePath_part6);
        tgaFile exampleFile6 = loadtgaFile(exampleFilePath_EXAMPLE_part6);

        if (areHeadersIdentical(outputFile6.header, exampleFile6.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile6.image, exampleFile6.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 7
    cout << "Test Check 7 " << endl;
    string outputFilePath_part7 = R"(./output/part7.tga)";
    string exampleFilePath_EXAMPLE_part7 = R"(./examples/EXAMPLE_part7.tga)";

    if (areFilesIdentical(outputFilePath_part7, exampleFilePath_EXAMPLE_part7)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile7 = loadtgaFile(outputFilePath_part7);
        tgaFile exampleFile7 = loadtgaFile(exampleFilePath_EXAMPLE_part7);

        if (areHeadersIdentical(outputFile7.header, exampleFile7.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile7.image, exampleFile7.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 8b
    cout << "Test Check 8b " << endl;
    string outputFilePath_part8b = R"(./output/part8_b.tga)";
    string exampleFilePath_EXAMPLE_part8b = R"(./examples/EXAMPLE_part8_b.tga)";

    if (areFilesIdentical(outputFilePath_part8b, exampleFilePath_EXAMPLE_part8b)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile8b = loadtgaFile(outputFilePath_part8b);
        tgaFile exampleFile8b = loadtgaFile(exampleFilePath_EXAMPLE_part8b);

        if (areHeadersIdentical(outputFile8b.header, exampleFile8b.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile8b.image, exampleFile8b.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 8g
    cout << "Test Check 8g " << endl;
    string outputFilePath_part8g = R"(./output/part8_g.tga)";
    string exampleFilePath_EXAMPLE_part8g = R"(./examples/EXAMPLE_part8_g.tga)";

    if (areFilesIdentical(outputFilePath_part8g, exampleFilePath_EXAMPLE_part8g)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile8g = loadtgaFile(outputFilePath_part8g);
        tgaFile exampleFile8g = loadtgaFile(exampleFilePath_EXAMPLE_part8g);

        if (areHeadersIdentical(outputFile8g.header, exampleFile8g.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile8g.image, exampleFile8g.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 8r
    cout << "Test Check 8r " << endl;
    string outputFilePath_part8r = R"(./output/part8_r.tga)";
    string exampleFilePath_EXAMPLE_part8r = R"(./examples/EXAMPLE_part8_r.tga)";

    if (areFilesIdentical(outputFilePath_part8r, exampleFilePath_EXAMPLE_part8r)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile8r = loadtgaFile(outputFilePath_part8r);
        tgaFile exampleFile8r = loadtgaFile(exampleFilePath_EXAMPLE_part8r);

        if (areHeadersIdentical(outputFile8r.header, exampleFile8r.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile8r.image, exampleFile8r.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 9
    cout << "Test Check 9 " << endl;
    string outputFilePath_part9 = R"(./output/part9.tga)";
    string exampleFilePath_EXAMPLE_part9 = R"(./examples/EXAMPLE_part9.tga)";

    if (areFilesIdentical(outputFilePath_part9, exampleFilePath_EXAMPLE_part9)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile9 = loadtgaFile(outputFilePath_part9);
        tgaFile exampleFile9 = loadtgaFile(exampleFilePath_EXAMPLE_part9);

        if (areHeadersIdentical(outputFile9.header, exampleFile9.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile9.image, exampleFile9.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }

    //File check 9
    cout << "Test Check 10 " << endl;
    string outputFilePath_part10 = R"(./output/part10.tga)";
    string exampleFilePath_EXAMPLE_part10 = R"(./examples/EXAMPLE_part10.tga)";

    if (areFilesIdentical(outputFilePath_part10, exampleFilePath_EXAMPLE_part10)) {
        cout << "Files are identical." << endl;
    }
    else {
        cout << "Files are different." << endl;

        tgaFile outputFile10 = loadtgaFile(outputFilePath_part10);
        tgaFile exampleFile10 = loadtgaFile(exampleFilePath_EXAMPLE_part10);

        if (areHeadersIdentical(outputFile10.header, exampleFile10.header)) {
            cout << "Headers are identical." << endl;
        }
        else {
            cout << "Headers are different." << endl;
        }

        if (areImagesIdentical(outputFile10.image, exampleFile10.image)) {
            cout << "Images are identical." << endl;
        }
        else {
            cout << "Images are different." << endl;
        }
    }
}