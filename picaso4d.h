#ifndef _PICASO_4D_H
#define _PICASO_4D_H

#include <Arduino.h>
#include "picaso4dConstants.h"

#define BACKGROUND_COLOR		BLACK
#define THEME_COLOR				WHITE
#define THEME_COLOR_SECONDARY	AQUAMARINE

#define AVENIR_24		0
#define AVENIR_36		1
#define AVENIR_72		2
#define AVENIR_104		3

#define PICASO_NUM_VIDEOS		1
#define PICASO_NUM_FONTS		4

class picaso4d : public Print
{
public:
	picaso4d();

	void begin();

	uint16_t charwidth(char c);
	uint16_t charheight(char c);
	uint16_t strwidth(const char * c);
	uint16_t strheight(const char *c);
	uint16_t integerwidth(int n);

	uint16_t gfx_BGcolour(uint16_t  Color);
	void gfx_Button(uint16_t  state, uint16_t  x, uint16_t  y, uint16_t  buttonColour, uint16_t  txtColour, uint16_t  font, uint16_t  txtWidth, uint16_t  txtHeight, char *   text);
	void gfx_ChangeColour(uint16_t  OldColor, uint16_t  NewColor);
	void gfx_Circle(uint16_t  x, uint16_t  y, uint16_t  rad, uint16_t  color);
	void gfx_CircleFilled(uint16_t  x, uint16_t  y, uint16_t  rad, uint16_t  color);
	void gfx_Clipping(uint16_t  OnOff);
	void gfx_ClipWindow(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2);
	void gfx_Cls();
	uint16_t gfx_Contrast(uint16_t  Contrast);
	void gfx_Ellipse(uint16_t  x, uint16_t  y, uint16_t  xrad, uint16_t  yrad, uint16_t  color);
	void gfx_EllipseFilled(uint16_t  x, uint16_t  y, uint16_t  xrad, uint16_t  yrad, uint16_t  color);
	uint16_t gfx_Get(uint16_t  parameter);
	uint16_t gfx_GetPixel(uint16_t  x, uint16_t  y);
	void gfx_Line(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color);
	uint16_t gfx_LinePattern(uint16_t  Pattern);
	void gfx_LineTo(uint16_t  x, uint16_t  y);
	void gfx_MoveTo(uint16_t  x, uint16_t  y);
	void gfx_Orbit(uint16_t  angle, uint16_t  distance, uint16_t *  xdest, uint16_t *  ydest);
	uint16_t gfx_OutlineColour(uint16_t  color);
	void gfx_Panel(uint16_t  state, uint16_t  x, uint16_t  y, uint16_t  width, uint16_t  height, uint16_t  color);

	void gfx_Polygon(uint16_t  n, uint16_t *  xvalues, uint16_t *  yvalues, uint16_t  color);
	void gfx_PolygonFilled(uint16_t  n, uint16_t *  xvalues, uint16_t *  yvalues, uint16_t  color);
	void gfx_Polyline(uint16_t  n, uint16_t *  xvalues, uint16_t *  yvalues, uint16_t  color);

	void gfx_PutPixel(uint16_t  x, uint16_t  y, uint16_t  color);
	void gfx_Rectangle(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color);
	void gfx_RectangleFilled(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color);
	void gfx_ScreenCopyPaste(uint16_t  xs, uint16_t  ys, uint16_t  xd, uint16_t  yd, uint16_t  width, uint16_t  height);
	uint16_t gfx_ScreenMode(uint16_t  mode);
	void gfx_Set(uint16_t  Func, uint16_t  Value);
	void gfx_SetClipRegion();
	void gfx_Slider(uint16_t  mode, uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2, uint16_t  color, uint16_t  scale, uint16_t  value);
	uint16_t gfx_Transparency(uint16_t  OnOff);
	uint16_t gfx_TransparentColour(uint16_t  color);
	void gfx_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
	void gfx_TriangleFilled(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);

	void touch_DetectRegion(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2);
	uint16_t touch_Get(uint16_t  mode);
	void touch_Set(uint16_t  mode);

	uint16_t txt_Attributes(uint16_t attribs);
	uint16_t txt_BGcolor(uint16_t color);
	uint16_t txt_Bold(uint16_t bold);
	uint16_t txt_FGcolor(uint16_t color);
	uint16_t txt_FontID(uint16_t fontNumber);
	uint16_t txt_FontSD(uint8_t fontNumber);
	uint16_t txt_Height(uint16_t multiplier);
	uint16_t txt_Inverse(uint16_t inverse);
	uint16_t txt_Italic(uint16_t italic);
	void txt_MoveCursor(uint16_t column, uint16_t line);
	uint16_t txt_Opacity(uint16_t transparentOpaque);
	uint16_t txt_Underline(uint16_t underline);
	uint16_t txt_Width(uint16_t multiplier);
	uint16_t txt_Wrap(uint16_t position);
	uint16_t txt_Xgap(uint16_t pixels);
	uint16_t txt_Ygap(uint16_t pixels);

	uint16_t fileLoadImageControl(const char * datFilename, const char * gciFilename, uint16_t mode);
	uint16_t fileMount(void);

	uint16_t img_SetWord(uint16_t handle, uint16_t index, uint16_t offset, uint16_t value);
	uint16_t img_Show(uint16_t handle, uint16_t index);

	void video_ShowFrame(uint8_t videoNumber, int frame);

	void loadSdVideos(void);
	void loadSdFonts(void);

	int width(void) { return _displayWidth; }
	int height(void) { return _displayHeight; }

private:

	void writeWord(uint16_t w);
	uint8_t getACK(void);
	uint16_t getACKresponse(void);

	static uint16_t _videoHandles[PICASO_NUM_VIDEOS];
	static uint16_t _fontHandles[PICASO_NUM_FONTS];

	virtual size_t write(uint8_t b);
	virtual size_t write(const uint8_t *buffer, size_t size);

	int _displayWidth;
	int _displayHeight;
};

extern picaso4d PICASO;

#endif