//
//  box.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef box_hpp
#define box_hpp

#include "point.hpp"

using namespace std;

namespace hotsearch
{
    class Box
    {
    public:
        Point center, halfSize;
        
        Box(Point center = Point(), Point halfSize = Point()): center(center), halfSize(halfSize){};
        
        bool contains(const Point& a) const
        {
            if(a.x <= center.x + halfSize.x && a.x >= center.x - halfSize.x)
            {
                if(a.y <= center.y + halfSize.y && a.y >= center.y - halfSize.y)
                {
                    return true;
                }
            }
            return false;
        }
        
        bool intersects(const Box& other) const
        {
            //this right > that left                                          this left <s that right
            if(center.x + halfSize.x > other.center.x - other.halfSize.x || center.x - halfSize.x < other.center.x + other.halfSize.x)
            {
                // This bottom > that top
                if(center.y + halfSize.y > other.center.y - other.halfSize.y || center.y - halfSize.y < other.center.y + other.halfSize.y)
                {
                    return true;
                }
            }
            return false;
        }
        
        friend ostream& operator<<(ostream& out, Box& box)
        {
            out << "[" << box.center << "," << box.halfSize << "]";
            return out;
        }
    };
}

#endif /* box_hpp */
