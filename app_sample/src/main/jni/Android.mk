LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := \

LOCAL_SHARED_LIBRARIES := irrlicht_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH)/Irrlicht)
$(call import-module,.)
