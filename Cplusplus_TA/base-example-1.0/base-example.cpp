#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <matrix4.h>
using namespace irr;
using namespace std;

/* The following class is for handling mouse and keyboard events
   You do not need to work on this. */
class MyEventReceiver : public IEventReceiver
{
public:
  core::position2di Position;
  virtual bool OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
	switch(event.MouseInput.Event)
	  {
	  case EMIE_MOUSE_MOVED:
	    Position.X = event.MouseInput.X;
	    Position.Y = event.MouseInput.Y;
	    break;
	    
	  default:
	    break;
	  }
      }    
    return false;
  }
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }
  MyEventReceiver()
  {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  } 
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


// The actual program
int main()
{
  // initialization of the irrLicht library/device
  video::E_DRIVER_TYPE driverType=video::EDT_OPENGL; 
  if (driverType==video::EDT_COUNT) return 1;
  MyEventReceiver receiver;  
  IrrlichtDevice* device = createDevice(driverType,
					core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
  if (device == 0) return 1; 
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  // add the sphere to the scene
  scene::ISceneNode * node = smgr->addSphereSceneNode(2.f,32);
  node->setPosition(core::vector3df(0,5.f,0));
  node->setMaterialFlag(video::EMF_LIGHTING
      			    , false);
  
  // add little cubes to the scene to form a boundary
  for(f32 i=-64.f; i<=64.f; i+=2.f){
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(-64.f,5.f,i));
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(64.f,5.f,i));
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(i,5.f,-64.f));
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(i,5.f,64.f));
  }
  const f32 minborder = -58.f;  
  const f32 maxborder = 58.f;

  // add a camera from where we are looking at the scene
  smgr->addCameraSceneNode(NULL,core::vector3df(20.f,120.f,0.f),core::vector3df(0.f,0.f,0.f));

  // hide the mouse cursor
  device->getCursorControl()->setVisible(false);

  // record the current time
  u32 then = device->getTimer()->getTime();

  int movex=1;
  int movey=1;
  int pause=1;

  // set the initial velocity of the sphere
  core::vector3df velocity(30.f,0.f,10.f);

  /* To be implemented: the sphere should get slower 
  by a certain factor due to friction over time, for
  simplicity we may not make this constant */
  f32 friction=.2f;

  // remember current mouse position
  core::position2di RefPosition=receiver.Position;

  // the main loop (basically running forever)
  while(device->run())
    {
      if(receiver.IsKeyDown(irr::KEY_KEY_Q)) exit(0); // quit game on key Q

      // Adapt speed by the difference in mouse position
      core::position2di mousemove;
      mousemove.X=(receiver.Position.X-RefPosition.X);
      mousemove.Y=(receiver.Position.Y-RefPosition.Y);
      // eliminating too rapid movements of the mouse
      if (fabs(mousemove.X)>10) mousemove.X=0;
      if (fabs(mousemove.Y)>10) mousemove.Y=0;      
      // update velocity 
      velocity.X += mousemove.Y;
      velocity.Z += mousemove.X;

      // remember current mouse position
      RefPosition=receiver.Position;

      // Measure the time that has passed since last drawing 
      const u32 now = device->getTimer()->getTime();
      const f32 frameDeltaTime = (f32)(now - then) / 1000.f; 
      then = now;

      // detect collision with wall and change speed accordingly
      core::vector3df nodePosition = node->getPosition();
      if (velocity.X<0){
	if (nodePosition.X<minborder){
	  velocity.X = -velocity.X;
	}
      }
      else{
	if (nodePosition.X>maxborder){
	  velocity.X = -velocity.X;
	}
      }
      
      if (velocity.Z<0){
	if (nodePosition.Z<minborder){
	  velocity.Z = -velocity.Z;
	}
      }
      else{
	if (nodePosition.Z>maxborder){
	  velocity.Z = -velocity.Z;
	}
      }


      // Update position
      nodePosition.X += velocity.X*frameDeltaTime;
      nodePosition.Z += velocity.Z*frameDeltaTime;
      node->setPosition(nodePosition);
     
      // Draw the picture anew
      driver->beginScene(true, true, video::SColor(255,113,113,133));
      smgr->drawAll();
      driver->endScene();
    }
  device->drop();
  return 0;
}
















