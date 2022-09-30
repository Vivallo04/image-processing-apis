#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ImageController
{
public:
    static int GaussianBlurFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height);
    static int GrayScaleFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height);
    static int BrightnessControlFilter(const cv::Mat &img_orig, cv::Mat &img_new, int delta_bright, int width, int height);
    static int GammaCorrectionFilter(const cv::Mat &img_orig, cv::Mat &img_new, int gamma_cor, int width,int height);
};