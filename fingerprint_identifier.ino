#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF


#define __CS 10
#define __DC 9
static const uint8_t icon [] PROGMEM = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x3f,0xc0,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0x7,0xff,0xfe,0x0,0x0,0x0,
0x0,0x0,0x1f,0xc0,0x7f,0x80,0x0,0x0,
0x0,0x0,0x3e,0x0,0x7,0xc0,0x0,0x0,
0x0,0x0,0x7c,0x0,0x3,0xe0,0x0,0x0,
0x0,0x0,0xfd,0xff,0x81,0xf0,0x0,0x0,
0x0,0x0,0xff,0xff,0xe0,0xf0,0x0,0x0,
0x0,0x1,0xff,0xff,0xf8,0x78,0x0,0x0,
0x0,0x1,0xff,0x80,0x7c,0x38,0x0,0x0,
0x0,0x3,0xfc,0x0,0xe,0x3c,0x0,0x0,
0x0,0x3,0xf0,0x0,0x7,0x1c,0x0,0x0,
0x0,0x7,0xc0,0x7f,0x83,0x8e,0x0,0x0,
0x0,0x7,0x83,0xff,0xe0,0xe,0x0,0x0,
0x0,0x7,0xf,0xff,0xf8,0xf,0x0,0x0,
0x0,0x6,0x1f,0x80,0xfc,0x7,0x0,0x0,
0x0,0x4,0x7e,0x0,0x3f,0x7,0x0,0x0,
0x0,0x0,0xf8,0x0,0xf,0x7,0x0,0x0,
0x0,0x0,0xf0,0x3e,0x7,0x87,0x0,0x0,
0x0,0x1,0xe1,0xff,0x83,0x83,0x80,0x0,
0x0,0x3,0xc3,0xff,0xc3,0xc3,0x80,0x0,
0x0,0x3,0xc7,0xc3,0xe1,0xc3,0x80,0x0,
0x0,0x3,0x8f,0x0,0xf1,0xe3,0x80,0x0,
0x0,0x7,0x1e,0x0,0x78,0xe3,0x80,0x0,
0x0,0x7,0x1e,0x3c,0x38,0xe3,0x80,0x0,
0x0,0x7,0x1c,0x7e,0x38,0xe3,0x80,0x0,
0x0,0xf,0x1c,0x7f,0x38,0xe3,0x80,0x0,
0x0,0xe,0x3c,0xf7,0x38,0x71,0x80,0x0,
0x0,0xe,0x38,0xe7,0x38,0x71,0xc0,0x0,
0x0,0xe,0x38,0xe7,0x38,0x71,0xc0,0x0,
0x0,0xe,0x38,0xe7,0x38,0x73,0xc0,0x0,
0x0,0xe,0x38,0xe3,0x98,0xe3,0xc0,0x0,
0x0,0xe,0x38,0xe3,0xb8,0xe3,0x80,0x0,
0x0,0x0,0x38,0xe3,0xf8,0xe3,0x80,0x0,
0x0,0x0,0x38,0xe3,0xf8,0xe3,0x80,0x0,
0x0,0x0,0x3c,0xf1,0xf1,0xe3,0x80,0x0,
0x0,0x6,0x1c,0x70,0x1,0xc7,0x80,0x0,
0x0,0xe,0x1c,0x78,0x3,0xc7,0x80,0x0,
0x0,0xf,0x1c,0x3e,0x7,0x87,0x0,0x0,
0x0,0xf,0x1e,0x3f,0xff,0x8f,0x0,0x0,
0x0,0xf,0x1e,0x1f,0xff,0x1f,0x0,0x0,
0x0,0xf,0xf,0x7,0xfc,0x3e,0x0,0x0,
0x0,0x7,0x87,0x80,0x0,0x7c,0x0,0x0,
0x0,0x7,0x87,0xe0,0x0,0xfc,0x0,0x0,
0x0,0x3,0xc3,0xf8,0x7,0xf8,0x0,0x0,
0x0,0x3,0xe1,0xff,0xff,0xe1,0x0,0x0,
0x0,0x1,0xe0,0x7f,0xff,0x83,0x0,0x0,
0x0,0x1,0xf8,0xf,0xfe,0x7,0x0,0x0,
0x0,0x0,0xfc,0x0,0x0,0xe,0x0,0x0,
0x0,0x0,0x3f,0x0,0x0,0x3c,0x0,0x0,
0x0,0x0,0x1f,0xe0,0x1,0xf8,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,
0x0,0x0,0x1,0xff,0xff,0xc0,0x0,0x0,
0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

TFT_ILI9163C display = TFT_ILI9163C(__CS,8, __DC);
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int fingerprintID = 0;

void setup(void)
{
	startFingerprintSensor();
	display.begin();
	displayLockScreen();
}

void loop()
{
	fingerprintID = getFingerprintID();
	delay(50);
	if(fingerprintID == 1)
	{
		display.drawBitmap(30,35,icon,60,60,GREEN);
		delay(2000);
		displayUnlockedScreen();
		displayEesaar();
	}

	if(fingerprintID == 2)
	{
		display.drawBitmap(30,35,icon,60,60,GREEN);
		delay(2000);
		displayUnlockedScreen();
		displayAakif();
		delay(5000);
		display.fillScreen(BLACK);
		displayLockScreen();
	}
}

void startFingerprintSensor()
{
	Serial.begin(9600);
	finger.begin(57600);

	if (finger.verifyPassword())
	{
		Serial.println("Found fingerprint scanner!");
	}
	else
	{
		Serial.println("Did not find fingerprint scanner.");
	}
	Serial.println("Waiting for valid finger");
}



void displayUnlockedScreen()
{
	display.fillScreen(BLACK);
	display.drawRect (128,128,128,128, WHITE);

	display.setCursor(18,10);
	display.setTextColor(GREEN);
	display.setTextSize(2);
	display.print("UNLOCKED");

	display.setCursor(20,50);
	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.print("WELCOME");
}
void displayEesaar()
{
	display.setCursor(5,75);
	display.setTextColor(CYAN);
	display.setTextSize(1);
	display.print("Hello King Wild");
}

void displayAakif()
{
	display.setCursor(25,75);
	display.setTextColor(GREEN);
	display.setTextSize(1);
	display.print("Hello Aakify");
}
void displayLockScreen()
{
	display.drawRect(0, 0, 48, 48,WHITE);
	display.setCursor(30,10);
	display.setTextColor(RED);
	display.setTextSize(2);
	display.print("LOCKED");

	display.setCursor(10,100);
	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.print("Waiting for valid \nfingerprint.");

	display.drawBitmap(30,35,icon,60,60,WHITE);
}

int getFingerprintID()
{
	uint8_t p = finger.getImage();
	if (p != FINGERPRINT_OK) return -1;

	p = finger.image2Tz();
	if (p != FINGERPRINT_OK) return -1;

	p = finger.fingerFastSearch();
	if (p != FINGERPRINT_OK) return -1;

	Serial.print("Found ID # ");
	Serial.print(finger.fingerID);
	Serial.print(" with confidence of ");
	Serial.print(finger.confidence);

	return finger.fingerID;
}
