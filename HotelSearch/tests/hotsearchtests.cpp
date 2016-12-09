//
//  hotsearchtests.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#include "hotsearchtests.hpp"

using namespace std::chrono;

/**
 * Tests Implementation
 */

void printHotel(hotsearch::Hotel* hotel)
{
//    cout << "---" << endl;
    cout << hotel->id << "\t";
    cout << hotel->rank << endl;
//    cout << hotel->name[hotsearch::LANGUAGE::EN] << endl;
//    cout << hotel->address.city[hotsearch::LANGUAGE::EN] << "\t";
//    cout << hotel->address.location << endl;
}

void printHotel(hotsearch::Hotel hotel)
{
    printHotel(&hotel);
}

/**
 * runSearchByNameTests
 * Runs tests over searching by name.
 */
void runSearchByNameTests(hotsearch::HotelSearchEngine& searchEngine)
{
    std::string searchInput = "Plaza";
    
    // DEBUG: timing
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    set<hotsearch::Hotel> results = searchEngine.searchHotelByName(searchInput);
    
    // print results
    for(set<hotsearch::Hotel>::iterator it = results.begin(); it != results.end(); it++)
    {
        printHotel(*it);
    }
    
    cout << endl;
    
    // DEBUG: timing
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    
    cout << "found " << results.size() << " Hotels by name in " << duration << " millisecs.\n\n";
}

/**
 * runSearchByAddressTests
 * Runs tests over searching by address: street names, city, zip code, ...
 */
void runSearchByAddressTests(hotsearch::HotelSearchEngine& searchEngine)
{
    std::string searchInput = "Paris";
    
    // DEBUG: timing
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    set<hotsearch::Hotel> results = searchEngine.searchHotelByAddress(searchInput);
    
    // print results
    for(set<hotsearch::Hotel>::iterator it = results.begin(); it != results.end(); it++)
    {
        printHotel(*it);
    }
    
    cout << endl;
    
    // DEBUG: timing
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    
    cout << "found " << results.size() << " Hotels by address in " << duration << " millisecs.\n\n";
}

/**
 * runSearchByGeolocationTests
 * Runs tests over searching by latitude and longitude
 */
void runSearchByGeolocationTests(hotsearch::HotelSearchEngine& searchEngine)
{
    // TODO: add more tests. For now tests are manual.
    // "id": 100216
    float latitude = 38.723953f;
    float longitude = -9.148317f;
    
    // DEBUG: timing
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    set<hotsearch::Hotel> results = searchEngine.searchHotelByGeolocation(latitude, longitude);
    
    // print results
    for(set<hotsearch::Hotel>::iterator it = results.begin(); it != results.end(); it++)
    {
        printHotel(*it);
    }
    
    cout << endl;
    
    // DEBUG: timing
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    
    cout << "found " << results.size() << " Hotels by location in " << duration << " millisecs.\n\n";
}
