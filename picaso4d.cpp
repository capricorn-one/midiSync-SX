#include "picaso4d.h"
#include "picaso4dConstants.h"
#include "audioPlayer.h"

#define DISPLAY_TIMEOUT		250
#define ORIENTATION			LANDSCAPE_R

#define DISPLAY_SERIAL		Serial2
#define BAUD_RATE			200000
#define DISPLAY_RESET_PIN	24


elapsedMillis timeout;

uint16_t picaso4d::_videoHandles[PICASO_NUM_VIDEOS];
uint16_t picaso4d::_fontHandles[PICASO_NUM_FONTS];

picaso4d::picaso4d() {}

void picaso4d::begin() {

	DISPLAY_SERIAL.begin(BAUD_RATE);

	CORE_PIN9_CONFIG = PORT_PCR_MUX(6); //Taken from Audio library, needed to preserve AUDIO library capability on pin 9
	CORE_PIN26_CONFIG = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(3);

	CORE_PIN10_CONFIG = 0;
	CORE_PIN31_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);

	pinMode(DISPLAY_RESET_PIN, OUTPUT);

	digitalWrite(DISPLAY_RESET_PIN, HIGH);
	delay(100);
	digitalWrite(DISPLAY_RESET_PIN, LOW);

	delay(4000);

	gfx_ScreenMode(ORIENTATION);
	_displayWidth = gfx_Get(X_MAX);
	_displayHeight = gfx_Get(Y_MAX);
}

uint16_t picaso4d::charwidth(char c) {
	writeWord(0x001E);
	DISPLAY_SERIAL.write((uint8_t)c);
	return getACKresponse();
}

uint16_t picaso4d::charheight(char c) {
	writeWord(0x001D);
	DISPLAY_SERIAL.write((uint8_t)c);
	return getACKresponse();
}

uint16_t picaso4d::strwidth(const char * str) {
	uint16_t width = charwidth(*str++);
	while (*str) {
		width += charwidth(*str++);
	}
	return width;
}

uint16_t picaso4d::strheight(const char * str) {
	return charheight(*str);
}

uint16_t picaso4d::integerwidth(int n) {
	char buffer[16];
	itoa(n, buffer, 10);
	return strwidth(buffer);
}

uint16_t picaso4d::gfx_BGcolour(uint16_t  color) {
	writeWord(0xFFA4);
	writeWord(color);
	return getACKresponse();
}

void picaso4d::gfx_Button(uint16_t  state, uint16_t  x, uint16_t  y, uint16_t  buttonColour, uint16_t  txtColour, uint16_t  font, uint16_t  txtWidth, uint16_t  txtHeight, char *   text) {
	writeWord(0x0011);
	writeWord(state);
	writeWord(x);
	writeWord(y);
	writeWord(buttonColour);
	writeWord(txtColour);
	writeWord(font);
	writeWord(txtWidth);
	writeWord(txtHeight);
	DISPLAY_SERIAL.print(text);
	getACK();
}

void picaso4d::gfx_ChangeColour(uint16_t  OldColor, uint16_t  NewColor) {
	writeWord(0xFFB4);
	writeWord(OldColor);
	writeWord(NewColor);
	getACK();
}

void picaso4d::gfx_Circle(uint16_t  x, uint16_t  y, uint16_t  rad, uint16_t  color) {
	writeWord(0xFFC3);
	writeWord(x);
	writeWord(y);
	writeWord(rad);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_CircleFilled(uint16_t  x, uint16_t  y, uint16_t  rad, uint16_t  color) {
	writeWord(0xFFC2);
	writeWord(x);
	writeWord(y);
	writeWord(rad);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_Clipping(uint16_t  OnOff) {
	writeWord(0xFFA2);
	writeWord(OnOff);
	getACK();
}

void picaso4d::gfx_ClipWindow(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2) {
	writeWord(0xFFB5);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	getACK();
}

void picaso4d::gfx_Cls() {
	writeWord(0xFFCD);
	getACK();
}

uint16_t picaso4d::gfx_Contrast(uint16_t  Contrast) {
	writeWord(0xFF9C);
	writeWord(Contrast);
	return getACKresponse();
}

void picaso4d::gfx_Ellipse(uint16_t  x, uint16_t  y, uint16_t  xrad, uint16_t  yrad, uint16_t  color) {
	writeWord(0xFFB2);
	writeWord(x);
	writeWord(y);
	writeWord(xrad);
	writeWord(yrad);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_EllipseFilled(uint16_t  x, uint16_t  y, uint16_t  xrad, uint16_t  yrad, uint16_t  color) {
	writeWord(0xFFB1);
	writeWord(x);
	writeWord(y);
	writeWord(xrad);
	writeWord(yrad);
	writeWord(color);
	getACK();
}

uint16_t picaso4d::gfx_Get(uint16_t parameter) {
	writeWord(0xFFA6);
	writeWord(parameter);
	return getACKresponse();
}

uint16_t picaso4d::gfx_GetPixel(uint16_t  x, uint16_t  y) {
	writeWord(0xFFC0);
	writeWord(x);
	writeWord(y);
	return getACKresponse();
}

void picaso4d::gfx_Line(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color) {
	writeWord(0xFFC8);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	writeWord(color);
	getACK();
}

uint16_t picaso4d::gfx_LinePattern(uint16_t  Pattern) {
	writeWord(0xFF9B);
	writeWord(Pattern);
	return getACKresponse();

}

void picaso4d::gfx_LineTo(uint16_t  x, uint16_t  y) {
	writeWord(0xFFCA);
	writeWord(x);
	writeWord(y);
	getACK();
}

void picaso4d::gfx_MoveTo(uint16_t  x, uint16_t  y) {
	writeWord(0xFFCC);
	writeWord(x);
	writeWord(y);
	getACK();
}

void picaso4d::gfx_Orbit(uint16_t  angle, uint16_t  distance, uint16_t *  xdest, uint16_t *  ydest) {
	writeWord(0x0012);
	writeWord(angle);
	writeWord(distance);
	getACK();
	timeout = 0;
	while ( timeout < 1000 ) {
		if (DISPLAY_SERIAL.available() > 3) {
			*xdest = DISPLAY_SERIAL.read() << 8;
			*xdest |= DISPLAY_SERIAL.read();
			*ydest = DISPLAY_SERIAL.read() << 8;
			*ydest |= DISPLAY_SERIAL.read();
			return;
		}
	}
}

uint16_t picaso4d::gfx_OutlineColour(uint16_t  color) {
	writeWord(0xFF9D);
	writeWord(color);
	return getACKresponse();
}

void picaso4d::gfx_Panel(uint16_t  state, uint16_t  x, uint16_t  y, uint16_t  width, uint16_t  height, uint16_t  color) {
	writeWord(0xFFAF);
	writeWord(state);
	writeWord(x);
	writeWord(y);
	writeWord(width);
	writeWord(height);
	writeWord(color);
	getACK();
}

//incomplete
void picaso4d::gfx_Polygon(uint16_t  n, uint16_t *  xvalues, uint16_t *  yvalues, uint16_t  color) {
	writeWord(0x0013);
	writeWord(n);
	for (int i = 0; i < n; i++)
		writeWord(xvalues[i]);
	for (int i = 0; i < n; i++)
		writeWord(yvalues[i]);
	writeWord(color);
	getACK();
}


void picaso4d::gfx_PolygonFilled(uint16_t  n, uint16_t *  xvalues, uint16_t *  yvalues, uint16_t  color) {
	writeWord(0x0013);
	writeWord(n);
	for (int i = 0; i < n; i++)
		writeWord(xvalues[i]);
	for (int i = 0; i < n; i++)
		writeWord(yvalues[i]);
	writeWord(color);
	getACK();
}


void picaso4d::gfx_Polyline(uint16_t  n, uint16_t *  xvalues, uint16_t *  yvalues, uint16_t  color) {
	writeWord(0x0015);
	writeWord(n);
	for (int i = 0; i < n; i++)
		writeWord(xvalues[i]);
	for (int i = 0; i < n; i++)
		writeWord(yvalues[i]);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_PutPixel(uint16_t  x, uint16_t  y, uint16_t  color) {
	writeWord(0xFFC1);
	writeWord(x);
	writeWord(y);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_Rectangle(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color) {
	writeWord(0xFFC5);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_RectangleFilled(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color) {
	writeWord(0xFFC4);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_ScreenCopyPaste(uint16_t  xs, uint16_t  ys, uint16_t  xd, uint16_t  yd, uint16_t  width, uint16_t  height) {
	writeWord(0xFFAD);
	writeWord(xs);
	writeWord(ys);
	writeWord(xd);
	writeWord(yd);
	writeWord(width);
	writeWord(height);
	getACK();
}

uint16_t picaso4d::gfx_ScreenMode(uint16_t mode) {
	writeWord(0xFF9E);
	writeWord(mode);
	return getACKresponse();
}

void picaso4d::gfx_Set(uint16_t  func, uint16_t  value) {
	writeWord(0xFFCE);
	writeWord(func);
	writeWord(value);
	getACK();
}

void picaso4d::gfx_SetClipRegion() {
	writeWord(0xFFB3);
	getACK();
}

void picaso4d::gfx_Slider(uint16_t  mode, uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color, uint16_t  scale, uint16_t  value) {
	writeWord(0xFFAE);
	writeWord(mode);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	writeWord(color);
	writeWord(scale);
	writeWord(value);
	getACK();
}

uint16_t picaso4d::gfx_Transparency(uint16_t  OnOff) {
	writeWord(0xFFA0);
	writeWord(OnOff);
	return getACKresponse();
}

uint16_t picaso4d::gfx_TransparentColour(uint16_t  color) {
	writeWord(0xFFA1);
	writeWord(color);
	return getACKresponse();
}

void picaso4d::gfx_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color) {
	writeWord(0xFFBF);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	writeWord(x3);
	writeWord(y3);
	writeWord(color);
	getACK();
}

void picaso4d::gfx_TriangleFilled(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color) {
	writeWord(0xFFA9);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	writeWord(x3);
	writeWord(y3);
	writeWord(color);
	getACK();
}

void picaso4d::touch_DetectRegion(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2) {
	writeWord(0xFF39);
	writeWord(x1);
	writeWord(y1);
	writeWord(x2);
	writeWord(y2);
	getACK();
}

uint16_t picaso4d::touch_Get(uint16_t mode) {
	writeWord(0xFF37);
	writeWord(mode);
	return getACKresponse();
}

void picaso4d::touch_Set(uint16_t  mode) {
	writeWord(0xFF38);
	writeWord(mode);
	getACK();
}

uint16_t picaso4d::txt_Attributes(uint16_t attribs) {
	writeWord(0xFFDA);
	writeWord(attribs);
	return getACKresponse();
}

uint16_t picaso4d::txt_BGcolor(uint16_t color) {
	writeWord(0xFFE6);
	writeWord(color);
	return getACKresponse();
}

uint16_t picaso4d::txt_Bold(uint16_t bold) {
	writeWord(0xFFDE);
	writeWord(bold);
	return getACKresponse();
}

uint16_t picaso4d::txt_FGcolor(uint16_t color) {
	writeWord(0xFFE7);
	writeWord(color);
	return getACKresponse();
}

uint16_t picaso4d::txt_FontID(uint16_t fontNumber) {
	writeWord(0xFFE5);
	writeWord(fontNumber);
	return getACKresponse();
}

uint16_t picaso4d::txt_FontSD(uint8_t fontNumber) {
	if (fontNumber >= PICASO_NUM_FONTS)
		return 0;
	writeWord(0xFFE5);
	writeWord(_fontHandles[fontNumber]);
	return getACKresponse();
}

uint16_t picaso4d::txt_Height(uint16_t multiplier) {
	writeWord(0xFFE3);
	writeWord(multiplier);
	return getACKresponse();
}

uint16_t picaso4d::txt_Inverse(uint16_t inverse) {
	writeWord(0xFFDC);
	writeWord(inverse);
	return getACKresponse();
}

uint16_t picaso4d::txt_Italic(uint16_t italic) {
	writeWord(0xFFDD);
	writeWord(italic);
	return getACKresponse();
}

void picaso4d::txt_MoveCursor(uint16_t column, uint16_t line) {
	writeWord(0xFFE9);
	writeWord(line);
	writeWord(column);
	getACK();
}

uint16_t picaso4d::txt_Opacity(uint16_t transparentOpaque) {
	writeWord(0xFFDF);
	writeWord(transparentOpaque);
	return getACKresponse();
}

uint16_t picaso4d::txt_Underline(uint16_t underline) {
	writeWord(0xFFDB);
	writeWord(underline);
	return getACKresponse();
}

uint16_t picaso4d::txt_Width(uint16_t multiplier) {
	writeWord(0xFFE4);
	writeWord(multiplier);
	return getACKresponse();
}

uint16_t picaso4d::txt_Wrap(uint16_t position) {
	writeWord(0xFFD9);
	writeWord(position);
	return getACKresponse();
}

uint16_t picaso4d::txt_Xgap(uint16_t pixels) {
	writeWord(0xFFE2);
	writeWord(pixels);
	return getACKresponse();
}

uint16_t picaso4d::txt_Ygap(uint16_t pixels) {
	writeWord(0xFFE1);
	writeWord(pixels);
	return getACKresponse();
}

uint16_t picaso4d::fileLoadImageControl(const char * datFilename, const char * gciFilename, uint16_t mode) {
	writeWord(0x0009);
	DISPLAY_SERIAL.print(datFilename);
	DISPLAY_SERIAL.write(0x00);		//send null terminator
	DISPLAY_SERIAL.print(gciFilename);
	DISPLAY_SERIAL.write(0x00);		//send null terminator (print does not include the null, uses strlen() to calculate num chars)
	writeWord(mode);
	return getACKresponse();
}

uint16_t picaso4d::fileMount() {
	writeWord(0xFF03);
	return getACKresponse();
}

uint16_t picaso4d::img_SetWord(uint16_t handle, uint16_t index, uint16_t offset, uint16_t value) {
	writeWord(0xFF49);
	writeWord(handle);
	writeWord(index);
	writeWord(offset);
	writeWord(value);
	return getACKresponse();
}

uint16_t picaso4d::img_Show(uint16_t handle, uint16_t index) {
	writeWord(0xFF47);
	writeWord(handle);
	writeWord(index);
	return getACKresponse();
}

void picaso4d::video_ShowFrame(uint8_t videoNumber, int frame) {
	if (videoNumber >= PICASO_NUM_VIDEOS)
		return;
	img_SetWord(_videoHandles[videoNumber], 0, 9, frame);
	img_Show(_videoHandles[videoNumber], 0);
}

//Custom function for loading application specific fonts
void picaso4d::loadSdFonts() {
	_fontHandles[AVENIR_24] = fileLoadImageControl("midiSync.da1", "midiSync.gc1", 1);
	_fontHandles[AVENIR_36] = fileLoadImageControl("midiSync.da2", "midiSync.gc2", 1);
	_fontHandles[AVENIR_72] = fileLoadImageControl("midiSync.da3", "midiSync.gc3", 1);
	_fontHandles[AVENIR_104] = fileLoadImageControl("midiSync.da4", "midiSync.gc4", 1);
}

//Custom function for loading application specific videos
void picaso4d::loadSdVideos() {
	_videoHandles[0] = fileLoadImageControl("midiSync.dat", "midiSync.gci", 1);
}

inline void picaso4d::writeWord(uint16_t w) {
	DISPLAY_SERIAL.write((uint8_t)(w >> 8));
	DISPLAY_SERIAL.write((uint8_t)(w & 0xFF));
}

inline uint8_t picaso4d::getACK() {
	timeout = 0;
	while (timeout < DISPLAY_TIMEOUT) {
		if (DISPLAY_SERIAL.available()) {
			if (DISPLAY_SERIAL.read() == 0x06)
				return 0;
			else
				return 1;
		}
	}
	return 0;
}

inline uint16_t picaso4d::getACKresponse() {
	uint16_t response = -1;
	getACK();
	timeout = 0;
	while ( timeout < DISPLAY_TIMEOUT) {
		if ( DISPLAY_SERIAL.available() > 1 ) {
			response = DISPLAY_SERIAL.read() << 8;
			response |= DISPLAY_SERIAL.read();
			return response;
		}
	}
	if (DISPLAY_SERIAL.available()) {
		Serial.print("Timeout ACKresponse: 0x");
		Serial.println(DISPLAY_SERIAL.read(), HEX);
	}
	else
		Serial.println("Timeout ACKresponse");
	return response;
}

size_t picaso4d::write(uint8_t b) {
	writeWord(0xFFFE);
	DISPLAY_SERIAL.write(0x00);
	DISPLAY_SERIAL.write(b);
	getACK();
	return 1;
}

size_t picaso4d::write(const uint8_t *buffer, size_t size) {
	uint8_t sizeCheck = 0;
	if (size == 1)
		return write(buffer[0]);

	writeWord(0x0018);
	while( sizeCheck < size ) {
		DISPLAY_SERIAL.write(*buffer++);
		sizeCheck++;
	}
	DISPLAY_SERIAL.write('\0');
	getACKresponse();
	return size;
}

picaso4d PICASO;