#pragma comment (lib, "Setupapi.lib")
#include <stdio.h>
#include <tchar.h>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <setupapi.h>
#include <regstr.h>

const int BUFFER = 100;

int main() 
{
	setlocale(LC_ALL, "Russian");

	HDEVINFO hDevInfo;
	hDevInfo = SetupDiGetClassDevs(NULL, REGSTR_KEY_PCIENUM, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);

	SP_DEVINFO_DATA spDevInfoData; // device ex
	ZeroMemory(&spDevInfoData, sizeof(SP_DEVINFO_DATA));
	spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	std::cout.setf(std::ios::left);

	std::cout << "___________________________________________________________________________________"
		         "___________________________________________________________________________________" << std::endl;
	std::cout << std::setw(3) << "#" << "| " << std::setw(10) << "Vendor ID" << "| " << std::setw(39) << "Vendor Name" << "| " 
		      << std::setw(10) << "Device ID" << "| " << std::setw(95) << "Device Name" << "|" << std::endl;
	std::cout << "___________________________________________________________________________________"
		         "___________________________________________________________________________________" << std::endl;

	DWORD i = 0;
	while (SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData))
	{
		TCHAR deviceID[BUFFER], deviceName[BUFFER], vendorName[BUFFER];
		ZeroMemory(&deviceID, sizeof(deviceID));
		ZeroMemory(&deviceName, sizeof(deviceName));
		ZeroMemory(&vendorName, sizeof(vendorName));

		// get device ID
		SetupDiGetDeviceInstanceId(hDevInfo, &spDevInfoData, deviceID, sizeof(deviceID), NULL);
		// get name
		SetupDiGetDeviceRegistryProperty(hDevInfo, &spDevInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL);
		SetupDiGetDeviceRegistryProperty(hDevInfo, &spDevInfoData, SPDRP_MFG, NULL, (PBYTE)vendorName, sizeof(vendorName), NULL);

		std::string id(deviceID);

		std::cout << std::setw(3) << i << "| " << std::setw(10) << id.substr(8, 4).c_str() << "| " << std::setw(39) << vendorName << "| " 
			      << std::setw(10) << id.substr(17, 4).c_str() << "| " << std::setw(95) << deviceName << "| " << std::endl;
		std::cout << "___________________________________________________________________________________"
			         "___________________________________________________________________________________" << std::endl;
		i++;
	}

	system("pause");
	return 0;
}