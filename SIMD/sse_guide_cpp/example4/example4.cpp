#include <vector>
#include <iostream>
#include <bitset>
#include <random>
#include <fstream>
#include <iomanip>
#include "./../sse.hpp"
#include "./../timer.hpp"
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#if VECLIB_SSE_VER<0x20
#error Need at least SSE2 support
#endif

#define noinline __attribute__((noinline))
#define finline  __attribute__((always_inline))

inline bool RayPlaneIntersection(const vec3& pos, const vec3& dir, const vec3& PlaneN, const vec3& PlanePoint, vec3& hitpoint)
{
        float t = sum((PlanePoint - pos)*PlaneN) / sum(dir * PlaneN);

        if (t >= 0.0f)
                {
                hitpoint = pos + t * dir;
                return true;
                }
        else
                return false;
}

typedef n_std::cvalarray<n_std::cvalarray<float,4>,3> smat4x3;
typedef n_std::cvalarray<float,4> svec4;
typedef n_std::cvalarray<bool,4> svec4b;

inline std::ostream& operator<< (std::ostream& output, const smat4x3& v)
{
for (int i=0;i<3;i++)
        output << "smat4x3 " << std::endl <<i <<"):" <<  v[i][0] << "\t" << v[i][1] << "\t" << v[i][2] << "\t" <<v[i][3] << std::endl;
return output;
}

noinline bool ConeQuadIntersection(const vec3& dir, const vec3& pos, const float cosphi2, const smat4x3& P)
{
svec4 pospx,pospy,pospz;
svec4 pospdir;
svec4 posp2;
svec4 pospdir2;

bool anyin=false;
svec4b otherside;

// Check if any of the points in inside the cone
for (int i=0;i<4;i++)
	{
	pospx[i]=P[0][i] - pos[0];
	pospy[i]=P[1][i] - pos[1];
	pospz[i]=P[2][i] - pos[2];
	pospdir[i] = pospx[i] * dir[0] + pospy[i] * dir[1] + pospz[i] * dir[2];
	
	if (pospdir[i] > 0)
		{
		anyin=true;
		otherside[i]=false;
		posp2[i] = pospx[i]*pospx[i] + pospy[i]*pospy[i] + pospz[i]*pospz[i];
		pospdir2[i] = pospdir[i]*pospdir[i];
		if (pospdir2[i] >= cosphi2 * posp2[i])
			{
			return true;
			}
		}
	else
		{
		otherside[i]=true;
		}
	}

if (!anyin)
	return false;

// Next test edges of the quad for intersection

vec3 edge1;
edge1[0] = P[0][1] - P[0][0];
edge1[1] = P[1][1] - P[1][0];
edge1[2] = P[2][1] - P[2][0];
float edge1l2 = edge1[0]*edge1[0] + edge1[1]*edge1[1] + edge1[2]*edge1[2];

if (!otherside[0] && !otherside[1])
	{
	float diredge = dir[0]*edge1[0] + dir[1]*edge1[1] + dir[2]*edge1[2];
	float c0 = pospdir2[0] - cosphi2*posp2[0];
	float c1 = diredge * pospdir[0] - cosphi2 * (edge1[0]*pospx[0] + edge1[1]*pospy[0] + edge1[2]*pospz[0]);
	float c2 = diredge*diredge - cosphi2 * edge1l2;

	if (c2 < 0.0f && 0.0f <= c1 && c1 <= (-1.0f)*c2 && c1*c1 >= c0*c2)
		return true;
	}

vec3 edge2;
edge2[0] = P[0][2] - P[0][0];
edge2[1] = P[1][2] - P[1][0];
edge2[2] = P[2][2] - P[2][0];
float edge2l2 = edge2[0]*edge2[0] + edge2[1]*edge2[1] + edge2[2]*edge2[2];

if (!otherside[0] && !otherside[2])
        {
        float diredge = dir[0]*edge2[0] + dir[1]*edge2[1] + dir[2]*edge2[2];
        float c0 = pospdir2[0] - cosphi2*posp2[0];
        float c1 = diredge * pospdir[0] - cosphi2 * (edge2[0]*pospx[0] + edge2[1]*pospy[0] + edge2[2]*pospz[0]);
        float c2 = diredge*diredge - cosphi2 * edge2l2;

        if (c2 < 0.0f && 0.0f <= c1 && c1 <= (-1.0f)*c2 && c1*c1 >= c0*c2)
		{
                return true;
		}
        }

for (int i=1;i<=2;i++)
{
if (!otherside[3] && !otherside[i])
        {
        vec3 edge;
        edge[0] = P[0][i] - P[0][3];
        edge[1] = P[1][i] - P[1][3];
        edge[2] = P[2][i] - P[2][3];
        float diredge = dir[0]*edge[0] + dir[1]*edge[1] + dir[2]*edge[2];
        float c0 = pospdir2[3] - cosphi2*posp2[3];
        float c1 = diredge * pospdir[3] - cosphi2 * (edge[0]*pospx[3] + edge[1]*pospy[3] + edge[2]*pospz[3]);
        float c2 = diredge*diredge - cosphi2 * (edge[0]*edge[0] + edge[1]*edge[1] + edge[2]*edge[2]);

        if (c2 < 0.0f && 0.0f <= c1 && c1 <= (-1.0f)*c2 && c1*c1 >= c0*c2)
                return true;
        }
}

// Next check if cone axis intersects quad

vec3 hitpoint;
vec3 planepoint;
planepoint[0]=P[0][0];
planepoint[1]=P[1][0];
planepoint[2]=P[2][0];
vec3 planenormal;

planenormal[0]=edge1[1]*edge2[2]-edge2[1]*edge1[2];
planenormal[1]=-edge1[0]*edge2[2]+edge2[0]*edge1[2];
planenormal[2]=edge1[0]*edge2[1]-edge2[0]*edge1[1];
float length = 1.0f/sqrtf(planenormal[0]*planenormal[0] + planenormal[1]*planenormal[1] + planenormal[2]*planenormal[2]);
planenormal *= length;

if (!RayPlaneIntersection(pos, dir, planenormal, planepoint, hitpoint))
        return false;

vec3 point = hitpoint - planepoint;

float p1 = ( point[0] * edge1[0] + point[1] * edge1[1] + point[2] * edge1[2] ) / edge1l2;
float p2 = ( point[0] * edge2[0] + point[1] * edge2[1] + point[2] * edge2[2] ) / edge2l2;

if (p1 >= 0.0f && p1 <= 1.0f && p2 >= 0.0f && p2 <= 1.0f) // cone inside quad?
	{
//	std::cout << "here " << std::endl;
//	exit(0);
        return true;
	}
else
        return false;

}

//	D = cone dir
//	L = cone start pos
//	cphi2 = cosine power 2 of cone angle
//	P = 4xvec3 Quad pos
//	Based on IntersectionTriangleCone.pdf
//
noinline bool ConeQuadIntersection(const vec3& D, const vec3& L, const float& cphi2, mat4x3& P)
{
vec4 LP0 = P[0] - L[0];
vec4 LP1 = P[1] - L[1];
vec4 LP2 = P[2] - L[2];
vec4 LPLP = LP0*LP0 + LP1*LP1 + LP2*LP2;
vec4 cLPLP = cphi2*LPLP;
vec4 LP0D = LP0*D[0] + LP1*D[1] + LP2*D[2];
vec4 LP0D2= LP0D*LP0D;
vec4b conesidemask = LP0D >= 0.0f;

if (ForAny(conesidemask))
	{
	vec4b insidemask = LP0D2 >= cLPLP;

	if (ForAny(insidemask && conesidemask)) // any point inside?
		return true;
	}
else
	return false; // all on other side of the plane

vec4 E0,E1,E2; // Edge vectors

E0[0] = P[0][1] - P[0][0];
E0[1] = P[0][2] - P[0][1];
E0[2] = P[0][3] - P[0][2];
E0[3] = P[0][0] - P[0][3];

E1[0] = P[1][1] - P[1][0];
E1[1] = P[1][2] - P[1][1];
E1[2] = P[1][3] - P[1][2];
E1[3] = P[1][0] - P[1][3];

E2[0] = P[2][1] - P[2][0];
E2[1] = P[2][2] - P[2][1];
E2[2] = P[2][3] - P[2][2];
E2[3] = P[2][0] - P[2][3];

vec4 DE = D[0]*E0 + D[1]*E1 + D[2]*E2;
vec4 c0 = LP0D2 - cLPLP;
vec4 c1 = DE * LP0D - cphi2 * (E0*LP0 + E1*LP1 + E2*LP2 );
vec4 Elen2 = E0*E0 + E1*E1 + E2*E2;
vec4 c2 = DE*DE - cphi2 * Elen2;

vec4b mask = c2 < 0.0f && c1*c1 >= c0*c2;

if (ForAny(mask)) // some edge can intersect
	{
	if (ForAll(conesidemask)) // all on the cone side
		{
		vec4b mask2 = mask && 0.0f <= c1 && c1 <= (-1.0f*c2);
		if (ForAny(mask2)) // edge intersects
			return true;
		}
	else
		{
		// unimplemented
		}
	}

vec3 hitpoint;
vec3 planepoint;
planepoint[0]=P[0][0];
planepoint[1]=P[1][0];
planepoint[2]=P[2][0];
vec3 planenormal;
planenormal[0]=E1[0]*E2[1]-E1[1]*E2[0];
planenormal[1]=-E0[0]*E2[1]+E0[1]*E2[0];
planenormal[2]=E0[0]*E1[1]-E0[1]*E1[0];
float length = 1.0f/sqrtf(planenormal[0]*planenormal[0] + planenormal[1]*planenormal[1] + planenormal[2]*planenormal[2]);
planenormal *= length;

if (!RayPlaneIntersection(L, D, planenormal, planepoint, hitpoint))
	return false;

vec3 point = hitpoint - planepoint;

float p1 = ( point[0] * E0[0] + point[1] * E1[0] + point[2] * E2[0] ) / Elen2[0];
float p2 = ( point[0] * E0[1] + point[1] * E1[1] + point[2] * E2[1] ) / Elen2[1];

if (p1 >= 0.0f && p1 <= 1.0f && p2 >= 0.0f && p2 <= 1.0f) // cone inside quad?
	return true;
else
	return false;
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

po::options_description desc("Allowed options");
desc.add_options()
    ("help,h", "produce help message")
    ("datasize,d", po::value<int>(&datasize)->default_value(512), "Datasize")
    ("repeats,r", po::value<int>(&repeats)->default_value(1), "Repeats")
    ("seed,s", po::value<int>(&seed)->default_value(-1), "Seed")
    ("print,p", po::value<bool>(&print_output)->default_value(false), "Print data to files")
    ("compare,c", po::value<bool>(&bitwise)->default_value(true), "Compare FP datas bitwise")
;

po::variables_map vm;
po::store(po::parse_command_line(argc, argv, desc), vm);
po::notify(vm);

if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
}

// Define a fixed cone at origin pointing in the direction of the positive x-axis with angle of pi/4
vec3 pos;
pos[0]=0.0f;
pos[1]=0.0f;
pos[2]=0.0f;
vec3 dir;
dir[0]=1.0f;
dir[1]=0.0f;
dir[2]=0.0f;
float cosphi = 1.0f/sqrtf(2.0f); // cos(45 degrees) = 1/sqrt(2)
float cosphi2 = cosphi*cosphi;

std::random_device rd;
if (seed == -1)
        seed = rd();

std::default_random_engine gen(seed);
std::uniform_real_distribution<> dis(-1,1);

//
//	Create quads
//

std::vector<smat4x3> pointset;
std::vector<mat4x3>  pointset2;
std::vector<bool> result(datasize);
std::vector<bool> result2(datasize);

mat4x3 raydir2,rayorig2;
int counter=0;
for (int i=0;i<datasize;i++)
        {
	smat4x3 P;
	mat4x3  P2;

	/* Construct a quad like

	P2----->P3
	|	|
	P0----->P1

	so that the normal of the quad is in the direction of x-axis. The center of mass point of the quad is at
	x-axis unless offsetx or offsety is defined.

	*/

        /* At distance = 5.0 quad side is the size of the diameter of the cone at the quad's plane.
	   This means it is exactly the point where the quad edges stop intersecting the cone. At
	   5.1 none of the vertices are inside cone and none of the edges intersect the cone. At
	   4.9 none of the vertices are inside cone and all of the edges intersect the cone. Increasing
	   distance further finally all of the quad vertices start being inside of the cone.
	*/
        float distance = 5.0f;
        float offsetx=0.0f;
        float offsety=0.0f;
	
	P[1][0]=offsetx-distance+dis(gen);
	P[2][0]=offsety-distance+dis(gen);
	P[1][1]=offsetx+distance+dis(gen);
	P[2][1]=offsety-distance+dis(gen);
	P[1][2]=offsetx-distance+dis(gen);
	P[2][2]=offsety+distance+dis(gen);
	P[1][3]=offsetx+distance+dis(gen);
	P[2][3]=offsety+distance+dis(gen);

	for (int i=0;i<4;i++)
		{
		P[0][i]=5.0f;
		P2[0][i] = P[0][i];
		P2[1][i] = P[1][i];
		P2[2][i] = P[2][i];
		}

	/* SSE version wants a quad defined like

	P3<-----P2
	|	|
	P0----->P1

	so switch P2 and P3

	*/

	P2[1][2]=P[1][3];
	P2[2][2]=P[2][3];
	P2[1][3]=P[1][2];
	P2[2][3]=P[2][2];

	pointset.push_back(P);
	pointset2.push_back(P2);
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
	for (int i=0;i<pointset.size();i++)
		result[i] = ConeQuadIntersection(dir, pos, cosphi2, pointset[i]);
        }
tim = t.stop();

t.start();
for (int r=0;r<repeats;r++)
        {
        //      2nd benchmark code here
	for (int i=0;i<pointset2.size();i++)
		result2[i] = ConeQuadIntersection(dir, pos, cosphi2, pointset2[i]);
        }
tim2 = t.stop();

// Ensure results are identical
if (bitwise)
	for (int i=0;i<pointset.size();i++)
		{
		if (result[i] != result2[i])
			{
			std::cout << "data differ!" << std::endl;
			exit(0);
			}
		}

if (print_output)
        {
        std::ofstream file("data1.dat",std::ios::out);
        std::ofstream file2("data2.dat",std::ios::out);

        for (int i=0;i<result.size();i++)
                file << result[i] << std::endl;
        for (int i=0;i<result2.size();i++)
                file2 << result2[i] << std::endl;
        }

std::cout << "SSE faster by factor: " << double(tim) / double(tim2) << std::endl;
//std::cout << double(tim) / double(tim2) << std::endl;

return 0;
}
