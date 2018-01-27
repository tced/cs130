#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
/*       
    // TODO
    double a = double(dot((ray.endpoint - x1), normal)); 
    double b = double(dot(ray.direction, normal)); 
    bool c1 = true; 
    if (a <= 0) { 
       c1 = true; 
    }
    else {
       c1 = false; 
    }
    if (c1 == false && (b > 0 || b == 0)) {
       return false; 
    }
    //case1: one intersection 
    else if (c1 == true && (b < 0 || b == 0)) {
       Hit intersec = Hit(); 
       intersec.t = 0; 
       intersec.object = this; 
       intersec.ray_exiting = false; 

       hits.push_back(intersec); 
       return true; 
    }
    //case2: two intersections 
    else if (c1 == true && b > 0) {
    	double t = -double(double(a) / double(b)); 
        Hit intersec = Hit(); 
        intersec.t = 0; 
        intersec.object = this; 
        intersec.ray_exiting = false; 
       
  	hits.push_back(intersec); 

	Hit intersec2 = Hit(); 
	intersec.t = t; 

	intersec2.object = this; 
	intersec2.ray_exiting = true; 

	hits.push_back(intersec2); 
	return true;         
    }
    else if(c1 == false && b < 0) {
    	double t = -double(double(a) / double(b)); 
	Hit intersec = Hit(); 
	intersec.t = t; 
	intersec.object = this; 
	intersec.ray_exiting = false; 
	hits.push_back(intersec); 

	return false; 
    }

    return false; 
*/ 

double denominator;

    if ((denominator = dot(normal,ray.direction)) != 0) {
      Hit hit;

      if((hit.t = -dot(normal,(ray.endpoint - x1))/(denominator)) >=0) {
        hit.object = this;
        if(hit.t >= 0) {
          hit.ray_exiting = false;
          hits.push_back(hit);
          return true;
        }
      } else if(-dot(normal,(ray.endpoint-x1)) != 0) {
                        return false;
                               } else {
                                       return false;
                                             }
                                                }
                                             return false;
}

vec3 Plane::Normal(const vec3& point) const 
{
	return normal; 
}
