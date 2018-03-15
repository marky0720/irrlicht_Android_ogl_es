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
#include "driverChoice.h"
#include "exampleHelper.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "sensor", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	IrrlichtDevice *device;
	s32				counter;
	IGUIListBox*	listbox;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR,
  GUI_INFO_FPS
};

/*
	Set the skin transparency by changing the alpha values of all skin-colors
*/
void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
{
	for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(alpha);
		skin->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
}

/*
The Event Receiver is not only capable of getting keyboard and
mouse input events, but also events of the graphical user interface
(gui). There are events for almost everything: button click,
listbox selection change, events that say that a element was hovered
and so on. To be able to react to some of these events, we create
an event receiver.
We only react to gui events, and if it's such an event, we get the
id of the caller (the gui element which caused the event) and get
the pointer to the gui environment.
*/
class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		LOGW("marky  file =%s, func=%s, line=%d , event.EventType=%d ", __FILE__, __FUNCTION__, __LINE__, event.EventType);
    //if (event.EventType == EET_GUI_EVENT)
    if (event.EventType == EET_TOUCH_INPUT_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			/*
			If a scrollbar changed its scroll position, and it is
			'our' scrollbar (the one with id GUI_ID_TRANSPARENCY_SCROLL_BAR), 
			then we change the transparency of all gui elements. This is an
			easy task: There is a skin object, in which all color
			settings are stored. We simply go through all colors
			stored in the skin and change their alpha value.
			*/
			case EGET_SCROLL_BAR_CHANGED:
        LOGW("marky  file =%s, func=%s, line=%d , EGET_SCROLL_BAR_CHANGED ", __FILE__, __FUNCTION__, __LINE__);
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					setSkinTransparency(pos, env->getSkin());
				}
				break;

			/*
			If a button was clicked, it could be one of 'our'
			three buttons. If it is the first, we shut down the engine.
			If it is the second, we create a little window with some
			text on it. We also add a string to the list box to log
			what happened. And if it is the third button, we create
			a file open dialog, and add also this as string to the list box.
			That's all for the event receiver.
			*/
			case EGET_BUTTON_CLICKED:
        LOGW("marky  file =%s, func=%s, line=%d , EGET_BUTTON_CLICKED ", __FILE__, __FUNCTION__, __LINE__);
				switch(id)
				{
				case GUI_ID_QUIT_BUTTON:
          LOGW("marky  file =%s, func=%s, line=%d , GUI_ID_QUIT_BUTTON ", __FILE__, __FUNCTION__, __LINE__);
					Context.device->closeDevice();
					return true;

				case GUI_ID_NEW_WINDOW_BUTTON:
          LOGW("marky  file =%s, func=%s, line=%d , GUI_ID_NEW_WINDOW_BUTTON ", __FILE__, __FUNCTION__, __LINE__);
					{
					Context.listbox->addItem(L"Window created");
					Context.counter += 30;
					if (Context.counter > 200)
						Context.counter = 0;

					IGUIWindow* window = env->addWindow(
						rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
						false, // modal?
						L"Test window");

					env->addStaticText(L"Please close me",
						rect<s32>(35,35,140,50),
						true, // border?
						false, // wordwrap?
						window);
					}
					return true;


				case GUI_ID_FILE_OPEN_BUTTON:
          LOGW("marky  file =%s, func=%s, line=%d , GUI_ID_FILE_OPEN_BUTTON ", __FILE__, __FUNCTION__, __LINE__);
					Context.listbox->addItem(L"File open");
					// There are some options for the file open dialog
					// We set the title, make it a modal window, and make sure
					// that the working directory is restored after the dialog
					// is finished.
					env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
					return true;

				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
				LOGW("marky  file =%s, func=%s, line=%d , EGET_FILE_SELECTED ", __FILE__, __FUNCTION__, __LINE__);
        {
					// show the model filename, selected in the file dialog
					IGUIFileOpenDialog* dialog =
						(IGUIFileOpenDialog*)event.GUIEvent.Caller;
					Context.listbox->addItem(dialog->getFileName());
				}
				break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
};

/* Mainloop.
*/
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
  
  
 
	//MyEventReceiver receiver(app);
	// Then create the event receiver, giving it that context structure.
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
	//param.EventReceiver = &receiver;

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
	//receiver.Init(device);
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	// And tell the device to use our custom event receiver.
	//device->setEventReceiver(&receiver);    


//	ANativeActivity_setWindowFlags(app->activity, AWINDOW_FLAG_FULLSCREEN, 0);
	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);


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
	IGUIFont* font = guienv->getFont(mediaPath + "fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);



    //Add by marky
	/*
	We add a hello world label to the window, using the GUI environment.
	The text is placed at the position (10,10) as top left corner and
	(260,22) as lower right corner.
	*/
/*
	We add three buttons. The first one closes the engine. The second
	creates a window and the third opens a file open dialog. The third
	parameter is the id of the button, with which we can easily identify
	the button in the event receiver.
	*/

	guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
			L"Quit", L"Exits Program");
	guienv->addButton(rect<s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
			L"New Window", L"Launches a new Window");
	guienv->addButton(rect<s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
			L"File Open", L"Opens a file");

	/*
	Now, we add a static text and a scrollbar, which modifies the
	transparency of all gui elements. We set the maximum value of
	the scrollbar to 255, because that's the maximal value for
	a color value.
	Then we create an other static text and a list box.
	*/

	guienv->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
	IGUIScrollBar* scrollbar = guienv->addScrollBar(true,
			rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
	scrollbar->setMax(255);
	scrollbar->setPos(255);
	setSkinTransparency( scrollbar->getPos(), guienv->getSkin());

	// set scrollbar position to alpha value of an arbitrary element
	scrollbar->setPos(guienv->getSkin()->getColor(EGDC_WINDOW).getAlpha());

	guienv->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
	IGUIListBox * listbox = guienv->addListBox(rect<s32>(50, 140, 250, 210));
	guienv->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

	// A field to show some text. Comment out stat->setText in run() if you want to see the dpi instead of the fps.
  guienv->getFont(mediaPath +"fonthaettenschweiler.bmp");  //add by marky
	IGUIStaticText *text = guienv->addStaticText(stringw(displayMetrics.xdpi).c_str(),
		rect<s32>(5,5,635,35), false, false, 0, GUI_INFO_FPS );

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;

	// Then create the event receiver, giving it that context structure.
	MyEventReceiver receiver(context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(&receiver);
  
	/*
	And at last, we create a nice Irrlicht Engine logo in the top left corner.
	*/
	guienv->addImage(driver->getTexture(mediaPath + "irrlichtlogo2.png"),
			position2d<int>(10,10));  


	/*
	To look at the mesh, we place a camera.
	*/
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	smgr->addCameraSceneNode(0, vector3df(15,40,-90), vector3df(0,30,0));

	/*
		Mainloop. Applications usually never quit themself in Android. The OS is responsible for that.
	*/
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	mainloop(device, text);
	LOGW("marky android_main file =%s, func=%s, line=%d  ", __FILE__, __FUNCTION__, __LINE__);
	/* Cleanup */
	device->setEventReceiver(0);
	device->closeDevice();
	device->drop();
}

#endif	// defined(_IRR_ANDROID_PLATFORM_)

/*
**/
