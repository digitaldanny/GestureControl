/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * INCLUDES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#include "wireless_api.h"

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * GLOBALS
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#if ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
static PyObject* pModule;      // server module                
static PyObject* pSocketObj;   // server.ServerSocket object
#endif

bool WirelessApi::Init()
{
#if TARGET_HW_MSP432
    return WirelessApi::MSP432::SetMode(HC05MODE_DATA);
#else
    return false;
#endif
}

bool WirelessApi::ConnectToClient(int port_num)
{
#if ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
    return Python::ConnectToClient(port_num);
#else
    return false;
#endif
}

bool WirelessApi::SendResponse(char* data, int dataSizeInBytes)
{
#if ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
    return Python::SendResponse(data, dataSizeInBytes);
#else
    return false;
#endif
}

RequestType_e WirelessApi::RecvRequest()
{
#if ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
    return Python::RecvRequest();
#else
    return REQ_INVALID;
#endif
}

bool WirelessApi::DisconnectFromClient()
{
#if ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
    return Python::DisconnectFromClient();
#else
    return false;
#endif
}

/*
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
* MSP432 HANDLERS
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#if TARGET_HW_MSP432

/*
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * DESCRIPTION: setExternalHwPower
 * This function enables/disables power to hardware on the Glove PCB.
 *
 * Hardware that is controlled with this function includes:
 * - HC-05 Bluetooth Module
 * - Flex sensor circuitry (amplifier, LPF)
 * - MPU6500 Gyro/Accelerometer
 * - CFAL6448A LCD
 *
 * INPUTS:
 * @enable - If true, enable power to the external hardware. False disables power.
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
bool WirelessApi::MSP432::SetMode(hc05Mode mode)
{
    baudRate_e baudRate;

    // Determine required baudRate and EN setting to place HC-05 is expected mode.
    if (mode == HC05MODE_DATA)
    {
        baudRate = BAUDRATE_9600;
        GPIO_setOutputLowOnPin(systemIO.bluetoothEn.port, systemIO.bluetoothEn.pin);
    }
    else
    {
        baudRate = BAUDRATE_38400;
        GPIO_setOutputHighOnPin(systemIO.bluetoothEn.port, systemIO.bluetoothEn.pin);
    }

    // Initialize UART TX/RX pins for communicating with the HC-05 module.
    if (!Uart::init(baudRate))
    {
        /* Uart initializations failed */
        while (1);
    }

    // Initialize a GPIO for controlling the HC-05 EN pin to select between
    // Data/Command modes.
    MAP_GPIO_setAsOutputPin(systemIO.bluetoothEn.port, systemIO.bluetoothEn.pin);

    return true;
}

#endif // TARGET_HW_MSP432

/*
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
* PYTHON HANDLERS
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#if ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
bool WirelessApi::Python::ConnectToClient(int port_num)
{
    printf("WirelessApi::Python::ConnectToClient\n");

    PyObject *pDict;    // server.py module's namespace
    PyObject *pSocket;  // server.ServerSocket class    

    // Move PYTHONPATH to current working directory to find nxp module
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");
    
    // Load the module object (nxp.py)
    PythonAssert((pModule = PyImport_ImportModule(SERVER_MODULE)));

    // Get functions from the module's namespace (PyObject.__dict__)
    PythonAssert((pDict = PyModule_GetDict(pModule)));
    
    // Get a handle to the nxp.sensor constructor
    PythonAssert((pSocket = PyDict_GetItemString(pDict, SOCKET_CLASS)));

    // Call the sensor constructor
    if (PyCallable_Check(pSocket)) 
    {
        PyObject* portNumObj = Py_BuildValue("i", port_num);
        PythonAssert((pSocketObj = PyObject_CallFunctionObjArgs(pSocket, portNumObj, NULL)));
        Py_DECREF(portNumObj);
    }
    else 
        PythonAssert(NULL); // forces an assertion

    // Remove references to Python objects for garbage collection
    Py_DECREF(pDict);
    Py_DECREF(pSocket);

    // Call the connect to socket function to search for a connection
    // with a client.
    printf("C: Listening for connection to client.\n");
    PyObject* conn = PyObject_CallMethod(pSocketObj, CONNECT_FUNC, NULL);
    if (conn == Py_None)
    {
        printf("WirelessApi::Python::ConnectToClient - Could not connect to a client.\n");
        return false;
    }
    else
    {
        printf("WirelessApi::Python::ConnectToClient - Connected successfully.\n");
        return true;
    }
    
}

bool WirelessApi::Python::SendResponse(char* data, int dataSizeInBytes)
{
    printf("WirelessApi::Python::SendResponse\n");

    // Convert character array into a Python list to be received by
    // client.recvResponse function.

    PyObject* rx = PyObject_CallMethod(pSocketObj, SEND_RESP_FUNC, NULL);
    if (rx == Py_False)
    {
        printf("WirelessApi::Python::SendResponse - Failed to send!!\n");
        return false;
    }
    return true;
}

WirelessApi::RequestType_e WirelessApi::Python::RecvRequest()
{
    printf("WirelessApi::Python::RecvRequest\n");
    return REQ_INVALID;
}

bool WirelessApi::Python::DisconnectFromClient()
{
    printf("WirelessApi::Python::DisconnectFromClient\n");
    PyObject_CallMethod(pSocketObj, DISCONNECT_FUNC, NULL);
    Py_DECREF(pModule);
    //Py_DECREF(pSocketObj);
    return true;
}

#endif // ENABLE_WIRELESS_API_PYTHON & TARGET_HW_PYTHON_CAPABLE
