// Author: Zuhayer Tashin
// Course: CSCI-135
// Instructor: Tong Yi
// Assignment: Lab 8B
// Write a program invert-half.cpp that inverts the colors only in the right half of the picture.

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Function to read the input image from a file
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
    char c;
    int x;
    ifstream instr;
    instr.open("inImage.pgm");

    // Read and validate the PGM file header
    instr >> c;
    assert(c == 'P');
    instr >> c;
    assert(c == '2');

    // Skip any comments in the file
    while ((instr >> ws).peek() == '#') {
        instr.ignore(4096, '\n');
    }

    // Read image width, height, and maximum pixel value
    instr >> width;
    instr >> height;
    assert(width <= MAX_W);
    assert(height <= MAX_H);
    int max;
    instr >> max;
    assert(max == 255);

    // Read pixel values into the image array
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            instr >> image[row][col];
    instr.close();
    return;
}

// Function to write the output image to a file
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
    ofstream ostr;
    ostr.open("outImage.pgm");
    if (ostr.fail()) {
        cout << "Unable to write file\n";
        exit(1);
    };

    // Write the PGM file header
    ostr << "P2" << endl;
    ostr << width << ' ';
    ostr << height << endl;
    ostr << 255 << endl;

    // Write pixel values to the output file
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            assert(image[row][col] < 256);
            assert(image[row][col] >= 0);
            ostr << image[row][col] << ' ';
        }
        ostr << endl;
    }
    ostr.close();
    return;
}

int main() {
    int img[MAX_H][MAX_W];
    int h, w;

    // Read the input image from the file
    readImage(img, h, w);

    int out[MAX_H][MAX_W];

    // Perform the image processing (negate pixel values)
    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            out[row][col] =  255 - img[row][col];
        
        }
        for (int col = w/2 - 1; col >= 0; col--) {
            out[row][col] = img[row][col];
        }
    }

    // Write the processed image to the output file
    writeImage(out, h, w);
}
