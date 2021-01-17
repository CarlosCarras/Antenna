 /****************************************************************************
 * ISIS_Antenna.h
 * 
 * Hardware   : LM94022 (GS=10)
 * Manual     : Texas Instruments, SNIS140F
 * About      : The lookup table for the temperature sensor.
 * 
 * Author     : Carlos Carrasquillo
 * Date       : August 20, 2020
 * Modified   : August 20, 2020
 * Proprty of : ADAMUS Lab
 ****************************************************************************/

#ifndef LM94022_GS10_LOOKUP
#define LM94022_GS10_LOOKUP

#include <stdint.h>

uint16_t vout[] = {2616, 2607, 2598, 2589, 2580, 2571, 2562, 2553, 2543, 2533,
				   2522, 2512, 2501, 2491, 2481, 2470, 2460, 2449, 2439, 2429,
				   2418, 2408, 2397, 2387, 2376, 2366, 2355, 2345, 2334, 2324,
				   2313, 2302, 2292, 2281, 2271, 2260, 2250, 2239, 2228, 2218,
				   2207, 2197, 2186, 2175, 2164, 2154, 2143, 2132, 2122, 2111,
				   2100, 2089, 2079, 2068, 2057, 2047, 2036, 2025, 2014, 2004,
				   1993, 1982, 1971, 1961, 1950, 1939, 1928, 1918, 1907, 1896,
				   1885, 1874, 1864, 1853, 1831, 1820, 1810, 1799, 1788, 1777,
				   1766, 1756, 1745, 1734, 1723, 1712, 1701, 1690, 1679, 1668,
				   1657, 1646, 1635, 1624, 1613, 1602, 1591, 1580, 1569, 1558,
				   1547, 1536, 1525, 1514, 1503, 1492, 1481, 1470, 1459, 1448,
				   1436, 1425, 1414, 1403, 1391, 1380, 1369, 1358, 1346, 1335,
				   1324, 1313, 1301, 1290, 1279, 1268, 1257, 1245, 1234, 1223,
				   1212, 1201, 1189, 1178, 1167, 1155, 1144, 1133, 1122, 1110,
				   1099, 1088, 1076, 1065, 1054, 1042, 1031, 1020, 1008, 997,
				   986, 974, 963, 951, 940, 929, 917, 906, 895, 883, 872, 860,
				   849, 837, 826, 814, 803, 791, 780, 769, 757, 745, 734, 722,
				   711, 699, 688, 676, 665, 653, 642, 630, 618, 607, 595, 584,
				   572, 560, 549, 537, 525, 514, 502, 490, 479, 467, 455, 443,
				   432, 420};

int16_t temp[] = {-50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, 
	 			  -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, 
	 			  -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15,
	 			  -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 
	 			  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 
	 			  18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 
	 			  34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
	 			  50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 
	 			  66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 
	 			  82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 
	 			  98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 
	 			  111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 
	 			  123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 
	 			  135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 
	 			  147, 148, 149, 150};

#endif //LM94022_GS10_LOOKUP