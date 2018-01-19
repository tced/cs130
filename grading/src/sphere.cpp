#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO

    // calculate discriminate 
    vec3 v = ray.endpoint - center;
    vec3 u = ray.direction; 
    double t3, t1, t2; 
    double a = 1; 
    double b = 2 * dot(u,v); 
    double c = dot(v,v) - radius * radius;  
    double result = 4 * (dot(u,v) * dot(u,v)) - 4 * (dot(v,v) - radius * radius);
  
    //return result; 
    //if there are no intersections 
    if (result < 0) {
    	return false; 
    }
    else if (result == 0) { 
    	t3 = -b / (2 * a * c); 
	Hit hit; 
	hit.t = t3;
        hit.ray_exiting = false; 
	hits.push_back(hit); 
    }
    else {
	t1 = (-b - sqrt(result)) / (2 * a *c);
	t2 = (-b + sqrt(result)) / (2 * a * c);
	if (t1 > 0) { //two intersections 
		Hit hit1, hit2;  
		hit1.t = t1; 
		hit1.ray_exiting = false; 
		hit2.t = t2; 
		hit2.ray_exiting = true; 
		hits.push_back(hit1); 
		hits.push_back(hit2); 
	} 
	else { //one intersection
		Hit hit3;  
		hit3.t = t2;
		hit3.ray_exiting = true;  
		hits.push_back(hit3);   
	}   
    }
    return true; 
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    return normal;
}
