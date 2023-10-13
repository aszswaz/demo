#include <iostream>

#include <windows.h>
#include <bluetoothapis.h>

#pragma comment(lib, "bthprops.lib")

static std::string wchar2str(WCHAR *buffer) {
	std::wstring wstr(buffer);
	return std::string(wstr.begin(), wstr.end());
}

/*
 搜索蓝牙设备，但是不打开窗口，也没有让用户选择的功能
*/
static int bl_scan01() {
	int code;
	BLUETOOTH_DEVICE_SEARCH_PARAMS params = {};
	BLUETOOTH_DEVICE_INFO btdi = {};
	HBLUETOOTH_DEVICE_FIND find = {};

	params.dwSize = sizeof(params);
	// 是否搜索经过身份验证的设备
	params.fReturnAuthenticated = true;
	// 是否搜索记住的蓝牙设备
	params.fReturnRemembered = true;
	// 是否搜索未知设备的蓝牙设备
	params.fReturnUnknown = true;
	// 是否搜索已连接的蓝牙设备
	params.fReturnConnected = true;
	// 是否发起新的查询
	params.fIssueInquiry = true;
	// 查询时间，10 * 1.28 = 12.8 秒
	params.cTimeoutMultiplier = 10;

	btdi.dwSize = sizeof(btdi);

	// 开始查询第一个蓝牙设备
	find = BluetoothFindFirstDevice(&params, &btdi);
	if (find) {
		std::cout << wchar2str(btdi.szName) << std::endl;

		while (BluetoothFindNextDevice(find, &btdi)) {
			std::cout << wchar2str(btdi.szName) << std::endl;
		}
		BluetoothFindDeviceClose(find);
	}
	else {
		code = GetLastError();
		switch (code) {
		case ERROR_INVALID_PARAMETER:
			std::cerr << "ERROR_INVALID_PARAMETER" << std::endl;
			break;
		case ERROR_REVISION_MISMATCH:
			std::cerr << "ERROR_REVISION_MISMATCH" << std::endl;
			break;
		default:
			break;
		}
		return 1;
	}
	return 0;
}

/*
 打开一个窗口显示所有可用蓝牙设备让用户选择
*/
static int bl_scan02() {
	int code;
	BLUETOOTH_SELECT_DEVICE_PARAMS params = {};
	HBLUETOOTH_DEVICE_FIND find = {};

	params.dwSize = sizeof(params);
	// 强制进行身份验证
	params.fForceAuthentication = true;
	// 是否显示经过验证的蓝牙设备
	params.fShowAuthenticated = true;
	// 是否显示记住的蓝牙设备
	params.fShowRemembered = true;
	// 是否显示未知的蓝牙设备
	params.fShowUnknown = true;
	// 强制添加新设备
	params.fAddNewDeviceWizard = false;
	// 所需的蓝牙设备数量，0 为无限制
	params.cNumDevices = 1;
	params.fSkipServicesPage = true;

	if (BluetoothSelectDevices(&params)) {
		// 用户选择了蓝牙设备
		BLUETOOTH_DEVICE_INFO_STRUCT device = params.pDevices[0];
		std::cout << wchar2str(device.szName) << std::endl;
		// 蓝牙设备地址，大小为 6 个字节
		BYTE *rgBytes = (BYTE *)(&device.Address);
		printf("%02X:%02X:%02X:%02X:%02X:%02X\n", rgBytes[5], rgBytes[4], rgBytes[3], rgBytes[2], rgBytes[1], rgBytes[0]);

		BluetoothSelectDevicesFree(&params);
	} else {
		// 发生错误
		return 1;
	}
	return 0;
}

/*
	搜索蓝牙设备
*/
int main() {
	// return bl_scan01();
	return bl_scan02();
}