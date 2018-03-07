LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := irrlicht_static

LOCAL_MODULE_FILENAME := libirrlicht

IRR_MESH_LOADER := \
	CBSPMeshFileLoader.cpp \
	CMD2MeshFileLoader.cpp \
	CMD3MeshFileLoader.cpp \
	CMS3DMeshFileLoader.cpp \
	CB3DMeshFileLoader.cpp \
	C3DSMeshFileLoader.cpp \
	COgreMeshFileLoader.cpp \
	COBJMeshFileLoader.cpp \
	CColladaFileLoader.cpp \
	CCSMLoader.cpp \
	CDMFLoader.cpp \
	CLMTSMeshFileLoader.cpp \
	CMY3DMeshFileLoader.cpp \
	COCTLoader.cpp \
	CXMeshFileLoader.cpp \
	CIrrMeshFileLoader.cpp \
	CSTLMeshFileLoader.cpp \
	CLWOMeshFileLoader.cpp \
	CPLYMeshFileLoader.cpp \
	CSMFMeshFileLoader.cpp

IRR_MESH_WRITER := \
	CColladaMeshWriter.cpp \
	CIrrMeshWriter.cpp \
	CSTLMeshWriter.cpp \
	COBJMeshWriter.cpp \
	CPLYMeshWriter.cpp

IRR_MESH_OBJ := \
	$(IRR_MESH_LOADER) \
	$(IRR_MESH_WRITER) \
	CSkinnedMesh.cpp \
	CBoneSceneNode.cpp \
	CMeshSceneNode.cpp \
	CAnimatedMeshSceneNode.cpp \
	CAnimatedMeshMD2.cpp \
	CAnimatedMeshMD3.cpp \
	CQ3LevelMesh.cpp \
	CQuake3ShaderSceneNode.cpp \
	CAnimatedMeshHalfLife.cpp

IRR_OBJ := \
	CBillboardSceneNode.cpp \
	CCameraSceneNode.cpp \
	CDummyTransformationSceneNode.cpp \
	CEmptySceneNode.cpp \
	CGeometryCreator.cpp \
	CLightSceneNode.cpp \
	CMeshManipulator.cpp \
	CMetaTriangleSelector.cpp \
	COctreeSceneNode.cpp \
	COctreeTriangleSelector.cpp \
	CSceneCollisionManager.cpp \
	CSceneManager.cpp \
	CShadowVolumeSceneNode.cpp \
	CSkyBoxSceneNode.cpp \
	CSkyDomeSceneNode.cpp \
	CTerrainSceneNode.cpp \
	CTerrainTriangleSelector.cpp \
	CVolumeLightSceneNode.cpp \
	CCubeSceneNode.cpp \
	CSphereSceneNode.cpp \
	CTextSceneNode.cpp \
	CTriangleBBSelector.cpp \
	CTriangleSelector.cpp \
	CWaterSurfaceSceneNode.cpp \
	CMeshCache.cpp \
	CDefaultSceneNodeAnimatorFactory.cpp \
	CDefaultSceneNodeFactory.cpp \
	CSceneLoaderIrr.cpp

IRR_PARTICLE_OBJ := \
	CParticleAnimatedMeshSceneNodeEmitter.cpp \
	CParticleBoxEmitter.cpp \
	CParticleCylinderEmitter.cpp \
	CParticleMeshEmitter.cpp \
	CParticlePointEmitter.cpp \
	CParticleRingEmitter.cpp \
	CParticleSphereEmitter.cpp \
	CParticleAttractionAffector.cpp \
	CParticleFadeOutAffector.cpp \
	CParticleGravityAffector.cpp \
	CParticleRotationAffector.cpp \
	CParticleSystemSceneNode.cpp \
	CParticleScaleAffector.cpp

IRR_ANIM_OBJ := \
	CSceneNodeAnimatorCameraFPS.cpp \
	CSceneNodeAnimatorCameraMaya.cpp \
	CSceneNodeAnimatorCollisionResponse.cpp \
	CSceneNodeAnimatorDelete.cpp \
	CSceneNodeAnimatorFlyCircle.cpp \
	CSceneNodeAnimatorFlyStraight.cpp \
	CSceneNodeAnimatorFollowSpline.cpp \
	CSceneNodeAnimatorRotation.cpp \
	CSceneNodeAnimatorTexture.cpp

IRR_DRIVER_OBJ := \
	CNullDriver.cpp \
	# COGLESDriver.cpp \
	COGLESTexture.cpp \
	COGLESExtensionHandler.cpp

IRR_RENDER_OBJ := \
	# COGLES2FixedPipelineShader.cpp \
	COGLES2ParallaxMapRenderer.cpp \
	COGLES2SLMaterialRenderer.cpp \
	COGLES2ExtensionHandler.cpp \
	COGLES2NormalMapRenderer.cpp \
	COGLES2Renderer2D.cpp \
	COGLES2Texture.cpp

IRR_IMAGE_OBJ := \
	CColorConverter.cpp \
	CImage.cpp \
	CImageLoaderBMP.cpp \
	CImageLoaderJPG.cpp \
	CImageLoaderPCX.cpp \
	CImageLoaderPNG.cpp \
	CImageLoaderPSD.cpp \
	CImageLoaderTGA.cpp \
	CImageLoaderPPM.cpp \
	CImageLoaderWAL.cpp \
	CImageLoaderRGB.cpp \
	CImageWriterBMP.cpp \
	CImageWriterJPG.cpp \
	CImageWriterPCX.cpp \
	CImageWriterPNG.cpp \
	CImageWriterPPM.cpp \
	CImageWriterPSD.cpp \
	CImageWriterTGA.cpp

IRR_VIDEO_OBJ := CVideoModeList.cpp CFPSCounter.cpp $(IRR_DRIVER_OBJ) $(IRR_IMAGE_OBJ)

IRR_SWRENDER_OBJ := \
	CSoftwareDriver.cpp \
	CSoftwareTexture.cpp \
	CTRFlat.cpp \
	CTRFlatWire.cpp \
	CTRGouraud.cpp \
	CTRGouraudWire.cpp \
	CTRTextureFlat.cpp \
	CTRTextureFlatWire.cpp \
	CTRTextureGouraud.cpp \
	CTRTextureGouraudAdd.cpp \
	CTRTextureGouraudNoZ.cpp \
	CTRTextureGouraudWire.cpp \
	CZBuffer.cpp \
	CTRTextureGouraudVertexAlpha2.cpp \
	CTRTextureGouraudNoZ2.cpp \
	CTRTextureLightMap2_M2.cpp \
	CTRTextureLightMap2_M4.cpp \
	CTRTextureLightMap2_M1.cpp \
	CSoftwareDriver2.cpp \
	CSoftwareTexture2.cpp \
	CTRTextureGouraud2.cpp \
	CTRGouraud2.cpp \
	CTRGouraudAlpha2.cpp \
	CTRGouraudAlphaNoZ2.cpp \
	CTRTextureDetailMap2.cpp \
	CTRTextureGouraudAdd2.cpp \
	CTRTextureGouraudAddNoZ2.cpp \
	CTRTextureWire2.cpp \
	CTRTextureLightMap2_Add.cpp \
	CTRTextureLightMapGouraud2_M4.cpp \
	IBurningShader.cpp \
	CTRTextureBlend.cpp \
	CTRTextureGouraudAlpha.cpp \
	CTRTextureGouraudAlphaNoZ.cpp \
	CTRNormalMap.cpp \
	CTRStencilShadow.cpp \
	CDepthBuffer.cpp \
	CBurningShader_Raster_Reference.cpp

IRR_IO_OBJ := \
	CFileList.cpp \
	CFileSystem.cpp \
	CLimitReadFile.cpp \
	CMemoryFile.cpp \
	CReadFile.cpp \
	CWriteFile.cpp \
	CXMLReader.cpp \
	CXMLWriter.cpp \
	CZipReader.cpp \
	CPakReader.cpp \
	CNPKReader.cpp \
	CTarReader.cpp \
	CMountPointReader.cpp \
	irrXML.cpp \
	CAttributes.cpp \
	lzma/LzmaDec.c

IRR_OTHER_OBJ := \
	CIrrDeviceConsole.cpp \
	CIrrDeviceStub.cpp \
	CLogger.cpp \
	Irrlicht.cpp \
	CWADReader.cpp \
	os.cpp

IRR_GUI_OBJ := \
	CGUIButton.cpp \
	CGUICheckBox.cpp \
	CGUIComboBox.cpp \
	CGUIContextMenu.cpp \
	CGUIEditBox.cpp \
	CGUIEnvironment.cpp \
	CGUIFileOpenDialog.cpp \
	CGUIFont.cpp \
	CGUIImage.cpp \
	CGUIInOutFader.cpp \
	CGUIListBox.cpp \
	CGUIMenu.cpp \
	CGUIMeshViewer.cpp \
	CGUIMessageBox.cpp \
	CGUIModalScreen.cpp \
	CGUIScrollBar.cpp \
	CGUISpinBox.cpp \
	CGUISkin.cpp \
	CGUIStaticText.cpp \
	CGUITabControl.cpp \
	CGUITable.cpp \
	CGUIToolBar.cpp \
	CGUIWindow.cpp \
	CGUIColorSelectDialog.cpp \
	CDefaultGUIElementFactory.cpp \
	CGUISpriteBank.cpp \
	CGUIImageList.cpp \
	CGUITreeView.cpp

ZLIB_OBJ := \
	zlib/adler32.c \
	zlib/compress.c \
	zlib/crc32.c \
	zlib/deflate.c \
	zlib/inffast.c \
	zlib/inflate.c \
	zlib/inftrees.c \
	zlib/trees.c \
	zlib/uncompr.c \
	zlib/zutil.c

JPEG_LIB_OBJ := \
	jpeglib/jcapimin.c \
	jpeglib/jcapistd.c \
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
	jpeglib/jcarith.c \
	jpeglib/jdarith.c \
	jpeglib/jaricom.c

PNG_LIB_OBJ := \
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
	libpng/pngwutil.c

AESGM_LIB_OBJ := \
	aesGladman/aescrypt.cpp \
	aesGladman/aeskey.cpp \
	aesGladman/aestab.cpp \
	aesGladman/fileenc.cpp \
	aesGladman/hmac.cpp \
	aesGladman/prng.cpp \
	aesGladman/pwd2key.cpp \
	aesGladman/sha1.cpp \
	aesGladman/sha2.cpp

BZIP2_LIB_OBJ := \
	bzip2/blocksort.c \
	bzip2/huffman.c \
	bzip2/crctable.c \
	bzip2/randtable.c \
	bzip2/bzcompress.c \
	bzip2/decompress.c \
	bzip2/bzlib.c

# LOCAL_CFLAGS := -O3 -DANDROID_NDK -DDISABLE_IMPORTGL -I./../include/ -I./
# LOCAL_CFLAGS := -O3 -DANDROID_NDK -DDISABLE_IMPORTGL

LOCAL_SRC_FILES := \
	$(IRR_MESH_OBJ) \
	$(IRR_OBJ) \
	$(IRR_PARTICLE_OBJ) \
	$(IRR_ANIM_OBJ) \
	$(IRR_RENDER_OBJ) \
	$(IRR_VIDEO_OBJ) \
	$(IRR_SWRENDER_OBJ) \
	$(IRR_IO_OBJ) \
	$(IRR_OTHER_OBJ) \
	$(IRR_GUI_OBJ) \
	$(ZLIB_OBJ) \
	$(JPEG_LIB_OBJ) \
	$(PNG_LIB_OBJ) \
	$(AESGM_LIB_OBJ) \
	$(BZIP2_LIB_OBJ) \

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/../include \

# include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
