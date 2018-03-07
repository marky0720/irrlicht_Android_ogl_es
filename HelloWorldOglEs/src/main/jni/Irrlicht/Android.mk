#LOCAL_PATH := $(realpath $(call my-dir)/../..)
LOCAL_PATH := $(call my-dir)
PVRSDKDIR := $(LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE    := IrrlichtAndroid
#IRRLICHT_LIB_NAME := lib$(LOCAL_MODULE).a
#LOCAL_MODULE_FILENAME := libIrrlichtAndroid
#LOCAL_ARM_MODE := arm

### Add all source file names to be included in lib separated by a whitespace
LOCAL_CFLAGS := -Wall -pipe -fno-exceptions -fno-rtti -fstrict-aliasing -D_IRR_ANDROID_PLATFORM_ -D_IRR_COMPILE_WITH_ANDROID_DEVICE_
ifndef NDEBUG
LOCAL_CFLAGS += -g -D_DEBUG
else
LOCAL_CFLAGS += -fexpensive-optimizations -O3
endif

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/Android \
	$(LOCAL_PATH)/../include \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/zlib $(LOCAL_PATH)/jpeglib $(LOCAL_PATH)/libpng

LOCAL_SRC_FILES := \
					Android/CIrrDeviceAndroid.cpp \
					Android/CAndroidAssetReader.cpp \
					Android/CAndroidAssetFileArchive.cpp \
					Android/CKeyEventWrapper.cpp \
					aesGladman/aescrypt.cpp \
					aesGladman/aeskey.cpp \
					aesGladman/aestab.cpp \
					aesGladman/fileenc.cpp \
					aesGladman/hmac.cpp \
					aesGladman/prng.cpp \
					aesGladman/pwd2key.cpp \
					aesGladman/sha1.cpp \
					aesGladman/sha2.cpp \
					C3DSMeshFileLoader.cpp \
					CAnimatedMeshHalfLife.cpp \
					CAnimatedMeshMD2.cpp \
					CAnimatedMeshMD3.cpp \
					CAnimatedMeshSceneNode.cpp \
					CAttributes.cpp \
					CB3DMeshFileLoader.cpp \
					CB3DMeshWriter.cpp \
					CBillboardSceneNode.cpp \
					CBoneSceneNode.cpp \
					CBSPMeshFileLoader.cpp \
					CBurningShader_Raster_Reference.cpp \
					CCameraSceneNode.cpp \
					CColladaFileLoader.cpp \
					CColladaMeshWriter.cpp \
					CColorConverter.cpp \
					CCSMLoader.cpp \
					CCubeSceneNode.cpp \
					CD3D9Driver.cpp \
					CD3D9HLSLMaterialRenderer.cpp \
					CD3D9NormalMapRenderer.cpp \
					CD3D9ParallaxMapRenderer.cpp \
					CD3D9ShaderMaterialRenderer.cpp \
					CD3D9Texture.cpp \
					CDefaultGUIElementFactory.cpp \
					CDefaultSceneNodeAnimatorFactory.cpp \
					CDefaultSceneNodeFactory.cpp \
					CDepthBuffer.cpp \
					CDMFLoader.cpp \
					CDummyTransformationSceneNode.cpp \
					CEmptySceneNode.cpp \
					CFileList.cpp \
					CFileSystem.cpp \
					CFPSCounter.cpp \
					leakHunter.cpp \
					CGeometryCreator.cpp \
					CGUIButton.cpp \
					CGUICheckBox.cpp \
					CGUIColorSelectDialog.cpp \
					CGUIComboBox.cpp \
					CGUIContextMenu.cpp \
					CGUIEditBox.cpp \
					CGUIEnvironment.cpp \
					CGUIFileOpenDialog.cpp \
					CGUIFont.cpp \
					CGUIImage.cpp \
					CGUIImageList.cpp \
					CGUIInOutFader.cpp \
					CGUIListBox.cpp \
					CGUIMenu.cpp \
					CGUIMeshViewer.cpp \
					CGUIMessageBox.cpp \
					CGUIModalScreen.cpp \
					CGUIScrollBar.cpp \
					CGUISkin.cpp \
					CGUISpinBox.cpp \
					CGUISpriteBank.cpp \
					CGUIStaticText.cpp \
					CGUITabControl.cpp \
					CGUITable.cpp \
					CGUIToolBar.cpp \
					CGUITreeView.cpp \
					CGUIWindow.cpp \
					CGUIProfiler.cpp \
					CImage.cpp \
					CImageLoaderBMP.cpp \
					CImageLoaderDDS.cpp \
					CImageLoaderJPG.cpp \
					CImageLoaderPCX.cpp \
					CImageLoaderPNG.cpp \
					CImageLoaderPPM.cpp \
					CImageLoaderPSD.cpp \
					CImageLoaderRGB.cpp \
					CImageLoaderTGA.cpp \
					CImageLoaderWAL.cpp \
					CImageWriterBMP.cpp \
					CImageWriterJPG.cpp \
					CImageWriterPCX.cpp \
					CImageWriterPNG.cpp \
					CImageWriterPPM.cpp \
					CImageWriterPSD.cpp \
					CImageWriterTGA.cpp \
					CImageLoaderPVR.cpp \
					CIrrDeviceConsole.cpp \
					CIrrDeviceFB.cpp \
					CIrrDeviceLinux.cpp \
					CIrrDeviceSDL.cpp \
					CIrrDeviceStub.cpp \
					CIrrDeviceWin32.cpp \
					CIrrMeshFileLoader.cpp \
					CIrrMeshWriter.cpp \
					CLightSceneNode.cpp \
					CLimitReadFile.cpp \
					CLMTSMeshFileLoader.cpp \
					CLogger.cpp \
					CLWOMeshFileLoader.cpp \
					CMD2MeshFileLoader.cpp \
					CMD3MeshFileLoader.cpp \
					CMemoryFile.cpp \
					CMeshCache.cpp \
					CMeshManipulator.cpp \
					CMeshSceneNode.cpp \
					CMeshTextureLoader.cpp \
					CMetaTriangleSelector.cpp \
					CMountPointReader.cpp \
					CMS3DMeshFileLoader.cpp \
					CMY3DMeshFileLoader.cpp \
					CNPKReader.cpp \
					CNullDriver.cpp \
					COBJMeshFileLoader.cpp \
					COBJMeshWriter.cpp \
					COCTLoader.cpp \
					COctreeSceneNode.cpp \
					COctreeTriangleSelector.cpp \
					CEGLManager.cpp \
					COGLES2Driver.cpp \
					COGLES2ExtensionHandler.cpp \
					COGLES2MaterialRenderer.cpp \
					COGLES2FixedPipelineRenderer.cpp \
					COGLES2NormalMapRenderer.cpp \
					COGLES2ParallaxMapRenderer.cpp \
					COGLES2Renderer2D.cpp \
					COGLESDriver.cpp \
					COGLESExtensionHandler.cpp \
					COgreMeshFileLoader.cpp \
					COpenGLCacheHandler.cpp \
					COpenGLDriver.cpp \
					COpenGLExtensionHandler.cpp \
					COpenGLNormalMapRenderer.cpp \
					COpenGLParallaxMapRenderer.cpp \
					COpenGLShaderMaterialRenderer.cpp \
					COpenGLSLMaterialRenderer.cpp \
					COSOperator.cpp \
					CPakReader.cpp \
					CParticleAnimatedMeshSceneNodeEmitter.cpp \
					CParticleAttractionAffector.cpp \
					CParticleBoxEmitter.cpp \
					CParticleCylinderEmitter.cpp \
					CParticleFadeOutAffector.cpp \
					CParticleGravityAffector.cpp \
					CParticleMeshEmitter.cpp \
					CParticlePointEmitter.cpp \
					CParticleRingEmitter.cpp \
					CParticleRotationAffector.cpp \
					CParticleScaleAffector.cpp \
					CParticleSphereEmitter.cpp \
					CParticleSystemSceneNode.cpp \
					CPLYMeshFileLoader.cpp \
					CPLYMeshWriter.cpp \
					CProfiler.cpp \
					CQ3LevelMesh.cpp \
					CQuake3ShaderSceneNode.cpp \
					CReadFile.cpp \
					CSceneCollisionManager.cpp \
					CSceneLoaderIrr.cpp \
					CSceneManager.cpp \
					CSceneNodeAnimatorCameraFPS.cpp \
					CSceneNodeAnimatorCameraMaya.cpp \
					CSceneNodeAnimatorCollisionResponse.cpp \
					CSceneNodeAnimatorDelete.cpp \
					CSceneNodeAnimatorFlyCircle.cpp \
					CSceneNodeAnimatorFlyStraight.cpp \
					CSceneNodeAnimatorFollowSpline.cpp \
					CSceneNodeAnimatorRotation.cpp \
					CSceneNodeAnimatorTexture.cpp \
					CShadowVolumeSceneNode.cpp \
					CSkinnedMesh.cpp \
					CSkyBoxSceneNode.cpp \
					CSkyDomeSceneNode.cpp \
					CSMFMeshFileLoader.cpp \
					CSoftwareDriver.cpp \
					CSoftwareDriver2.cpp \
					CSoftwareTexture.cpp \
					CSoftwareTexture2.cpp \
					CSphereSceneNode.cpp \
					CSTLMeshFileLoader.cpp \
					CSTLMeshWriter.cpp \
					CTarReader.cpp \
					CTerrainSceneNode.cpp \
					CTerrainTriangleSelector.cpp \
					CTextSceneNode.cpp \
					CTRFlat.cpp \
					CTRFlatWire.cpp \
					CTRGouraud.cpp \
					CTRGouraud2.cpp \
					CTRGouraudAlpha2.cpp \
					CTRGouraudAlphaNoZ2.cpp \
					CTRGouraudWire.cpp \
					CTriangleBBSelector.cpp \
					CTriangleSelector.cpp \
					CTRNormalMap.cpp \
					CTRStencilShadow.cpp \
					CTRTextureBlend.cpp \
					CTRTextureDetailMap2.cpp \
					CTRTextureFlat.cpp \
					CTRTextureFlatWire.cpp \
					CTRTextureGouraud.cpp \
					CTRTextureGouraud2.cpp \
					CTRTextureGouraudAdd.cpp \
					CTRTextureGouraudAdd2.cpp \
					CTRTextureGouraudAddNoZ2.cpp \
					CTRTextureGouraudAlpha.cpp \
					CTRTextureGouraudAlphaNoZ.cpp \
					CTRTextureGouraudNoZ.cpp \
					CTRTextureGouraudNoZ2.cpp \
					CTRTextureGouraudVertexAlpha2.cpp \
					CTRTextureGouraudWire.cpp \
					CTRTextureLightMap2_Add.cpp \
					CTRTextureLightMap2_M1.cpp \
					CTRTextureLightMap2_M2.cpp \
					CTRTextureLightMap2_M4.cpp \
					CTRTextureLightMapGouraud2_M4.cpp \
					CTRTextureWire2.cpp \
					CVideoModeList.cpp \
					CVolumeLightSceneNode.cpp \
					CWADReader.cpp \
					CWaterSurfaceSceneNode.cpp \
					CWriteFile.cpp \
					CXMeshFileLoader.cpp \
					CXMLReader.cpp \
					CXMLWriter.cpp \
					CZBuffer.cpp \
					CZipReader.cpp \
					IBurningShader.cpp \
					Irrlicht.cpp \
					irrXML.cpp \
					os.cpp	 \
					bzip2/blocksort.c \
					bzip2/bzcompress.c \
					bzip2/bzlib.c \
					bzip2/crctable.c \
					bzip2/decompress.c \
					bzip2/huffman.c \
					bzip2/randtable.c \
					jpeglib/jaricom.c \
					jpeglib/jcapimin.c \
					jpeglib/jcapistd.c \
					jpeglib/jcarith.c \
					jpeglib/jccoefct.c \
					jpeglib/jccolor.c \
					jpeglib/jcdctmgr.c \
					jpeglib/jchuff.c \
					jpeglib/jcinit.c \
					jpeglib/jcmainct.c \
					jpeglib/jcmarker.c \
					jpeglib/jcmaster.c \
					jpeglib/jcomapi.c \
					jpeglib/jcparam.c \
					jpeglib/jcprepct.c \
					jpeglib/jcsample.c \
					jpeglib/jctrans.c \
					jpeglib/jdapimin.c \
					jpeglib/jdapistd.c \
					jpeglib/jdarith.c \
					jpeglib/jdatadst.c \
					jpeglib/jdatasrc.c \
					jpeglib/jdcoefct.c \
					jpeglib/jdcolor.c \
					jpeglib/jddctmgr.c \
					jpeglib/jdhuff.c \
					jpeglib/jdinput.c \
					jpeglib/jdmainct.c \
					jpeglib/jdmarker.c \
					jpeglib/jdmaster.c \
					jpeglib/jdmerge.c \
					jpeglib/jdpostct.c \
					jpeglib/jdsample.c \
					jpeglib/jdtrans.c \
					jpeglib/jerror.c \
					jpeglib/jfdctflt.c \
					jpeglib/jfdctfst.c \
					jpeglib/jfdctint.c \
					jpeglib/jidctflt.c \
					jpeglib/jidctfst.c \
					jpeglib/jidctint.c \
					jpeglib/jmemmgr.c \
					jpeglib/jmemnobs.c \
					jpeglib/jquant1.c \
					jpeglib/jquant2.c \
					jpeglib/jutils.c \
					libpng/png.c \
					libpng/pngerror.c \
					libpng/pngget.c \
					libpng/pngmem.c \
					libpng/pngpread.c \
					libpng/pngread.c \
					libpng/pngrio.c \
					libpng/pngrtran.c \
					libpng/pngrutil.c \
					libpng/pngset.c \
					libpng/pngtrans.c \
					libpng/pngwio.c \
					libpng/pngwrite.c \
					libpng/pngwtran.c \
					libpng/pngwutil.c \
					lzma/LzmaDec.c \
zlib/adler32.c   zlib/crc32.c    zlib/gzclose.c  zlib/gzread.c   zlib/infback.c  zlib/inflate.c   zlib/trees.c    zlib/zutil.c\
zlib/compress.c  zlib/deflate.c  zlib/gzlib.c    zlib/gzwrite.c  zlib/inffast.c  zlib/inftrees.c  zlib/uncompr.c

LOCAL_LDLIBS := -lEGL -llog -lGLESv1_CM -lGLESv2 -lz -landroid

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,android/native_app_glue)

					
# faild--------------------------------------------------------------------------					
#the same as #$(call import-module,android/native_app_glue)

#LOCAL_PATH:= $(call my-dir)

#include $(CLEAR_VARS)

#LOCAL_MODULE:= android_native_app_glue
#LOCAL_SRC_FILES:= android_native_app_glue.c
#LOCAL_C_INCLUDES := \
#	$(LOCAL_PATH) \
#	$(LOCAL_PATH)/../include \
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
#LOCAL_EXPORT_LDLIBS := -llog

#include $(BUILD_STATIC_LIBRARY)

# --------------------------------------------------------------------------	

					
JNI_FOLDER := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := twodgraphics
#LOCAL_MODULE_FILENAME := libtwodgraphics
#LOCAL_ARM_MODE := arm

### Add all source file names to be included in lib separated by a whitespace

LOCAL_CFLAGS := -pipe -fno-exceptions -fno-rtti -fstrict-aliasing -D_IRR_ANDROID_PLATFORM_ -D_IRR_COMPILE_WITH_ANDROID_DEVICE_

ifndef NDEBUG
LOCAL_CFLAGS += -g -D_DEBUG
else
LOCAL_CFLAGS += -fexpensive-optimizations -O3
endif

ifeq ($(TARGET_ARCH_ABI),x86)
LOCAL_CFLAGS += -fno-stack-protector
endif


LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/Android \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/HelloWorld_Android \
  
LOCAL_SRC_FILES := HelloWorld_Android/main.cpp HelloWorld_Android/android_tools.cpp
##HelloWorld_Android/main.cpp
##HelloWorld_Android/main_hellow2.cpp
##HelloWorld_Android/main_hellow.cpp
##HelloWorld_Android/main_Google.cpp


LOCAL_LDLIBS := -lEGL -llog -lGLESv1_CM -lGLESv2 -lz -landroid


LOCAL_STATIC_LIBRARIES := \
				          android_native_app_glue \
						  IrrlichtAndroid

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)


# copy Irrlicht data to assets
##IRRLICHT_PROJECT_PATH := $(LOCAL_PATH)
#$(shell mkdir -p $(IRRLICHT_PROJECT_PATH)/assets)
#$(shell mkdir -p $(IRRLICHT_PROJECT_PATH)/assets/media)
#$(shell mkdir -p $(IRRLICHT_PROJECT_PATH)/assets/media/Shaders)
#$(shell mkdir -p $(IRRLICHT_PROJECT_PATH)/src)
#$(shell cp $(IRRLICHT_PROJECT_PATH)/../../media/Shaders/*.* $(IRRLICHT_PROJECT_PATH)/assets/media/Shaders/)
#$(shell cp $(IRRLICHT_PROJECT_PATH)/../../media/irrlichtlogo3.png $(IRRLICHT_PROJECT_PATH)/assets/media/)
#$(shell cp $(IRRLICHT_PROJECT_PATH)/../../media/sydney.md2 $(IRRLICHT_PROJECT_PATH)/assets/media/)
#$(shell cp $(IRRLICHT_PROJECT_PATH)/../../media/sydney.bmp $(IRRLICHT_PROJECT_PATH)/assets/media/)
#$(shell cp $(IRRLICHT_PROJECT_PATH)/../../media/fonthaettenschweiler.bmp $(IRRLICHT_PROJECT_PATH)/assets/media/)
#$(shell cp $(IRRLICHT_PROJECT_PATH)/../../media/bigfont.png $(IRRLICHT_PROJECT_PATH)/assets/media/)
#====





