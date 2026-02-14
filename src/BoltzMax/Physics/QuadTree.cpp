#include <BoltzMax/Physics/QuadTree.hpp>

QuadTree::QuadTree(): QuadTree(RectShape(), 0u, 0u) {}

QuadTree::QuadTree(const QuadTree &tree): QuadTree(tree.bounds, tree.capacity, tree.maxLevel) {}

QuadTree::QuadTree(const RectShape &bounds, unsigned capacity, unsigned maxLevel): parent(nullptr), bounds(bounds), capacity(capacity), level(0u), maxLevel(maxLevel), isLeaf(true), children(), objects(), foundObjects() {
    
    for(QuadTree* &child: children) child = nullptr; objects.reserve(capacity); foundObjects.reserve(capacity);
    
}

QuadTree::~QuadTree() { clear(); for(QuadTree* &child: children) if(child) delete child; }

bool QuadTree::insert(Collidable *collidable) {
    
    if(collidable->quadTree) return false; if(!isLeaf) if(QuadTree *child = getChild(collidable->bounds)) return child->insert(collidable);
    
    objects.push_back(collidable); collidable->quadTree = this; if(isLeaf && level < maxLevel && objects.size() >= capacity) { subdivideTree(); update(collidable); }
    
    return true;
    
}

bool QuadTree::remove(Collidable *collidable) {
    
    if(!collidable->quadTree) return false; if(collidable->quadTree != this) return collidable->quadTree->remove(collidable);
    
    objects.erase(std::find(objects.begin(), objects.end(), collidable)); collidable->quadTree = nullptr; discardEmptyBuckets(); return true;
    
}

bool QuadTree::update(Collidable *collidable) {
    
    if(!remove(collidable)) return false; if(parent && !bounds.contains(collidable->bounds)) return parent->insert(collidable);
    
    if(!isLeaf) if(QuadTree *child = getChild(collidable->bounds)) return child->insert(collidable); return insert(collidable);
    
}

void QuadTree::clear() noexcept {
    
    if(!objects.empty()) { for(Collidable* &collidable: objects) collidable->quadTree = nullptr; objects.clear(); }
    
    if(!isLeaf) { for(QuadTree *child: children) child->clear(); isLeaf = true; }
    
}

unsigned QuadTree::objectCount() const noexcept { unsigned count = (unsigned)objects.size(); if(!isLeaf) for(QuadTree *child: children) count += child->objectCount(); return count; }

unsigned QuadTree::childrenCount() const noexcept { unsigned count = 0u; if(isLeaf) return count; for(QuadTree *child: children) count += child->childrenCount() + 1u; return count; }

std::vector<Collidable*>& QuadTree::getObjectsWithinBounds(const RectShape &bounds) {
    
    foundObjects.clear(); for(const auto &collidable: objects) if(&collidable->bounds != &bounds && collidable->bounds.intersects(bounds)) foundObjects.push_back(collidable);
    
    if(!isLeaf) {
        
        if(QuadTree *child = getChild(bounds)) { child->getObjectsWithinBounds(bounds); foundObjects.insert(foundObjects.end(), child->foundObjects.begin(), child->foundObjects.end()); }
        
        else for(QuadTree *child: children) if(child->bounds.intersects(bounds)) { child->getObjectsWithinBounds(bounds); foundObjects.insert(foundObjects.end(), child->foundObjects.begin(), child->foundObjects.end()); }
        
    }
    
    return foundObjects;
    
}

void QuadTree::subdivideTree() {
    
    float x = 0.f, y = 0.f, width = bounds.width / 2.f, height = bounds.height / 2.f;
    
    for(unsigned child = 0u; child < 4u; child++) {
        
        switch(child) {
            
            case 0u: x = bounds.x; y = bounds.y; break;
            
            case 1u: x = bounds.x + width; y = bounds.y; break;
            
            case 2u: x = bounds.x + width; y = bounds.y + height; break;
            
            case 3u: x = bounds.x; y = bounds.y + height; break;
            
        }
        
        children[child] = new QuadTree(RectShape(x, y, width, height), capacity, maxLevel); children[child]->level = level + 1u; children[child]->parent = this;
        
    }
    
    isLeaf = false;
    
}

void QuadTree::discardEmptyBuckets() {
    
    if(!objects.empty()) return; if(!isLeaf) for(QuadTree *child: children) if(!child->isLeaf || !child->objects.empty()) return;
    
    if(clear(), parent) parent->discardEmptyBuckets();
    
}

QuadTree* QuadTree::getChild(const RectShape &bounds) const noexcept {
    
    bool left = bounds.x + bounds.width < this->bounds.getRight(), right = bounds.x > this->bounds.getRight(), top = bounds.y + bounds.height < this->bounds.getTop(), bottom = bounds.y > this->bounds.getTop();
    
    if(top) { if(left) return children[0u]; if(right) return children[1u]; }
    
    else if(bottom) { if(left) return children[3u]; if(right) return children[2u]; }
    
    return nullptr;
    
}