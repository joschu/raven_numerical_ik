#include <openrave/openrave.h>
#include <openrave-core.h>
using namespace OpenRAVE;
using namespace std;

int main(int argc, char* argv[]) {
	RaveInitialize(true);
	EnvironmentBasePtr env = RaveCreateEnvironment();
	env->Load("/home/joschu/Dropbox/Proj/Raven/collada/ravenII_2arm.dae");
	OpenRAVE::ViewerBasePtr viewer = OpenRAVE::RaveCreateViewer(env, "qtcoin");
	int ind_arr[7] = {};
	double val_arr[7] = {};
	viewer->main(true);
}
