/** 
 * Art-Net Matrix
 *
 * Control a MAX7219 LED Matrix display over Art-Net DMX with a Wifi ESP8266/Arduino
 * 
 * Author: Owen McAteer
 * Handle: @motus_art
 * Web: www.motus.art
 * Git: https://github.com/owenmcateer/Art-Net_Matrix
 * 
 * Required libraries:
 * 
 * LedControl
 * ---
 * An Arduino library for the MAX7219 and MAX7221
 * Author: Eberhard Fahle
 * https://wayoda.github.io/LedControl/
 * https://github.com/wayoda/LedControl
 * 
 * ArtNet
 * ---
 * Art-Net Sender/Receiver for Arduino (Ethernet, WiFi)
 * Author: Hideaki Tai
 * https://github.com/hideakitai/ArtNet
 */
#include <LedControl.h>
#include <ArtnetWiFi.h>

// Matrix settings
int BRIGHTNESS = 1;
int DIN = D6;
int CS = D8;
int CLK = D5;
LedControl lc = LedControl(DIN, CLK, CS, 4);
int WIDHT = 32;
int HEIGHT = 8;
int THRESHOLD = 127; // 0-255

// WiFi settings
const char* ssid = "";
const char* pwd = "";
const IPAddress ip(192, 168, 1, 101);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet_mask(255, 255, 255, 0);

// Art-Net settings
ArtnetWiFiReceiver artnet;
uint16_t universe = 8;  // 0 - 32767
uint8_t net = 0;        // 0 - 127
uint8_t subnet = 0;     // 0 - 15


// Setup
void  setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet_mask);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());

  // Start Art-Net
  artnet.begin();
  artnet.subscribeArtDmxUniverse(net, subnet, universe, callback);

  // Setup Matrix
  for(int i = 0; i < 4; i++) {
    lc.shutdown(i, false);
    lc.setScanLimit(i, 7);
    lc.setIntensity(i, BRIGHTNESS);
    lc.clearDisplay(i);
  }
}

// Main loop
void loop() {
  // Listen for Art-Net data
  artnet.parse();
}

// Output ArtNet data to matrix
void callback(const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote) {
  for (size_t i = 0; i < WIDHT * HEIGHT; ++i) {
    int panelIndex = (i % WIDHT) / HEIGHT;
    int rowIndex = i / WIDHT;
    int colIndex = i % HEIGHT;
    boolean ledState = data[i] > THRESHOLD;

    // Send data to matrix
    lc.setLed(panelIndex, 7 - rowIndex, 7 - colIndex, ledState);
  }
}
