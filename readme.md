# CIRC 2023 GPS Beacon, and Night Task hardware/Software

Simple overview of use/purpose.

## Description

This is a variety of hardware to support the CIRC 2023 Night Task
- Reactor GPS Beacon - Located at the reactor. Rovers can connect to the reactor to obtain GPS location and other information
- Astronaut GPS Beacon - Located on the suit of the Astronaut to recover. Can be used to help locate and traverse to the Astronaut
- Reactor module CAD diagram to aid in testing with rover arm
- Reactor itself which houses the reactor modules (3)

## Getting Started

To use the Reactor GPS Beacon, connect to the open SSID Reactor
* Reactor IP will be accessible at http://10.10.10.1 Port 80
* Reactor also accessible by Telnet at 10.10.10.1 Port 23

To use the Astronaut GPS Beacon, connect to the open SSID Isaac_Asimov
* Astronaut IP will be accessible at http://10.10.11.1 Port 80
* Astronaut also accessible by Telnet at 10.10.11.1 Port 23

## Authors

Torban Peterson - torban@torban.ca

## Version History
* 1.1 - ESP32-WROOM-32 GPS Beacon
    * Underclock to 80MHz to save power, add some code for RSSI but doesnt work when in AP mode
* 1.0 - ESP32-WROOM-32 GPS Beacon
    * Initial Release - GPS Beacon Firmware

## License

