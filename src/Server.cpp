#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"

#include "../src/handlers/ImageHandler.cpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>


#define PORT 9080

// Enums for filters
#define GAMMA 1
#define GAUSSIAN 2
#define BRIGHTNESS 3
#define GRAYSCALE 4

// Enums for instructions
#define ACCEPT_WIDTH 5
#define ACCEPT_HEIGHT 6
#define ACCEPT_BLOCK_WIDTH 7
#define ACCEPT_BLOCK_HEIGHT 8
#define ACCEPT_FILTER 9
#define ACCEPT_BRIGHT 10
#define ACCEPT_GAMMA 11
#define ACCEPT_IMAGE 12
#define APPLY_FILTER 13
#define CLOSE_SOCKET 14

namespace {

    std::string image_path = "/home/josev/CLionProjects/image-processing-apis/assets/jose.jpg";
    cv::Mat img = cv::imread(image_path);

    cv::Mat img_filter;
}

class Server {
private:
    //Variables used for the managing of sockets
    //some of this are used to connect the server with the client and 
    //other ones are used for the image passing from the client
    //to the server

    int Is_connecting, Socket_serverSS, LATEST_socket;
    struct sockaddr_in address_SERVER;
    int port_use, address_LENGTH;
    ImageHandler *image_accepted;
    int Filter_image, Size_of_image, Width_image, Height_image, Delta_image, GammaC_image;

public:
    Server() {
        port_use = 1;
        address_LENGTH = sizeof(address_SERVER); // get bytes len of address and assign
        image_accepted = new ImageHandler();
    }

    // Function that try to create a new server socket and configurate it
    int createServer() {
        // Try to create the file descriptor of server socket
        if ((Socket_serverSS = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            // Error message if fail
            cout << "Socket failed" << endl;
            exit(EXIT_FAILURE);
        }

        // Try to forcefully set the port socket to 8080
        if (setsockopt(Socket_serverSS, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &port_use, sizeof(port_use))) {
            // Error message if fail
            cout << "Error trying to set the socket parameters" << endl;
            exit(EXIT_FAILURE);
        }

        // Set the int attributes of address_SERVER struct
        address_SERVER.sin_family = AF_INET;
        address_SERVER.sin_addr.s_addr = INADDR_ANY;
        address_SERVER.sin_port = htons(PORT);

        // Try to export the configuration of address struct and bind it to the socket
        if (bind(Socket_serverSS, (struct sockaddr *) &address_SERVER, sizeof(address_SERVER)) < 0) {
            // Error message if fail
            cout << "Bind failed" << endl;
            exit(EXIT_FAILURE);
        }
        cout << ">>> Server successfully turned on <<<" << endl;

        // Try to put the server waiting for clients
        if (listen(Socket_serverSS, 3) < 0) {
            // Error message if fail
            cout << "Listen failed" << endl;
            exit(EXIT_FAILURE);
        }
        cout << ">>> Server waiting for connections <<<" << endl;

        // Accept the solicitude of a new client and create a specific socket for him
        if ((LATEST_socket = accept(Socket_serverSS, (struct sockaddr *) &address_SERVER,
                                    (socklen_t *) &address_LENGTH)) < 0) {
            // Error message if fail
            std::cout << "Accept failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        Is_connecting = true; // set in active the connection between server and client
        cout << ">> New client has connected <<" << endl;

        return 0;
    }

    // Hear a int from sockets
    int hearNum() {
        int value;
        int n = recv(LATEST_socket, &value, sizeof(value), 0);
        if (n < 0) {
            cout << "Receive failed" << endl;
            return -1;
        }
        return value;
    }


    // Hub of instruction (what server do if received a specific enum?)
    int hearMessages() {
        while (Is_connecting) {
            int value = hearNum();
            if (value == ACCEPT_FILTER) setFilter();
            if (value == ACCEPT_BRIGHT) setBright();
            if (value == ACCEPT_GAMMA) setGamma();
            if (value == ACCEPT_WIDTH) setWidth();
            if (value == ACCEPT_HEIGHT) setHeight();
            if (value == ACCEPT_BLOCK_WIDTH) setBlockWidth();
            if (value == ACCEPT_BLOCK_HEIGHT) setBlockHeight();
            if (value == ACCEPT_IMAGE) hearImage();
            if (value == APPLY_FILTER) applyFilter();
            if (value == CLOSE_SOCKET) Is_connecting = false;
        }
        return 0;
    }

    // All the next functions get int value from socket and save it where it corresponds
    int setFilter() {
        int value = hearNum();
        Filter_image = value;
        return 0;
    }

    int setBright() {
        int value = hearNum();
        Delta_image = value;
        return 0;
    }

    int setGamma() {
        int value = hearNum();
        GammaC_image = value;
        return 0;
    }

    int setWidth() {
        int value = hearNum();
        image_accepted->Width_image = value;
        return 0;
    }

    int setHeight() {
        int value = hearNum();
        image_accepted->Height_image = value;
        image_accepted->define_datavariables();
        return 0;
    }

    int setBlockWidth() {
        int value = hearNum();
        Width_image = value;
        return 0;
    }

    int setBlockHeight() {
        int value = hearNum();
        Height_image = value;
        return 0;
    }

    // Function that hear the image from client and save it
    int hearImage() {
        int bytes;
        Mat block = Mat::zeros(Height_image, Width_image,
                               CV_8UC3); // initialize the mat instance with the size of image
        Size_of_image = block.total() * block.elemSize(); // get the bit size of image
        uchar sockData[Size_of_image]; // Buffer where the pixels of the image are saved

        for (int i = 0; i < Size_of_image; i += bytes) {
            if ((bytes = recv(LATEST_socket, sockData + i, Size_of_image - i, 0)) ==
                -1) { // read the data and save it in buffer
                cout << "Receive failed" << endl;
                return -1;
            }
        }

        int ptr = 0;

        for (int i = 0; i < block.rows; ++i) { // Get the color information in the buffer and apply it to Mat instance
            for (int j = 0; j < block.cols; ++j) {
                block.at<cv::Vec3b>(i, j) = cv::Vec3b(sockData[ptr + 0], sockData[ptr + 1], sockData[ptr + 2]);
                ptr += 3;
            }
        }
        image_accepted->filter_Boxes.push_back(block);
        return 0;
    }

    // When all the blocks was received start to apply the filter
    int applyFilter() {
        int width = 300;
        int height = 300;
        cout << ">>> All blocks of the image successfully received <<<" << endl;

        image_accepted->makeimage_again(); // build the image
        image_accepted->Image_toShow("Image received by Server (Original Image)",
                                     image_accepted->image_FILTER); // show the remake image

        Mat *imagePtr = &(image_accepted->image_FILTER); // create pointers to use the API's
        Mat *filterImagePtr = &(image_accepted->image_FILTER);

        // Apply the respective filter
        /*if (Filter_image == GAMMA) ImageController::GammaCorrectionFilter(imagePtr, filterImagePtr, GammaC_image,Width_image ,height);
        if (Filter_image == GAUSSIAN) ImageController::GaussianBlurFilter(imagePtr,filterImagePtr,Width_image,Height_image);
        if (Filter_image == GRAYSCALE) ImageController::GrayScaleFilter(imagePtr,filterImagePtr,Width_image,Height_image);
        if (Filter_image == BRIGHTNESS) ImageController::BrightnessControlFilter(imagePtr,filterImagePtr,Delta_image,Width_image,Height_image);*/
        cout << ">>> The filter was successfully applied to your image <<<" << endl;

        image_accepted->Image_toShow("Image with filter (in server)",
                                     image_accepted->image_FILTER); // Show the filter image
        image_accepted->fragment_image(); // Create blocks of filter image

        //image->showVector(); // show all the blocks

        // send all the blocks to client
        for (int i = 0; i < image_accepted->orig_Boxes.size(); ++i) {
            sendImage(image_accepted->orig_Boxes[i]);
        }
        return 0;
    }

    // Function that send image through the socket
    int sendImage(Mat Image) {
        int bytes = 0;
        Size_of_image = Image.total() * Image.elemSize();
        bytes = send(LATEST_socket, Image.data, Size_of_image, 0); // send the image through the socket to client
        if (bytes < 0) { // Error code
            cout << "Error writing to socket" << endl;
            closeSocket();
        }
        return 0;
    }

    // Function that close the socket with the client
    int closeSocket() {
        // Closing the connected socket
        close(LATEST_socket);
        cout << ">>> The client socket was successfully closed <<<" << endl;
        return 0;
    }

    // Function that turn off the server socket
    int closeServer() {
        // Closing the listening socket
        shutdown(Socket_serverSS, SHUT_RDWR);
        cout << ">>> The server was successfully turned off <<<" << endl;
        return 0;
    }
};

// The main function create a new instance of server and initialize it
int main() {
    /*Server server;
    server.createServer();
    server.hearMessages();
    server.closeSocket();
    server.closeServer();*/


    ImageController imageController;
    int width = 400;
    int height = 400;

    cv::imshow("ORIGINAL IMAGE",img);
    cv::waitKey(0);

    //Grayscale Filter
    imageController.GrayScaleFilter(img,img_filter,width,height);
    cv::imshow("GrayScaleImage",img_filter);
    std::cout<<"Se aplica GrayScaleFilter"<<std::endl;
   /* cv::waitKey(0);*/

    //GaussianBlurFilter
    imageController.GaussianBlurFilter(img,img_filter,width-200,height-200);
    cv::imshow("GaussianBlurFilter",img_filter);
    std::cout<<"Se aplica GaussianBlurFilter"<<std::endl;
    /*cv::waitKey(0);*/


    //GammaCorrectionFilter
    imageController.GammaCorrectionFilter(img,img_filter,4,width,height);
    cv::imshow("GammaCorrectionFilter",img_filter);
    std::cout<<"Se aplica GammaCorrectionFilter"<<std::endl;
    /*cv::waitKey(0);*/


    //BrightnessControlFilter
    imageController.BrightnessControlFilter(img,img_filter,20,width,height);
    cv::imshow("BrightnessControlFilter",img_filter);
    std::cout<<"Se aplica BrightnessControlFilter"<<std::endl;
    /*cv::waitKey(0);*/
    cv::waitKey(0);
    return 0;
}

/*
Server::Server()
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor_(io_service,
                                             boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), this -> PORT));
    boost::asio::ip::tcp::socket socket_(io_service);

    BOOST_LOG_TRIVIAL(info) <<"Server initialized";
    acceptor_.accept(socket_);

    BOOST_LOG_TRIVIAL(info) <<"Client Connected";

    std::string message = ReadMessage(socket_);
    std::cout << "Client says: " + message << std::endl;

    auto return_message = "Este mensaje viene del servidor";

    SendMessage(socket_, return_message);
    BOOST_LOG_TRIVIAL(info) << "Message sent";
    socket_.close();
}

std::string Server::ReadMessage(boost::asio::ip::tcp::socket &socket)
{
    BOOST_LOG_TRIVIAL(info) <<"Reading message...";
    boost::asio::streambuf streamBuff;
    boost::asio::read_until(socket, streamBuff, "\n");
    std::string data = boost::asio::buffer_cast<const char *>(streamBuff.data());
    BOOST_LOG_TRIVIAL(info) << "Data: " + data;
    return data;
}

std::string Server::SendMessage(boost::asio::ip::tcp::socket &socket, const std::string &message)
{
    BOOST_LOG_TRIVIAL(info) <<"Sending message";
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message));
    BOOST_LOG_TRIVIAL(info) << "Message sent";
}*/
