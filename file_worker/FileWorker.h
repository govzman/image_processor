#include <cstdint>
#include <vector>
#include "../Image.h"

class FileWorker {
public:
    Image Read(const std::string& path) const;
    void Write(const std::string& path, const Image& image) const;
};
