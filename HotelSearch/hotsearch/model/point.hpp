//
//  point.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <iostream>

namespace hotsearch
{
    /**
     * Point model implementation as (latitud,longitud)
     */
    class Point
    {
    public:
        float x, y;
        
        Point():x(0.0f),y(0.0f){}
        Point(float x,float y):x(x),y(y){}
        
        friend std::ostream& operator<<(std::ostream& out, Point& point)
        {
            out << "(" << point.x << "," << point.y << ")";
            return out;
        }
    };
}

#endif /* point_hpp */
