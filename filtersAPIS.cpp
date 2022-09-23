#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"
#include "filtersAPIS.h"

using namespace cv;
using namespace std;

namespace {

    std::string image_path = "/home/josev/CLionProjects/proyectoprueba/Resources/jose.jpg";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;
}

Mat filtersAPIS::GaussianBlur_Filter(cv::Mat img_orig, cv::Mat img_new, int o) {
    int z = 0;
    GaussianBlur(img_orig,img_new,Size(15,15),0);
    while (z < o) {
        GaussianBlur(img_orig, img_new, Size(15, 15), 0);
        z++;
    }
    imshow("Display imgBlur", img_new);
    waitKey(0);
}

Mat filtersAPIS::GrayScale_Filter(cv::Mat img_orig, cv::Mat img_new) {

    cvtColor(img,img_new,COLOR_BGR2GRAY);
    /*if(img.empty())
    {
        std::cout<<"COULD NOT READ IMAGE"<<std::endl;
        return 1;
    }*/
    //imshow("Display Window", img);
    imshow("Display Window", img_new);

    waitKey(0);
}

Mat filtersAPIS::BrightnessControl_Filter(cv::Mat img_orig, cv::Mat img_new, int contrast, int bright) {

    img_orig.convertTo(img_new,-1,contrast,bright-150);

    imshow("Display Window", img);
    imshow("Display Window", img_new);

    waitKey(0);
}


Mat filtersAPIS::GammaCorrection_Filter(cv::Mat img_orig, cv::Mat img_new, int gamma_cor) {


    unsigned char lut[256];
    for (int i = 0; i < 256; i++) {
        lut[i] = saturate_cast<uchar>(pow((float) (i / 255.0), gamma_cor) * 255.0f);
    }
    img_new = img_orig.clone();

    const int channels = img_new.channels();
    switch (channels) {
        case 1: {
            MatIterator_<uchar> it, end;
            for (it = img_new.begin<uchar>(), end = img_new.end<uchar>(); it != end; it++)
                *it = lut[(*it)];
            // Show results
            imshow("img_orig", img_orig);
            imshow("img_new", img_new);
            waitKey(0);
            break;
        }
        case 3: {
            MatIterator_<Vec3b> it, end;
            for (it = img_new.begin<Vec3b>(), end = img_new.end<Vec3b>(); it != end; it++) {
                (*it)[0] = lut[((*it)[0])];
                (*it)[1] = lut[((*it)[1])];
                (*it)[2] = lut[((*it)[2])];
            }
            // Show results
            imshow("img_orig", img_orig);
            imshow("img_new", img_new);
            waitKey(0);
            break;
        }
    }
}

Mat filtersAPIS::ShowImages(cv::Mat img_new) {

}

int main(int argc,char **argv){
    filtersAPIS jose;
    //jose.GaussianBlur_Filter(img,img_new,5);
    //jose.GammaCorrection_Filter(img,img_new,8);
    //jose.GrayScale_Filter(img,img_new);
    //jose.BrightnessControl_Filter(img,img_new,5,5);
    printf("hola");
    return 0;

}


