//
//  quadtree.hpp
//  HotelSearch
//
//  Created by Javier Campos on 12/6/16.
//  Copyright © 2016 Javier Campos. All rights reserved.
//

#ifndef quadtree_hpp
#define quadtree_hpp

#include <vector>
#include "box.hpp"

using namespace std;

namespace hotsearch
{
    /**
     * QuadTreeNodeData
     * Data that would be stored in a used Node of the QuadTree
     */
    template <typename T>
    class QuadTreeNodeData
    {
    public:
        Point p;
        T load;
    };
    
    /**
     * Quadtree is a node that could be a leaf or an internal node. If it's internal node
     * it has four children. if it's a leaf, it represents a unique box containing a spatial
     * range of data entry (location points).
     */
    template <class T>
    class QuadTree
    {
    private:
        // box boundary
        Box boundary;
        
        // 4 children
        QuadTree<T>* NW;
        QuadTree<T>* NE;
        QuadTree<T>* SW;
        QuadTree<T>* SE;
        
        // items
        vector<QuadTreeNodeData<T>> objects;
        static constexpr int capacity = 4;
        
        //
        bool subdivide();
        
    public:
        QuadTree<T>();
        QuadTree<T>(Box boundary);
        
        ~QuadTree();
        
        bool insert(QuadTreeNodeData<T> d);
        std::vector< QuadTreeNodeData<T>> queryRange(Box& range);
        
        friend ostream& operator<<(ostream& out, QuadTree& quadTree)
        {
            out << quadTree.boundary;
            return out;
        }
    };
    
    template <class T>
    QuadTree<T>::QuadTree():
    NW{nullptr},
    NE{nullptr},
    SW{nullptr},
    SE{nullptr}
    {
        objects = std::vector<QuadTreeNodeData<T>>();
    }
    
    template <class T>
    QuadTree<T>::QuadTree(Box boundary):
    NW{nullptr},
    NE{nullptr},
    SW{nullptr},
    SE{nullptr}
    {
        objects = std::vector<QuadTreeNodeData<T>>();
        this->boundary = boundary;
    }
    
    template <class T>
    QuadTree<T>::~QuadTree()
    {
        delete NW;
        delete SW;
        delete NE;
        delete SE;
    }
    
    template <class T>
    bool QuadTree<T>::subdivide()
    {
        Point qSize = Point(boundary.halfSize.x / 2, boundary.halfSize.y / 2);
        
        Point qCentre = Point(boundary.center.x - qSize.x, boundary.center.y - qSize.y);
        
        SW = new QuadTree(Box(qCentre, qSize));
        
        qCentre = Point(boundary.center.x + qSize.x, boundary.center.y - qSize.y);
        SE = new QuadTree(Box(qCentre, qSize));
        
        qCentre = Point(boundary.center.x - qSize.x, boundary.center.y + qSize.y);
        NW = new QuadTree(Box(qCentre, qSize));
        
        qCentre = Point(boundary.center.x + qSize.x, boundary.center.y + qSize.y);
        NE = new QuadTree(Box(qCentre, qSize));
        
        // Insert points to children
        bool inserted;
        for(QuadTreeNodeData<T> o: objects)
        {
            inserted = (NW->insert(o) || NE->insert(o) || SW->insert(o) || SE->insert(o));
            
            // Error
            if (!inserted)
            {
                cout << "Error: " << o.p << " not inserted in " << boundary << endl;
                return false;
            }
        }
        
        objects.clear();
        
        return true;
    }
    
    template <class T>
    bool QuadTree<T>::insert(QuadTreeNodeData<T> d)
    {
        // Return false if it is out of bound
        if(!boundary.contains(d.p))
            return false;
        
        // Check children
        // It doesn't have children => This is a leaf
        if (NW == nullptr)
        {
            // Add to this leaf
            objects.push_back(d);
            
            // Check capacity
            if(objects.size() <= capacity)
                return true;
            
            // Over capacity => subdivide!
            return subdivide();
        }
        
        // Insert in children
        return (NW->insert(d) || NE->insert(d) || SW->insert(d) || SE->insert(d));
    }
    
    template <class T>
    std::vector< QuadTreeNodeData<T>> QuadTree<T>::queryRange(Box& range)
    {
        std::vector<QuadTreeNodeData<T>> pInRange = std::vector<QuadTreeNodeData<T>>();
        
        if(!boundary.intersects(range))
        {
            return pInRange;
        }
        
        if (NW != nullptr)
        {
            std::vector<QuadTreeNodeData<T>> temp = NW->queryRange(range);
            pInRange.insert(pInRange.end(), temp.begin(), temp.end());
            
            temp = NE->queryRange(range);
            pInRange.insert(pInRange.end(), temp.begin(), temp.end());
            
            temp = SW->queryRange(range);
            pInRange.insert(pInRange.end(), temp.begin(), temp.end());
            
            temp = SE->queryRange(range);
            pInRange.insert(pInRange.end(), temp.begin(), temp.end());
        }
        else
        {
            for(auto&& object: objects)
            {
                if(range.contains(object.p))
                {
                    pInRange.push_back(object);
                }
            }
        }
        
        return pInRange;
    }
}

#endif /* quadtree_hpp */
