#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>
#include "../src/controllers/ImageController.hpp"

#include "gtest/gtest.h"
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"
//#include "controllers/ImageController.hpp"


#include "gtest/gtest.h"

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

int GrayScale_Filter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height) {
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

int BrightnessControl_Filter(const cv::Mat &img_orig, cv::Mat &img_new, int delta_bright, int width,
                             int height) {
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

int GammaCorrection_Filter(const cv::Mat &img_orig, cv::Mat &img_new, int gamma_cor, int width,int height) {
    {
        cv::Mat img_sizer;
        unsigned char lut[256];
        for (int i = 0; i < 256; i++) {
            lut[i] = cv::saturate_cast<uchar>(pow((float) (i / 255.0), gamma_cor) * 255.0f);
        }

        img_sizer = img_orig.clone();
        const int channels = img_sizer.channels();
        switch (channels) {
            case 1: {
                cv::MatIterator_<uchar> it, end;
                for (it = img_sizer.begin<uchar>(), end = img_sizer.end<uchar>(); it != end; it++) {
                    *it = lut[(*it)];
                }
                cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
                return 0;
                break;

            }
            case 3: {
                cv::MatIterator_<cv::Vec3b> it, end;
                for (it = img_sizer.begin<cv::Vec3b>(), end = img_sizer.end<cv::Vec3b>(); it != end; it++) {
                    (*it)[0] = lut[((*it)[0])];
                    (*it)[1] = lut[((*it)[1])];
                    (*it)[2] = lut[((*it)[2])];
                }
                cv::resize(img_sizer,img_new, cv::Size(width,height),cv::INTER_LINEAR);
                return 0;
                break;
            }
            default:
                return -1;
        }
    }


}

//Arrange
/*imageController.GrayScale_Filter(img,img_new,300,300);
imageController.GaussianBlur_Filter(img,img_new,300,300);
imageController.GammaCorrection_Filter(img,img_new,2.34,300,300);
imageController.BrightnessControl_Filter(img,img_new,50,300,300);
*/

//Assert


TEST(GrayScale_FilterTest, Handlesemptyimage) {
    //Act

    std::string const image_path = "../assets/naruto.png";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    //Arrange
    //auto actor=imageController.GrayScale_Filter(img,img_new,300,300);

    //Assert
    EXPECT_EQ(GrayScale_Filter(img,img_new,300,300),0);
}

TEST(GaussianBlur_FilterTest, Handlesemptyimage) {
    //Act

    std::string const image_path = "../assets/naruto.png";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    //Arrange
    auto actor=GaussianBlur_Filter(img,img_new,300,300);

    EXPECT_EQ(actor,0);
}

TEST(GammaCorrection_FilterTest, Handlesemptyimage) {
    //Act

    std::string const image_path = "../assets/naruto.png";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    //Arrange
    auto actor=GammaCorrection_Filter(img,img_new,2.54,300,300);

    EXPECT_EQ(actor,-1);

}

TEST(BrightnessControl_FilterTest, Handlesemptyimage) {
    //Act

    std::string const image_path = "../assets/naruto.png";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    //Arrange
    auto actor=BrightnessControl_Filter(img,img_new,50,300,300);

    EXPECT_EQ(actor, 0);
}

TEST(Suma, sumatest)
{
    int a = 3;
    int b = 3;
    EXPECT_EQ(a+b, 6);
}