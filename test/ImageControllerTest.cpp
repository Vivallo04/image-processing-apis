#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>

#include "gtest/gtest.h"
#include "opencv2/imgproc.hpp"


int GaussianBlur_Filter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height)
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

int GrayScaleFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height)
{
    cv::Mat img_sizer;
    cv::Mat();
    if(img_orig.empty())
    {
        std::cout << "COULD NOT READ IMAGE" << std::endl;
        return -1;
    }
    cvtColor(img_orig,img_sizer,cv::COLOR_BGR2GRAY);
    cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
    return 0;
}

int BrightnessControlFilter(const cv::Mat &img_orig, cv::Mat &img_new, int delta_bright,
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

int GammaCorrectionFilter(const cv::Mat &img_orig, cv::Mat &img_new, int gamma_cor, int width, int height)
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

// Tests --------------------------------------------------------
const std::string happy_path = "/home/vivallo/Development/Datos II/image-processing-apis/assets/naruto.png";
TEST(GrayScaleFilterTest, Handlesemptyimage)
{
    // Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    // Arrange
    auto actual = GrayScaleFilter(img, img_new, 300, 300);

    // Assert
    EXPECT_EQ(actual, 0);
}

TEST(GaussianBlurFilterTest, Handlesemptyimage)
{
    //Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    //Arrange
    auto actor=GaussianBlur_Filter(img,img_new,300,300);

    // Assert
    EXPECT_EQ(actor,0);
}

TEST(GammaCorrectionFilterTest, Handlesemptyimage)
{
    // Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    // Arrange
    auto actual= GammaCorrectionFilter(img, img_new, 2.54, 300, 300);

    // Assert
    EXPECT_EQ(actual, -1);
}

TEST(BrightnessControlFilterTest, Handlesemptyimage)
{
    // Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    // Arrange
    auto actual= BrightnessControlFilter(img, img_new, 50, 300, 300);

    // Assert
    EXPECT_EQ(actual, 0);
}