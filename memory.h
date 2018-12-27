//This intensly relies on the EEPROM Library


int lookup(int color){
    for (int i = 0; i < 142; i++){
        if (color == fullColourArray[i]){
            return i;
        }
    }
    return -1;
}



int charToChipStorage(char value){
    return int(value);
}

char charFromStorage(int value){
    return char(value);
}

void getName(){

    String name = "";
    for (int i = 0; i < 8; i++){
        if (testSave[i] == 0){
            continue;
        }

        char letter = charFromStorage(testSave[i]);
        
        name += letter;
    }
    Serial.println(name);
}

void getLocation(){

    String location = "";

    for (int i = 12; i < 24; i++){
        if (testSave[i] == 0){
            continue;
        }

        char letter = charFromStorage(testSave[i]);
        
        location += letter;
    }
    Serial.println(location);
}

void getSSID(){

    String ssid = "";

    for (int i = 32; i < 52; i++){
        if (testSave[i] == 0){
            continue;
        }

        char letter = charFromStorage(testSave[i]);
        
        ssid += letter;
    }
    Serial.println(ssid);
}

//Dec-Q9K-Fkz-Kny

int fetchData(){
    //Mode
    //Previous
    //Previous
    int prev = testSave[8];
    // //CURRENT
    // chipStorage[9];
    // //BRIGHTNESS
    // chipStorage[10];
    // //COLOUR
    // chipStorage[11];

    // //RELAYS
    // for (int i = 24; i < 32; i++){
    //     chipStorage[i] = 1;
    // }

    // //SETS
    // for (int i = 198; i < 325; i++){
    //     chipStorage[i] = 12;
    // }
    return prev;
}

int sendData(int mode, int color, int brightness, int previous){

    //Mode
    //Previous
    chipStorage[8] = previous;
    //CURRENT
    chipStorage[9] = mode;
    //BRIGHTNESS
    chipStorage[10] = brightness;
    //COLOUR
    chipStorage[11] = lookup(color);

    //RELAYS
    for (int i = 24; i < 32; i++){
        chipStorage[i] = 1;
    }

    //SETS
    for (int i = 198; i < 325; i++){
        chipStorage[i] = 12;
    }

}

void printChipStorage(){
    for (int i = 0; i < 512 ; i++){
        // Serial.print(i);
        // Serial.print(" - ");
        Serial.println(chipStorage[i]);
    }
}


void printChip(){
    for (int i = 0; i < 512 ; i++){
        if (testSave[i] == 0){
            Serial.print(i);
            Serial.println(" - ");
            continue;
        }
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(charFromStorage(testSave[i]));
    }
}

void oneTime(){
    //SSID
    for (int i = 32; i < (32 + WIFI_SSID.length()); i++){
        chipStorage[i] = charToChipStorage((char) WIFI_SSID[i-32]);
    }

    //PASSWORD
    for (int i = 52; i < (52 + WIFI_PASSWORD.length()); i++){
        chipStorage[i] = charToChipStorage((char) WIFI_PASSWORD[i-52]);
    }

    //NAME
    for (int i = 0; i < 8; i++){
        chipStorage[i] = charToChipStorage((char) NAME[i]);
    }

    //LOCATION
    for (int i = 12; i < (12 + LOCATION.length()); i++){
        chipStorage[i] = charToChipStorage((char) LOCATION[i-12]);
    }
}