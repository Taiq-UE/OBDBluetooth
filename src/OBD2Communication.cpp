// #include "OBD2Communication.hpp"
// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <map>
// #include <algorithm>
//
//
// OBD2Communication::OBD2Communication(BluetoothConnection& bt) : btConnection(bt) {}
//
// struct PID {
//     std::string description;
//     int length{};
//     std::string unit;
// };
//
// std::map<std::string, PID> pidDetails = {
//         {"0100", {"PIDs supported [01-20]", 4, ""}},
//         {"0101", {"Monitor status since DTCs cleared", 4, ""}},
//         {"0102", {"Freeze DTC", 2, ""}},
//         {"0103", {"Fuel system status", 2, ""}},
//         {"0104", {"Calculated engine load", 1, "%"}},
//         {"0105", {"Engine coolant temperature", 1, "°C"}},
//         {"0106", {"Short term fuel trim—Bank 1", 1, "%"}},
//         {"0107", {"Long term fuel trim—Bank 1", 1, "%"}},
//         {"0108", {"Short term fuel trim—Bank 2", 1, "%"}},
//         {"0109", {"Long term fuel trim—Bank 2", 1, "%"}},
//         {"010A", {"Fuel pressure", 1, "kPa"}},
//         {"010B", {"Intake manifold absolute pressure", 1, "kPa"}},
//         {"010C", {"Engine RPM", 2, "rpm"}},
//         {"010D", {"Vehicle speed", 1, "km/h"}},
//         {"010E", {"Timing advance", 1, "°"}},
//         {"010F", {"Intake air temperature", 1, "°C"}},
//         {"0110", {"MAF air flow rate", 2, "g/s"}},
//         {"0111", {"Throttle position", 1, "%"}},
//         {"0112", {"Commanded secondary air status", 1, ""}},
//         {"0113", {"Oxygen sensors present (2 banks)", 1, ""}},
//         {"0114", {"Oxygen Sensor 1 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"0115", {"Oxygen Sensor 2 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"0116", {"Oxygen Sensor 3 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"0117", {"Oxygen Sensor 4 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"0118", {"Oxygen Sensor 5 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"0119", {"Oxygen Sensor 6 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"011A", {"Oxygen Sensor 7 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"011B", {"Oxygen Sensor 8 A: Voltage, Short term fuel trim", 2, "V"}},
//         {"011C", {"OBD standards this vehicle conforms to", 1, ""}},
//         {"011D", {"Oxygen sensors present (4 banks)", 1, ""}},
//         {"011E", {"Auxiliary input status", 1, ""}},
//         {"011F", {"Run time since engine start", 2, "s"}},
//         {"0120", {"PIDs supported [21-40]", 4, ""}},
//         {"0121", {"Distance traveled with malfunction indicator lamp (MIL) on", 2, "km"}},
//         {"0122", {"Fuel Rail Pressure (relative to manifold vacuum)", 2, "kPa"}},
//         {"0123", {"Fuel Rail Pressure (diesel, or gasoline direct inject)", 2, "kPa"}},
//         {"0124", {"Oxygen Sensor 1 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0125", {"Oxygen Sensor 2 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0126", {"Oxygen Sensor 3 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0127", {"Oxygen Sensor 4 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0128", {"Oxygen Sensor 5 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0129", {"Oxygen Sensor 6 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"012A", {"Oxygen Sensor 7 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"012B", {"Oxygen Sensor 8 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"012C", {"Commanded EGR", 1, "%"}},
//         {"012D", {"EGR Error", 1, "%"}},
//         {"012E", {"Commanded evaporative purge", 1, "%"}},
//         {"012F", {"Fuel Tank Level Input", 1, "%"}},
//         {"0130", {"Warm-ups since codes cleared", 1, ""}},
//         {"0131", {"Distance traveled since codes cleared", 2, "km"}},
//         {"0132", {"Evaporative system vapor pressure", 2, "Pa"}},
//         {"0133", {"Barometric pressure", 1, "kPa"}},
//         {"0134", {"Oxygen Sensor 1 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0135", {"Oxygen Sensor 2 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0136", {"Oxygen Sensor 3 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0137", {"Oxygen Sensor 4 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0138", {"Oxygen Sensor 5 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"0139", {"Oxygen Sensor 6 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"013A", {"Oxygen Sensor 7 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"013B", {"Oxygen Sensor 8 B: Voltage, Short term fuel trim", 2, "V"}},
//         {"013C", {"Catalyst Temperature: Bank 1, Sensor 1", 2, "°C"}},
//         {"013D", {"Catalyst Temperature: Bank 2, Sensor 1", 2, "°C"}},
//         {"013E", {"Catalyst Temperature: Bank 1, Sensor 2", 2, "°C"}},
//         {"013F", {"Catalyst Temperature: Bank 2, Sensor 2", 2, "°C"}},
//         {"0140", {"PIDs supported [41-60]", 4, ""}},
//         {"0141", {"Monitor status this drive cycle", 4, ""}},
//         {"0142", {"Control module voltage", 2, "V"}},
//         {"0143", {"Absolute load value", 2, "%"}},
//         {"0144", {"Commanded equivalence ratio", 2, ""}},
//         {"0145", {"Relative throttle position", 1, "%"}},
//         {"0146", {"Ambient air temperature", 1, "°C"}},
//         {"0147", {"Absolute throttle position B", 1, "%"}},
//         {"0148", {"Absolute throttle position C", 1, "%"}},
//         {"0149", {"Accelerator pedal position D", 1, "%"}},
//         {"014A", {"Accelerator pedal position E", 1, "%"}},
//         {"014B", {"Accelerator pedal position F", 1, "%"}},
//         {"014C", {"Commanded throttle actuator", 1, "%"}},
//         {"014D", {"Time run with MIL on", 2, "min"}},
//         {"014E", {"Time since trouble codes cleared", 2, "min"}},
//         {"014F", {"Maximum value for equivalence ratio, oxygen sensor voltage, oxygen sensor current, and intake manifold absolute pressure", 2, ""}},
//         {"0150", {"Maximum value for air flow rate from mass air flow sensor", 2, "g/s"}},
//         {"0151", {"Fuel Type", 1, ""}},
//         {"0152", {"Ethanol fuel %", 1, "%"}},
//         {"0153", {"Absolute Evap system Vapor Pressure", 2, "kPa"}},
//         {"0154", {"Evap system vapor pressure", 2, "Pa"}},
//         {"0155", {"Short term secondary oxygen sensor trim—Bank 1", 1, "%"}},
//         {"0156", {"Long term secondary oxygen sensor trim—Bank 1", 1, "%"}},
//         {"0157", {"Short term secondary oxygen sensor trim—Bank 2", 1, "%"}},
//         {"0158", {"Long term secondary oxygen sensor trim—Bank 2", 1, "%"}},
//         {"0159", {"Fuel rail pressure (absolute)", 2, "kPa"}},
//         {"015A", {"Relative accelerator pedal position", 1, "%"}},
//         {"015B", {"Hybrid battery pack remaining life", 1, "%"}},
//         {"015C", {"Engine oil temperature", 1, "°C"}},
//         {"015D", {"Fuel injection timing", 2, "°"}},
//         {"015E", {"Engine fuel rate", 2, "L/h"}},
//         {"015F", {"Emission requirements to which vehicle is designed", 1, ""}},
//         {"0160", {"PIDs supported [61-80]", 4, ""}},
//         {"0161", {"Driver's demand engine - percent torque", 1, "%"}},
//         {"0162", {"Actual engine - percent torque", 1, "%"}},
//         {"0163", {"Engine reference torque", 2, "Nm"}},
//         {"0164", {"Engine percent torque data", 5, "%"}},
//         {"0165", {"Auxiliary input/output supported", 4, ""}},
//         {"0166", {"Mass air flow sensor", 2, "g/s"}},
//         {"0167", {"Engine coolant temperature", 1, "°C"}},
//         {"0168", {"Intake air temperature", 1, "°C"}},
//         {"0169", {"Throttle position", 1, "%"}},
//         {"016A", {"Fuel pressure", 1, "kPa"}},
//         {"016B", {"Barometric pressure", 1, "kPa"}},
//         {"016C", {"Commanded evaporative purge", 1, "%"}},
//         {"016D", {"Fuel level input", 1, "%"}},
//         {"016E", {"Ambient air temperature", 1, "°C"}},
//         {"016F", {"Time run with MIL on", 2, "min"}},
//         {"0170", {"Time since trouble codes cleared", 2, "min"}},
//         {"0171", {"Maximum value for equivalence ratio", 2, ""}},
//         {"0172", {"Maximum value for air flow rate", 2, "g/s"}},
//         {"0173", {"Fuel Type", 1, ""}},
//         {"0174", {"Ethanol fuel %", 1, "%"}},
//         {"0175", {"Absolute Evap system vapor pressure", 2, "kPa"}},
//         {"0176", {"Evap system vapor pressure", 2, "Pa"}},
//         {"0177", {"Short term secondary oxygen sensor trim—Bank 1", 1, "%"}},
//         {"0178", {"Long term secondary oxygen sensor trim—Bank 1", 1, "%"}},
//         {"0179", {"Short term secondary oxygen sensor trim—Bank 2", 1, "%"}},
//         {"017A", {"Long term secondary oxygen sensor trim—Bank 2", 1, "%"}},
//         {"017B", {"Fuel rail pressure (absolute)", 2, "kPa"}},
//         {"017C", {"Relative accelerator pedal position", 1, "%"}},
//         {"017D", {"Hybrid battery pack remaining life", 1, "%"}},
//         {"017E", {"Engine oil temperature", 1, "°C"}},
//         {"017F", {"Fuel injection timing", 2, "°"}},
//         {"0180", {"PIDs supported [81-A0]", 4, ""}},
//         {"0181", {"Engine coolant temperature", 1, "°C"}},
//         {"0182", {"Intake air temperature", 1, "°C"}},
//         {"0183", {"Throttle position", 1, "%"}},
//         {"0184", {"Fuel pressure", 1, "kPa"}},
//         {"0185", {"Barometric pressure", 1, "kPa"}},
//         {"0186", {"Commanded evaporative purge", 1, "%"}},
//         {"0187", {"Fuel level input", 1, "%"}},
//         {"0188", {"Ambient air temperature", 1, "°C"}},
//         {"0189", {"Time run with MIL on", 2, "min"}},
//         {"018A", {"Time since trouble codes cleared", 2, "min"}},
//         {"018B", {"Maximum value for equivalence ratio", 2, ""}},
//         {"018C", {"Maximum value for air flow rate", 2, "g/s"}},
//         {"018D", {"Fuel Type", 1, ""}},
//         {"018E", {"Ethanol fuel %", 1, "%"}},
//         {"018F", {"Absolute Evap system vapor pressure", 2, "kPa"}},
//         {"0190", {"PIDs supported [A1-C0]", 4, ""}},
//         {"0191", {"Engine coolant temperature", 1, "°C"}},
//         {"0192", {"Intake air temperature", 1, "°C"}},
//         {"0193", {"Throttle position", 1, "%"}},
//         {"0194", {"Fuel pressure", 1, "kPa"}},
//         {"0195", {"Barometric pressure", 1, "kPa"}},
//         {"0196", {"Commanded evaporative purge", 1, "%"}},
//         {"0197", {"Fuel level input", 1, "%"}},
//         {"0198", {"Ambient air temperature", 1, "°C"}},
//         {"0199", {"Time run with MIL on", 2, "min"}},
//         {"019A", {"Time since trouble codes cleared", 2, "min"}},
//         {"019B", {"Maximum value for equivalence ratio", 2, ""}},
//         {"019C", {"Maximum value for air flow rate", 2, "g/s"}},
//         {"019D", {"Fuel Type", 1, ""}},
//         {"019E", {"Ethanol fuel %", 1, "%"}},
//         {"019F", {"Absolute Evap system vapor pressure", 2, "kPa"}},
//         {"01A0", {"PIDs supported [C1-C8]", 4, ""}},
//         {"01A1", {"Engine coolant temperature", 1, "°C"}},
//         {"01A2", {"Intake air temperature", 1, "°C"}},
//         {"01A3", {"Throttle position", 1, "%"}},
//         {"01A4", {"Fuel pressure", 1, "kPa"}},
//         {"01A5", {"Barometric pressure", 1, "kPa"}},
//         {"01A6", {"Commanded evaporative purge", 1, "%"}},
//         {"01A7", {"Fuel level input", 1, "%"}},
//         {"01A8", {"Ambient air temperature", 1, "°C"}},
//         {"01A9", {"Time run with MIL on", 2, "min"}},
//         {"01AA", {"Time since trouble codes cleared", 2, "min"}},
//         {"01AB", {"Maximum value for equivalence ratio", 2, ""}},
//         {"01AC", {"Maximum value for air flow rate", 2, "g/s"}},
//         {"01AD", {"Fuel Type", 1, ""}},
//         {"01AE", {"Ethanol fuel %", 1, "%"}},
//         {"01AF", {"Absolute Evap system vapor pressure", 2, "kPa"}},
//         {"01B0", {"PIDs supported [C9-C8]", 4, ""}},
//         {"01B1", {"Engine coolant temperature", 1, "°C"}},
//         {"01B2", {"Intake air temperature", 1, "°C"}},
//         {"01B3", {"Throttle position", 1, "%"}},
//         {"01B4", {"Fuel pressure", 1, "kPa"}},
//         {"01B5", {"Barometric pressure", 1, "kPa"}},
//         {"01B6", {"Commanded evaporative purge", 1, "%"}},
//         {"01B7", {"Fuel level input", 1, "%"}},
//         {"01B8", {"Ambient air temperature", 1, "°C"}},
//         {"01B9", {"Time run with MIL on", 2, "min"}},
//         {"01BA", {"Time since trouble codes cleared", 2, "min"}},
//         {"01BB", {"Maximum value for equivalence ratio", 2, ""}},
//         {"01BC", {"Maximum value for air flow rate", 2, "g/s"}},
//         {"01BD", {"Fuel Type", 1, ""}},
//         {"01BE", {"Ethanol fuel %", 1, "%"}},
//         {"01BF", {"Absolute Evap system vapor pressure", 2, "kPa"}},
//         {"01C0", {"PIDs supported [C1-C8]", 4, ""}},
//         {"01C1", {"Engine coolant temperature", 1, "°C"}},
//         {"01C2", {"Intake air temperature", 1, "°C"}},
//         {"01C3", {"Throttle position", 1, "%"}},
//         {"01C4", {"Fuel pressure", 1, "kPa"}},
//         {"01C5", {"Barometric pressure", 1, "kPa"}},
//         {"01C6", {"Commanded evaporative purge", 1, "%"}},
//         {"01C7", {"Fuel level input", 1, "%"}},
//         {"01C8", {"Ambient air temperature", 1, "°C"}}
// };
//
//
// bool OBD2Communication::initialize() {
//     // Initialize OBD-II communication (e.g., send AT commands)
//     btConnection.send("AT Z\r"); // Reset all
//     std::cout << "Initializing OBD2 communication" << std::endl;
//     Sleep(1000); // Wait for device to reset
//
//     btConnection.send("AT E0\r"); // Echo Off
//     Sleep(100);
//     btConnection.send("AT L0\r"); // Linefeeds Off
//     Sleep(100);
//     btConnection.send("AT SP 0\r"); // Set Protocol to Auto
//     Sleep(100);
//     btConnection.send("AT H1\r"); // Headers On
//     Sleep(100);
//     btConnection.send("AT DPN\r"); // Describe Protocol by Number
//     Sleep(100);
//     btConnection.send("0100\r"); // Check supported PIDs
//     Sleep(100);
//
//     std::string response = btConnection.receive();
//     std::cout << "Initialization response: " << response << std::endl;
//
//     return true;
// }
//
// std::string OBD2Communication::sendCommand(const std::string& command) {
//     btConnection.send(command);
//     Sleep(75); // Wait for response
//     return btConnection.receive();
// }
//
// int OBD2Communication::getSpeed() {
//     std::string response = sendCommand("010D\r"); // PID for vehicle speed
//     if (response.empty()) {
//         return -1;
//     }
//
//     size_t start = response.find("41 ");
//     if (start == std::string::npos) {
//         return -1;
//     }
//
//     std::string data = response.substr(start + 6);
//     std::istringstream ss(data);
//
//     std::string byteStr;
//     if (!(ss >> byteStr)) {
//         return -1;
//     }
//
//     int value;
//     std::istringstream(byteStr) >> std::hex >> value;
//
//     return value;
// }
//
// int OBD2Communication::getRPM() {
//     std::string response = sendCommand("010C\r"); // PID for RPM
//     if (response.empty()) {
//         return -1;
//     }
//
//     size_t start = response.find("41 ");
//     if (start == std::string::npos) {
//         return -1;
//     }
//
//     std::string data = response.substr(start + 6);
//     std::istringstream ss(data);
//
//     std::string byteStr1, byteStr2;
//     if (!(ss >> byteStr1 >> byteStr2)) {
//         return -1;
//     }
//
//     int value1, value2;
//     std::istringstream(byteStr1) >> std::hex >> value1;
//     std::istringstream(byteStr2) >> std::hex >> value2;
//
//     int rpm = ((value1 * 256) + value2) / 4; // RPM needs to be divided by 4.0 as per OBD-II spec
//
//     return rpm;
// }
//
// double OBD2Communication::getThrottlePosition() {
//     std::string response = sendCommand("0111\r"); // PID for throttle position
//     if (response.empty()) {
//         return -1;
//     }
//
//     size_t start = response.find("41 ");
//     if (start == std::string::npos) {
//         return -1;
//     }
//
//     std::string data = response.substr(start + 6);
//     std::istringstream ss(data);
//
//     std::string byteStr;
//     if (!(ss >> byteStr)) {
//         return -1;
//     }
//
//     int value;
//     std::istringstream(byteStr) >> std::hex >> value;
//
//     return value * 100.0 / 255.0; // Throttle position is a percentage of the maximum value (255)
// }
//
// double OBD2Communication::getBoostLevel() {
//     // Get absolute manifold pressure
//     std::string responseManifold = sendCommand("010B\r"); // PID for Intake Manifold Absolute Pressure
//     if (responseManifold.empty()) {
//         return -1;
//     }
//
//     size_t startManifold = responseManifold.find("41 ");
//     if (startManifold == std::string::npos) {
//         return -1;
//     }
//
//     std::string dataManifold = responseManifold.substr(startManifold + 6);
//     std::istringstream ssManifold(dataManifold);
//
//     std::string byteStrManifold;
//     if (!(ssManifold >> byteStrManifold)) {
//         return -1;
//     }
//
//     int valueManifold;
//     std::istringstream(byteStrManifold) >> std::hex >> valueManifold;
//
//     // Use hardcoded barometric (ambient) pressure
//     double valueBarometric = 101.6;
//
//     // Calculate and return boost level in bars
//     return (valueManifold - valueBarometric) / 100.0;
// }
//
// int OBD2Communication::getCoolantTemperature() {
//     std::string response = sendCommand("0105\r"); // PID for coolant temperature
//     if (response.empty()) {
//         return -1;
//     }
//
//     size_t start = response.find("41 ");
//     if (start == std::string::npos) {
//         return -1;
//     }
//
//     std::string data = response.substr(start + 6);
//     std::istringstream ss(data);
//
//     std::string byteStr;
//     if (!(ss >> byteStr)) {
//         return -1;
//     }
//
//     int value;
//     std::istringstream(byteStr) >> std::hex >> value;
//
//     return value - 40; // The value needs to be offset by -40 as per OBD-II spec
// }
//
// double OBD2Communication::getOBDSupplyVoltage() {
//     std::string response = sendCommand("AT RV\r");
// //    std::cout << "Raw response: " << response << std::endl; // Print raw response
//
//     // Remove any non-digit characters from the response
//     response.erase(std::remove_if(response.begin(), response.end(), [](char c) { return !std::isdigit(c) && c != '.'; }), response.end());
//
//     if (response.empty()) {
//         return -1;
//     }
//
//     return std::stod(response);
// }
//
// std::string OBD2Communication::getDTCs() {
//     return sendCommand("03\r"); // Mode 03 for DTCs
// }
//
// void OBD2Communication::parseAndPrintResponse(const std::string& command, const std::string& response) {
//     if (response.empty()) {
//         std::cout << "No response for command " << command << std::endl;
//         return;
//     }
//
//     std::cout << "Response for command " << command << ": " << response << std::endl;
//     size_t start = response.find("41 ");
//     if (start == std::string::npos) {
//         std::cout << "Invalid response for command " << command << std::endl;
//         return;
//     }
//
//     std::string data = response.substr(start + 3); // Skip "41 "
//     std::istringstream ss(data);
//     std::vector<int> bytes;
//     std::string byteStr;
//
//     while (ss >> byteStr) {
//         int byteValue;
//         std::istringstream(byteStr) >> std::hex >> byteValue;
//         bytes.push_back(byteValue);
//     }
//
//     if (pidDetails.find(command) == pidDetails.end()) {
//         std::cout << "Unknown PID length for command " << command << std::endl;
//         return;
//     }
//
//     int length = pidDetails[command].length;
//     if (bytes.size() < length) {
//         std::cout << "Incomplete response for command " << command << std::endl;
//         return;
//     }
//
//     // Print parsed values
//     std::cout << pidDetails[command].description << ": ";
//     if (command == "010C") { // RPM
//         int rpm = ((bytes[2] * 256) + bytes[3]) / 4;
//         std::cout << rpm << " " << pidDetails[command].unit << std::endl;
//     } else if (command == "010D") { // Speed
//         int speed = bytes[2];
//         std::cout << speed << " " << pidDetails[command].unit << std::endl;
//     } else if (command == "0105") { // Coolant temperature
//         int temp = bytes[2] - 40;
//         std::cout << temp << " " << pidDetails[command].unit << std::endl;
//     } else {
//         for (int i = 0; i < length; ++i) {
//             std::cout << std::hex << bytes[i] << " ";
//         }
//         std::cout << pidDetails[command].unit << std::endl;
//     }
// }
//
// void OBD2Communication::queryAllPIDs() {
//     for (const auto& pid : pidDetails) {
//         std::string command = pid.first + "\r";
//         std::string response = sendCommand(command);
//         parseAndPrintResponse(pid.first, response);
//         Sleep(100); // Wait for a short while before sending the next command
//     }
// }
