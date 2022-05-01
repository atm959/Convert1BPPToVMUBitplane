# ConvertBWToVMUBitplane
Converts "image.png" to the format that KallistiOS uses for VMU display images.

The image must be named "image.png" (without the quotes), it must be 48x32, and it must be 8-bit grayscale. The pixels that are a complete black color will be dark on the VMU screen, and pixels that are a complete white color will be light on the VMU screen.

Example to display the image on the first VMU plugged into the Dreamcast:
```C
maple_device_t* vmuLCD;
vmuLCD = maple_enum_type(0, MAPLE_FUNC_LCD);
vmu_draw_lcd(vmuLCD, vmuImage);
```

To compile it with GCC:
```
gcc main.c
```
