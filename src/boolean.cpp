#include "boolean.h"


// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
   /*
     // TODO
    bool b = false; 
    bool a = false; 

    if (type == type_union) {
       if (A != NULL) {
          a = A->Intersection(ray,hits); 
       }
       if (B != NULL) {}
       if (a||b) { return true; }
    } 
       if (type == type_intersection) { return true;} 
       if (type == type_difference) {return true;} 
    */
    return false;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}
