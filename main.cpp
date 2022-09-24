#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
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
    imshow("Processed Image", img);
    cv::waitKey(0);
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    import_image(); 
    return 0;
}
