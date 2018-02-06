#include <stdio.h>
#include "faceRecognition.h"

int main(int argc, char** argv)  {
    if (argc <= 1) {
        fprintf(stderr, "%s sample_img\n", argv[0]);
        return -1;
    }

    paramFR para;
    para.imagepath1 = argv[1];
    para.desample = 1; 

    faceRecognition face;
    int res = face.faceidentify(para);
    
    return 0;
}
