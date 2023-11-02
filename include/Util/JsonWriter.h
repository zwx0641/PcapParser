#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <typeinfo>

namespace Util
{

class JsonWriter
{

  public:
    JsonWriter() = default;

    JsonWriter(const std::string_view jsonPath)
    {
        json_.open(jsonPath.data(), std::ios::out);

        if (!json_.is_open())
        {
            throw std::runtime_error("Unable to open output file");
        }
    }

    ~JsonWriter()
    {
        json_.close();
    }

    void write(const std::string &output)
    {
        json_.write(output.c_str(), output.size());
    }

  private:
    std::ofstream json_;
};

} // namespace Util