//
//  hotel.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef hotel_hpp
#define hotel_hpp

#include <map>
#include <string>
#include "language.hpp"
#include "address.hpp"

namespace hotsearch
{
    /**
     * Hotel model implementation
     */
    class Hotel
    {
    public:
        /**
         * unique identifier
         */
        long id;
        
        /**
         * rank
         */
        double rank;
        
        /**
         * name per language
         */
        std::map<LANGUAGE, std::string> name;
        
        /**
         * description per language
         */
        std::map<LANGUAGE, std::string> description;
        
        /**
         * address
         */
        Address address;
        
        bool operator == (const Hotel &other)
        {
            return (id == other.id);
        }
        
        bool operator != (const Hotel &other)
        {
            return (id != other.id);
        }
        
        bool operator > (const Hotel &other)
        {
            return other.rank > rank;
        }
        
        bool operator>= (const Hotel &other)
        {
            return other.rank >= rank;
        }
        
        bool operator < (const Hotel &right) const
        {
            return right.rank < rank;
        }
        
        bool operator <= (const Hotel &other)
        {
            return other.rank <= rank;
        }
    };
    
    /**
     * Hotel Ranking Comparer.
     * compares the ranking of two hotels
     */
    class HotelRankingComparer
    {
    public:
        bool operator() (Hotel *h1, Hotel *h2) { return h1->rank > h2->rank; }
    };
    
}

#endif /* hotel_hpp */
