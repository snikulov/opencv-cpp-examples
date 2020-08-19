#include <fmt/format.h>
#include <opencv2/imgcodecs.hpp>

#include <filesystem>
#include <map>

int main(int argc, char** argv)
{
    namespace fs = std::filesystem;

    if (argc < 2)
    {
        fmt::print("Usage: {} <image file path>\n", fs::path{argv[0]}.filename().string());
        return -1;
    }

    std::string fpath{argv[1]};

    if (!fs::exists(fpath) || !fs::is_regular_file(fpath))
    {
        fmt::print("{}: not exists or not a file\n", fpath);
        return -2;
    }

    // check if we able to read those format...
    if (cv::haveImageReader(fpath))
    {
        // read image into cv::Mat
        auto img = cv::imread(fpath);

        if (!img.empty())
        {
            std::map<int, std::string> DEPTHMAP {
                {CV_8U,  "8-bit unsigned integers ( 0..255 )"},
                {CV_8S,  "8-bit signed integers ( -128..127 )"},
                {CV_16U, "16-bit unsigned integers ( 0..65535 )"},
                {CV_16S, "16-bit signed integers ( -32768..32767 )"},
                {CV_32S, "32-bit signed integers ( -2147483648..2147483647 )"},
                {CV_32F, "32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )"},
                {CV_64F, "64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )"}
            };

            // print out some info about file and cv::Mat produced with imread
            fmt::print("File OpenCV info\n================\n");
            fmt::print("File:\t\t{}\nSize:\t\t{} bytes\n", fpath, fs::file_size(fpath));
            fmt::print("Dimention:\t{}\n", img.dims);
            fmt::print("Num channels:\t{}\n", img.channels());
            fmt::print("Resolution:\t{} x {}\n", img.cols, img.rows);
            fmt::print("In-memory size:\t{} bytes\n", img.total()*img.elemSize());
            auto depth = img.depth();
            fmt::print("Depth:\t\t{}\n", DEPTHMAP.count(depth) ? DEPTHMAP[depth] : "Unknown");

            return 0;
        }
        else
        {
            fmt::print("{}: unable to read\n", fpath);
            return -3;
        }
    }
    fmt::print("{}: unsupported format\n", fpath);
    return -4;
}

