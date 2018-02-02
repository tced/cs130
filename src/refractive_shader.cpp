#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    vec3 normal = (same_side_normal).normalized(); 
           refraction_color = {0,0,0}; 
    
    if(!world.disable_fresnel_refraction)
    { 
       vec3 ray_D = (ray.direction).normalized(); 
       double Ni, Nr, Ni_over_Nr, cosR, cosI, cosR_sqrt; 
       if (!is_exiting) {
	  Ni = refractive_index; 
  	  Nr = REFRACTIVE_INDICES::AIR; 
       }
 
       else {
	  Ni = REFRACTIVE_INDICES::AIR; 
          Nr = refractive_index; 
       }      
       
        Ni_over_Nr = Ni/Nr; 
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. i
        cosI = dot(-1.0 * ray_D, normal);
        cosR = 1.0 - (pow(Ni_over_Nr, 2.0)) * (1.0 - pow(cosI, 2.0)); 
        cosR_sqrt = sqrt(cosR);  
        //if (total internal reflection) }
        // If so update the reflectance_ratio for total internal refraction
        if (cosR <= 0) {
           reflectance_ratio = 1; 
        }
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //
        else { 
           vec3 T = (Ni/Nr) * (ray_D - dot(ray_D, normal) * normal) - cosR_sqrt * normal; 
	   Ray refraction_ray; 
           refraction_ray.endpoint = intersection_point; 
	   refraction_ray.direction = T; 
           ++recursion_depth; 
	   refraction_color = world.Cast_Ray(refraction_ray, recursion_depth); 

	   double R_par, R_per; 
           R_par = ((Nr * cosI) - (Ni * cosR_sqrt)) / ((Nr * cosI) + (Ni * cosR_sqrt)); 
           R_par = pow(R_par, 2); 
           R_per = ((Ni * cosI) - (Nr * cosR_sqrt)) / ((Ni * cosI) + (Nr * cosR_sqrt));
           R_per = pow(R_per, 2); 
       
           reflectance_ratio = (R_par + R_per) / 2.0; 
        }
   }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        Ray reflected_ray;
        vec3 D = ray.direction; 
 	reflected_ray.endpoint = intersection_point;
	reflected_ray.direction = D - 2 * dot(D, same_side_normal) * same_side_normal;
	reflection_color = world.Cast_Ray(reflected_ray, recursion_depth);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    //
    color = reflectance_ratio * reflection_color + (1 - reflectance_ratio) * refraction_color; 
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

