# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/fdk-aac/include $(PROJECT_PATH)/components/fdk-aac/libAACdec/include $(PROJECT_PATH)/components/fdk-aac/libFDK/include $(PROJECT_PATH)/components/fdk-aac/libMpegTPDec/include $(PROJECT_PATH)/components/fdk-aac/libPCMutils/include $(PROJECT_PATH)/components/fdk-aac/libSBRdec/include $(PROJECT_PATH)/components/fdk-aac/libSYS/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/fdk-aac -lfdk-aac
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += fdk-aac
fdk-aac-build: 
