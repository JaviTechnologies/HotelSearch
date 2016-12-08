//
//  address.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef address_hpp
#define address_hpp

#include <string>
#include <map>
#include "language.hpp"
#include "point.hpp"

namespace hotsearch
{
    /**
     * Address model implementation
     */
    class Address
    {
    public:
        // street
        std::string street;
        
        // city per language
        std::map<LANGUAGE, std::string> city;
        
        // state per language
        std::map<LANGUAGE, std::string> state;
        
        // country per language
        std::map<LANGUAGE, std::string> country;
        
        // zipcode
        std::string zipCode;
        
        // latitud, longitud
        Point location;
        
        // gets the address as a localized string
        std::string toLocalizedString(LANGUAGE lang);
    };
}

#endif /* address_hpp */
