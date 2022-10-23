#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>

#include <gmock/gmock-spec-builders.h>
#include "gtest/gtest.h"

#include "mocks/MockImageController.cpp"

using ::testing::AtLeast;

// Tests --------------------------------------------------------
TEST(BrightnessControlFilterTest, ChangesBrightness)
{
    // Act
    MockImageController mockImageController;
    const std::string happy_path = "/home/vivallo/Development/Datos II/image-processing-apis/assets/mai.png";

    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;

    // Arrange + Assert
    EXPECT_EQ(mockImageController.BrightnessControlFilter(img, img_new, 50, 300, 300), 0);
}

TEST(GaussianFilterTest, ChangesOpacity)
{
    // Act
    MockImageController mockImageController;
    const std::string happy_path = "/home/vivallo/Development/Datos II/image-processing-apis/assets/mai.png";

    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;

    // Arrange + Assert
    EXPECT_EQ(mockImageController.GaussianBlurFilter(img, img_new, 300, 300), 0);
}

TEST(GrayScaleFilterTest, ChangesToGrayScale)
{
    // Act
    MockImageController mockImageController;
    const std::string happy_path = "/home/vivallo/Development/Datos II/image-processing-apis/assets/mai.png";

    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;

    // Arrange + Assert
    EXPECT_EQ(mockImageController.GrayScaleFilter(img, img_new, 300, 300), 0);
}

TEST(GammaCorrectionFilterTest, ChangesGamma)
{
    // Act
    MockImageController mockImageController;
    const std::string happy_path = "/home/vivallo/Development/Datos II/image-processing-apis/assets/mai.png";

    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;

    // Arrange + Assert
    EXPECT_EQ(mockImageController.GammaCorrectionFilter(img, img_new, 50, 300, 300), 0);
}

TEST(AllFiltersTest, ChangesAllFilters)
{
    // Act
    MockImageController mockImageController;
    const std::string happy_path = "/home/vivallo/Development/Datos II/image-processing-apis/assets/mai.png";

    std::string const image_path = happy_path;
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;

    // Arrange + Assert
    EXPECT_EQ(mockImageController.GammaCorrectionFilter(img, img_new, 50, 300, 300), 0);
    EXPECT_EQ(mockImageController.BrightnessControlFilter(img, img_new, 50, 300, 300), 0);
    EXPECT_EQ(mockImageController.GaussianBlurFilter(img, img_new, 300, 300), 0);
    EXPECT_EQ(mockImageController.GrayScaleFilter(img, img_new, 300, 300), 0);
}
