//
// Created by josev on 19/09/22.
//
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class filtersAPIS{

    public:
        static Mat GaussianBlur_Filter(Mat img_orig,Mat img_new,int o);
        static Mat GrayScale_Filter(Mat img_orig,Mat img_new);
        static Mat BrightnessControl_Filter(Mat img_orig,Mat img_new,int contrast,int bright);
        static Mat GammaCorrection_Filter(Mat img_orig,Mat img_new,int gamma_cor);
private:
    static Mat ShowImages(Mat img_new);

};


#ifndef PROYECTOPRUEBA_FILTERSAPIS_H
#define PROYECTOPRUEBA_FILTERSAPIS_H

#endif //PROYECTOPRUEBA_FILTERSAPIS_H
