#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{ 
   vec3 color, ambient, diffuse, light_color, specular, 
	L, reflectance_vector, C;   
   
    // TODO: determine the color
    for (unsigned int i = 0; i < world.lights.size(); ++i) { 
    //Ray ray_from_object_to_light_source; 
    //ray_from_object_to_light_source.direction = (world.lights.at(i)->position - intersection_point).normalized();
    //ray_from_object_to_light_source.endpoint = intersection_point + small_t * ray_from_object_to_light_source.direction;  
    
     //Hit intercepting_object_hit; 
     //Object* intercepting_object = world.Closest_Intersection(ray_from_object_to_light_source, intercepting_object_hit); 

     //double distance_between_object_and_light = (world.lights.at(i)->position - intersection_point).magnitude(); 

     //double distance_between_object_and_hit = intercepting_object_hit.t; 
     //if (intercepting_object == nullptr || distance_between_object_and_light <= distance_between_object_and_hit) {
	L =  (world.lights.at(i)->position - intersection_point).normalized(); 
        light_color = world.lights.at(i)->Emitted_Light(ray)/(world.lights.at(i)->position - intersection_point).magnitude_squared();
        diffuse += color_diffuse * light_color * std::max(0.0, dot(same_side_normal.normalized(),L));  
     // }
    }
    ///specular = color_specular * world.specular_intensity; 
    //color_diffuse diffuse color of the surface
      
    ambient = world.ambient_intensity * world.ambient_color * color_ambient;
    color = ambient + diffuse;       	  
    return color;
}


	
