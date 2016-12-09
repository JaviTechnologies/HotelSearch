//
//  main.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/2/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#include "hotsearchtests.hpp"

// for convenience
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

    return 0;
}
