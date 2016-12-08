//
//  address.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#include "address.hpp"

namespace hotsearch
{
    // gets the address as a localized string
    std::string Address::toLocalizedString(LANGUAGE lang)
    {
        return street + " " + city[lang] + " " + state[lang] + " " + country[lang] + " " + zipCode;
    }
}
