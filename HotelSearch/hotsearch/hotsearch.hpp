//
//  hotsearch.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/5/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef hotsearch_hpp
#define hotsearch_hpp

#include <map>
#include <set>
#include "token_inverted_index_db.hpp"
#include "geolocation_inverted_index_db.hpp"

namespace hotsearch
{
    /**
     * HotelSearchEngine helps us search for hotels. It provides:
     *
     * > loadDataFromJSONFile(string filePath). To read the entry data.
     * > set<Hotel*> searchHotelByName(string name). To retrieve hotels by name.
     * > set<Hotel*> searchHotelByAddress(string address). To retrieve hotels by addres.
     * > set<Hotel*> searchHotelByGeolocation(float latitude, float longitude). To retrieve hotel around a position.
     *
     */
    class HotelSearchEngine
    {
        /**
         * The container for the hotels is going to be a map for now.
         * Another version should run as a service and use a database to map hotels. */
        std::map<long,Hotel> hotels;
        
        /**
        * Inverted indexes would be used to retrieve the hotels faster.
        * Why? because it allows us to group hotels under a criteria shrinking the range of search.
        * Depending on the data structure, the criteria could be common words, proximity,
        * or raking for example.
        *
        * The first index database would be for tokens.
        * TokenInvertedIndexDB uses a trie to map words to a list of ids where they appear.
        * For example, if hotel.name has the words list<tokens> then for each token
        * this class maps hotel.id to token.
        * This way, when we query one of those tokens, the hotel would be retrieve.
        * This takes O(l), where l:= number of words.
        * This is constant in terms of number of hotels.
        * See documentation inside the class for more information. */
        TokenInvertedIndexDB tokenInvertedIndexDB;
        
        /**
        * The second index database would be for geolocation.
        * GeolocationInvertedIndexDB uses a quadtree to map points to areas.
        * This takes O(log4 N) because of the quadtree. */
        GeolocationInvertedIndexDB<long> geoInvertedIndexDB;
        
        /*********************
         * Private methods
         *********************/
        
        /**
         * Adds the hotel to db. It also creates all inverted indexes required.
         */
        void registerHotel(Hotel hotel);
        
        /**
         * For all words in 'text', inserts the set('word','id','entryType') into the inverted indexes library.
         */
        void addTokensToIndexDB(long id, std::string text, InvertedIndexType entryType, LANGUAGE lang);
        
        /**
         * Tokenizes 'searchPhrase' and, for every token, it searches document indexes where the token appears.
         */
        void getIndexesByTokens(const std::string &searchPhrase, std::set<long> &documents, InvertedIndexType entryType);
        
    public:
        /*********************
         * Public methods
         *********************/
        
        /**
         * loadDataFromJSONFile loads all the hotels from a file and keps them in a map so they can be retrieve by id.
         * It also register tokens in a token invertex index database so we can retrieve hotel ids by strings.
         * and also register the hotel location in a geolocation index database so we can retrieve hotels by proximity.
         */
        void loadDataFromJSONFile(std::string filePath);
        
        /**
         * searchHotelByName retrieves hotels by name.
         * For every word in 'text', searches hotel ids associated with that word in the 'name' context,
         * then retrieves the hotels by id applying a default sort.
         */
        std::set<Hotel> searchHotelByName(std::string text);
        
        /**
         * searchHotelByAddress retrieves hotels by address.
         * For every word in 'text', searches hotel ids associated with that word in the 'addres' context,
         * then retrieves the hotels by id applying a default sort.
         */
        std::set<Hotel> searchHotelByAddress(std::string text);
        
        /**
         * searchHotelByGeolocation retrieves hotels by latitude longitude.
         * Recursively searches in a Quadtree for all the locations l[] contained in a box
         * defined by center=(latitude,longitude) and halfSize=(SEARCH_RANGE,SEARCH_RANGE).
         * With the ids[] kept in locations l[], the hotels are retrieved applying a default sort.
         */
        std::set<Hotel> searchHotelByGeolocation(float latitude, float longitude);
    };
}

#endif /* hotsearch_hpp */
