#include "utils.hpp"
#include <iostream>

using namespace std;

Arguments::Arguments(int argc, char** argv)
{
    valid = argc > 1;
    if (valid) {
        for (auto c = 0; c < argc; ++c) {
            if (!strcmp(argv[c], HELP_ARG.c_str())) {
                print_help();
                help = true;
                return;
            }
            if (!strcmp(argv[c], CONFIDENCE_ARG.c_str())) {
                if (++c < argc) {
                   confidence = stof(argv[c]);
                    continue;
                }
                valid = false;
                cout << "ERROR: Confidence value not found!" << endl;
                break;
            }
            has_caffee = strcmp(argv[c], CAFFEE_ARG.c_str()) == 0;
            if (!has_caffee)
                has_tensorflow = strcmp(argv[c], TENSORFLOW_ARG.c_str()) == 0;
            if (!strcmp(argv[c], SAVE_IMAGE_ARG.c_str())) {
                if (++c < argc)
                    saved_image_path = argv[c];
                continue;
            }
            image = argv[c];
        }
        valid = !image.empty();
    }
}

void print_help() noexcept
{
    cout << "Usage: " << PROGRAMM_NAME << " [option | value ] " << "/path/to/image \n"
         << "Options: \n"
         << "   --help                      Display this information.\n"
         << "   --save [/path/to/save]      Save result to the image.\n"
         << "   --confidence [0.1 - 0.9]    Set confidence.\n"
         << "   --caffee                    Use caffee face model.\n"
         << "   --tensorflow                Use tensorflow face model. Not working at the moment.\n"
         << "Example: \n"
         << "   " << PROGRAMM_NAME << " --caffee image-with-people.jpg" << endl;
}
