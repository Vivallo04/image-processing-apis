#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include "src/controllers/ImageController.hpp"
//#include "src/controllers/ImageController.cpp"



int import_image()
{
    std::string const image_path = "/home/josev/CLionProjects/image-processing-apis/assets/mai.png";
    cv::Mat img = cv::imread(image_path);
    if(img.empty())
    {
        std::cout << "COULD NOT READ IMAGE" << std::endl;
        return -1;
    }
    imshow("Processed Image", img);
    cv::waitKey(0);
}

int main()
{
    std::string const image_path = "../assets/mai.png";
    cv::Mat img = cv::imread(image_path);
    cv::Mat img_new;
    ImageController jose;
    jose.GrayScale_Filter(img,img_new,200,200);
    cv::imshow("Display image",img_new);
    cv::waitKey(0);
    return 0;
}
