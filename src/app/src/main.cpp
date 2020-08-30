#include <iostream>
#include "VideoTracker.h"
#include "param.h"
using namespace std;

void read_vid(VideoTracker t)
{
	t.Video_Read();
}

void run_vid(VideoTracker t)
{
	t.run();
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << "/path/to/the/config/file" << std::endl;
		exit(-1);
	}

	DeepSortParam params;
	params.read(argv[1]);

	
	VideoTracker t(params);
	// std::cout << "Tracker inited " << std::endl;
	// std::thread thread1(read_vid,t);
	// std::thread thread2(run_vid, t);
	// thread1.join();
	// thread2.join();
	t.run();
	return 0;
}
