#include <iostream>
#include "src/Server.hpp"

#include <boost/log/trivial.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>



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

/*

int main()
{
    BOOST_LOG_TRIVIAL(info) << "Image Processing API Started";
    auto* server = new Server();
    int const PORT = 9080;
    return 0;
}
*/
