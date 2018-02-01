//
// Created by root on 18-1-12.
//

#include "faceRecognition.h"
faceRecognition::faceRecognition(const std::string a,const std::string b)
{
    dlib::load_image(train_img,a);
    dlib::load_image(test_img,b);
}

int faceRecognition::facerecd(double th)
try
{


    // The first thing we are going to do is load all our models.  First, since we need to
    // find faces in the image we will need a face detector:
    frontal_face_detector detector = get_frontal_face_detector();
    // We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
    shape_predictor sp;
    deserialize("../dat/shape_predictor_68_face_landmarks.dat") >> sp;
    anet_type net;
    deserialize("../dat/dlib_face_recognition_resnet_model_v1.dat") >> net;

    matrix<rgb_pixel> img=train_img;
    matrix<rgb_pixel> img2=test_img;
    //load_image(img, "../dat/5.jpg");
    //load_image(img2, "../dat/3.jpg");
    // Display the raw image on the screen
    image_window win(img);
    image_window win2(img2);
    // Run the face detector on the image of our action heroes, and for each face extract a
    // copy that has been normalized to 150x150 pixels in size and appropriately rotated
    // and centered.
    std::vector<matrix<rgb_pixel>> faces1;

    for (auto face : detector(img,0))
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces1.push_back(move(face_chip));
        // Also put some boxes on the faces so we can see that the detector is finding
        // them.
        win.add_overlay(face);
    }
    std::vector<matrix<rgb_pixel>> faces2;
    for (auto face : detector(img2,0))
    {
        auto shape = sp(img2, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img2, get_face_chip_details(shape,150,0.25), face_chip);
        faces2.push_back(move(face_chip));
        // Also put some boxes on the faces so we can see that the detector is finding
        // them.
        win2.add_overlay(face);
    }


    if (faces1.size() == 0)
    {
        cout << "No faces found in the first image!" << endl;
        return 1;
    }
    else
        cout << "The number of faces found in the first image: "<< faces1.size() << endl;

    if (faces2.size() == 0)
    {
        cout << "No faces found in the second image!" << endl;
        return 2;
    }
    else
        cout << "The number of faces found in the second image: "<< faces2.size() << endl;
    // This call asks the DNN to convert each face image in faces into a 128D vector.
    // In this 128D vector space, images from the same person will be close to each other
    // but vectors from different people will be far apart.  So we can use these vectors to
    // identify if a pair of images are from the same person or from different people.
    std::vector<matrix<float,0,1>> face_descriptors1 = net(faces1);
    std::vector<matrix<float,0,1>> face_descriptors2 = net(faces2);
    int flag=0;
    for (size_t i = 0; i < face_descriptors1.size(); ++i)
    {
        for (size_t j = 0; j < face_descriptors2.size(); ++j) {
            cout<< "The distance of two faces: "<<length(face_descriptors1[i]-face_descriptors2[j])<<endl;
            if (length(face_descriptors1[i]-face_descriptors2[j]) < th) {
                flag = 1;
                cout << "The two pictures have the same face" << endl;
                return 4;
            }
        }
    }
    // In particular, one simple thing we can do is face clustering.  This next bit of code
    // creates a graph of connected faces and then uses the Chinese whispers graph clustering
    // algorithm to identify how many people there are and which faces belong to whom.
    /*std::vector<sample_pair> edges;
    for (size_t i = 0; i < face_descriptors.size(); ++i)
    {
        for (size_t j = i; j < face_descriptors.size(); ++j)
        {
            // Faces are connected in the graph if they are close enough.  Here we check if
            // the distance between two face descriptors is less than 0.6, which is the
            // decision threshold the network was trained to use.  Although you can
            // certainly use any other threshold you find useful.
            if (length(face_descriptors[i]-face_descriptors[j]) < 0.6)
                edges.push_back(sample_pair(i,j));
        }
    }*?
    //std::vector<unsigned long> labels;
    //const auto num_clusters = chinese_whispers(edges, labels);
    // This will correctly indicate that there are 4 people in the image.
    //cout << "number of people found in the image: "<< num_clusters << endl;


    // Now let's display the face clustering results on the screen.  You will see that it
    // correctly grouped all the faces.
    /*std::vector<image_window> win_clusters(num_clusters);
    for (size_t cluster_id = 0; cluster_id < num_clusters; ++cluster_id)
    {
        std::vector<matrix<rgb_pixel>> temp;
        for (size_t j = 0; j < labels.size(); ++j)
        {
            if (cluster_id == labels[j])
                temp.push_back(faces[j]);
        }
        win_clusters[cluster_id].set_title("face cluster " + cast_to_string(cluster_id));
        win_clusters[cluster_id].set_image(tile_images(temp));
    }*/




    // Finally, let's print one of the face descriptors to the screen.
    //cout << "face descriptor for one face in first image: " << trans(face_descriptors1[0]) << endl;
    //cout << "face descriptor for one face in second image: " << trans(face_descriptors2[0]) << endl;

    // It should also be noted that face recognition accuracy can be improved if jittering
    // is used when creating face descriptors.  In particular, to get 99.38% on the LFW
    // benchmark you need to use the jitter_image() routine to compute the descriptors,
    // like so:

    // cout << "hit enter to terminate" << endl;
    // cin.get();
    cout << "The two pictures don't have the same face" << endl;
    return 0;
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}

int faceRecognition::facerec(double th) try{

frontal_face_detector detector = get_frontal_face_detector();
shape_predictor sp;
deserialize("../dat/shape_predictor_68_face_landmarks.dat") >> sp;
anet_type net;
deserialize("../dat/dlib_face_recognition_resnet_model_v1.dat") >> net;
matrix<rgb_pixel> img=train_img;
matrix<rgb_pixel> img2=test_img;
std::vector<matrix<rgb_pixel>> faces1;
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


if (faces1.size() == 0)
{
    cout << "No faces found in the first image!" << endl;
    return 1;
}


if (faces2.size() == 0)
{
    cout << "No faces found in the second image!" << endl;
    return 2;
}

std::vector<matrix<float,0,1>> face_descriptors1 = net(faces1);
std::vector<matrix<float,0,1>> face_descriptors2 = net(faces2);
for (size_t i = 0; i < face_descriptors1.size(); ++i)
{
    for (size_t j = 0; j < face_descriptors2.size(); ++j) {
        cout<< "The distance of two faces: "<<length(face_descriptors1[i]-face_descriptors2[j])<<endl;
        if (length(face_descriptors1[i]-face_descriptors2[j]) < th) {
            cout << "The two pictures have the same face" << endl;
            return 4;
        }
    }
}
    cout << "The two pictures don't have the same face" << endl;
    return 0;
}
catch (std::exception& e)
{
cout << e.what() << endl;
}