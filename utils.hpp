#ifndef UTILS_H
#define UTILS_H

#include "constants.hpp"
#include <string>

class Arguments
{
public:
    explicit Arguments(int argc, char** argv);
    ~Arguments() = default;
    Arguments(Arguments&&) = delete;
    Arguments(const Arguments&) = delete;

    Arguments& operator=(Arguments&&) = delete;
    Arguments& operator=(const Arguments&) = delete;

    inline bool is_valid() const noexcept { return valid; }

    inline bool show_help() const noexcept { return help; }
    
    inline bool has_confidence() const noexcept { return confidence != DEFAULT_CONFIDENCE && confidence >= 0; }
    inline float get_confidence() const noexcept { return confidence; }
    inline bool caffee() const noexcept { return has_caffee; }
    inline bool tensorflow() const noexcept { return has_tensorflow; }
    inline std::string image_path() const noexcept { return image; }
    inline bool has_saved_path() const noexcept { return !saved_image_path.empty(); }
    inline std::string saved_image_index() const noexcept { return saved_image_path; }
    
private:
    bool help{false};
    float confidence{DEFAULT_CONFIDENCE};
    bool has_caffee{false};
    bool has_tensorflow{false};
    std::string image;
    std::string saved_image_path{""};
    bool valid{true};
};

void print_help() noexcept;

#endif // UTILS_H
