#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    double result; 
    vec3 u = ray.direction; 
    vec3 v = ray.endpoint - center; 
    
    result = pow(dot(u,v),2) - (dot(u,u)*(dot(v,v) - radius*radius));
    result  = pow(dot(u,v),2) - (dot(u,u)*(dot(v,v) - pow(radius,2)));
    
    Hit hit1; 
    Hit hit2;
    
    //if there are no intersections 
    if (result  < 0) {
	return false;
    }
   
    //if there is one intersection  
     else if (result == 0){ 
        hit1.t = (-1.0*dot(u,v) + sqrt(result)) / dot(u,u); 
        hit1.ray_exiting = false;
        hits.push_back(hit1);
        return true;
     }
    //if there are two intersections
    else {
        hit1.t = (-1.0 * dot(u,v) + sqrt(result)) / dot(u,u);
        hit2.t = (-1.0* dot(u,v) - sqrt(result)) / dot(u,u);
        
        hit1.ray_exiting = false;
        hits.push_back(hit1);
        
        hit2.ray_exiting = true;
        hits.push_back(hit2);
        
	return true;
     }
  
     
     return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
     vec3 normal = ((center - point)).normalized(); 
     return normal; 
}
