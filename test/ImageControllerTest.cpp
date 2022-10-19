#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>

#include "gtest/gtest.h"

#include ".././src/controllers/ImageController.hpp"


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
    auto sut = ImageController::GrayScaleFilter(img, img_new, 300, 300);

    // Assert
    EXPECT_EQ(sut, 0);
}

TEST(GaussianBlurFilterTest, Handlesemptyimage)
{
    //Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    //Arrange
    auto sut= ImageController::GaussianBlurFilter(img,img_new,300,300);

    // Assert
    EXPECT_EQ(sut, 0);
}

TEST(GammaCorrectionFilterTest, Handlesemptyimage)
{
    // Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    // Arrange
    auto sut= ImageController::GammaCorrectionFilter(img, img_new, 2.54, 300, 300);

    // Assert
    EXPECT_EQ(sut, 0);
}

TEST(BrightnessControlFilterTest, Handlesemptyimage)
{
    // Act
    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_error;
    cv::Mat img_new;

    // Arrange
    auto sut= ImageController::BrightnessControlFilter(img, img_new, 50, 300, 300);

    // Assert
    EXPECT_EQ(sut, 0);
}