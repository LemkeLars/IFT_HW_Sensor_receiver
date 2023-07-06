
# IFT_HW_Sensor_receiver

## Introduction

IFT_HW_Sensor_receiver is a Project written in C++ that receives data from different sensors related to water Quality via bluetooth, saves the data to an SD card and displays it on an LCD screen. The sender source code can be found [here](https://github.com/LemkeLars/IFT_HW_Sensor)

## Repository Structure

The repository is organized into four main directories:

- `include`: Contains the header files for the project.
- `lib`: Stores the library files needed for the sensor readings.
- `src`: Contains the main source code files for the project.
- `test`: Includes any test files to verify the project's functionality.

In addition to these, the repository includes:

- `.gitignore`: Specifies the files and directories that Git should ignore.
- `README.md`: The file you are currently reading.
- `platformio.ini`: Configuration file for PlatformIO, a cross-platform build system.

## Main Functionality

The primary functionality of the code lies in the `src` directory, specifically within the `main.cpp` file. The code is structured to receive data from the temperature and TDS sensors via bluetooth, store these readings on an SD card and display them on an LCD screen.
The code is designed to receive readings over a 60-second interval and take new samples every 15 minutes.

## Recent Updates

The most recent update to this project (as of July 6, 2023) added support for receiving the readings via bluetooth from the [sender](https://github.com/LemkeLars/IFT_HW_Sensor). The arduino then saves the data to an SD card and displays it on an LCD screen.

## Future Work

This project is actively being developed. Future updates may include additional sensor support and enhanced error handling.

## License

This project is open source under the MIT license.

## Contributing

Contributions to this project are welcome. Please feel free to fork the project and submit a pull request with your changes.

---
