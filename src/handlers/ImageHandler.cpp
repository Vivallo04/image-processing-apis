
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "../controllers/ImageController.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ImageHandler {
public:
    // imgSize --> size of bits of the image
    // Width_image and imgHeight --> width and height in pixels of the image
    int Width_image, Height_image;

    // String with the local path of the image
    std::string path_of_image;

    // image and filterImage --> place where the image is saved
    cv::Mat image_ORIGINAL, image_FILTER;

    // size in pixels of any block, also the last block to
    int Box_WIDTH, Box_HEIGHT, last_Box_width, last_Box_height;

    // number of blocks of any row and colum
    int Boxes_HORIZ, Boxes_VERTICAL;

    // Dynamic data structure that contends all the blocks
    std::vector<cv::Mat> orig_Boxes, filter_Boxes;

    // Constructor for server side (the server do not have the image when the program starts)
    ImageHandler() {
        // Here you set the size of the blocks do you want
        Box_WIDTH = 100;
        Box_HEIGHT = 100;
    }

    // Constructor for client side (have the image when the program starts)
    ImageHandler(std::string imgPATH) {
        // Here you set the size of the blocks do you want
        Box_WIDTH = 100;
        Box_HEIGHT = 100;

        // Read the image given
        path_of_image = imgPATH;
        image_ORIGINAL = cv::imread(imgPATH, 1);
        if (!image_ORIGINAL.data) {
            std::cout << "NO IMAGE DATA RECEIVED" << std::endl;
            exit(0);

        }
        // Set the dimensions of the image
        Width_image = image_ORIGINAL.cols;
        Height_image = image_ORIGINAL.rows;

        define_datavariables();
    }

    // Function that defines some parameters of class (kind of builder pattern)
    int define_datavariables() {

        //Now we have to divide the image depending on the
        //size of the Boxes
        Boxes_HORIZ = (int) (Width_image / Box_WIDTH);
        Boxes_VERTICAL = (int) (Height_image / Box_HEIGHT);

        // Get the size of pixels of the last Box
        last_Box_width = Width_image % Box_WIDTH;
        last_Box_height = Height_image % Box_HEIGHT;

        // If the image have Boxes with different sizes (the last Boxes) we need to aggregate it to the number of Boxes
        if (last_Box_width != 0) Boxes_HORIZ++;
        if (last_Box_height != 0) Boxes_VERTICAL++;

        // initialize the filter image for later give it color
        image_FILTER = cv::Mat::zeros(Height_image, Width_image, CV_8UC3);
        return 0;
    }

    // Function that shows a specific image on the screen
    int Image_toShow(std::string windows, cv::Mat image_toshow) {
        cv::namedWindow(windows, cv::WINDOW_AUTOSIZE);
        cv::imshow(windows, image_toshow);
        cv::waitKey(0);
        return 0;

    }

    int Vector_toshow() {

        for (int i = 0; i < orig_Boxes.size(); ++i) {
            Image_toShow("Box #" + std::to_string(i + 1), orig_Boxes[i]);
        }
        return 0;
    }
    // Auxiliar function to show all the blocks in vector



    int fragment_image() {
        int xpos = 0, ypos = 0, bsizewidth, bsizeheight;
        for (int i = 0; i < Boxes_VERTICAL; ++i) { // Go through the number of vertical Boxes
            // Define the size of the y-axis cut
            if (i == (Boxes_VERTICAL - 1) && last_Box_height != 0) bsizeheight = last_Box_height;
            else bsizeheight = Box_HEIGHT;
            xpos = 0;
            for (int j = 0; j < Boxes_HORIZ; ++j) { // Go through the number of horizontal Boxes
                // Define the size of the x-axis cut
                if (j == (Boxes_HORIZ - 1) && last_Box_width != 0) bsizewidth = last_Box_width;
                else bsizewidth = Box_WIDTH;

                orig_Boxes.push_back(image_ORIGINAL(
                        Rect(xpos, ypos, bsizewidth, bsizeheight)).clone()); // make the Box and save it in vector
                xpos += Box_WIDTH;
            }
            ypos += Box_HEIGHT;
        }
        return 0;
    }


    int makeimage_again() {
        int xpos, ypos, temporaryx, temporaryy;
        for (int i = 0; i < filter_Boxes.size(); ++i) { // go through all the Boxes in the vector
            temporaryy = (int) i / Boxes_HORIZ;
            ypos = Box_HEIGHT * temporaryy;
            for (int j = 0; j < filter_Boxes[i].rows; ++j) { // go through the rows of the Box
                temporaryx = i % Boxes_HORIZ;
                xpos = Box_WIDTH * temporaryx;
                for (int k = 0; k < filter_Boxes[i].cols; ++k) { // go through the columns of the Box
                    cv::Vec3b pixel = filter_Boxes[i].at<cv::Vec3b>(j, k); // save the color of the Box pixel
                    image_FILTER.at<cv::Vec3b>(ypos, xpos) = pixel; // assign the color to filter image
                    xpos++;
                }
                ypos++;
            }
        }
        return 0;
    }
};
