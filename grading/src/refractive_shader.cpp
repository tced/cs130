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
    
    vec3 D = ray.direction.normalized(); 
    vec3 I = intersection_point; 
    vec3 N = same_side_normal; 
    vec3 R = (D - 2.0 * dot(D,N)*N); 

    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
	Ray rayrefract; 
   	vec3 R_norm = R.normalized(); 
	double Nr = refractive_index; 
	double Ni = 1; 
	double Ns = Ni/Nr; 

	if (is_exiting) { 
	   Ns = Nr/Ni; 
	}	

	double cos_angle_incidence = dot(N, R_norm) / (N.magnitude() * R_norm.magnitude());
	double cos_angle_refraction_squared = 1 - (pow(Ns,2) * (1 - pow(cos_angle_incidence,2))); 
	double cos_angle_refraction = sqrt(cos_angle_refraction_squared);
  
	if (cos_angle_refraction_squared < 0) {
	   reflectance_ratio = 1; 
	   refraction_color = {0,0,0};  
	}
	else { 
	   vec3 Refract = Ns * (D - dot(D,N) * N ) - cos_angle_refraction * N; 
	   rayrefract.endpoint = I; 
	   rayrefract.direction = Refract; 
	   recursion_depth++;
	   refraction_color = world.Cast_Ray(rayrefract, recursion_depth); 
	  
           double RII = pow((Nr*cos_angle_incidence - Ni*cos_angle_refraction)/(Nr*cos_angle_incidence + Ni*cos_angle_refraction),2); 
	   double RT = pow((Ni*cos_angle_incidence - Nr*cos_angle_refraction)/(Ni*cos_angle_incidence + Nr*cos_angle_refraction),2); 
	   reflectance_ratio = (RII + RT)/2; 
        }
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. i
        //if (total internal reflection) }
        //      If so update the reflectance_ratio for total internal refraction
        //
        
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        Ray reflected_ray;
        vec3 D;  
 	D = ray.direction; 
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

