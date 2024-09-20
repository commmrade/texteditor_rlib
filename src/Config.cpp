#include "Config.hpp"
#include <string>



Config::Cfg Config::parse(const std::string &path)
    {
        Cfg config;

        std::ifstream file;
        file.open(path);

        if(file.is_open())
        {
            std::string line;
            //printf("opened\n");
            while (std::getline(file, line))
            {
                if (line.contains("#")) { //Means line is commented
                    continue;
                } else if (line.contains("font")) { 
                    if (line.find("=") != std::string::npos) {
                        std::string font = line.substr(line.find("=") + 1);
                        int var = atoi(font.c_str());
                        if (var != 0) {
                            config.fontSize = atoi(font.c_str());
                        }    
                    }
                } else if (line.contains("spacing")) {
                    if (line.find("=") != std::string::npos) {
                        std::string spacing = line.substr(line.find("=") + 1);
                        int var = atoi(spacing.c_str());
                        if (var != 0) {
                            config.spacing = var;
                        }
                    }
                } else if (line.contains("path")) {
                    if (line.find("=") != std::string::npos) {
                        std::string path = line.substr(line.find("=") + 1);
                        config.fontPath = path;
                    }
                } else if (line.contains("scroll_step")){
                    if (line.find("=") != std::string::npos) {
                        std::string scroll_step_s = line.substr(line.find("=") + 1);
                        int var = atoi(scroll_step_s.c_str());
                        if (var != 0) {
                            config.scroll_step = atoi(scroll_step_s.c_str());
                        }
                    }
                }
            }
        }

        return config;
    }