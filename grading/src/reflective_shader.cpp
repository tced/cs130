#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
#include "light.h" 

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{   
    vec3 color, D, reflected_color, shader_color; 
    //compute reflected ray
    Ray reflected_ray; 
    D = ray.direction;  
    //reflected_ray.direction = -ray.direction;
    reflected_ray.endpoint = intersection_point; 
    reflected_ray.direction = D - 2 * dot(D, same_side_normal) * same_side_normal; 
    ++recursion_depth; 
    reflected_color = shader->world.Cast_Ray(reflected_ray, recursion_depth);
    shader_color = shader->Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth, is_exiting); 
    color = reflectivity * reflected_color + (1 - reflectivity) * shader_color;

        return color; 
}
