// Example two. N-particle dynamics

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <bitset>
#include <fstream>
#include "./../timer.hpp"
#include "./../sse.hpp"
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#if VECLIB_SSE_VER<0x20
#error Need at least SSE2 support
#endif

class Particle {
public:
vec3 pos;
vec3 vel;
vec3 acc;
float mass;

Particle(vec3 pos, vec3 vel, float mass)
{
Particle::pos=pos;
Particle::vel=vel;
Particle::acc=0.0f;
Particle::mass=mass;
}

/** Newton's gravitation law */
void force(Particle& p)
{
vec3 diff = pos - p.pos;
float r2=sum(diff*diff);
diff /= sqrtf(r2)*(r2+1.0f);
acc   -= diff*p.mass;
p.acc += diff*mass;
}
};

/** SSE version of Particle */
class NParticle {
public:
mat4x3 pos;
mat4x3 vel;
mat4x3 acc;
vec4 mass;

NParticle(mat4x3 pos, mat4x3 vel, vec4 mass)
{
NParticle::pos=pos;
NParticle::vel=vel;
NParticle::acc=0.0f;
NParticle::mass=mass;
}

/** Calculate forces to each Particle from another NParticle */
void force(NParticle& p)
{
for (int n=0;n<4;n++)
	{
	vec4 diffx = vec4(pos[0][n]) - p.pos[0];
	vec4 diffy = vec4(pos[1][n]) - p.pos[1];
	vec4 diffz = vec4(pos[2][n]) - p.pos[2];
	vec4 r2 = diffx*diffx + diffy*diffy + diffz*diffz;
	vec4 rlen = 1.0f/(Sqrt(r2)*(r2+1.0f));
	diffx *= rlen;
	diffy *= rlen;
	diffz *= rlen;
	acc[0][n] -= sum(diffx*p.mass);
	acc[1][n] -= sum(diffy*p.mass);
	acc[2][n] -= sum(diffz*p.mass);
	p.acc[0] += diffx*mass;
	p.acc[1] += diffy*mass;
	p.acc[2] += diffz*mass;
	}
}

/** Calculate forces to a single particle from another NParticle. More optimal. */
void force(NParticle& p, const vec4& posx, const vec4& posy, const vec4& posz, vec4& accx, vec4& accy, vec4& accz)
{
        vec4 diffx = posx - p.pos[0];
        vec4 diffy = posy - p.pos[1];
        vec4 diffz = posz - p.pos[2];
        vec4 r2 = diffx*diffx + diffy*diffy + diffz*diffz;
        vec4 rlen = 1.0f/(Sqrt(r2)*(r2+1.0f));
        diffx *= rlen;
        diffy *= rlen;
        diffz *= rlen;
        accx -= diffx*p.mass;
        accy -= diffy*p.mass;
        accz -= diffz*p.mass;
        p.acc[0] += diffx*mass;
        p.acc[1] += diffy*mass;
        p.acc[2] += diffz*mass;
}

// Calculate forces between particles inside this NParticle
void insideforces(void)
{
for (int n=0;n<4;n++)
	for (int k=n+1;k<4;k++)
	{
	vec3 diff;
	diff[0] = pos[0][n] - pos[0][k];
	diff[1] = pos[1][n] - pos[1][k];
	diff[2] = pos[2][n] - pos[2][k];
	float r2=sum(diff*diff);
	diff /= sqrtf(r2)*(r2+1.0f);
	acc[0][n] -= diff[0]*mass[k];
	acc[1][n] -= diff[1]*mass[k];
	acc[2][n] -= diff[2]*mass[k];
	acc[0][k] += diff[0]*mass[n];
	acc[1][k] += diff[1]*mass[n];
	acc[2][k] += diff[2]*mass[n];
	}
}

};

#ifdef _WIN32
#undef main
#endif
int main(int argc, char *argv[])
{
if (sizeof(float) != sizeof(int))
	{
	std::cout << "float != int" << std::endl;
	exit(0);
	}

//
//	Program options with Boost program options
//
int datasize,iterations,seed;
bool print_output,bitwise;
float dt,mass,velocity;

po::options_description desc("Allowed options");
desc.add_options()
    ("help,h", "produce help message")
    ("datasize,d", po::value<int>(&datasize)->default_value(512), "Datasize")
    ("iterations,i", po::value<int>(&iterations)->default_value(100), "Iterations")
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

vec4 dt4 = vec4(dt);

timer t;

//
//	Create identical datasets
//
std::vector<Particle> data1;
std::vector<NParticle> data2;

std::random_device rd;
if (seed == -1)
	seed = rd();

std::default_random_engine gen(seed);
std::uniform_real_distribution<> dis(0,1);

mat4x3 SSEpos,SSEvel;
int counter=0;
for (int i=0;i<datasize;i++)
	{
	float maxrad=1.0f;
	vec3 pos;
	pos[0]=2.0f*maxrad*dis(gen) - 1.0f;
	pos[1]=2.0f*maxrad*dis(gen) - 1.0f;
	pos[2]=2.0f*maxrad*dis(gen) - 1.0f;
	vec3 vel;
	vel[0]=velocity*dis(gen);
	vel[1]=velocity*dis(gen);
	vel[2]=velocity*dis(gen);

	data1.push_back(Particle(pos,vel,mass));
	
	SSEpos[0][counter]=pos[0];
	SSEpos[1][counter]=pos[1];
	SSEpos[2][counter]=pos[2];
        SSEvel[0][counter]=vel[0];
        SSEvel[1][counter]=vel[1];
        SSEvel[2][counter]=vel[2];

	if (counter == 3)
		{
		counter=0;
		data2.push_back(NParticle(SSEpos, SSEvel,vec4(mass)));
		}
	else
		counter++;
	}

//
//	Benchmarking
//

uint64_t tim,tim2;
t.start();
for (int r=0;r<iterations;r++)
        {
        //      1st benchmark code here
	for (int i=0;i<data1.size();i++)
		data1[i].acc=0.0f;

	for (int i=0;i<data1.size();i++)
		for (int j=i+1;j<data1.size();j++)
			data1[i].force(data1[j]);

	for (int i=0;i<data1.size();i++)
		{
		data1[i].vel += data1[i].acc*dt;
	        data1[i].pos += data1[i].vel*dt;
		}
        }
tim = t.stop();

t.start();
for (int r=0;r<iterations;r++)
        {
        //      2nd benchmark code here
	for (int i=0;i<data2.size();i++)
		data2[i].acc=0.0f;

	for (int i=0;i<data2.size();i++)
		{
		data2[i].insideforces();
		for (int n=0;n<4;n++)
		{
			vec4 posx = data2[i].pos[0][n];
			vec4 posy = data2[i].pos[1][n];
			vec4 posz = data2[i].pos[2][n];
			vec4 accx=0.0f;
			vec4 accy=0.0f;
			vec4 accz=0.0f;
		        for (int j=i+1;j<data2.size();j++)
				data2[i].force(data2[j],posx,posy,posz,accx,accy,accz);
			data2[i].acc[0][n] += sum(accx);
			data2[i].acc[1][n] += sum(accy);
			data2[i].acc[2][n] += sum(accz);
		}
		}

	for (int i=0;i<data2.size();i++)
		{
		data2[i].vel += data2[i].acc*dt4;
		data2[i].pos += data2[i].vel*dt4;
		}

        }
tim2 = t.stop();

//
//	Compare results bitwise NOTE: calculations performed in different order between paths!
//

if (bitwise)
{
counter=0;
int counter2=0;
for (int i=0;i<data1.size();i++)
        {
	for (int r=0;r<3;r++)
		{
		int f1 = *(int*)&data1[i].pos[r];
		int f2 = *(int*)&data2[counter2].pos[r][counter];

		if (f1 != f2)
			{
			std::cout << "Error! Floating point results differ between scalar and SSE!" << std::endl;
			std::cout << std::setprecision(100) << data1[i].pos[r] << std::endl;
			std::cout << std::setprecision(100) << data2[counter2].pos[r][counter] << std::endl;
			exit(0);
			}
		}

        if (counter == 3)
		{
                counter=0;
		counter2++;
		}
        else
                counter++;
        }
}

//
//	Optionally print output to files
//

if (print_output)
	{
	std::ofstream file("data1.dat",std::ios::out);
	std::ofstream file2("data2.dat",std::ios::out);

	for (int i=0;i<data1.size();i++)
		file << std::setprecision(100) << data1[i].pos << std::endl;
	for (int i=0;i<data2.size();i++)
		file2 << std::setprecision(100) << data2[i].pos << std::endl;
	}

std::cout << "SSE faster by factor: " << double(tim) / double(tim2) << std::endl;
//std::cout << double(tim) / double(tim2) << std::endl;

return 0;
}
