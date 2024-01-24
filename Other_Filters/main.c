//
//  main.c
//  CS136
//
//  Created by nha2 on 9/1/23.
// Test and demo program for netpbm. Reads a sample image and creates several output images.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "netpbm.h"
#include <stdio.h>
#include <stdbool.h>



Image function_imageBlackWhite(Image img, int intensityThreshold);
Image expand(Image img);
Image shrink(Image img);
Image noise(Image img, float p);
Image labelComponenets(Image img, int threshold);
void recursiveLabel(Image img, Matrix mat, int x, int y, int currentComponentNumber);
Matrix smoothing_filter(Matrix m1, Matrix m2);
Matrix median_filter(Matrix m1, Matrix m2);
Image imageToGrayscale(Image img);
Image sobel(Image img);
bool cannyLinking(Matrix mat, int x, int y, Matrix visited);
Image canny(Image img);
void edgeDetection(char *inputFilename, char *sobelFilename, char *cannyFilename);
void houghTransformLines(Image img);

int main(int argc, const char * argv[]) {
    //-------------------------------------------------------------------------------
       //create blackWhiteImage:
        // You need to change the path file: /Users/nha2/Downloads/Proj1_part1_2/Proj1_part1_2/ to your local directory
       Image inputImage = readImage("/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/plate1.ppm");

       //-------------------------------------------------------------------------------
       // COMMENT THIS FUNCTION IF YOU DON'T WANT IT TO RUN EVEY TIME
//    Image rotatedImage = createImage(inputImage.height, inputImage.width);
//    Image invertedImage = createImage(inputImage.height, inputImage.width);
//       for (int x = 0; x < inputImage.width; x++)
//           for (int y = 0; y < inputImage.height; y++)
//           {
//               rotatedImage.map[y][x] = inputImage.map[inputImage.height - y - 1][inputImage.width - x - 1];
//
//               invertedImage.map[y][x].r = 255 - inputImage.map[y][x].r;
//               invertedImage.map[y][x].g = 255 - inputImage.map[y][x].g;
//               invertedImage.map[y][x].b = 255 - inputImage.map[y][x].b;
//               // Let's just ignore 'i' here; it's irrelevant if we want to save image as PPM.
//           }
//       writeImage(rotatedImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/rotated.pbm");
//       writeImage(invertedImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/inverted.pbm");
//       writeImage(inputImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/gray.pgm");
//       writeImage(inputImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/black-white.pbm");

    //-------------------------------------------------------------------------------
       //create blackWhiteImage:
//    writeImage(function_imageBlackWhite, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/function_imageBlackWhite.pbm");
    Image blackWhiteImage = function_imageBlackWhite(inputImage, 128);

    writeImage(blackWhiteImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/black-white.pbm");
//
    
    Image grayscaleImage = imageToGrayscale(inputImage);
    writeImage(grayscaleImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/grayscale.ppm");
    
    Image expandedImage = expand(inputImage);
    Image shrunkenImage = shrink(expandedImage);
    
    writeImage(shrunkenImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/plate_cleaned.pbm");
    
    
    
//    Matrix m1 = image2Matrix(coloredImage);
    
//    double data1[6][6] = {
//        {1.0, 2.0, 3.0, 4.0, 5.0, 6.0},
//        {7.0, 8.0, 9.0, 10.0, 11.0, 12.0},
//        {13.0, 14.0, 15.0, 16.0, 17.0, 18.0},
//        {19.0, 20.0, 21.0, 22.0, 23.0, 24.0},
//        {25.0, 26.0, 27.0, 28.0, 29.0, 30.0},
//        {31.0, 32.0, 33.0, 34.0, 45.0, 36.0}
//    };

//    Matrix m1 = createMatrixFromArray((double *)data1, 6, 6);
    Matrix m1 = image2Matrix(inputImage);
    
    double data2[5][5] = {
            {1.0, 1.0, 1.0, 1.0,1.0},
        {1.0, 1.0, 1.0, 1.0,1.0},
        {1.0, 1.0, 1.0, 1.0,1.0},
        {1.0, 1.0, 1.0, 1.0,1.0},
        {1.0, 1.0, 1.0, 1.0,1.0},
        };

    Matrix m2 = createMatrixFromArray((double *)data2, 5, 5);
    Matrix smoothMat = smoothing_filter(m1, m2);
    Matrix medianMat = median_filter(m1, m2);
    
    Image smoothImage = matrix2Image(smoothMat, 0, 1);
    Image medianImage = matrix2Image(medianMat, 0, 1);

    writeImage(smoothImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/smoothedImagePlate.ppm");
    
    writeImage(medianImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/medianImagePlate.ppm");
    

    edgeDetection("/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/plate1.ppm", "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/sobelFilterPlates.pbm", "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/cannyFilterPlatesHighDerivative.ppm");
    

//    houghTransformLines(inputImage);
    
    
       //-------------------------------------------------------------------------------
       // Uncomment this after you finish your homework
       // Function that does threshold, noise and numbers of spanding and shrinking
       // COMMENT THIS FUNCTION IF YOU DON'T WANT IT TO RUN EVEY TIME
       //function_readImage();

        /* Delete back and white, noise, Expand and Shrink */
       deleteImage(inputImage);
//       deleteImage(rotatedImage);
//       deleteImage(invertedImage);

        


       printf("Program ends ... ");


       return 0;
}



//-------------------------------function_imageBlackWhite-------------------------------------------------
/* function that receives an Image structure and an intensity threshold
 to convert each pixel in the image to either black (intensity = 0)
 or white (intensity = 255). The function should return an Image structure
 containing the result. */

Image function_imageBlackWhite(Image img, int intensityThreshold){
    Image newImg = imageToGrayscale(img);
    
    int x,y;
    for(x = 0; x < newImg.width; x++){
        for(y = 0; y < newImg.height; y++){
            if(newImg.map[y][x].i >= intensityThreshold){
                newImg.map[y][x].i = 255;
            } else {
                newImg.map[y][x].i = 0;
            }
        }
    }
    return newImg;
}


Image imageToGrayscale(Image img){
    Matrix mat = image2Matrix(img);
    Image newImg = matrix2Image(mat, 0, 1);
    return newImg;
}


//--------------------------------Expand function-----------------------------------------------------------
/* Expand operation */
Image expand(Image img){
    Image newImg = createImage(img.height, img.width);
    int x,y;
    for(x = 1; x < img.width-1; x++){
        for(y = 1; y < img.height-1; y++){
            if(img.map[y][x+1].i == 0 || img.map[y][x-1].i == 0 || img.map[y+1][x].i == 0 || img.map[y-1][x].i == 0){
                newImg.map[y][x].i = 0;
            } else {
                newImg.map[y][x].i = img.map[y][x].i;
            }
        }
    }
    return newImg;
}



//--------------------------------Shrink function-----------------------------------------------------------
/* Shrink operation */

Image shrink(Image img){
    Image newImg = createImage(img.height, img.width);
    int x,y;
    for(x = 1; x < img.width-1; x++){
        for(y = 1; y < img.height-1; y++){
            if(img.map[y][x+1].i == 255 || img.map[y][x-1].i == 255 || img.map[y+1][x].i == 255 || img.map[y-1][x].i == 255){
                newImg.map[y][x].i = 255;
            } else {
                newImg.map[y][x].i = img.map[y][x].i;
            }
            
        }
    }
    return newImg;
}


//--------------------------------noise function-----------------------------------------------------------
/* function that adds binary noise to an image. This function receives an
 image and a floating point number p that indicates the probability
 (in percent) that each pixel in the image will be flipped, i.e.,
 turned from black to white or vice versa.
 */

Image noise(Image img, float p){
    Image newImg = createImage(img.height, img.width);
    int x,y;
    for(x = 1; x < img.width-1; x++){
        for(y = 1; y < img.height-1; y++){
            float random_value = (float)rand() / RAND_MAX;
            if(random_value < p){
                if(img.map[y][x].i == 255){
                    newImg.map[y][x].i = 0;
                } else {
                    newImg.map[y][x].i = 255;
                }
            } else {
                newImg.map[y][x].i = img.map[y][x].i;
            }
        }
    }
    return newImg;
}



//--------------------------------label componenets function-----------------------------------------------------------



void recursiveLabel(Image img, Matrix mat, int x, int y, int currentComponentNumber){
    
    mat.map[y][x] = currentComponentNumber;
    

    if(x < img.width-2 && mat.map[y][x+1] == 0 && img.map[y][x+1].i < 10){
        recursiveLabel(img, mat, x+1, y, currentComponentNumber);
    }
    if(x > 1 && mat.map[y][x-1] == 0 && img.map[y][x-1].i  < 50){
        recursiveLabel(img, mat, x-1, y, currentComponentNumber);
    }
    if(y < img.height-2 && mat.map[y+1][x] == 0 && img.map[y+1][x].i  < 50){
        recursiveLabel(img, mat, x, y+1, currentComponentNumber);
    }
    if(y > 1 && mat.map[y-1][x] == 0 && img.map[y-1][x].i  < 50){
        recursiveLabel(img, mat, x, y-1, currentComponentNumber);
    }
}



Image labelComponenets(Image img, int threshold){
    int currentComponentNumber = 1;
    Matrix mat = createMatrix(img.height, img.width);
    int x,y;
    
    for(x = 1; x < img.width-1; x++){
        for(y = 1; y < img.height-1; y++){
            if(mat.map[y][x] == 0 && img.map[y][x].i  < 50){
                recursiveLabel(img, mat, x, y, currentComponentNumber);
                currentComponentNumber++;
            }
            
        }
    }
    
    
    int maxComponentNumber = currentComponentNumber;
    for(int z = 1; z < maxComponentNumber; z++){
        int totalInThisComp = 0;
        for(x = 1; x < mat.width-1; x++){
            for(y = 1; y < mat.height-1; y++){
                if(mat.map[y][x] == z){
                    totalInThisComp++;
                }
            }
        }
//        printf("z: %d\n", z);
        
        if(totalInThisComp < threshold){
            currentComponentNumber--;
//            printf("maxComponentNumber: %d\n", maxComponentNumber);
            for(x = 1; x < mat.width-1; x++){
                for(y = 1; y < mat.height-1; y++){
                    if(mat.map[y][x] == z){
                        mat.map[y][x] = 0;
                    }
                }
            }
        }
//        printf("total: %d\n", currentComponentNumber);
    }
    
    printf("The number of above-threshold sized connected component is: %d\n", currentComponentNumber);
    
    int colors[maxComponentNumber][3];
    
    for (int i = 0; i < maxComponentNumber; i++) {
        colors[i][0] = rand() % 256; // Random red value (0-255)
        colors[i][1] = rand() % 256; // Random green value (0-255)
        colors[i][2] = rand() % 256; // Random blue value (0-255)
    }
    
    for(x = 1; x < mat.width-1; x++){
        for(y = 1; y < mat.height-1; y++){
            int compNumber = mat.map[y][x];
            if(compNumber != 0){
                setPixel(img, y, x, colors[compNumber][0], colors[compNumber][1], colors[compNumber][2], 255);
            } else {
                setPixel(img, y, x, 255, 255, 255, 255);
            }
            
        }
    }

    
    
    return img;

}

void printMatrix(Matrix mx) {
    int i, j;
    for (i = 0; i < mx.height; i++) {
        for (j = 0; j < mx.width; j++) {
            printf("%f ", mx.map[i][j]);
        }
        printf("\n");
    }
}

Matrix smoothing_filter(Matrix m1, Matrix m2){
    Matrix mat = createMatrix(m1.height, m1.width);
    
    bool evenHeight = (m2.height % 2 == 0);
    bool evenWidth = m2.width % 2 == 0;
    
    int startCol = evenWidth ? m2.width/2 -1 : floor(m2.width/2);
    int startRow = evenHeight ? m2.height/2 -1 : floor(m2.height/2);
//    printf("startRow: %d ", startRow);
//    printf("\n");
    
    int endCol = evenWidth ? m1.width - startCol-1 :  m1.width - startCol;
    int endRow = evenHeight ? m1.height - startRow-1 : m1.height - startRow;
    

    for(int x = startCol; x < endCol; x++){
        for(int y = startRow; y < endRow; y++){
            int newValue = 0;
            int filterSize = m2.width * m2.height;
            
            for(int i =0; i< m2.width;i++){
                for(int j = 0; j< m2.height;j++){
                    int yCoord = evenHeight ? y-m2.height/2 + j+1 : y-m2.height/2 + j;
                    int xCoord = evenWidth ? x-m2.width/2 + i+1 : x-m2.width/2 + i;
                    int originalValue = m1.map[yCoord][xCoord];
//                    printf("originalValue: %d ", originalValue);
//                    printf("\n");
                    
                    int weightedValue = originalValue * m2.map[j][i] / filterSize;
//                    printf("weightedValue: %d ", weightedValue);
//                    printf("\n");
                    
                    newValue += weightedValue;
                }

            }
            
//            printf("Y: %d ", y);
//            printf("\n");
            
            mat.map[y][x] = newValue;
            
        }
    }
    //printMatrix(mat);
    return mat;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int findMedian(int arr[], int size) {
    bubbleSort(arr, size);

    if (size % 2 != 0) {
        return arr[size / 2];
    } else {
        return (arr[size / 2 - 1] + arr[size / 2]) / 2;
    }
}




Matrix median_filter(Matrix m1, Matrix m2){
    Matrix mat = createMatrix(m1.height, m1.width);
    
    bool evenHeight = (m2.height % 2 == 0);
    bool evenWidth = m2.width % 2 == 0;
    
    int startCol = evenWidth ? m2.width/2 -1 : floor(m2.width/2);
    int startRow = evenHeight ? m2.height/2 -1 : floor(m2.height/2);
//    printf("startRow: %d ", startRow);
//    printf("\n");
    
    int endCol = evenWidth ? m1.width - startCol-1 :  m1.width - startCol;
    int endRow = evenHeight ? m1.height - startRow-1 : m1.height - startRow;
    

    for(int x = startCol; x < endCol; x++){
        for(int y = startRow; y < endRow; y++){
            int newValue[m2.width*m2.height];
            int counter = 0;
            
            for(int i =0; i< m2.width;i++){
                for(int j = 0; j< m2.height;j++){
                    int yCoord = evenHeight ? y-m2.height/2 + j+1 : y-m2.height/2 + j;
                    int xCoord = evenWidth ? x-m2.width/2 + i+1 : x-m2.width/2 + i;
                    int originalValue = m1.map[yCoord][xCoord];
//                    printf("originalValue: %d ", originalValue);
//                    printf("\n");
                    
                    int weightedValue = originalValue * m2.map[j][i];
                    newValue[counter] = weightedValue;
                    counter++;
//                    printf("weightedValue: %d ", weightedValue);
//                    printf("\n");
                    
                }

            }
            
//            printf("Y: %d ", y);
//            printf("\n");
            
            unsigned long size = sizeof(newValue) / sizeof(newValue[0]);
            
            for (int i = 0; i < size; i++) {
//                    printf("%d ", newValue[i]);
                }
//            printf("\n");

            int median = findMedian(newValue, (int)(size));
//            printf("median: %d ", median);
//            printf("\n");
            mat.map[y][x] = median;
            
        }
    }
    //printMatrix(mat);
    return mat;
}


Matrix convolve(Matrix m1, Matrix m2){
    Matrix mat = createMatrix(m1.height, m1.width);
    
    bool evenHeight = (m2.height % 2 == 0);
    bool evenWidth = m2.width % 2 == 0;
    
    int startCol = evenWidth ? m2.width/2 -1 : floor(m2.width/2);
    int startRow = evenHeight ? m2.height/2 -1 : floor(m2.height/2);
//    printf("startRow: %d ", startRow);
//    printf("\n");
    
    int endCol = evenWidth ? m1.width - startCol-1 :  m1.width - startCol;
    int endRow = evenHeight ? m1.height - startRow-1 : m1.height - startRow;
    

    for(int x = startCol; x < endCol; x++){
        for(int y = startRow; y < endRow; y++){
            int newValue = 0;
            int filterSize = m2.width * m2.height;
            
            for(int i =0; i< m2.width;i++){
                for(int j = 0; j< m2.height;j++){
                    int yCoord = evenHeight ? y-m2.height/2 + j+1 : y-m2.height/2 + j;
                    int xCoord = evenWidth ? x-m2.width/2 + i+1 : x-m2.width/2 + i;
                    int originalValue = m1.map[yCoord][xCoord];
//                    printf("originalValue: %d ", originalValue);
//                    printf("\n");
                    
                    int weightedValue = originalValue * m2.map[j][i];
//                    printf("weightedValue: %d ", weightedValue);
//                    printf("\n");
                    
                    newValue += weightedValue;
                }

            }
            
//            printf("Y: %d ", y);
//            printf("\n");
            
            mat.map[y][x] = newValue;
            
        }
    }
    //printMatrix(mat);
    return mat;
}


Image sobel(Image img){
    
    Matrix imgMatrix = image2Matrix(img);
    
    double smoothFilterArray[3][3] = {
            {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        };
    
    Matrix smoothFilterMatrix = createMatrixFromArray((double *)smoothFilterArray, 3, 3);
    Matrix smoothMatrix = smoothing_filter(imgMatrix, smoothFilterMatrix);
    
    
    double SiArray[3][3] = {
            {4.0, 8.0, 4.0},
        {0.0, 0.0, 0.0},
        {-4.0, -8.0, -4.0},
        };
    
    double SjArray[3][3] = {
            {4.0, 0.0, -4.0},
        {8.0, 0.0, -8.0},
        {4.0, 0.0, -4.0},
        };

    Matrix SiMatrix = createMatrixFromArray((double *)SiArray, 3, 3);
    Matrix SjMatrix = createMatrixFromArray((double *)SjArray, 3, 3);
    
    Matrix Si = convolve(smoothMatrix, SiMatrix);
    Matrix Sj = convolve(smoothMatrix, SjMatrix);
    
    Matrix mat = createMatrix(img.height, img.width);
    
    for(int x = 1; x < img.width-1; x++){
        for(int y = 1; y < img.height-1; y++){
            int s1 = Si.map[y][x];
            int s2 = Sj.map[y][x];
            mat.map[y][x] = sqrt(s1 * s1 + s2 * s2)/3;
        }
    }
    
    Image sobelImage = matrix2Image(mat, 0, 1);
    return sobelImage;
}

Image canny(Image img){
    
    Matrix imgMatrix = image2Matrix(img);
    
    double smoothFilterArray[3][3] = {
            {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        };
    
    Matrix smoothFilterMatrix = createMatrixFromArray((double *)smoothFilterArray, 3, 3);
    Matrix smoothMatrix = smoothing_filter(imgMatrix, smoothFilterMatrix);
    
    
    double PArray[2][2] = {
            {0.7, 0.7},
        {-0.7, -0.7},
        };
    
    double QArray[2][2] = {
            {0.7, -0.7},
        {0.7, -0.7},
        };

    Matrix Pmatrix = createMatrixFromArray((double *)PArray, 2, 2);
    Matrix Qmatrix = createMatrixFromArray((double *)QArray, 2, 2);
    
    Matrix P = convolve(smoothMatrix, Pmatrix);
    Matrix Q = convolve(smoothMatrix, Qmatrix);
    
    Matrix m = createMatrix(img.height, img.width);
    Matrix a = createMatrix(img.height, img.width);
    
    for(int x = 1; x < img.width-1; x++){
        for(int y = 1; y < img.height-1; y++){
            int Pij = P.map[y][x];
            int Qij = Q.map[y][x];
            
            m.map[y][x] = sqrt(Pij * Pij + Qij * Qij);
            a.map[y][x] = atan2(Qij, Pij);
        }
    }
    
    Matrix C = createMatrix(img.height, img.width);
    
    for(int x = 1; x < img.width-1; x++){
        for(int y = 1; y < img.height-1; y++){
            if((a.map[y][x] < 22.5 || a.map[y][x] > 337.5) || (a.map[y][x] > 157.5 && a.map[y][x] < 202.5)){
                C.map[y][x] = 0;
            } else if((a.map[y][x] > 22.5 && a.map[y][x] < 67.5) || (a.map[y][x] > 202.5 && a.map[y][x] < 247.5)){
                C.map[y][x] = 1;
            } else if((a.map[y][x] > 67.5 && a.map[y][x] < 112.5) || (a.map[y][x] > 247.5 && a.map[y][x] < 292.5)){
                C.map[y][x] = 2;
            } else {
                C.map[y][x] = 3;
            }
        }
    }
    
    Matrix E = createMatrix(img.height, img.width);
    
    for(int x = 2; x < img.width-2; x++){
        for(int y = 2; y < img.height-2; y++){
            if(C.map[y][x] == 0){
                if(m.map[y][x] < m.map[y-1][x] || m.map[y][x] < m.map[y+1][x]){
                    E.map[y][x] = 0;
                    E.map[y][x] = 0;
                } else {
                    E.map[y][x] = m.map[y][x];
                }
            }
            if(C.map[y][x] == 1){
                if(m.map[y][x] < m.map[y+1][x-1] || m.map[y][x] < m.map[y-1][x+1]){
                    E.map[y][x] = 0;
                } else {
                    E.map[y][x] = m.map[y][x];
                }
            }
            if(C.map[y][x] == 2){
                if(m.map[y][x] < m.map[y][x-1] || m.map[y][x] < m.map[y][x+1]){
                    E.map[y][x] = 0;
                } else {
                    E.map[y][x] = m.map[y][x];
                }
            }
            if(C.map[y][x] == 3){
                if(m.map[y][x] < m.map[y-1][x-1] || m.map[y][x] < m.map[y+1][x+1]){
                    E.map[y][x] = 0;
                } else {
                    E.map[y][x] = m.map[y][x];
                }
            }
        }
    }
    
    
    
    int high_threshold = 25;
    int low_threshold = 4;
    
    //2 is edge, 1 is candidate, 0 is not an edge
    Matrix candidateMat = createMatrix(img.height, img.width);
    
    for(int x = 2; x < img.width-2; x++){
        for(int y = 2; y < img.height-2; y++){
            if(E.map[y][x] > high_threshold){
                candidateMat.map[y][x] = 2;
            } else if (E.map[y][x] > low_threshold){
                candidateMat.map[y][x] = 1;
            }
            
        }
    }
    
    
    
    Matrix finalMatrix = createMatrix(img.height, img.width);
    Matrix visited = createMatrix(img.height, img.width);
    
    //printMatrix(candidateMat);
    
    for(int x = 2; x < img.width-2; x++){
        for(int y = 2; y < img.height-2; y++){
            if(cannyLinking(candidateMat, x, y, visited)){
                finalMatrix.map[y][x] = 255;
            }
            
        }
    }
    
    
    Image cannyImage = matrix2Image(finalMatrix, 0, 1);
    return cannyImage;
}


bool cannyLinking(Matrix mat, int x, int y, Matrix visited){
    
    
    bool validPosition = (x > 2 && x < mat.width-2 && y > 2 && y < mat.height-2);
    
    
    if(!validPosition || mat.map[y][x] == 0 || visited.map[y][x]){
        return false;
    } else if (mat.map[y][x] == 2){
        return true;
    } else {
        
        visited.map[y][x] = true;
        
        bool left = cannyLinking(mat, x-1, y, visited);
        bool right = cannyLinking(mat, x+1, y, visited);
        bool top = cannyLinking(mat, x, y+1, visited);
        bool bottom = cannyLinking(mat, x, y-1, visited);
        bool topLeft = cannyLinking(mat, x-1, y+1, visited);
        bool topRight = cannyLinking(mat, x+1, y+1, visited);
        bool bottomLeft = cannyLinking(mat, x-1, y-1, visited);
        bool bottomRight = cannyLinking(mat, x+1, y-1, visited);
        
        return left || right || top || bottom || topLeft || topRight || bottomLeft || bottomRight;
        
    }
    
}


void edgeDetection(char *inputFilename, char *sobelFilename, char *cannyFilename){
    Image inputImage = readImage(inputFilename);
    
    Image sobelImg = sobel(inputImage);
    
    Image blackWhiteImage = function_imageBlackWhite(sobelImg, 128);
    
    writeImage(blackWhiteImage, sobelFilename);
    
    Image sobelImg2 = expand(blackWhiteImage);
    Image sobelImg3 = shrink(sobelImg2);
    Image sobelImg4 = expand(sobelImg3);
    Image sobelImg5 = shrink(sobelImg4);
    
    writeImage(sobelImg5, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/sobelFilterPlates_shrunked_expanded_2.ppm");
    
    Image cannyImg = canny(inputImage);
    writeImage(cannyImg, cannyFilename);
    
}

void houghTransformLines(Image img){
    Image sobelImage = sobel(img);
    
    Image blackWhiteImage = function_imageBlackWhite(sobelImage, 75);
    writeImage(blackWhiteImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/black-white-sobel.pbm");
    
    int maxRadius = 25;
    
    
    printf("%d ", sobelImage.width); //prints 640
    int outputSpaceWidth = sobelImage.width/4;
    int outputSpaceHeight = sobelImage.height/4;
    
    int outputSpace[maxRadius][outputSpaceHeight][outputSpaceWidth];
    
    for (int i = 0; i < outputSpaceWidth; i++) {
       for (int j = 0; j < outputSpaceHeight; j++) {
           for (int r = 0; r < maxRadius; r++) {
              outputSpace[r][j][i] = 0;
           }
       }
    }
    
    int counter  = 0;
    int counter1  = 0;
    
    for(int x = 3; x < sobelImage.width-3; x++){
        
        for(int y = 3; y < sobelImage.height-3; y++){
            counter1++;
            if(sobelImage.map[y][x].i > 75){
                counter++;
                
                
                for(int i = 0; i < outputSpaceWidth; i++){
                    for(int j = 0; j < outputSpaceHeight; j++){
                        for(int r = 25; r < maxRadius; r++){
                            
                            
                            int distanceFromCircle = fabs(sqrt((x - i*4) * (x - i*4) +(y - j*4) * (y - j*4)) - r);
                            
                            if (distanceFromCircle < 2){
                                outputSpace[r][j][i]++;
                            }
                            
                        }
                    }
                }
            }
            
            
        }
    }
    
    printf("counter: %d ", counter);
    printf("counter1: %d ", counter1);
        
    
//    for (int i = 0; i < outputSpaceWidth; i++) {
//       for (int j = 0; j < outputSpaceHeight; j++) {
//           for (int r = 0; r < maxRadius; r++) {
//               printf("%d ", outputSpace[i][j][r]);
//           }
//           printf("\n");
//       }
//       printf("\n");
//    }
    
    int largest = 0;
    int largestX = 0;
    int largestY = 0;
    int largestRad = 0;
    
    for (int r = 0; r < maxRadius; r++) {
        for (int j = 0; j < outputSpaceHeight; j++) {
            for (int i = 0; i < outputSpaceWidth; i++){
                
                if(outputSpace[r][j][i] > largest){
                    largest = outputSpace[r][j][i];
                    largestX = i;
                    largestY = j;
                }
                
                
               printf("%d ", outputSpace[r][j][i]);
           }
           printf("\n");
       }
       printf("\n");
    }
    
    printf("\n Largest = %d ", largest);
    
    Matrix maximaMatrix = createMatrix(outputSpaceHeight, outputSpaceWidth);
    
    int maxValue = 0;
    
    for (int j = 0; j < maximaMatrix.height; j++) {
        for (int i = 0; i < maximaMatrix.width; i++){
            
            int maxValueAtPosition = 0;
            
            for (int r = 0; r < maxRadius; r++) {
                if(outputSpace[r][j][i] > maxValueAtPosition){
                    maxValueAtPosition =  outputSpace[r][j][i];
                }
            }
            
            maximaMatrix.map[j][i] = maxValueAtPosition;
            
            if(maxValueAtPosition > maxValue){
                maxValue = maxValueAtPosition;
            }
       }
       printf("\n");
   }
    
    for (int j = 0; j < maximaMatrix.height; j++) {
        for (int i = 0; i < maximaMatrix.width; i++){
            maximaMatrix.map[j][i] = (maximaMatrix.map[j][i]/maxValue)*255;
       }
       printf("\n");
   }
    
    Image houghTransformImage = matrix2Image(maximaMatrix, 0, 1);

    writeImage(houghTransformImage, "/Users/adityanair/Development/SJSU/CS 136/project1/Project 1/Project 1/houghTransformImage.ppm");

}
