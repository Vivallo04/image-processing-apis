#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include "src/Server.hpp"


int import_image()
{
    std::string const image_path = "/home/vivallo/Development/Datos II/OpenCVPOC/assets/mai.png";
    cv::Mat img = cv::imread(image_path);
    if(img.empty())
    {
        std::cout << "COULD NOT READ IMAGE" << std::endl;
        return 1;
    }
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    auto* server = new Server;
    //import_image();
    return 0;
}
