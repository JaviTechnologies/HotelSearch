//
//  hotsearch.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/5/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "hotsearch.hpp"
#include "language.hpp"
#include "hotsearchutils.hpp"

// for convenience
using namespace nlohmann;       // json
using namespace std;            // standard
using namespace std::chrono;    // chrono

namespace hotsearch
{
    /**
     * HotelSearchEngine Implementation
     *
     */
    
    /**
     * loadDataFromJSONFile loads all the hotels from a file and keps them in a map so they can be retrieve by id.
     * It also register tokens in a token invertex index database so we can retrieve hotel ids by strings.
     * and also register the hotel location in a geolocation index database so we can retrieve hotels by proximity.
     */
    void HotelSearchEngine::loadDataFromJSONFile(string filePath)
    {
        // set dictionary
        hotels = {};
        
        // DEBUG: timing
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        
        // get data as json
        json j = utils::parseJSONFile(filePath);
        
        // iterate over json elements to get hotels
        size_t N = j.size();
        for (unsigned long i = 0; i < N; i++)
        {
            registerHotel(utils::createHotelFromJSON(j[i]));
        }
        
        // DEBUG: timing
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        double duration = duration_cast<milliseconds>( t2 - t1 ).count();
        
        cout << "loaded " << hotels.size() << " Hotels in " << duration << " millisecs.\n";
    }
    
    /**
     * searchHotelByName retrieves hotels by name.
     * For every word in 'text', searches hotel ids associated with that word in the 'name' context,
     * then retrieves the hotels by id applying a default sort.
     */
    set<Hotel> HotelSearchEngine::searchHotelByName(string text)
    {
        // TODO: check local language. Loading english by default.
        
        // get hotel indexes for all token words in name
        set<long> ids;
        getIndexesByTokens(text, ids, InvertedIndexType::NAME);
        
        // get hotels sorted by HotelRanking criteria
        set<Hotel> results;
        for(set<long>::iterator it = ids.begin(); it != ids.end(); it++)
        {
            if (hotels.count(*it))
                results.insert(hotels[*it]);
        }
        
        return results;
    }
    
    /**
     * searchHotelByAddress retrieves hotels by address.
     * For every word in 'text', searches hotel ids associated with that word in the 'addres' context,
     * then retrieves the hotels by id applying a default sort.
     */
    set<Hotel> HotelSearchEngine::searchHotelByAddress(string text)
    {
        // TODO: check local language. Loading english by default.
        
        // get hotel indexes
        set<long> ids;
        getIndexesByTokens(text, ids, InvertedIndexType::ADRESS);
        
        // get hotels sorted by HotelRanking criteria
        set<Hotel> results;
        for(set<long>::iterator it = ids.begin(); it != ids.end(); it++)
        {
            if (hotels.count(*it))
                results.insert(hotels[*it]);
        }
        
        return results;
    }
    
    /**
     * searchHotelByGeolocation retrieves hotels by latitude longitude.
     * Recursively searches in a Quadtree for all the locations l[] contained in a box
     * defined by center=(latitude,longitude) and halfSize=(SEARCH_RANGE,SEARCH_RANGE).
     * With the ids[] kept in locations l[], the hotels are retrieved applying a default sort.
     */
    set<Hotel> HotelSearchEngine::searchHotelByGeolocation(float latitude, float longitude)
    {
        // create range box
        float thetha = 2.000000f;
        Box box = Box(Point(latitude,longitude), Point(thetha,thetha));
        
        // get hotel indexes
        set<long> ids;
        geoInvertedIndexDB.retrieveDocumentsByRange(box,ids);
        
        set<Hotel> results;
        
        for(long id : ids)
        {
            if (hotels.count(id))
                results.insert(hotels[id]);
        }
        
        return results;
    }
    
    // Adds the hotel to db. It also creates all inverted indexes required.
    void HotelSearchEngine::registerHotel(Hotel hotel)
    {
        // If already added => skip it
        if (hotels.count(hotel.id) > 0)
            return;
        
        // Add hotel to token inverted index db
        // add inverted index for names and addresses per each language
        for (LANGUAGE lang : LanguageUtils::LANGUAGE_LIST)
        {
            // add inverted index for name tokens
            addTokensToIndexDB(hotel.id, hotel.name[lang], InvertedIndexType::NAME, lang);
            
            // add inverted index for address tokens
            addTokensToIndexDB(hotel.id, hotel.address.toLocalizedString(lang), InvertedIndexType::ADRESS, lang);
        }
        
        // Add hotel to geolocation inverted index db
        geoInvertedIndexDB.insertPoint(hotel.address.location, hotel.id);
        
        // add hotel to dictionary
        hotels.insert(pair<long, Hotel>(hotel.id, hotel));
    }
    
    // For all words in 'text', inserts the set('word','id','entryType') into the inverted indexes library.
    void HotelSearchEngine::addTokensToIndexDB(long id, string text, InvertedIndexType entryType, LANGUAGE lang)
    {
        // get tokens from text
        vector<string> tokens;
        utils::tokenizeString(text, ' ', tokens);
        
        // for every token, register the id per entryType and language
        for (vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it)
            tokenInvertedIndexDB.insertWord(*it, id, entryType, lang);
    }
    
    // Tokenizes 'searchPhrase' and, for every token, it searches document indexes where the token appears.
    void HotelSearchEngine::getIndexesByTokens(const string &searchPhrase, set<long> &documents, InvertedIndexType entryType)
    {
        // get tokens
        vector<string> tokens;
        utils::tokenizeString(searchPhrase, ' ', tokens);
        
        // get hotel indexes per token
        for (vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it)
            tokenInvertedIndexDB.retrieveDocumentsByEntryType(*it, documents, entryType, LANGUAGE::EN);
    }
}
