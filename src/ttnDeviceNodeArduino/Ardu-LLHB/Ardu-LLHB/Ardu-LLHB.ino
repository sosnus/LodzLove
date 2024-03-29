/*******************************************************************************
 * Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman
 *
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * This example sends a valid LoRaWAN packet with payload "Hello,
 * world!", using frequency and encryption settings matching those of
 * the The Things Network.
 *
 * This uses ABP (Activation-by-personalisation), where a DevAddr and
 * Session keys are preconfigured (unlike OTAA, where a DevEUI and
 * application key is configured, while the DevAddr and session keys are
 * assigned/generated in the over-the-air-activation procedure).
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in
 * g1, 0.1% in g2), but not the TTN fair usage policy (which is probably
 * violated by this sketch when left running for longer)!
 *
 * To use this sketch, first register your application and device with
 * the things network, to set or generate a DevAddr, NwkSKey and
 * AppSKey. Each device should have their own unique values for these
 * fields.
 *
 * Do not forget to define the radio type correctly in config.h.
 *
 *******************************************************************************/

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

//#include <Adafruit_SSD1306.h>

#define NODE_SERIAL_NUMBER  7
//                  SELECT 2,5,7
// #define NODE_SERIAL_NUMBER  5
// #define NODE_SERIAL_NUMBER  2

#include <CayenneLPP.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>



// information about the LCD connection
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008,7,6,5,4,3,2,1,HIGH);


CayenneLPP lpp(51);
//Adafruit_SSD1306 display(NULL);


int cnt=0;
float adc0=11, adc2=11, adc3=11;


#if NODE_SERIAL_NUMBER == 5
const int id = 5;
static const PROGMEM u1_t NWKSKEY[16] = { 0x0C, 0xCF, 0x62, 0x0C, 0x97, 0xDE, 0x11, 0x21, 0x9E, 0xAA, 0xF7, 0x36, 0x36, 0x33, 0xC1, 0x04 };
static const u1_t PROGMEM APPSKEY[16] = { 0x01, 0xBF, 0x6F, 0x8A, 0xDA, 0x95, 0xF1, 0x27, 0xD4, 0xF5, 0xBC, 0x73, 0x65, 0x8C, 0xE9, 0x98 };
static const u4_t DEVADDR = 0x26011F87;
#endif

#if NODE_SERIAL_NUMBER == 2
const int id = 2;
static const PROGMEM u1_t NWKSKEY[16] = { 0xB6, 0x8E, 0x3A, 0x60, 0x3D, 0x85, 0xB4, 0x4A, 0xA5, 0x0D, 0x62, 0x02, 0xD7, 0xE8, 0xCA, 0x07 };
static const u1_t PROGMEM APPSKEY[16] = { 0xF3, 0x7B, 0x08, 0x4F, 0xE5, 0x31, 0xCD, 0x51, 0x23, 0x9F, 0xCE, 0x0C, 0xE4, 0x53, 0x55, 0x54 };
static const u4_t DEVADDR = 0x260118C9;
#endif

#if NODE_SERIAL_NUMBER == 7
const int id = 7;
static const PROGMEM u1_t NWKSKEY[16] = { 0x76, 0x49, 0x5B, 0x2D, 0xE4, 0x1F, 0x22, 0x37, 0xF3, 0x72, 0x74, 0x0E, 0xC4, 0x70, 0xF5, 0xBC };
static const u1_t PROGMEM APPSKEY[16] = { 0xD4, 0x2D, 0xAA, 0x96, 0xE0, 0x86, 0xF1, 0x72, 0x64, 0x32, 0xDB, 0xD9, 0xA8, 0x12, 0x3C, 0x90 };
static const u4_t DEVADDR = 0x26011ACD;
#endif

// LoRaWAN NwkSKey, network session key
// This is the default Semtech key, which is used by the early prototype TTN
// network.
//{ 0x39, 0xF7, 0x7E, 0xB7, 0x24, 0xC7, 0xEE, 0xB7, 0x80, 0x6B, 0xBF, 0xF2, 0xD2, 0x09, 0x08, 0xD4 };
//{ 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

// LoRaWAN AppSKey, application session key
// This is the default Semtech key, which is used by the early prototype TTN
// network.
//{ 0x39, 0x5F, 0x43, 0x2F, 0x8B, 0x54, 0xBB, 0x36, 0xF6, 0xA1, 0x1B, 0x01, 0xFC, 0x75, 0xF5, 0x47 };
//{ 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

// LoRaWAN end-device address (DevAddr)
//03FF0001 ; // <-- Change this address for every node!

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

// uint8_t lcd_content [4][30] = {{"CNT="},{"A0"},{"A2"},{"A3"}};


static uint8_t mydata[] = "Hello, world! LLHB";
static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 10;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 10,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 5,
    .dio = {2, 3, LMIC_UNUSED_PIN},
};


void getAdc()
{
    // 0 microphone
    // 2 - temp
    // 3 - proxim
    adc0 = analogRead(A0);
    adc2 = analogRead(A2) * 0.125 - 22.0; //analogRead(A2);
    adc3 = analogRead(A3) / 1023.0 * 100; //analogRead(A3);
    //convert to decimal values

    cnt++;

    
#if NODE_SERIAL_NUMBER == 7
adc0 = random(0, 1400);
adc0 /= 100;
adc2 = random(150,300);
adc2 /= 10;
adc3 = random(0, 100);
#endif
}

void setLcd()
{
   lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("i=");
 lcd.print(cnt);
  lcd.setCursor(7, 0);
 lcd.print("m=");
 lcd.print(adc0);
  lcd.setCursor(0, 1);
 lcd.print("t=");
 lcd.print(adc2);
  lcd.setCursor(7, 1);
 lcd.print("p=");
 lcd.print(adc3);

   lcd.setCursor(15, 0);
 lcd.print(id);
   lcd.setCursor(15, 1);
 lcd.print("^");
 
}

void prepareMsg()
{
    getAdc();
    setLcd();
        lpp.reset();
lpp.addAnalogInput(1, id); //ID
lpp.addAnalogInput(2, adc0); // A0, Mic
lpp.addAnalogInput(3, adc2); // A2, Temperature
lpp.addAnalogInput(4, adc3); // A3, Proxim
// lpp.addGPS(2, 51.76873, 19.45699, 2);
// lpp.addAnalogInput(4, 2.721);
// lpp.addAnalogInput(5, 1.721);

lpp.copy(mydata);
}


void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
            }
            // Schedule next transmission
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
         default:
            Serial.println(F("Unknown event"));
            break;
    }
}

void do_send(osjob_t* j){
        Serial.println(F("prepareMsg()..."));
        //prepareMsg (Convert ADC measurements to LPP message"));
    prepareMsg();
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
        Serial.println(F("Packet queued"));
    }
    // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
    lcd.begin(16, 2);
 lcd.setCursor(0, 0);
 lcd.print("START...");
 // set the cursor t

//      display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
//  delay(500);
//  display.clearDisplay();
//   display.setTextColor(WHITE);
//  display.setCursor(0,0);

//  display.println("TEST LINE");
//  display.display();
    Serial.begin(115200);
    Serial.println(F("Starting"));

    #ifdef VCC_ENABLE
    // For Pinoccio Scout boards
    pinMode(VCC_ENABLE, OUTPUT);
    digitalWrite(VCC_ENABLE, HIGH);
    delay(1000);
    #endif

    // LMIC init
    os_init();
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    // Set static session parameters. Instead of dynamically establishing a session
    // by joining the network, precomputed session parameters are be provided.
    #ifdef PROGMEM
    // On AVR, these values are stored in flash and only copied to RAM
    // once. Copy them to a temporary buffer here, LMIC_setSession will
    // copy them into a buffer of its own again.
    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
    #else
    // If not running an AVR with PROGMEM, just use the arrays directly
    LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
    #endif

    #if defined(CFG_eu868)
    // Set up the channels used by the Things Network, which corresponds
    // to the defaults of most gateways. Without this, only three base
    // channels from the LoRaWAN specification are used, which certainly
    // works, so it is good for debugging, but can overload those
    // frequencies, so be sure to configure the full frequency range of
    // your network here (unless your network autoconfigures them).
    // Setting up channels should happen after LMIC_setSession, as that
    // configures the minimal channel set.
    // NA-US channels 0-71 are configured automatically
    LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
    LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
    // TTN defines an additional channel at 869.525Mhz using SF9 for class B
    // devices' ping slots. LMIC does not have an easy way to define set this
    // frequency and support for class B is spotty and untested, so this
    // frequency is not configured here.
    #elif defined(CFG_us915)
    // NA-US channels 0-71 are configured automatically
    // but only one group of 8 should (a subband) should be active
    // TTN recommends the second sub band, 1 in a zero based count.
    // https://github.com/TheThingsNetwork/gateway-conf/blob/master/US-global_conf.json
    LMIC_selectSubBand(1);
    #endif

    // Disable link check validation
    LMIC_setLinkCheckMode(0);

    // TTN uses SF9 for its RX2 window.
    LMIC.dn2Dr = DR_SF9;

    // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
    LMIC_setDrTxpow(DR_SF7,14);

    // Start job
    do_send(&sendjob);
 //   set_lcd();
}

void loop() {
    os_runloop_once();
}


