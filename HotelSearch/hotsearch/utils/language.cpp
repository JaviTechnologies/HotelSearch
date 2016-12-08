//
//  language.cpp
//  HotelSearch
//
//  Created by Javier Campos on 12/5/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//


#include "language.hpp"

namespace hotsearch
{
    /**
     * Language enum list
     */
    std::vector<LANGUAGE> LanguageUtils::LANGUAGE_LIST = {LANGUAGE::AR, LANGUAGE::CN, LANGUAGE::DE, LANGUAGE::ES, LANGUAGE::GR, LANGUAGE::EN};
    
    /**
     * getLanguageAsString
     * Returns the language as string
     */
    std::string LanguageUtils::getLanguageAsString (LANGUAGE lang)
    {
        switch (lang) {
            case LANGUAGE::AR:
                return "AR";
                break;
                
            case LANGUAGE::CN:
                return "CN";
                break;
                
            case LANGUAGE::DE:
                return "DE";
                break;
                
            case LANGUAGE::ES:
                return "ES";
                break;
                
            case LANGUAGE::GR:
                return "GR";
                break;
                
            default:
                return "EN";
                break;
        }
        
        return NULL;
    }
}

