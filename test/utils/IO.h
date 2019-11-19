#pragma once

#include <string>
#include <entities/entrypoint/InputCVRP.h>

class IO {
public:
    static InputCVRP fileToInputCVRP(std::string file_path);
};