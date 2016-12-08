//
//  hotsearchtests.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef hotsearchtests_hpp
#define hotsearchtests_hpp


#include <string>
#include "hotel.hpp"
#include "hotsearch.hpp"

/**
 * runSearchByNameTests
 * Runs tests over searching by name.
 */
void runSearchByNameTests(hotsearch::HotelSearchEngine& searchEngine);

/**
 * runSearchByAddressTests
 * Runs tests over searching by address: street names, city, zip code, ...
 */
void runSearchByAddressTests(hotsearch::HotelSearchEngine& searchEngine);

/**
 * runSearchByGeolocationTests
 * Runs tests over searching by latitude and longitude
 */
void runSearchByGeolocationTests(hotsearch::HotelSearchEngine& searchEngine);

/**
 * printHotel
 * Prints an hotel to the standard output
 */
void printHotel(hotsearch::Hotel* hotel);


#endif /* hotsearchtests_hpp */
