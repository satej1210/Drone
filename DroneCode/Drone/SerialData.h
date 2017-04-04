#ifndef SerialData
String serialData;
void startSerialData() {
	serialData += "{";
}

void appendSerialData(String x) {
	if (strcmp(serialData.c_str(), "{") != 0) {
		serialData += ",";
	}
	serialData += x;
//serialData = "";
}

void endSerialData() {
	serialData += "}";
}

#endif
