#pragma once

#ifndef BOLTZMAX_PHYSICS_COLLIDABLE_HPP
#define BOLTZMAX_PHYSICS_COLLIDABLE_HPP

#include <BoltzMax/Physics/RectShape.hpp>
#include <any>

class QuadTree;

struct Collidable {
    
    friend QuadTree;
    
    public: Collidable(const RectShape &bounds = {}, std::any data = {}): bounds(bounds), data(data), quadTree(nullptr) {}
    
    private: Collidable(const Collidable&) = delete;
    
    public: RectShape bounds; std::any data;
    
    private: QuadTree *quadTree;
    
};

#endif