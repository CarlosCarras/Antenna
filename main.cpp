#include <iostream>
#include "ISIS_Antenna.h"

#define DEBUG 1

int main() {
    ISIS_Antenna Antenna(DEBUG);
    
    /*  
    float temperature; 
    for(int i=1; i<5; i++) {
        Antenna.getStatus();
        temperature = Antenna.getTemperature();
        std::cout << "Antenna System Temperature: " << temperature << " DegC\n" << std::endl; 
        usleep(2000000);            // 2 second delay
    } 
    */

	Antenna.armAntennas();
    Antenna.overrideAntenna(1);
	Antenna.getStatusCode();
	//printf("Deployment Count: %d\n", Antenna.getDeploymentCount(1));
	//printf("Deployment Time: %2.4f\n", Antenna.getDeploymentTime(1));
	//Antenna.resetController();
};