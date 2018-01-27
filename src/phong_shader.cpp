#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <math.h> 

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
  vec3 color, ambient, diffuse, specular, light_color, L, R, C;

  //calculating ambient 
  ambient = world.ambient_color * world.ambient_intensity * color_ambient;
   
  //shadows not enabled 
  if(!world.enable_shadows) {
      for (unsigned int i = 0; i < world.lights.size(); i++){
             //color of light source 
	     light_color = world.lights.at(i)->Emitted_Light(ray)/(world.lights.at(i)->position - intersection_point).magnitude_squared();
             
	     //calculating L and diffuse component 
             L = (world.lights.at(i)->position - intersection_point).normalized();
             diffuse += std::max( 0.0, dot( same_side_normal.normalized(), L )) * color_diffuse * light_color;
             
             //calculating R, C, specular component 
             R = (2 * dot(L,same_side_normal.normalized()) * same_side_normal-L).normalized();
             C = (ray.endpoint - intersection_point).normalized();
             specular += pow(std::max(0.0, dot(C, R)), specular_power) * light_color * color_specular;

       }   
   }  

  //shadows enabled 
  else {
     for (unsigned int i = 0; i < world.lights.size(); i++){

         // Contruct a ray from object to light
         Ray ray_object_light_source;
         ray_object_light_source.direction = (world.lights.at(i)->position - intersection_point).normalized();
         ray_object_light_source.endpoint = intersection_point + small_t*ray_object_light_source.direction;

         Hit intercept_obj_hit;

         Object* intercept_obj = world.Closest_Intersection(ray_object_light_source, intercept_obj_hit);

         double dist_bw_object_and_light = (world.lights.at(i)->position - intersection_point ).magnitude();
         double dist_bw_object_and_hit = intercept_obj_hit.t;
         if (intercept_obj == 0 || dist_bw_object_and_light <= dist_bw_object_and_hit){
	      light_color = world.lights.at(i)->Emitted_Light(ray)/(world.lights.at(i)->position - intersection_point).magnitude_squared();
	      
	      //calculating L and diffuse component 
              L = (world.lights.at(i)->position - intersection_point).normalized();
              diffuse += std::max( 0.0, dot( same_side_normal.normalized(), L )) * color_diffuse * light_color;

	      //calculating R, C, specular component 
              R = (2 * dot(L,same_side_normal.normalized()) * same_side_normal-L).normalized();
              C = (ray.endpoint - intersection_point).normalized();
              specular += pow(std::max( 0.0, dot(C,R)), specular_power) * light_color * color_specular;

              color = ambient + diffuse + specular;
          }
         else {
             diffuse += vec3(0,0,0);
             specular += vec3(0,0,0);  
          }
     }
   } 
    
   color = ambient + diffuse + specular; 
   return color;
}
