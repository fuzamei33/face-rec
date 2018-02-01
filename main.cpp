#include "faceRecognition.h"

int main(int argc, char** argv)  {
    faceRecognition face("../dat/3.jpg","../dat/2.jpg");
    int res=face.facerec(0.6);
    return 0;
}


