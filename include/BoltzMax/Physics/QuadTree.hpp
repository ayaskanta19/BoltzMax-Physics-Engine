#pragma once

#ifndef BOLTZMAX_PHYSICS_QUADTREE_HPP
#define BOLTZMAX_PHYSICS_QUADTREE_HPP

#include <BoltzMax/Physics/Collidable.hpp>
#include <algorithm>
#include <vector>
#include <array>

class QuadTree {
    
    public:
        
        QuadTree();
        QuadTree(const QuadTree&);
        QuadTree(const RectShape&, unsigned, unsigned);
        
        ~QuadTree();
        
        bool insert(Collidable*);
        bool remove(Collidable*);
        bool update(Collidable*);
        
        void clear() noexcept;
        
        unsigned objectCount() const noexcept;
        unsigned childrenCount() const noexcept;
        
        std::vector<Collidable*>& getObjectsWithinBounds(const RectShape&);
        
    private:
        
        void subdivideTree();
        void discardEmptyBuckets();
        
        QuadTree* getChild(const RectShape&) const noexcept;
        
    private:
        
        QuadTree *parent; RectShape bounds;
        
        unsigned capacity, level, maxLevel; bool isLeaf;
        
        std::array<QuadTree*, 4u> children; std::vector<Collidable*> objects, foundObjects;
        
};

#endif