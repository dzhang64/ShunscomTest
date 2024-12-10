# ShunscomTest

ShunscomTest is a C++ project that includes various utilities and functionalities for serial communication, XML parsing, and logging.

## Requirements

- CMake 3.26 or higher
- Windows OS
- Vcpkg for dependency management
- libusb-1.0

## Installation

1. **Clone the repository:**
    ```sh
    git clone https://github.com/yourusername/ShunscomTest.git
    cd ShunscomTest
    ```

2. **Install dependencies using vcpkg:**
    ```sh
    ./vcpkg/vcpkg install libusb
    ```

3. **Configure and build the project:**
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## Usage

Run the executable:
the main function showed how to use the codes, you can make it as a dll or so by changing the CmakeList.
