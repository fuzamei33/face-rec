#include "faceRecognition.h"

/***
 * para has for parameter:
 * imagepath1,imagepath2 are the input image paths
 * threshold is the
 * desample is resizing image for accelerating
 *
 *
 * facerec() to recognize the if two images have the same person
 * faceidentify() is to recognize the if the same person is in one image
 */

int main(int argc, char** argv)  {

    clock_t time_begin=clock();
    faceRecognition face;
    clock_t time_point1=clock();

    paramFR para;
    para.imagepath1="../dat/1.jpg";
    para.imagepath2="../dat/2.jpg";
    para.desample=1; // default is 1


    int res=face.facerec(para);
    clock_t time_end=clock();
    cout<<"******************************************"<<endl;
    int res2=face.faceidentify(para);  //only imagepath1 is valid
    cout<<"******************************************"<<endl;
    cout<<"The loading model time: "<<(1.0)*(time_point1-time_begin)/CLOCKS_PER_SEC<<endl;
    cout<<"The recognition time: "<<(1.0)*(time_end-time_point1)/CLOCKS_PER_SEC<<endl;
    cout<<"The runing time: "<<(1.0)*(time_end-time_begin)/CLOCKS_PER_SEC<<endl;
    return 0;
}

