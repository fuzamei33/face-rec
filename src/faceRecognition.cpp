//
// Created by root on 18-1-12.
//

#include "faceRecognition.h"
faceRecognition::faceRecognition()
{

    this->detector = get_frontal_face_detector();
    deserialize("../dat/shape_predictor_68_face_landmarks.dat") >> sp;
    deserialize("../dat/dlib_face_recognition_resnet_model_v1.dat") >> net;
}

int faceRecognition::facerec(const paramFR& para)
try
{

    // The first thing we are going to do is load all our models.  First, since we need to
    // find faces in the image we will need a face detector:

    // We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
    matrix<rgb_pixel> img;
    matrix<rgb_pixel> img2;

    dlib::load_image(img,para.imagepath1);
    dlib::load_image(img2,para.imagepath2);

    resize_image(para.desample,img);
    resize_image(para.desample,img2);



    std::vector<matrix<rgb_pixel>> faces1;
    double s1=clock();
    for (auto face : detector(img,0))
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces1.push_back(move(face_chip));
    }


    std::vector<matrix<rgb_pixel>> faces2;
    for (auto face : detector(img2,0))
    {
        auto shape = sp(img2, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img2, get_face_chip_details(shape,150,0.25), face_chip);
        faces2.push_back(move(face_chip));
    }
    double s2=clock();
    cout<<"# Time detect faces: "<< (s2-s1)/CLOCKS_PER_SEC <<endl;
    if (faces1.empty())
    {
        cout << "No faces found in the first image!" << endl;
        return 1;
    }
    else
        cout << "The number of faces found in the first image: "<< faces1.size() << endl;
    if (faces2.empty())
    {
        cout << "No faces found in the second image!" << endl;
        return 2;
    }
    else
        cout << "The number of faces found in the second image: "<< faces2.size() << endl;

    std::vector<matrix<float,0,1>> face_descriptors1 = net(faces1);
    std::vector<matrix<float,0,1>> face_descriptors2 = net(faces2);
    int flag=0;
    for (const auto &i : face_descriptors1) {
        for (const auto &j : face_descriptors2) {
            cout<< "The distance of two faces: "<<length(i - j)<<endl;
            if (length(i - j) < para.threshold) {
                flag = 1;
                cout << "The two pictures have the same face" << endl;
                return 4;
            }
        }
    }
    double s3=clock();
    cout<<"# Time run Resnet: "<< (s3-s2)/CLOCKS_PER_SEC <<endl;
    cout << "The two pictures don't have the same face" << endl;
    return 0;
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}

int faceRecognition::faceidentify(const paramFR &para) {
    matrix<rgb_pixel> img;
    dlib::load_image(img,para.imagepath1);
    resize_image(para.desample,img);
    std::vector<matrix<rgb_pixel>> faces1;
    double s1=clock();
    pyramid_up(img);
    for (auto face : detector(img,0))
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces1.push_back(move(face_chip));
    }
    if (faces1.empty())
    {
        cout << "No faces found!" << endl;
        return 1;
    }
    else if (faces1.size()!=2) {
        cout << "can't find two faces in the image: " << faces1.size() << endl;
        return 2;
    }
    std::vector<matrix<float,0,1>> face_descriptors1 = net(faces1);
    cout<< "The distance of two faces: "<<length(face_descriptors1[0] - face_descriptors1[1])<<endl;
    if (length(face_descriptors1[0] - face_descriptors1[1]) < para.threshold) {
        cout << "It's the same person!" << endl;
        return 4;
    }
    else  cout << "It isn't the same person!" << endl;
    return 0;
}


