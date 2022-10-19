#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"
#include "ImageController.hpp"

namespace {

    std::string image_path = "/home/josev/CLionProjects/image-processing-apis/assets/jose.jpg";
    cv::Mat img = cv::imread(image_path);
    cv::Mat *img_ptr = &img;
    cv::Mat * img_new;
}

int ImageController::GaussianBlurFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height)
{
    if(img_orig.empty())
    {
        std::cout << "COULD NOT READ IMAGE" << std::endl;
        return -1;
    }

    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;
    GaussianBlur(img_orig,img_new, cv::Size(width, height),0);
    return 0;

}

int ImageController::GrayScaleFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height)
{
    cv::Mat img_sizer;
    if(img_orig.empty())
    {
        std::cout << "COULD NOT READ IMAGE" << std::endl;
        return -1;
    }

    cvtColor(img_orig,img_sizer,cv::COLOR_BGR2GRAY);
    cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
    return 0;
}

int ImageController::BrightnessControlFilter(const cv::Mat &img_orig, cv::Mat &img_new, int delta_bright,
                                             int width, int height)
 {


    cv::Mat img_sizer;
    if(img_orig.empty())
    {
        std::cout << "COULD NOT READ IMAGE" << std::endl;
        return -1;
    }
    img_orig.convertTo(img_sizer,-1,1, delta_bright - 150);
    cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
    return 0;
}

int ImageController::GammaCorrectionFilter(const cv::Mat &img_orig, cv::Mat &img_new, int gamma_cor, int width,int height)
{

    cv::Mat img_sizer;
    unsigned char lut[256];
    for (int i = 0; i < 256; i++)
    {
        lut[i] = cv::saturate_cast<uchar>(pow((float) (i / 255.0), gamma_cor) * 255.0f);
    }
    img_sizer = img_orig.clone();
    const int channels = img_sizer.channels();

    switch (channels)
    {
        case 1:
        {
            cv::MatIterator_<uchar> it, end;
            for (it = img_sizer.begin<uchar>(), end = img_sizer.end<uchar>(); it != end; it++)
            {
                *it = lut[(*it)];
            }

            cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
            return 0;
        }
        case 3:
        {
            cv::MatIterator_<cv::Vec3b> it, end;
            for (it = img_sizer.begin<cv::Vec3b>(), end = img_sizer.end<cv::Vec3b>(); it != end; it++)
            {
                (*it)[0] = lut[((*it)[0])];
                (*it)[1] = lut[((*it)[1])];
                (*it)[2] = lut[((*it)[2])];
            }
            cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
            return 0;
        }
        default:
            return -1;
    }
}
