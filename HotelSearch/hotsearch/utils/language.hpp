//
//  language.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/5/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef language_hpp
#define language_hpp

#include <vector>
#include <string>

namespace hotsearch
{
    /**
     * Language enum
     */
    enum class LANGUAGE { AR, CN, DE, ES, GR, EN };
    
    class LanguageUtils
    {
    public:
        /**
         * Language enum list
         */
        static std::vector<LANGUAGE> LANGUAGE_LIST;
        
        /**
         * getLanguageAsString
         * Returns the language as string
         */
        static std::string getLanguageAsString (LANGUAGE lang);
    };
}

#endif /* language_hpp */
