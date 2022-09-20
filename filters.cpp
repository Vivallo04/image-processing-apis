#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

namespace {

    int alpha = 100;
    int beta = 100;
    int gamma_cor = 100;
    Mat img_original, img_corrected, img_gamma_corrected;
    std::string image_path = "/home/josev/CLionProjects/proyectoprueba/Resources/jose.jpg";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;
}

//Importing images
int importimage() {


    cv::Mat img = cv::imread(image_path);
    /*if(img.empty())
    {
        std::cout<<"COULD NOT READ IMAGE"<<std::endl;
        return 1;
    }*/
    imshow("Display Window", img);
    waitKey(0);
}



//Setting an image into gray scale
int grayimages() {


    cv::Mat img = cv::imread(image_path);
    cv::Mat imgGray;

    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    /*if(img.empty())
    {
        std::cout<<"COULD NOT READ IMAGE"<<std::endl;
        return 1;
    }*/
    //imshow("Display Window", img);
    imshow("Display Window", imgGray);

    waitKey(0);
}


void Gaussian_Blur(Mat imgorig,Mat img){

    cv::Mat imgBlur;
    GaussianBlur(img,imgBlur,Size(7,7),5,0);
    imshow("Display imggray", imgBlur);
    waitKey(0);
}
void GammaCorrection(Mat& src, Mat& dst, float fGamma)
{
    unsigned char lut[256];
    for (int i = 0; i < 256; i++)
    {
        lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
    }
    dst = src.clone();

    const int channels = dst.channels();
    switch (channels)
    {
        case 1:
        {
            MatIterator_<uchar> it, end;
            for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
                *it = lut[(*it)];
            // Show results
            imshow("SRC", src);
            imshow("DST", dst);
            waitKey();
            break;
        }
        case 3:
        {
            MatIterator_<Vec3b> it, end;
            for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
            {
                (*it)[0] = lut[((*it)[0])];
                (*it)[1] = lut[((*it)[1])];
                (*it)[2] = lut[((*it)[2])];
            }
            // Show results
            imshow("SRC", src);
            imshow("DST", dst);
            waitKey();
            break;
        }
    }
}

void BrightControl()

int main(int argc,char **argv){
    //importimage();
    //grayimages();
    //GaussianBlur();
    GammaCorrection(img,img_new,1.66);
    printf("hola");
    return 0;

}


