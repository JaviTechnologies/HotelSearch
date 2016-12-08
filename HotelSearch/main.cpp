//
//  main.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/2/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

//#include <iostream>
#include "hotsearchtests.hpp"

// for convenience
//using namespace nlohmann;   // json
using namespace std;        // standard
using namespace hotsearch;  // hotel search



int main(int argc, const char * argv[])
{
    // create search engine
    HotelSearchEngine searchEngine;
    searchEngine.loadDataFromJSONFile("/Users/jcampos/Documents/Projects/HotelSearch/hotels.json");
    
    // start search engine
//    runSearchByNameTests(searchEngine);
    
//    runSearchByAddressTests(searchEngine);
    
    runSearchByGeolocationTests(searchEngine);
    
//    while (true)
//    {
//        cout << "Search: ";
//        getline(cin,searchInput);
//        
//        if (searchInput.empty() || cin.eof())
//            break;
//        
//        // DEBUG: timing
//        high_resolution_clock::time_point t1 = high_resolution_clock::now();
//
//        
//        // DEBUG: timing
//        high_resolution_clock::time_point t2 = high_resolution_clock::now();
//        double duration = duration_cast<milliseconds>( t2 - t1 ).count();
//        
//        cout << "found " << results.size() << " Hotels in " << duration << " millisecs.\n\n";
//    }
    
    return 0;
}
