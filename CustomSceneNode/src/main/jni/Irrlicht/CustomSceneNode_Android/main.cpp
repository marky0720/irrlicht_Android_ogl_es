/** Example 027 Helloworld_Android
	This example shows a simple application for Android.
*/

#include "IrrCompileConfig.h"
#include <irrlicht.h>


#ifdef _IRR_ANDROID_PLATFORM_

#include <android_native_app_glue.h>
#include "android_tools.h"
#include "android/window.h"
#include <android/log.h>
#include <stdio.h>
#include "os.h"


/* Add by marky for customScene */
#include "driverChoice.h"
/* End by marky for customScene */

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "sensor", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


/* Add by marky for customScene */
#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

/*
Here comes the more sophisticated part of this tutorial:
The class of our very own custom scene node. To keep it simple,
our scene node will not be an indoor portal renderer nor a terrain
scene node, but a simple tetrahedron, a 3D object consisting of 4
connected vertices, which only draws itself and does nothing more.
Note that this scenario does not require a custom scene node in Irrlicht.
Instead one would create a mesh from the geometry and pass it to a
irr::scene::IMeshSceneNode. This example just illustrates creation of a custom
scene node in a simple setting.

To allow our scene node to be inserted into the Irrlicht
Engine scene, the class we create needs to be derived from the
irr::scene::ISceneNode class and has to override some methods.
*/

class CSampleSceneNode : public scene::ISceneNode
{

	/*
	First, we declare some member variables:
	The bounding box, 4 vertices, and the material of the tetrahedron.
	*/
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;

public:

	/*
	The parameters of the constructor specify the parent of the scene node,
	a pointer to the scene manager, and an id of the scene node.
	In the constructor we call the parent class' constructor,
	set some properties of the material, and create the 4 vertices of 
	the tetrahedron.
	*/

	CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id)
	{
		Material.Wireframe = false;
		Material.Lighting = false;
		Material.Thickness=0.f;

		Vertices[0] = video::S3DVertex(0,0,10, 5,1,0,
				video::SColor(255,0,255,255), 0, 1);
		Vertices[1] = video::S3DVertex(10,0,-10, 10,0,0,
				video::SColor(255,255,0,255), 1, 1);
		Vertices[2] = video::S3DVertex(0,20,0, 20,1,1,
				video::SColor(255,255,255,0), 1, 0);
		Vertices[3] = video::S3DVertex(-10,0,-10, 40,0,1,
				video::SColor(255,0,255,0), 0, 0);

	/*
	The Irrlicht Engine needs to know the bounding box of a scene node.
	It will use it for automatic culling and other things. Hence, we
	need to create a bounding box from the 4 vertices we use.
	If you do not want the engine to use the box for automatic culling,
	and/or don't want to create the box, you could also call
	irr::scene::ISceneNode::setAutomaticCulling() with irr::scene::EAC_OFF.
	*/
		Box.reset(Vertices[0].Pos);
		for (s32 i=1; i<4; ++i)
			Box.addInternalPoint(Vertices[i].Pos);
	}

	/*
	Before it is drawn, the irr::scene::ISceneNode::OnRegisterSceneNode()
	method of every scene node in the scene is called by the scene manager.
	If the scene node wishes to draw itself, it may register itself in the
	scene manager to be drawn. This is necessary to tell the scene manager
	when it should call irr::scene::ISceneNode::render(). For
	example, normal scene nodes render their content one after another,
	while stencil buffer shadows would like to be drawn after all other
	scene nodes. And camera or light scene nodes need to be rendered before
	all other scene nodes (if at all). So here we simply register the
	scene node to render normally. If we would like to let it be rendered
	like cameras or light, we would have to call
	SceneManager->registerNodeForRendering(this, SNRT_LIGHT_AND_CAMERA);
	After this, we call the actual irr::scene::ISceneNode::OnRegisterSceneNode() 
	method of the base class, which lets all the child scene nodes of this node 
	register themselves.
	*/
	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	/*
	In the render() method most of the interesting stuff happens: The
	Scene node renders itself. We override this method and draw the
	tetrahedron.
	*/
	virtual void render()
	{
		/* Indices into the 'Vertices' array. A triangle needs 3 vertices 
		so you have to pass the 3 corresponding indices for each triangle to 
		tell which of the vertices should be used for it.	*/
		u16 indices[] = {	0,2,3, 2,1,3, 1,0,3, 2,0,1	}; 
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
	}

	/*
	And finally we create three small additional methods.
	irr::scene::ISceneNode::getBoundingBox() returns the bounding box of
	this scene node, irr::scene::ISceneNode::getMaterialCount() returns the
	amount of materials in this scene node (our tetrahedron only has one
	material), and irr::scene::ISceneNode::getMaterial() returns the
	material at an index. Because we have only one material, we can
	return that and assume that no one ever calls getMaterial() with an index 
	greater than 0.
	*/
	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return Material;
	}	
};
/* End by marky for customScene */

enum GUI_IDS
{
	GUI_INFO_FPS,
	GUI_IRR_LOGO,
};


/*
	Android is using multitouch events.
	We allow users to move around the Irrlicht logo as example of how to use those.
*/
class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(android_app* app )
	: Device(0), AndroidApp(app), SpriteToMove(0), TouchID(-1)
	{
	}

	void Init(IrrlichtDevice *device)
	{
		Device = device;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_TOUCH_INPUT_EVENT)
		{
			/*
				For now we fake mouse-events. Touch-events will be handled inside Irrlicht in the future, but until
				that is implemented you can use this workaround to get a GUI which works at least for simple elements like
				buttons. That workaround does ignore multi-touch events - if you need several buttons pressed at the same
				time you have to handle that yourself.
			*/
			SEvent fakeMouseEvent;
			fakeMouseEvent.EventType = EET_MOUSE_INPUT_EVENT;
			fakeMouseEvent.MouseInput.X = event.TouchInput.X;
			fakeMouseEvent.MouseInput.Y = event.TouchInput.Y;
			fakeMouseEvent.MouseInput.Shift = false;
			fakeMouseEvent.MouseInput.Control = false;
			fakeMouseEvent.MouseInput.ButtonStates = 0;
			fakeMouseEvent.MouseInput.Event = EMIE_COUNT;

			switch (event.TouchInput.Event)
			{
				case ETIE_PRESSED_DOWN:
				{
					// We only work with the first for now.force opengl error
					if ( TouchID == -1 )
					{
						fakeMouseEvent.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;

						if (Device)
						{
							position2d<s32> touchPoint(event.TouchInput.X, event.TouchInput.Y);
							IGUIElement * logo = Device->getGUIEnvironment()->getRootGUIElement()->getElementFromId ( GUI_IRR_LOGO );
							if ( logo && logo->isPointInside (touchPoint) )
							{
								TouchID = event.TouchInput.ID;
								SpriteToMove = logo;
								SpriteStartRect =  SpriteToMove->getRelativePosition();
								TouchStartPos = touchPoint;
							}
						}
					}
					break;
				}
				case ETIE_MOVED:
					if ( TouchID == event.TouchInput.ID )
					{
						fakeMouseEvent.MouseInput.Event = EMIE_MOUSE_MOVED;
						fakeMouseEvent.MouseInput.ButtonStates = EMBSM_LEFT;

						if ( SpriteToMove && TouchID == event.TouchInput.ID )
						{

							position2d<s32> touchPoint(event.TouchInput.X, event.TouchInput.Y);
							MoveSprite(touchPoint);
						}
					}
					break;
				case ETIE_LEFT_UP:
					if ( TouchID == event.TouchInput.ID )
					{
						fakeMouseEvent.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;

						if ( SpriteToMove )
						{
							TouchID = -1;
							position2d<s32> touchPoint(event.TouchInput.X, event.TouchInput.Y);
							MoveSprite(touchPoint);
							SpriteToMove = 0;
						}
					}
					break;
				default:
					break;
			}

			if ( fakeMouseEvent.MouseInput.Event != EMIE_COUNT && Device )
			{
				Device->postEventFromUser(fakeMouseEvent);
			}
		}
		else if ( event.EventType == EET_GUI_EVENT )
		{
			/*
				Show and hide the soft input keyboard when an edit-box get's the focus.
			*/
			switch(event.GUIEvent.EventType)
			{
				case EGET_EDITBOX_ENTER:
					if ( event.GUIEvent.Caller->getType() == EGUIET_EDIT_BOX )
					{
						if( Device->getGUIEnvironment() )
							Device->getGUIEnvironment()->setFocus(NULL);
						android::setSoftInputVisibility(AndroidApp, false);
					}
				break;
                case EGET_ELEMENT_FOCUS_LOST:
					if ( event.GUIEvent.Caller->getType() == EGUIET_EDIT_BOX )
					{
						/* 	Unfortunatly this only works on some android devices.
							On other devices Android passes through touch-input events when the virtual keyboard is clicked while blocking those events in areas where the keyboard isn't.
							Very likely an Android bug as it only happens in certain cases (like Android Lollipop with landscape mode on MotoG, but also some reports from other devices).
							Or maybe Irrlicht still does something wrong.
							Can't figure it out so far - so be warned - with landscape mode you might be better off writing your own keyboard.
						*/
						android::setSoftInputVisibility(AndroidApp, false);
					}
                break;
                case EGET_ELEMENT_FOCUSED:
					if ( event.GUIEvent.Caller->getType() == EGUIET_EDIT_BOX )
					{
						android::setSoftInputVisibility(AndroidApp, true);
					}
                break;
				default:
					break;
			}
		}

		return false;
	}

	void MoveSprite(const irr::core::position2d<irr::s32> &touchPos)
	{
		irr::core::position2d<irr::s32> move(touchPos-TouchStartPos);
		SpriteToMove->setRelativePosition(SpriteStartRect.UpperLeftCorner + move);
	}

private:
	IrrlichtDevice * Device;
	android_app* AndroidApp;
	gui::IGUIElement * SpriteToMove;
	core::rect<s32> SpriteStartRect;
	core::position2d<irr::s32> TouchStartPos;
	s32 TouchID;
};

/* Mainloop.
*/
 #if 0   
void mainloop( IrrlichtDevice *device, IGUIStaticText * infoText )
{
	u32 loop = 0;	// loop is reset when the app is destroyed unlike runCounter
	static u32 runCounter = 0;	// static's seem to survive even an app-destroy message (not sure if that's guaranteed).
	while(device->run())
	{
		//LOGW("marky mainloop file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
		/*
			The window seems to be always active in this setup.
			That's because when it's not active Android will stop the code from running.
		*/
		if (device->isWindowActive())
		{
			/*
				Show FPS and some counters to show which parts of an app run
				in different app-lifecycle states.
			*/
  
			if ( infoText )
			{
				//LOGW("marky mainloop file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
				stringw str = L"FPS:";
				str += (s32)device->getVideoDriver()->getFPS();
				str += L" r:";
				str += runCounter;
				str += L" l:";
				str += loop;
				infoText->setText ( str.c_str() );
			}
    

			device->getVideoDriver()->beginScene(true, true, SColor(0,100,100,100));
			device->getSceneManager()->drawAll();
			device->getGUIEnvironment()->drawAll();
			device->getVideoDriver()->endScene ();
		}
		device->yield(); // probably nicer to the battery
		++runCounter;
		++loop;
	}
}
#else
  void mainloop( IrrlichtDevice *device ,IVideoDriver* driver, ISceneManager* smgr) {
	u32 frames=0;
	while(device->run())
	{


		driver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, video::SColor(0,100,100,100));
		smgr->drawAll();
        device->getGUIEnvironment()->drawAll();
		driver->endScene();
		if (++frames==100) // don't update more often, setWindowCaption can be expensive
		{
			LOGW("marky mainloop file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

			device->setWindowCaption(str.c_str());
			frames=0;
		}
	}  
  }
#endif  

/* Main application code. */
void android_main(android_app* app)
{
	// Make sure glue isn't stripped.
	app_dummy();
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);

	/*
		The receiver can already receive system events while createDeviceEx is called.
		So we create it first.
	*/
	MyEventReceiver receiver(app);
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);

	/*
		Create the device.
		You have currently the choice between 2 drivers:
		EDT_OGLES1 is basically a opengl fixed function pipeline.
		EDT_OGLES2 is a shader pipeline. Irrlicht comes with shaders to simulate
				   typical fixed function materials. For this to work the
				   corresponding shaders from the Irrlicht media/Shaders folder are
				   copied to the application assets folder (done in the Makefile).
	*/
	SIrrlichtCreationParameters param;
	param.DeviceType = EIDT_ANDROID;
	param.DriverType = EDT_OGLES1;				// android:glEsVersion in AndroidManifest.xml should be "0x00010000" (requesting 0x00020000 will also guarantee that ES1 works)
//	param.DriverType = EDT_OGLES2;				// android:glEsVersion in AndroidManifest.xml should be "0x00020000"
//    param.DriverType = EDT_SOFTWARE;
	param.WindowSize = dimension2d<u32>(0,0);	// using 0,0 it will automatically set it to the maximal size //marky : 0, 0 doesnot work

	param.PrivateData = app;
	param.Bits = 24;
	param.ZBufferBits = 16;
	param.AntiAlias  = 0;
	param.EventReceiver = &receiver;

	/* Logging is written to a file. So your application should disable all logging when you distribute your
       application or it can fill up that file over time.
	*/
#ifndef _DEBUG
	param.LoggingLevel = ELL_NONE;
#endif

	IrrlichtDevice *device = createDeviceEx(param);
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	if (device == 0)
       	return;
    LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	receiver.Init(device);
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);

//	ANativeActivity_setWindowFlags(app->activity, AWINDOW_FLAG_FULLSCREEN, 0);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	ILogger* logger = device->getLogger();
	IFileSystem * fs = device->getFileSystem();
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);

	/* Access to the Android native window. You often need this when accessing NDK functions like we are doing here.
	   Note that windowWidth/windowHeight have already subtracted things like the taskbar which your device might have,
	   so you get the real size of your render-window.
	*/
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	ANativeWindow* nativeWindow = static_cast<ANativeWindow*>(driver->getExposedVideoData().OGLESAndroid.Window);
	int32_t windowWidth = ANativeWindow_getWidth(app->window);
	int32_t windowHeight = ANativeWindow_getHeight(app->window);

	/* Get display metrics. We are accessing the Java functions of the JVM directly in this case as there is no NDK function for that yet.
	   Checkout android_tools.cpp if you want to know how that is done. */
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	irr::android::SDisplayMetrics displayMetrics;
	memset(&displayMetrics, 0, sizeof displayMetrics);
	irr::android::getDisplayMetrics(app, displayMetrics);


	/* For troubleshooting you can use the Irrlicht logger.
       The Irrlicht logging messages are send to the Android logging system using the tag "Irrlicht".
	   They stay in a file there, so you can check them even after running your app.
       You can watch them with the command: "adb logcat Irrlicht:V DEBUG:V *:S"
       This means Irrlicht _V_erbose, debug messages verbose (p.E callstack on crashes) and all other messages _S_ilent.
	   Clean the logging file with: "adb logcat -c".
       See http://developer.android.com/tools/debugging/debugging-log.html for more advanced log options.
	*/
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	char strDisplay[1000];
	sprintf(strDisplay, "Window size:(%d/%d)\nDisplay size:(%d/%d)", windowWidth, windowHeight, displayMetrics.widthPixels, displayMetrics.heightPixels);
	logger->log(strDisplay);

	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	core::dimension2d<s32> dim(driver->getScreenSize());
	sprintf(strDisplay, "getScreenSize:(%d/%d)", dim.Width, dim.Height);
	logger->log(strDisplay);


#if 0
	/* Your media must be somewhere inside the assets folder. The assets folder is the root for the file system.
	   This example copies the media in the Android.mk makefile. */
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
   	stringc mediaPath = "/sdcard/irr/";

	// The Android assets file-system does not know which sub-directories it has (blame google).
	// So we have to add all sub-directories in assets manually. Otherwise we could still open the files,
	// but existFile checks will fail (which are for example needed by getFont).
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	for ( u32 i=0; i < fs->getFileArchiveCount(); ++i )
	{
		IFileArchive* archive = fs->getFileArchive(i);
		if ( archive->getType() == EFAT_ANDROID_ASSET )
		{
			archive->addDirectoryToFileList(mediaPath);
			break;
		}
	}

	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	/* Set the font-size depending on your device.
	   dpi=dots per inch. 1 inch = 2.54 cm. */
	IGUISkin* skin = guienv->getSkin();
	IGUIFont* font = 0;
	if ( displayMetrics.xdpi < 100 ) {	// just guessing some value where fontsize might start to get too small
		LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
		font = guienv->getFont(mediaPath + "fonthaettenschweiler.bmp");
	}
	else {
	    LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
		font = guienv->getFont(mediaPath + "bigfont.png");
	}

	if (font) {
		LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
		skin->setFont(font);
    }

	// A field to show some text. Comment out stat->setText in run() if you want to see the dpi instead of the fps.
    guienv->getFont("/sdcard/irr/fonthaettenschweiler.bmp");  //add by marky
	IGUIStaticText *text = guienv->addStaticText(stringw(displayMetrics.xdpi).c_str(),
		rect<s32>(5,5,635,35), false, false, 0, GUI_INFO_FPS );
	//IGUIStaticText *text = guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
	//	rect<s32>(5,5,635,35), false, false, 0, GUI_INFO_FPS );
	guienv->addEditBox( L"", rect<s32>(5,40,475,80));


    //Add by marky
	/*
	We add a hello world label to the window, using the GUI environment.
	The text is placed at the position (10,10) as top left corner and
	(260,22) as lower right corner.
	*/

	//guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
	//	rect<s32>(10,10,260,22), true);

	// add irrlicht logo
	IGUIImage * logo = guienv->addImage(driver->getTexture(mediaPath + "irrlichtlogo3.png"),
					core::position2d<s32>(5,85), true, 0, GUI_IRR_LOGO);
	s32 minLogoWidth = windowWidth/3;
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	if ( logo && logo->getRelativePosition().getWidth() < minLogoWidth )
	{
		/* Scale to make it better visible on high-res devices (we could also work with dpi here).
		*/
		LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
		logo->setScaleImage(true);
		core::rect<s32> logoPos(logo->getRelativePosition());
		f32 scale = (f32)minLogoWidth/(f32)logoPos.getWidth();
		logoPos.LowerRightCorner.X = logoPos.UpperLeftCorner.X + minLogoWidth;
		logoPos.LowerRightCorner.Y = logoPos.UpperLeftCorner.Y + (s32)((f32)logoPos.getHeight()*scale);
		logo->setRelativePosition(logoPos);
	}

	/*
		Add a 3d model. Note that you might need to add light when using other models.
		A copy of the model and it's textures must be inside the assets folder to be installed to Android.
		In this example we do copy it to the assets folder in the Makefile jni/Android.mk
	*/
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	IAnimatedMesh* mesh = smgr->getMesh(mediaPath + "dwarf.x");

    //test read file by marky
    /*
	{
        FILE* file = fopen("/sdcard/dwarf1.bb","w+");
	    LOGW("marky android_main file =%s, func=%s, line=%d , file=%X", __FILE__, __FUNCTION__, __LINE__, file);
	}
	*/


	if (!mesh)
	{
		LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
		device->closeDevice();
		device->drop();
       	return;
	}
	smgr->addAnimatedMeshSceneNode( mesh );


	/*
	To look at the mesh, we place a camera.
	*/
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	smgr->addCameraSceneNode(0, vector3df(15,40,-90), vector3df(0,30,0));
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	mainloop(device, text);
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	/*
		Mainloop. Applications usually never quit themself in Android. The OS is responsible for that.
	*/    
#else

    //IGUIStaticText *text = NULL;
    IGUIStaticText * text=guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer! from himax", rect<s32>(100,100,300,200), false, false, 0, GUI_INFO_FPS);
    text->
    /* Add by marky for customScene */
    device->setWindowCaption(L"Custom Scene Node - Irrlicht Engine Demo");
    smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));
	/*
	Create our scene node. I don't check the result of calling new, as it
	should throw an exception rather than returning 0 on failure. Because
	the new node will create itself with a reference count of 1, and then
	will have another reference added by its parent scene node when it is
	added to the scene, I need to drop my reference to it. Best practice is
	to drop it only *after* I have finished using it, regardless of what
	the reference count of the object is after creation.
	*/    
	  CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666); 
	/*
	To animate something in this boring scene consisting only of one
	tetrahedron, and to show that you now can use your scene node like any
	other scene node in the engine, we add an animator to the scene node,
	which rotates the node a little bit.
	irr::scene::ISceneManager::createRotationAnimator() could return 0, so
	should be checked.
	*/
  	scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));       
    /* End by marky for customScene */
	if(anim)
	{
		myNode->addAnimator(anim);
		
		/*
		I'm done referring to anim, so must
		irr::IReferenceCounted::drop() this reference now because it
		was produced by a createFoo() function. As I shouldn't refer to
		it again, ensure that I can't by setting to 0.
		*/
		anim->drop();
		anim = 0;
	}

	/*
	I'm done with my CSampleSceneNode object, and so must drop my reference.
	This won't delete the object, yet, because it is still attached to the
	scene graph, which prevents the deletion until the graph is deleted or the
	custom scene node is removed from it.
	*/
	myNode->drop();
	myNode = 0; // As I shouldn't refer to it again, ensure that I can't  

  mainloop( device , driver, smgr);
	/*
		Mainloop. Applications usually never quit themself in Android. The OS is responsible for that.
	*/  
  
#endif


	/* Cleanup */
	device->setEventReceiver(0);
	device->closeDevice();
	device->drop();
}

#endif	// defined(_IRR_ANDROID_PLATFORM_)

/*
**/
