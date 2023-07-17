# CIRC 2023 GPS Beacon, and Night Task hardware/Software

## Description

This is a variety of information to support the CIRC 2023 Night Task & Traversal Task

## Usage during CIRC Search & Rescue task

To use the Astronaut GPS Beacon, connect to the open SSID "Isaac_Asimov"
* Astronaut IP will be accessible at http://10.10.11.1 Port 80
* Astronaut also accessible by Telnet at 10.10.11.1 Port 23
* Astronaut Beacon is a standard 802.11b/g/n 2.4Ghz access point on Channel 1
* See the Simulation folder in this repo for example output (GPS Beacon) Web/Telnet

To use the Reactor GPS Beacon, connect to the open SSID "Reactor"
* Reactor IP will be accessible at http://10.10.10.1 Port 80
* Reactor also accessible by Telnet at 10.10.10.1 Port 23
* Reactor hardware is a standard 802.11b/g/n 2.4Ghz access point on Channel 1
* See the Simulation folder in this repo for example output (GPS Beacon) Web/Telnet
	* There may be additional functionality/data added before event time permitting to assist teams
		* Telnet commands to test/start reactor
		* Separate webpage to test/start reactor
		* This page will be updated if so, as well as simulation folder
* CAD files provided
	* Reactor Module - May be used to confirm handling and gripping requirements
	* Reactor - May be used to test and confirm clearance
		* There is a minimum of 30mm between the reactor and module and housing wall for arm clearance
	* Control Panel - Can be used to test ability to manually press buttons if required

## Usage during CIRC Search & Rescue task

To use the BLE Beacon, you will need a device that supports Bluetooth LE
* A great place to start for [information](https://circuitdigest.com/microcontroller-projects/esp32-based-bluetooth-ibeacon) 
* The beacon in the field has an external antenna, using an ESP32-S3 module 
* The antenna on the beacon is omnidirectional (Vertical Polarity).
	* Initial testing showed range of around 90M with Samsung S21 Ultra phone using [Link](https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner&hl=en_CA&gl=US)
	* Some ability to roughly identify bearing would be convenient
* The beacon will broadcast at 1Hz, FSS (Spread Spectrum)
* Example code provided and is similar to code that will be on the device
  
## Setting up your own hardware for testing

* The reactor and astronaut gps beacons are largely identical code-wise.
* The microcontroller used for all devices is a ESP-32-S3 Dev board you can view [Here](https://www.digikey.ca/en/products/detail/espressif-systems/ESP32-S3-DEVKITC-1U-N8R2/16162648)
	* The code is written in the arduino IDE, which means you can likely use the code on other hardware with wireless functionality. The code uses common libraries and a standard UART GPS module
	*  Using the older common ESP32 WROOM/WROVER is likely code compatible.
* The BLE Beacon code is based on this [Example](https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_iBeacon/BLE_iBeacon.ino)

## Authors

Torban Peterson - torban@torban.ca

## License
The MIT License (MIT)

Copyright (c) 2023 Torban Peterson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.