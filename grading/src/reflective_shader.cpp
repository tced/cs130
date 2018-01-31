#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
#include "light.h" 

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 color, L, reflected_color; 
    Ray reflected_ray;
    // TODO: determine the color
    for (unsigned int i = 0; i < world.lights.size(); ++i) {
        reflected_ray.direction = (world.lights.at(i)->position - intersection_point).normalized(); 
	reflected_ray.endpoint = intersection_point * reflected_ray.direction;
   	reflected_color = world.Cast_Ray(reflected_ray, recursion_depth); 
     }
    return color;
}
