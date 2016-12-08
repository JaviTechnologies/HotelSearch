//
//  geolocation_inv_ind_db.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef geolocation_inverted_index_db
#define geolocation_inverted_index_db

//#include <iostream>
#include <vector>
#include "quadtree.hpp"

using namespace std;

namespace hotsearch
{
    template <class T>
    class GeolocationInvertedIndexDB
    {
        QuadTree<T>* library;
        
    public:
        GeolocationInvertedIndexDB<T>();
        ~GeolocationInvertedIndexDB();

        void insertPoint(Point p, T load);
        void retrieveDocumentsByRange(Box &range, set<long> &docIds);
    };
    
    template <class T>
    GeolocationInvertedIndexDB<T>::GeolocationInvertedIndexDB()
    {
        library = new QuadTree<T>(Box(Point(0.0f, 0.0f), Point(90,180)));
    }
    
    template <class T>
    GeolocationInvertedIndexDB<T>::~GeolocationInvertedIndexDB()
    {
        delete library;
    }
    
    template <class T>
    void GeolocationInvertedIndexDB<T>::insertPoint(Point p, T load)
    {
        QuadTreeNodeData<T> d;
        d.p = p;
        d.load = load;
        
        if(!library->insert(d))
            cout << "Error inserting (" << p.x << "," << p.y << ") for load=" << load << endl;
//        else
//            cout << "inserted (" << p.x << "," << p.y << ") for load=" << d.load << endl;
    }
    
    template <class T>
    void GeolocationInvertedIndexDB<T>::retrieveDocumentsByRange(Box &range, set<long> &docIds)
    {
        vector<QuadTreeNodeData<T>> results = library->queryRange(range);
        for (QuadTreeNodeData<T> entry : results)
        {
            docIds.insert((entry.load));
        }
    }
}

#endif /* geolocation_inverted_index_db */
