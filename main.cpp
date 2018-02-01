#include <stdio.h>
#include "faceRecognition.h"

int main(int argc, char** argv)  {
    if (argc <= 2) {
        fprintf(stderr, "%s train_img test_img\n", argv[0]);
        return -1;
    }

    faceRecognition face(argv[1], argv[2]);
    int res = face.facerec(0.6);
    switch (res) {
        case 1: cout << "No faces found in the first image!" << endl; break;
        case 2: cout << "No faces found in the second image!" << endl; break;
        case 4: cout << "The two pictures have the same face" << endl; break;
        case 0: cout << "The two pictures don't have the same face" << endl; break;
        default:cout << "Internal error" << endl; break;
    }

    return 0;
}
