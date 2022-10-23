#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ImageController
{
public:
    int static GaussianBlurFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height);
    int static GrayScaleFilter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height);
    int static BrightnessControlFilter(const cv::Mat &img_orig, cv::Mat &img_new, int delta_bright, int width, int height);
    int static GammaCorrectionFilter(const cv::Mat &img_orig, cv::Mat &img_new, int gamma_cor, int width, int height);
};