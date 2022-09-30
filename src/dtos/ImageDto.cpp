#include "ImageDto.hpp"

ImageDTO::ImageDTO(char *path, char *filter)
{
    this -> path = path;
    this -> filter = filter;
}

const char *ImageDTO::getPath() const
{
    return path;
}

void ImageDTO::setPath(const char *path)
{
    ImageDTO::path = path;
}

const char *ImageDTO::getFilter() const
{
    return filter;
}

void ImageDTO::setFilter(const char *filter)
{
    ImageDTO::filter = filter;
}


