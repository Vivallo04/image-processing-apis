#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ImageController
{
public:
    static int GaussianBlur_Filter(const cv::Mat &img_orig, cv::Mat &img_new, int width, int height);
    static int GrayScale_Filter(const cv::Mat &img_orig, cv::Mat &img_new,int width,int height);
    static int BrightnessControl_Filter(const cv::Mat &img_orig, cv::Mat &img_new,int delta_bright,int width,int height);
    static int GammaCorrection_Filter(const cv::Mat &img_orig, cv::Mat &img_new,int gamma_cor, int width,int height);

private:
    
};