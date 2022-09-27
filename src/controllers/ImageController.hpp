#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ImageController
{
public:
    static cv::Mat GaussianBlur_Filter(const cv::Mat &img_orig, cv::Mat img_new, int width, int height);
    static cv::Mat GrayScale_Filter(const cv::Mat &img_orig, cv::Mat img_new,int width,int height);
    static cv::Mat BrightnessControl_Filter(const cv::Mat &img_orig, cv::Mat img_new,int delta_bright,int width,int height);
    static cv::Mat GammaCorrection_Filter(const cv::Mat &img_orig, cv::Mat img_new,int gamma_cor, int width,int height);
};