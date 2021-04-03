 /****************************************************************************
 * ISIS_Antenna.cpp
 * 
 * Hardware   : ISIS Antenna
 * Manual     : ISIS.ANTS.DS.001, version 3.0
 * About      : The class definition to interface with the UHF transceiver.
 * 
 * Author     : Carlos Carrasquillo
 * Date       : July 16, 2020
 * Modified   : March 26, 2021
 * Proprty of : ADAMUS Lab
 ****************************************************************************/

#include <unistd.h>
#include "ISIS_Antenna.h"


ISIS_Antenna::ISIS_Antenna(bool debug, uint8_t bus) {
	this->debug = debug;
	i2c = new I2C_Functions(bus, ISIS_ANTENNA_I2C_ADDR_M0);
	microcontroller = 0;
	resetController();
}

void ISIS_Antenna::resetController() {
	i2c->write(RESET, 0x00);
	usleep(30000);
}

void ISIS_Antenna::selectMicrocontroller(int microcontroller) {
	if (microcontroller == USE_M0){
		i2c->set_address(ISIS_ANTENNA_I2C_ADDR_M0); 
		microcontroller = 0;
		resetController();
	} else if (microcontroller == USE_M1) {
		i2c->set_address(ISIS_ANTENNA_I2C_ADDR_M1);
		microcontroller = 1;
		resetController();
	} else {
		printe("Please select an microcontroller (0 or 1).");
	}
}

void ISIS_Antenna::toggleMicrocontroller() {
	if (microcontroller == USE_M0) {
		i2c->set_address(ISIS_ANTENNA_I2C_ADDR_M1); 
		microcontroller = 1;
	} else {
		i2c->set_address(ISIS_ANTENNA_I2C_ADDR_M0); 
		microcontroller = 0;
	}
	resetController();
}

void ISIS_Antenna::armAntennas() {
	i2c->write(ARM, 0x00);
}

void ISIS_Antenna::disarmAntennas() {
	i2c->write(DISARM, 0x00);
}

void ISIS_Antenna::deployAntenna(uint8_t antenna, uint8_t deploy_time) {
	uint8_t command;

	switch (antenna) {
		case 1: command = DEPLOY_ANT_1; break;
		case 2: command = DEPLOY_ANT_2; break;
		case 3: command = DEPLOY_ANT_3; break;
		case 4: command = DEPLOY_ANT_4; break;
		default: command = 0;
	}

	if (command) i2c->write(command, deploy_time);
}

void ISIS_Antenna::autoDeployAll(uint8_t deploy_time) {
	i2c->write(AUTO_DEPLOY_ALL, deploy_time);
}

void ISIS_Antenna::overrideAntenna(uint8_t antenna, uint8_t deploy_time) {
	uint8_t command;

	switch (antenna) {
		case 1: command = OVERRIDE_ANT_1; break;
		case 2: command = OVERRIDE_ANT_2; break;
		case 3: command = OVERRIDE_ANT_3; break;
		case 4: command = OVERRIDE_ANT_4; break;
		default: command = 0;
	}

	if (command) i2c->write(command, deploy_time);
}

void ISIS_Antenna::cancelActivation() {
	i2c->write(CANCEL_ACTIVATION, 0x00);
}

float ISIS_Antenna::getTemperature() {
	uint16_t raw_data = i2c->read2(MEASURE_TEMPERATURE);
	float vread = 3.22580645 * raw_data;								// (3.3/1024) * raw_data * 1000

	uint8_t vout_length = sizeof(vout) / sizeof(vout[0]);
	if (vread < vout[vout_length-1] || vread > vout[0]) return -200;	// error check

	for (uint8_t i = 0; i < vout_length; i++) {
		 if (vread >= vout[i]) {
		 	return temp[i];
		 }
	}
	return -200;				
}

uint16_t ISIS_Antenna::getStatusCode() {
	uint16_t status = i2c->read2(REPORT_DEPLOY_STATUS);
	std::cout << "Status Code: " << std::hex << static_cast<int>(status) << std::endl;
	return status;
}

uint16_t ISIS_Antenna::getStatus() {
	uint16_t status = i2c->read2(REPORT_DEPLOY_STATUS);

	std::string out_str = "Status:\n";

	if (BIT_VAL(status, 0))  out_str += "\tAntenna system is currently armed.\n";
					    else out_str += "\tAntenna system is currently NOT armed.\n";

	/* Antenna 4 */
	if (BIT_VAL(status, 1))  out_str += "\tAntenna 4's deployment system is currently active.\n";
					    else out_str += "\tAntenna 4's deployment system is currently NOT active.\n";
	if (BIT_VAL(status, 2))  out_str += "\tThe latest deployment system activation for Antenna 4 was stopped because a time limit was reached.\n";
					    else out_str += "\tThe latest deployment system activation for Antenna 4 was stopped for a reason other than exceeding the time limit.\n";
	if (BIT_VAL(status, 3))  out_str += "\tAntenna 4's deployment switch indicates the antenna is NOT deployed.\n";
						else out_str += "\tAntenna 4's deployment switch indicates the antenna is deployed.\n";

	/* Antenna 3 */
	if (BIT_VAL(status, 5))  out_str += "\tAntenna 3's deployment system is currently active.\n";
						else out_str += "\tAntenna 3's deployment system is currently NOT active.\n";
	if (BIT_VAL(status, 6))  out_str += "\tThe latest deployment system activation for Antenna 3 was stopped because a time limit was reached.\n";
						else out_str += "\tThe latest deployment system activation for Antenna 3 was stopped for a reason other than exceeding the time limit.\n";
	if (BIT_VAL(status, 7))  out_str += "\tAntenna 3's deployment switch indicates the antenna is NOT deployed.\n";
						else out_str += "\tAntenna 3's deployment switch indicates the antenna is deployed.\n";

	/* IG */
	if (BIT_VAL(status, 8))  out_str += "\tAntenna system is currently ignoring the antenna deployment switches.\n";
						else out_str += "\tAntenna system is currently NOT ignoring the antenna deployment switches.\n";

	/* Antenna 2 */
	if (BIT_VAL(status, 9))  out_str += "\tAntenna 2's deployment system is currently active.\n";
					    else out_str += "\tAntenna 2's deployment system is currently NOT active.\n";
	if (BIT_VAL(status, 10)) out_str += "\tThe latest deployment system activation for Antenna 2 was stopped because a time limit was reached.\n";
						else out_str += "\tThe latest deployment system activation for Antenna 2 was stopped for a reason other than exceeding the time limit.\n";
	if (BIT_VAL(status, 11)) out_str += "\tAntenna 2's deployment switch indicates the antenna is NOT deployed.\n";
						else out_str += "\tAntenna 2's deployment switch indicates the antenna is deployed.\n";

	/* Antenna 1 */
	if (BIT_VAL(status, 13)) out_str += "\tAntenna 1's deployment system is currently active.\n";
						else out_str += "\tAntenna 1's deployment system is currently NOT active.\n";
	if (BIT_VAL(status, 14)) out_str += "\tThe latest deployment system activation for Antenna 1 was stopped because a time limit was reached.\n";
						else out_str += "\tThe latest deployment system activation for Antenna 1 was stopped for a reason other than exceeding the time limit.\n";
	if (BIT_VAL(status, 15)) out_str += "\tAntenna 1's deployment switch indicates the antenna is NOT deployed.\n";
					 	else out_str += "\tAntenna 1's deployment switch indicates the antenna is deployed.\n";

	if (debug) {
		std::cout << out_str += "Status Code: " << status << ".\n" << std::endl;
	}
	
	return status;
}

uint8_t ISIS_Antenna::getDeploymentCount(uint8_t antenna) {
	uint8_t command;

	switch (antenna) {
		case 1: command = REPORT_DEPLOY_CNT_ANT1; break;
		case 2: command = REPORT_DEPLOY_CNT_ANT2; break;
		case 3: command = REPORT_DEPLOY_CNT_ANT3; break;
		case 4: command = REPORT_DEPLOY_CNT_ANT4; break;
		default: command = 0;
	}

	if (command) return i2c->read(command);
	return 0;
}

float ISIS_Antenna::getDeploymentTime(uint8_t antenna) {
	uint8_t command;

	switch (antenna) {
		case 1: command = REPORT_DEPLOY_TIME_ANT1; break;
		case 2: command = REPORT_DEPLOY_TIME_ANT2; break;
		case 3: command = REPORT_DEPLOY_TIME_ANT3; break;
		case 4: command = REPORT_DEPLOY_TIME_ANT4; break;
		default: command = 0;
	}

	uint16_t time = i2c->read2(command);

	if (command) return ((float)time)/20.0;
	return 0;
}