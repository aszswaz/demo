#include <iostream>

#include <windows.h>
#include <bluetoothapis.h>

#pragma comment(lib, "bthprops.lib")

static std::string wchar2str(WCHAR *buffer) {
	std::wstring wstr(buffer);
	return std::string(wstr.begin(), wstr.end());
}

/*
 ���������豸�����ǲ��򿪴��ڣ�Ҳû�����û�ѡ��Ĺ���
*/
static int bl_scan01() {
	int code;
	BLUETOOTH_DEVICE_SEARCH_PARAMS params = {};
	BLUETOOTH_DEVICE_INFO btdi = {};
	HBLUETOOTH_DEVICE_FIND find = {};

	params.dwSize = sizeof(params);
	// �Ƿ��������������֤���豸
	params.fReturnAuthenticated = true;
	// �Ƿ�������ס�������豸
	params.fReturnRemembered = true;
	// �Ƿ�����δ֪�豸�������豸
	params.fReturnUnknown = true;
	// �Ƿ����������ӵ������豸
	params.fReturnConnected = true;
	// �Ƿ����µĲ�ѯ
	params.fIssueInquiry = true;
	// ��ѯʱ�䣬10 * 1.28 = 12.8 ��
	params.cTimeoutMultiplier = 10;

	btdi.dwSize = sizeof(btdi);

	// ��ʼ��ѯ��һ�������豸
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
 ��һ��������ʾ���п��������豸���û�ѡ��
*/
static int bl_scan02() {
	int code;
	BLUETOOTH_SELECT_DEVICE_PARAMS params = {};
	HBLUETOOTH_DEVICE_FIND find = {};

	params.dwSize = sizeof(params);
	// ǿ�ƽ��������֤
	params.fForceAuthentication = true;
	// �Ƿ���ʾ������֤�������豸
	params.fShowAuthenticated = true;
	// �Ƿ���ʾ��ס�������豸
	params.fShowRemembered = true;
	// �Ƿ���ʾδ֪�������豸
	params.fShowUnknown = true;
	// ǿ��������豸
	params.fAddNewDeviceWizard = false;
	// ����������豸������0 Ϊ������
	params.cNumDevices = 1;
	params.fSkipServicesPage = true;

	if (BluetoothSelectDevices(&params)) {
		// �û�ѡ���������豸
		BLUETOOTH_DEVICE_INFO_STRUCT device = params.pDevices[0];
		std::cout << wchar2str(device.szName) << std::endl;
		// �����豸��ַ����СΪ 6 ���ֽ�
		BYTE *rgBytes = (BYTE *)(&device.Address);
		printf("%02X:%02X:%02X:%02X:%02X:%02X\n", rgBytes[5], rgBytes[4], rgBytes[3], rgBytes[2], rgBytes[1], rgBytes[0]);

		BluetoothSelectDevicesFree(&params);
	} else {
		// ��������
		return 1;
	}
	return 0;
}

/*
	���������豸
*/
int main() {
	// return bl_scan01();
	return bl_scan02();
}