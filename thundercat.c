#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bitthunder.h>
#include <lib/putc.h>

BT_ERROR thread(BT_HANDLE hThread, void *pParam) {
	
	//char buffer[128];
	BT_u32 value;

	BT_kPrint("Thread started");

	while(1) {
		/*sprintf(buffer, "%f", 3.14);
		if(strcmp(buffer, "3.140000")) {
			BT_kPrint("shit, %s : %f", buffer);
			}*/

		value = strtoul("4096", NULL, 10);
		if(value != 4096) {
			BT_kPrint("Bad value");
		}
	}
}

void test_error() {
	BT_kPrint("Bad value");
}


extern BT_ERROR test_case(BT_HANDLE hThread, void *pParam);

int main(void) {

	BT_HANDLE hUart = BT_Open("/dev/serial1", 0, NULL);
	
	BT_UART_CONFIG oConfig;
	BT_SetPowerState(hUart, BT_POWER_STATE_AWAKE);

	oConfig.eMode			= BT_UART_MODE_POLLED;
	oConfig.ucDataBits		= BT_UART_8_DATABITS;
	oConfig.ucStopBits		= BT_UART_ONE_STOP_BIT;
	oConfig.ucParity		= BT_UART_PARITY_NONE;
	oConfig.ulBaudrate		= 115200;

	BT_UartSetConfiguration(hUart, &oConfig);

	BT_UartEnable(hUart);
	BT_SetStdout(hUart);
	BT_SetStdin(hUart);

	BT_HANDLE hKernel = BT_GetKernelProcessHandle();
	BT_SetProcessFileDescriptor(hKernel, 1, hUart);

	BT_kPrint("ThunderCat booted:");
	BT_kPrint("Starting init program");

	BT_THREAD_CONFIG oTConfig;
	oTConfig.ulStackDepth = 1024;
	oTConfig.ulPriority = 0;
	oTConfig.ulFlags = 0;

	//test_case(0, 0);

//	BT_CreateProcess(thread, "pr-0", &oTConfig, NULL);
//	BT_CreateProcess(thread, "pr-1", &oTConfig, NULL);
//	BT_CreateProcess(thread, "pr-2", &oTConfig, NULL);
//	BT_CreateProcess(thread, "pr-3", &oTConfig, NULL);
//	BT_CreateThread(thread, &oTConfig, NULL);
	BT_CreateThread(test_case, &oTConfig, NULL);
	//BT_CreateThread(thread, &oTConfig, NULL);

	BT_HANDLE hShell = BT_ShellCreate(hUart, hUart, "ThunderCat>", 0, NULL);
	BT_Shell(hShell);

	while(1) {
		BT_ThreadSleep(1000);
	}
}
