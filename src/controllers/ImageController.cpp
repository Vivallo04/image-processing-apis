#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"
#include "ImageController.hpp"

namespace
{
    std::string const image_path = "/home/josev/CLionProjects/proyectoprueba/Resources/jose.jpg";
    cv::Mat img = cv::imread(image_path);
}

cv::Mat ImageController::GaussianBlur_Filter(const cv::Mat &img_orig, cv::Mat img_new, int width, int height)
{
    GaussianBlur(img_orig,img_new, cv::Size(width, height),0);
}

cv::Mat ImageController::GrayScale_Filter(const cv::Mat &img_orig, cv::Mat img_new)
{
    cvtColor(img,img_new,cv::COLOR_BGR2GRAY);
}

cv::Mat ImageController::BrightnessControl_Filter(const cv::Mat &img_orig, cv::Mat img_new, int contrast, int bright)
{
    img_orig.convertTo(img_new,-1,contrast, bright - 150);
}

cv::Mat ImageController::GammaCorrection_Filter(const cv::Mat &img_orig, cv::Mat img_new, int gamma_cor)
{
    unsigned char lut[256];
    for (int i = 0; i < 256; i++)
    {
        lut[i] = cv::saturate_cast<uchar>(pow((float) (i / 255.0), gamma_cor) * 255.0f);
    }

    img_new = img_orig.clone();
    const int channels = img_new.channels();
    switch (channels)
    {
        case 1:
        {
            cv::MatIterator_<uchar> it, end;
            for (it = img_new.begin<uchar>(), end = img_new.end<uchar>(); it != end; it++)
            {
                *it = lut[(*it)];
            }
            break;
        }
        case 3:
        {
            cv::MatIterator_<cv::Vec3b> it, end;
            for (it = img_new.begin<cv::Vec3b>(), end = img_new.end<cv::Vec3b>(); it != end; it++)
            {
                (*it)[0] = lut[((*it)[0])];
                (*it)[1] = lut[((*it)[1])];
                (*it)[2] = lut[((*it)[2])];
            }
            break;
        }
        default:
            break;
    }
}