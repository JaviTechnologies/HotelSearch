//
//  hotsearchutils.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/7/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef hotsearchutils_hpp
#define hotsearchutils_hpp

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "hotel.hpp"
#include "json.hpp"


namespace hotsearch
{
    namespace utils
    {
        // void tokenizeLine(const string &str, char delim, vector<string> &tokens) const:
        // ---
        // Divides a string phrase into unique unsorted string tokens
        // TODO: remove blacklist words
        static void tokenizeString(const std::string &str, char delim, std::vector<std::string> &tokens) __attribute__ ((unused));
        
        // json parseJSONFile(string path):
        // ---
        // Returns a json object parsed from a file
        static nlohmann::json parseJSONFile(std::string path) __attribute__ ((unused));
        
        static Point createPointFromString(std::string location) __attribute__ ((unused));
        
        // Hotel createHotelFromJSON(json jh):
        // ---
        // Returns a localized Hotel created from a json data
        static Hotel createHotelFromJSON(nlohmann::json jh) __attribute__ ((unused));
        
        
        static void tokenizeString(const std::string &str, char delim, std::vector<std::string> &tokens)
        {
            std::stringstream ss;
            ss.str(str);
            std::string item;
            
            while (std::getline(ss, item, delim))
            {
                if (item.empty())
                    continue;
                
                if (std::find(tokens.begin(), tokens.end(), item) == tokens.end())
                    tokens.push_back(item);
            }
        }
        
        static nlohmann::json parseJSONFile(std::string path)
        {
            nlohmann::json j;
            
            std::ifstream jsonFile(path);
            jsonFile >> j;
            jsonFile.close();
            
            return j;
        }
        
        static Point createPointFromString(std::string location)
        {
            Point p;
            
            std::vector<std::string> tokens;
            utils::tokenizeString(location, ',', tokens);
            
            std::vector<std::string>::iterator it = tokens.begin();
            p.x = std::stof(it->c_str());
            p.y = std::stof((++it)->c_str());
            
            return p;
        }
        
        static Hotel createHotelFromJSON(nlohmann::json jh)
        {
            Hotel hotel;
            
            hotel.id    = jh["id"].get<long>();
            hotel.rank  = jh["rank"].get<double>();
            
            // address
            Address address;
            address.location = createPointFromString(jh["geo_location"]);
            
            hotel.address = address;
            
            for (LANGUAGE lang : LanguageUtils::LANGUAGE_LIST)
            {
                std::string l = LanguageUtils::getLanguageAsString(lang);
                
                // name
                if (jh["name_" + l] != nullptr)
                    hotel.name.insert(std::make_pair(lang, jh["name_" + l].get<std::string>()));
                
                // description
                
                // address city
                if (jh["city_" + l] != nullptr)
                    hotel.address.city.insert(std::make_pair(lang, jh["city_" + l].get<std::string>()));
            }
            
            return hotel;
        }
    };
}

#endif /* hotsearchutils_hpp */
