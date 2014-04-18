#ifndef SV_HANGMAN_UTIL_HPP
#define SV_HANGMAN_UTIL_HPP
#include <string>

namespace sv
{
    namespace util
    {
        /*
        *
        */
        std::string get_http_data(const std::string& server, const std::string& file);

        /*
        *
        */
        void init_words(std::string& correct_word, std::string& out_word);
    }
}
#endif
