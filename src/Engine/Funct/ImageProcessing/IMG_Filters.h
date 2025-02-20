#ifndef IMG_FILTERGAUSSIANBLUR_H_
#define IMG_FILTERGAUSSIANBLUR_H_

#include "SYS_Defs.h"
#include "SYS_Main.h"

#include "CImageData.h"
#include "CImageKernel.h"

#define SEGMENTATION_MARKER_NOT_MARKED	0
#define SEGMENTATION_MARKER_BACKGROUND	1
#define SEGMENTATION_MARKER_OBJECT		2	// starting from 2

CImageKernel *FLT_GetGaussianKernel(double sigma);

void FLT_Convolve(CImageData *imageData, CImageKernel *imageKernel);
void FLT_GradientMagnitude(CImageData *image, float *kern_h, float *kern_v);
void FLT_Dilate(CImageData *imageData, CImageKernel *imageKernel);
void FLT_Erode(CImageData *imageData, CImageKernel *imageKernel);
void FLT_Subtract(CImageData *image, CImageData *subImage);
void FLT_Add(CImageData *image, CImageData *subImage);
CImageData *FLT_Convolve_old(CImageData *imageData, CImageKernel *imageKernel);
CImageData *IMG_FilterGaussianBlur(CImageData *imageData, double sigma);
CImageData *IMG_FilterSobelEdgeDetect(CImageData *image);
void IMG_FilterThreshold(CImageData *image, int threshold);
void IMG_FilterThresholdRGBA(CImageData *image, u8 thresholdR, u8 thresholdG, u8 thresholdB, u8 thresholdA);
void IMG_FilterEqualize(CImageData *image);
void IMG_SpotRotate(CImageData *image, float angle);
CImageData *IMG_CropToBoundingBox(CImageData *image);
CImageData *IMG_CropImage(CImageData *image, int posX, int posY, int width, int height);
CImageData *IMG_CropImageRGB(CImageData *image, int posX, int posY, int width, int height);
CImageData *IMG_CropImageRGBA(CImageData *image, int posX, int posY, int width, int height);
CImageData *IMG_CropSupersampleImageRGBA(CImageData *image, int supersamplingFactor, int posX, int posY, int width, int height);
CImageData *IMG_SpotCropImage(CImageData *image, int posX, int posY, int spotRadius);
void IMG_CircleSpot(CImageData *image);
CImageData * IMG_MorphologicalGradient(CImageData *cielabRaster);
CImageData * IMG_SimpleSegmentation(CImageData *image);
void IMG_FindBound(CImageData *img, bool invert, int *retMinX, int *retMinY, int *retMaxX, int *retMaxY);
void IMG_ScaleNearest(CImageData *img, double factor);

#endif /*IMG_FILTERGAUSSIANBLUR_H_*/
