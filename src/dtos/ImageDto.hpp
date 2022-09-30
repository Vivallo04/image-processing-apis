#ifndef IMAGE_PROCESSING_APIS_IMAGEDTO_HPP
#define IMAGE_PROCESSING_APIS_IMAGEDTO_HPP


class ImageDTO
{
public:
    ImageDTO(char* path, char* filter);
    const char *getPath() const;
    void setPath(const char *path);
    const char *getFilter() const;
    void setFilter(const char *filter);
private:
    const char* path;
    const char* filter;
};


#endif //IMAGE_PROCESSING_APIS_IMAGEDTO_HPP
