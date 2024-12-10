#include <gazebo/gazebo.hh> //basic gazebo functions 

namespace gazebo 
{
	class WorldPluginTutorial : public WorldPlugin //each plugin must inherit from a plugin type
	{
		public: WorldPluginTutorial() : WorldPlugin() { //WorldPlugin class
			printf("Hello World!\n");
		}
		public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) {} //receives SDF element
	}; 
	GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial) //a macro that registers w/ the simulator
}
