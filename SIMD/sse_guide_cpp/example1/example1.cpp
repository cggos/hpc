// Example one. Normalizing AOS vectors

#include <iostream>
#include <vector>
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

#define noinline __attribute__((noinline))
#define finline  __attribute__((always_inline))

// Scalar
noinline void normalize(std::vector<vec3>& data)
{
  for (int i=0;i<data.size();i++)
  {
    vec3& m = data[i];
    m /= sqrtf( m[0]*m[0] + m[1]*m[1] + m[2]*m[2] );
  }
}

// SSE
noinline void normalize(std::vector<mat4x3>& data)
{
  for (int i=0;i<data.size();i++)
  {
    vec4 mx = data[i][0]; 
    vec4 my = data[i][1];
    vec4 mz = data[i][2];

    vec4 multiplier = 1.0f/Sqrt(mx*mx + my*my + mz*mz);
    mx*=multiplier;
    my*=multiplier;
    mz*=multiplier;

    data[i][0]=mx;
    data[i][1]=my;
    data[i][2]=mz;
  }
}

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
int datasize,repeats;
bool print_output,bitwise;

po::options_description desc("Allowed options");
desc.add_options()
    ("help,h", "produce help message")
    ("datasize,d", po::value<int>(&datasize)->default_value(10000), "Datasize")
    ("repeats,r", po::value<int>(&repeats)->default_value(1), "Repeats")
    ("print,p", po::value<bool>(&print_output)->default_value(false), "Print data to files")
    ("compare,c", po::value<bool>(&bitwise)->default_value(false), "Compare output bitwise")
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

timer t;

//
//	Create identical AOS datasets
//
std::vector<vec3 > data1; // scalar AOS
std::vector<mat4x3> data2; // SSE AOS

mat4x3 input2;
int counter=0;
for (int i=0;i<datasize;i++)
	{
	vec3 input;
	input[0]=5 + (i+1);
	input[1]=i+1;
	input[2]=i+1;
	data1.push_back(input);
	
	input2[0][counter]=5 + (i+1);
	input2[1][counter]=i+1;
	input2[2][counter]=i+1;

	if (counter == 3)
		{
		counter=0;
		data2.push_back(input2);
		}
	else
		counter++;
	}

//
//	Benchmarking
//
uint64_t tim=0;
uint64_t tim2=0;

t.start();
for (int r=0;r<repeats;r++)
        {
        //      1st benchmark code here
	normalize(data1);
        }
tim = t.stop();

t.start();
for (int r=0;r<repeats;r++)
        {
        //      2nd benchmark code here
	normalize(data2);
        }
tim2 = t.stop();

//
//	Compare results bitwise
//

if (bitwise) {
counter=0;
int counter2=0;
for (int i=0;i<data1.size();i++)
        {
	for (int r=0;r<3;r++)
		{
		int f1 = *(int*)&data1[i][r];
		int f2 = *(int*)&data2[counter2][r][counter];

		if (f1 != f2)
			{
			std::cout << "Error! Floating point results differ between scalar and SSE!" << std::endl;
			std::cout << data1[i][r] << std::endl;
			std::cout << data2[counter2][r][counter] << std::endl;
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
		file << std::setprecision(100) << data1[i] << std::endl;
	for (int i=0;i<data2.size();i++)
		file2 << std::setprecision(100) << data2[i] << std::endl;
	}

std::cout << "SSE faster by factor: " << double(tim) / double(tim2) << std::endl;
//std::cout << double(tim) / double(tim2) << std::endl;

return 0;
}
