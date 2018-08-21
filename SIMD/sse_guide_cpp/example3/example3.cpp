#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "./../sse.hpp"
#include <random>
#include "./../timer.hpp"
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#if VECLIB_SSE_VER<0x20
#error Need at least SSE2 support
#endif

#define noinline __attribute__((noinline))
#define finline  __attribute__((always_inline))

noinline bool intersect(const vec3& raydir, const vec3& rayorig, const vec3& pos, const float& rad, vec3& hitpoint, float& distance, vec3& normal)
{
float a = sum(raydir*raydir);
float b = sum(raydir * (2.0f * ( rayorig - pos)));
float c = sum(pos*pos) + sum(rayorig*rayorig) - 2.0f*sum(rayorig*pos) - rad*rad;

float D = b*b - 4.0f*a*c;

// If line does not intersect the sphere then stop
if (D < 0)
        return false;

D=sqrtf(D);

// Ray can intersect the sphere, return the closer hitpoint
float t = (-0.5f)*(b+D)/a;

if (t > 0.0f)
        {
        distance=sqrtf(a)*t;
        hitpoint=rayorig + t*raydir;
        normal=(hitpoint - pos) / rad;
        }
else
        return false;

return true;
}

noinline vec4b intersect(const mat4x3& raydir, const mat4x3& rayorig, const vec3& pos, const float& rad, mat4x3& hitpoint, vec4& distance, mat4x3& normal, vec4b& mask)
{
vec4 raydirx = raydir[0];
vec4 raydiry = raydir[1];
vec4 raydirz = raydir[2];
vec4 a = raydirx*raydirx + raydiry*raydiry + raydirz*raydirz;
vec4 rayorigx = rayorig[0];
vec4 rayorigy = rayorig[1];
vec4 rayorigz = rayorig[2];
vec4 posx = pos[0];
vec4 posy = pos[1];
vec4 posz = pos[2];
vec4 b = raydirx * 2.0f * (rayorigx - posx) + raydiry * 2.0f * (rayorigy - posy) + raydirz * 2.0f * (rayorigz - posz);
vec4 c = sum(pos*pos) + rayorigx*rayorigx + rayorigy*rayorigy + rayorigz*rayorigz - 2.0f*(rayorigx*posx + rayorigy*posy + rayorigz*posz) - rad*rad;
vec4 D = b*b + (-4.0f)*a*c;

mask = mask && D > 0.0f;
if (ForWhich(mask) == 0)
	return mask;

D = Sqrt(D);

vec4 t = (-0.5f)*(b+D)/a;

mask = mask && t > 0.0f;
int bitmask = ForWhich(mask);

if (bitmask == 15)
	{
	distance = Sqrt(a) * t;
	vec4 hitpointx = rayorigx + t*raydirx;
	vec4 hitpointy = rayorigy + t*raydiry;
	vec4 hitpointz = rayorigz + t*raydirz;
	vec4 rad4=1.0f/rad;
	normal[0]=(hitpointx - posx) * rad4;
	normal[1]=(hitpointy - posy) * rad4;
	normal[2]=(hitpointz - posz) * rad4;
	hitpoint[0]=hitpointx;
	hitpoint[1]=hitpointy;
	hitpoint[2]=hitpointz;
	}
else if (bitmask == 0)
	return mask;
else
	{
	distance = Condition(mask, Sqrt(a) * t, distance);
        vec4 hitpointx = rayorigx + t*raydirx;
        vec4 hitpointy = rayorigy + t*raydiry;
        vec4 hitpointz = rayorigz + t*raydirz;
	normal[0]=Condition(mask, hitpointx - posx, normal[0]);
	normal[1]=Condition(mask, hitpointy - posy, normal[1]);
	normal[2]=Condition(mask, hitpointz - posz, normal[2]);
	hitpoint[0]=Condition(mask, hitpointx, hitpoint[0]);
	hitpoint[1]=Condition(mask, hitpointy, hitpoint[1]);
	hitpoint[2]=Condition(mask, hitpointz, hitpoint[2]);
	}
return mask;
}

#ifdef _WIN32
#undef main
#endif
int main(int argc, char *argv[])
{
//
//      Program options with Boost program options
//
int datasize,repeats,seed;
bool print_output,bitwise;
float dt,mass,velocity;

po::options_description desc("Allowed options");
desc.add_options()
    ("help,h", "produce help message")
    ("datasize,d", po::value<int>(&datasize)->default_value(512), "Datasize")
    ("repeats,r", po::value<int>(&repeats)->default_value(1), "Repeats")
    ("seed,s", po::value<int>(&seed)->default_value(-1), "Seed")
    ("dt,t", po::value<float>(&dt)->default_value(0.01f), "Time step")
    ("mass,m", po::value<float>(&mass)->default_value(1.0f), "Particle mass")
    ("vel,v", po::value<float>(&velocity)->default_value(0.0f), "Max starting velocity")
    ("print,p", po::value<bool>(&print_output)->default_value(false), "Print data to files")
    ("compare,c", po::value<bool>(&bitwise)->default_value(false), "Compare FP datas bitwise")
;

po::variables_map vm;
po::store(po::parse_command_line(argc, argv, desc), vm);
po::notify(vm);

if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
}

if (datasize % 4 != 0)
        {
        std::cout << "datasize must be multiple of 4" << std::endl;
        exit(0);
        }

std::random_device rd;
if (seed == -1)
        seed = rd();

std::default_random_engine gen(seed);
std::uniform_real_distribution<> dis(0,1);

vec3 pos;
pos[0]=10.0f;
pos[1]=0.0f;
pos[2]=0.0f;
float rad=5.0f;

vec4b mask=vec4(1.0f) > vec4(0.0f);
//ToggleMaskOff(0,mask);
//ToggleMaskOff(1,mask);
//ToggleMaskOff(2,mask);

//
//	Create data
//

std::vector<vec3> draydir;
std::vector<vec3> drayorig;
std::vector<mat4x3> draydir2;
std::vector<mat4x3> drayorig2;

vec3 one2;
one2=1.0f;
std::vector<vec3> normal(datasize,one2);
std::vector<vec3> hitpoint(datasize,one2);
std::vector<float> distance(datasize,1.0f);

mat4x3 one;
one[0]=vec4(1.0f);
one[1]=vec4(1.0f);
one[2]=vec4(1.0f);
std::vector<mat4x3> normal2(datasize/4,one);
std::vector<mat4x3> hitpoint2(datasize/4,one);
std::vector<vec4> distance2(datasize/4,vec4(1.0f));

mat4x3 raydir2,rayorig2;
int counter=0;
for (int i=0;i<datasize;i++)
        {
	vec3 raydir,rayorig;
        raydir[0] = 5.0f + 5.0f*dis(gen);
        raydir[1] = 0.1f*dis(gen);
        raydir[2] = 0.1f*dis(gen);
        rayorig[0]= 0.1f*dis(gen);
        rayorig[1]= 0.1f*dis(gen);
        rayorig[2]= 0.1f*dis(gen);
        draydir.push_back(raydir);
        drayorig.push_back(rayorig);
        raydir2[0][counter]=raydir[0];
        raydir2[1][counter]=raydir[1];
        raydir2[2][counter]=raydir[2];
        rayorig2[0][counter]=rayorig[0];
        rayorig2[1][counter]=rayorig[1];
        rayorig2[2][counter]=rayorig[2];
        if (counter == 3)
                {
                counter=0;
                draydir2.push_back(raydir2);
                drayorig2.push_back(rayorig2);
                }
        else
                counter++;
        }

//
//      Benchmarking
//
uint64_t tim=0;
uint64_t tim2=0;
timer t;

t.start();
for (int r=0;r<repeats;r++)
        {
        //      1st benchmark code here
	for (int i=0;i<draydir.size();i++)
	        intersect(draydir[i], drayorig[i], pos, rad, hitpoint[i], distance[i], normal[i]);
        }
tim = t.stop();

t.start();
for (int r=0;r<repeats;r++)
        {
        //      2nd benchmark code here
	//vec4b hitmask;
	for (int i=0;i<draydir2.size();i++)
        	intersect(draydir2[i], drayorig2[i], pos, rad, hitpoint2[i], distance2[i], normal2[i], mask);
        	//hitmask = intersect(draydir2[i], drayorig2[i], pos, rad, hitpoint2[i], distance2[i], normal2[i], mask);
	//if (!ForAll(hitmask))
	//	std::cout << "not all hit!" << std::endl;
        }
tim2 = t.stop();

if (print_output)
        {
        std::ofstream file("data1.dat",std::ios::out);
        std::ofstream file2("data2.dat",std::ios::out);

        for (int i=0;i<draydir.size();i++)
                file << std::setprecision(100) << normal[i] << " " << hitpoint[i] << " " << distance[i] << std::endl;
        for (int i=0;i<draydir2.size();i++)
                file2 << std::setprecision(100) << normal2[i] << " " << hitpoint2[i] << " " << distance2[i] << std::endl;
        }

std::cout << "SSE faster by factor: " << double(tim) / double(tim2) << std::endl;
//std::cout << double(tim) / double(tim2) << std::endl;

return 0;
}
