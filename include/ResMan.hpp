#ifndef SV_RESOURCE_MANAGGER_HPP
#define SV_RESOURCE_MANAGER_HPP
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace sv
{
    template<typename T>
    class ResMan
    {
        std::map<std::string, T> data;

        public:
        ResMan() : data()
        {
            
        }

        /*
        *
        }*/
        const T& get(const std::string& path)
        {            
            if (data.find(path) == data.end())
            {
                data.insert({ path, T() });
                data[path].loadFromFile(path);
            }
            return data.at(path);            
        }
    };
}
#endif
