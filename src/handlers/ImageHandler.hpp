#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"

#ifndef IMAGE_PROCESSING_APIS_IMAGEHANDLER_HPP
#define IMAGE_PROCESSING_APIS_IMAGEHANDLER_HPP


class ImageHandler
{
public:
    std::string path;
    std::string filter;
    cv::Mat img;
    ImageHandler(auto path, auto filter);


    void ProcessImage(int filter);
    ImageHandler(std::string imgPATH);

    // imgSize --> size of bits of the image
    // imgWidth and imgHeight --> width and height in pixels of the image
    int Width_image, Height_image;

    // String with the local path of the image
    std::string path_of_image;

    // image and filterImage --> place where the image is saved
    cv::Mat image_ORIGINAL, image_FILTER;

    // size in pixels of any Box, also the last Box to
    int Box_WIDTH, Box_HEIGHT, last_Box_width, last_Box_height;

    // number of Boxes of any row and colum
    int Boxes_HORIZ,Boxes_VERTICAL;

    // Dinamic data structure that contends all the Boxes
    std::vector<cv::Mat> orig_Boxes,filter_Boxes;

    //Define variables from the same class
    int define_datavariables();
    //Method to show images from open cv library
    int Image_toShow(std::string windows, cv::Mat image_toshow);
    //Method to show all the Boxes made in a vector
    int Vector_toshow();

    //method to fragment image due to bandwidth restriction
    int fragment_image();

    //method to recreate image from fragmented to full
    int makeimage_again();

};


#endif //IMAGE_PROCESSING_APIS_IMAGEHANDLER_HPP