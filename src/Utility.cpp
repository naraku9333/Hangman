#include <Utility.hpp>
#include <algorithm>
#include <boost/asio.hpp>

namespace sv
{
    namespace util
    {
        std::string get_http_data(const std::string& server, const std::string& file)
        {
            try
            {
                boost::asio::ip::tcp::iostream sock(server, "http");
                sock.expires_from_now(boost::posix_time::seconds(60));

                if (!sock){ throw "Unable to connect: " + sock.error().message(); }

                // ask for the file
                sock << "GET /" << file << " HTTP/1.0\r\n" << "Host: "
                    << server << "\r\n" << "Accept: */*\r\n" << "Connection: close\r\n\r\n";

                // Check that response is OK.
                std::string http_version;
                unsigned int status_code;
                sock >> http_version >> status_code;

                std::string status_message;
                std::getline(sock, status_message);
                if (!sock && http_version.substr(0, 5) != "HTTP/"){ throw "Invalid response\n"; }
                if (status_code != 200){ throw "Response returned with status code " + status_code + status_message; }

                // Process the response headers, which are terminated by a blank line.
                std::string header;
                while (std::getline(sock, header) && header != "\r"){}

                std::string tmp;
                std::getline(sock, tmp, '\r');
                return tmp;// std::string(tmp.begin(), tmp.end() - 2); //strip trailing \r\n
            }
            catch (std::exception& e)
            {
                return e.what();
            }
        }

        void init_words(std::string& correct_word, std::string& out_word)
        {
            correct_word.clear();
            while ((correct_word = get_http_data("randomword.setgetgo.com", "get.php")).length() < 5){}
            out_word.clear();
            std::replace_copy_if(correct_word.begin(), correct_word.end(), std::back_inserter(out_word), ::isalpha, '*');
            std::cout << correct_word << " " << out_word << std::endl;
        }

    }
}
