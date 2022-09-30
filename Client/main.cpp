#include <QApplication>
#include <QPushButton>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/cuda.hpp>
#include "opencv2/imgproc.hpp"
#include "../src/handlers/ImageHandler.hpp"
#include "../src/controllers/ImageController.hpp"



//Now we are going to make some constant values in order to achieve our goal which is
//moving the image through the sockets

//We must get the number of the filters that are going to be made by the imageController
#define GAMMA 1
#define GAUSSIAN 2
#define BRIGHTNESS 3
#define GRAYSCALE 4

//We must get the number of the actions that we are going to make
#define TAKES_WIDTH 5
#define TAKES_HEIGHT 6
#define TAKES_BLOCK_WIDTH 7
#define TAKES_BLOCK_HEIGHT 8
#define TAKES_FILTER 9
#define TAKES_BRIGHT 10
#define TAKES_GAMMA 11
#define TAKES_IMAGE 12
#define APPLY_FILTER 13
#define CLOSE_SOCKET 14



class ClientSocket {
private:

    // Basic parameters of the image and blocks
    int Size_image, width_block, height_box;

    // Instance of the class that manipulate the image
    ImageHandler *image_taken;

public:
    // Variables that save the data given by the user
    int filter, brightness, gamma;

    ClientSocket(std::string imgPATH) { //constructor method
        //newSocket = 0;
        image_taken = new ImageHandler(imgPATH);
        image_taken->fragment_image(); // start the pagination of the image
    }


//Function to take the filter of an image
    int Filter_choosingclient() {
        // Get the filter and save it
        std::string message;
        int answer;
        std::cout << ">>> Type the number of the filter do tou want to apply to your image <<<" << std::endl;
        std::cout << "1) Gamma Filter  2) Gaussian Filter  3) Brightness Control  4) Gray Scale" << std::endl;
        getline(std::cin, message);
        answer = stoi(message);
        filter = answer;

        // If the filter its equal to bright control we need to ask the level of bright
        if (filter == BRIGHTNESS) {
            std::cout
                    << ">>> In a scale of 1 to 300 (150 its the same bright) how much brightness do you want to apply to your image <<<"
                    << std::endl;
            std::string bright_message;
            int bright_int;
            getline(std::cin, bright_message);
            bright_int = stoi(bright_message);
            brightness = bright_int;
        }

        // If the filter its equal to gamma correction we need to ask the level gamma
        if (filter == GAMMA) {
            std::cout << ">>> In a scale of 1 to 3 define the gamma value you want to apply to your image <<<" << std::endl;
            std::string gamma_message;
            int gamma_int;
            getline(std::cin, gamma_message);
            gamma_int = stoi(gamma_message);
            gamma = gamma_int;
        }

        //filterProtocol(filter); //Start the comunication with server
        return 0;
    }


};






int main(int argc, char *argv[])
{
    //Take image path from client
    std::string imgPath;

    std::cout<<"Enter the path of your image \n";
    std::getline(std::cin,imgPath);



    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    boost::system::error_code error;
    boost::asio::streambuf receive_buffer;
    const std::string outMessage = "Hola, soy el cliente\n";

    const int PORT = 9080;

    socket.connect(boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), PORT));
    std::cout << "Conectado al servidor" << std::endl;

    boost::asio::write(socket, boost::asio::buffer(outMessage), error );

    if(!error)
    {
        std::cout << "Mensaje enviado" << std::endl;
    }
    else
    {
        std::cout << "error" << error.message() << std::endl;
    }

    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

    if (error && error != boost::asio::error::eof)
    {
        std::cout << "error" << error.message() << std::endl;
    }
    else
    {
        const char* inMessage = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << "Servidor dice: " + (std::string) inMessage << std::endl;
    }
    
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
