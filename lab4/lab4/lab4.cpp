﻿#include <stdio.h>
#include <Windows.h>
#include <setupapi.h>
#include <locale.h>
#include <string.h> 
#include <iostream>
#include <wdmguid.h>
#include <devguid.h>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#pragma comment(lib, "setupapi.lib")

int main() 
{
	setlocale(LC_ALL, "rus");

	HDEVINFO hDeviceInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_CAMERA, NULL, NULL, DIGCF_PRESENT);
	if (hDeviceInfo == INVALID_HANDLE_VALUE)
		return 1;

	SP_DEVINFO_DATA spDeviceInfoData = { 0 };
	ZeroMemory(&spDeviceInfoData, sizeof(SP_DEVINFO_DATA));
	spDeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	
	SetupDiEnumDeviceInfo(hDeviceInfo, 0, &spDeviceInfoData);
	PBYTE deviceName[256];
	PBYTE deviceMan[256];
	PBYTE deviceID[256];
	SetupDiGetDeviceRegistryProperty(hDeviceInfo, &spDeviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL);
	SetupDiGetDeviceRegistryProperty(hDeviceInfo, &spDeviceInfoData, SPDRP_MFG, NULL, (PBYTE)deviceMan, sizeof(deviceMan), NULL);
	SetupDiGetDeviceRegistryProperty(hDeviceInfo, &spDeviceInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)deviceID, sizeof(deviceID), NULL);

	cout << "NAME: " << deviceName << endl;
	cout << "MANUFACTURER: " << deviceMan << endl;
	cout << "CAMERA HARDWARE ID: " << deviceID << endl << endl;

	Mat matrix; // declare a matrix for image
	VideoCapture capture(0 + CAP_DSHOW); //declare a capture object
	capture >> matrix;

	cout << "1. PHOTO" << endl << "2. VIDEO" << endl;

	int input;
	cin >> input;

	switch (input) 
	{
	case 1:
	{
		capture.read(matrix);
		imwrite("photo.jpg", matrix);
		break;
	}
	case 2:
	{
		int videoLen;
		cout << "ENTER SECONDS: " << endl;
		cin >> videoLen;
		ShowWindow(GetConsoleWindow(), SW_HIDE);

		VideoWriter writer;
		int codec = VideoWriter::fourcc('P', 'I', 'M', '1'); // MPEG-1 codec
		string filename = "./video.mpeg";
		writer.open(filename, codec, 10.0, matrix.size(), true); // 10.0 - fps; color true

		time_t timeStart;
		time(&timeStart);
		while (time(NULL) <= timeStart + videoLen)
		{
			writer.write(matrix);
			waitKey(60);
			capture.read(matrix);
		}
		break;
	}
	default:
	{
		cout << "INCORRECT DATA" << endl;
		Sleep(1000);
		break;
	}
	}

	SetupDiDestroyDeviceInfoList(hDeviceInfo);
	return 0;
}