// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2015.1
// Copyright (C) 2015 Xilinx Inc. All rights reserved.
// 
// ==============================================================

#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "ximage_filter_fh.h"

extern XImage_filter_fh_Config XImage_filter_fh_ConfigTable[];

XImage_filter_fh_Config *XImage_filter_fh_LookupConfig(u16 DeviceId) {
	XImage_filter_fh_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIMAGE_FILTER_FH_NUM_INSTANCES; Index++) {
		if (XImage_filter_fh_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XImage_filter_fh_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XImage_filter_fh_Initialize(XImage_filter_fh *InstancePtr, u16 DeviceId) {
	XImage_filter_fh_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XImage_filter_fh_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XImage_filter_fh_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif
