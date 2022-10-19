#include <iostream>

#include <boost/log/trivial.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>

#include "src/controllers/ImageController.hpp"

/*int import_image()
{
    std::string const image_path = "/home/vivallo/Development/Datos II/OpenCVPOC/assets/mai.png";
    cv::Mat* img = &(cv::imread(image_path));
    cv::Mat* img_new;
    ImageController::GrayScaleFilter(img, img_new, 200, 200);
    cv::imshow("Result", img_new);
    cv::waitKey(0);
}*/

/*int main()
{
    BOOST_LOG_TRIVIAL(info) << "Image Processing API Started";
    //auto* server = new Server();
    //int const PORT = 9080;
    //import_image();
    return 0;
}*/
