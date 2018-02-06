#include <stdio.h>
#include "faceRecognition.h"

int main(int argc, char** argv)  {
    if (argc <= 2) {
        fprintf(stderr, "%s model_img sample_img\n", argv[0]);
        return -1;
    }

    paramFR para;
    para.imagepath1 = argv[1];
    para.imagepath2 = argv[2];
    para.desample = 1; 

    faceRecognition face;
    int res = face.facerec(para);

    return 0;
}
