#include <openrave/openrave.h>
#include <openrave-core.h>
#include "stdafx.h"
#include "GeneralIK.h"
using namespace std;
using namespace OpenRAVE;

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

int main(int argc, char* argv[]) {
	RaveInitialize(true);
	EnvironmentBasePtr env = RaveCreateEnvironment();
	env->Load(EXPAND(RAVEN_DATA_DIR) "/ravenII_2arm.xml");
	OpenRAVE::ViewerBasePtr viewer = OpenRAVE::RaveCreateViewer(env, "qtcoin");
	const size_t n_joints = 16;
	double val_arr[n_joints] = {0, 0.51637494564056396, 1.627062201499939, -0.049243684858083725, -7.1537528128828853e-05, 0.00013125920668244362, 0.92412233352661133, 0.89203071594238281,
						        0, 0.67030531167984009, 1.8251663446426392, -0.062828727066516876, -0.0041922205127775669, 0.0022199407685548067, -0.65188699960708618, -0.66819572448730469};
	vector<double> joint_vals;
	joint_vals.assign(val_arr, val_arr+n_joints);
	RobotBasePtr raven = env->GetRobot("raven_2");
	raven->SetDOFValues(joint_vals);
	vector<RobotBase::ManipulatorPtr> manips = 	raven->GetManipulators();
	RobotBase::ManipulatorPtr leftarm = manips[0];
	RobotBase::ManipulatorPtr rightarm = manips[1];

	raven->SetActiveManipulator(0);
	raven->SetActiveDOFs(leftarm->GetArmIndices());
	GeneralIK iksolver(env);
	iksolver.Init(leftarm);

	Transform current_pose = leftarm->GetTransform();
	vector<double> current_vals;
	current_vals.assign(&joint_vals[1], &joint_vals[7]);
	vector<double> free_params(1,6);
	boost::shared_ptr< vector<double> > result( new vector<double> );
	iksolver.Solve(IkParameterization(current_pose), current_vals, free_params, 0, result);
	viewer->main(true);
}
