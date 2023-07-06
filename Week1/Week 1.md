# Week 1

## Introduction to Computer Vision



### Problems in Computer Vision

#### Image Processing

* Image denoising
* Image enhancement
* Image restoration
* Image & video compression
* Edge detection

#### Structure from Motion

* Stereo Vision
* Projector camera systems
* Construction of 3D from 2D images

#### Visual Slam 

* Simultaneous Localization and Mapping

#### Shape from X

* Shape from shading
* Photometric Stereo

#### Featuring Detection and Matching

* Image alignment
* Medical image registration
* Document rectification
* Motion estimation
* Video stabilization

#### Image Recognition

* Image classification
* Object detection
* Object tracking
* Image segmentation
* Natural image mapping
* Face / fingerprint / iris / gait recognition
* Document analysis
* Counterfeit detection

#### Measurement of Images

* Facial landmark detection
* head pose detection
* body pose estimation

#### Computation Photography

* HDR
* Pano
* Light field photography
* Black hole photography
* Colorization



## Getting Started with Images

### Reading an Image: `cv::imread`

**Function Syntax** 

```c++
Mat cv::imread  (   const String &  filename,
int     flags = IMREAD_COLOR 
)
```

It has **2 arguments**:

1. `Path of the image file` (`filename`): This can be an **absolute** or **relative** path. This is a **mandatory argument**.
2. `flags`: These flags are used to read an image in a particular format (for example, grayscale/color/with alpha channel). This is an **optional argument** with a default value of `IMREAD_COLOR` or `1` which loads the image as a color image.

Before we proceed with some examples, let's also have a look at the `flags` available.

**Flags**

1. **`IMREAD_GRAYSCALE`** or **`0`**: Loads image in grayscale mode
2. **`IMREAD_COLOR`** or **`1`**: Loads a color image. Any transparency of image will be neglected. It is the default flag.
3. **`IMREAD_UNCHANGED`** or **`-1`**: Loads image as such including alpha channel.

### Image Data Types

* `8UC1`: 8 bit unsigned int with 1 channel
* `8SC1`: 8 bit signed int with 1 channel
* `8UC3`: 8 bit unsigned with 3 channels
* `32FC3`: 32 bit floating with 3 channels

### Image Dimensions

``` c++
auto [width, height] = img.size();
```

``` python
height, width = img.shape()
```

### Manipulating Pixels

The first index of the matrix is `row number` and the second is `column number`.

For example, to access the element at `4th row` and `5th column`, we should use `img[3,4]`. But as we will see in Image annotation section, we will deal with points which are represented as `(x,y)` and thus, the coordinates will be `(4,3)`.

``` c++
// manipulate single pixel
img.at<unchar>(0, 0) = 255;
// manipulate group of pixels
img(Range(0, 2), Range(0, 4)).setTo(111);
```

### Image Channels

Gray images have only one channel, for most color images, they have three channels (R, G, B). In some cases there may be an additional channel (alpha channel) which contains transparency information of the pixels.

``` c++
// Split and merge color channels
Mat imgBGR;
Mat imgPNGChannels[4];
split(img, imgChannels);
merge(imgPNGChannels, 3, imgBGR);

// Modify color pixels
img.at<Vec3b>(1, 1) = Vec3b(255, 255, 0);
img(Range(3, 6), Range(0, 3)).setTo(Scalar(0, 255, 0));
```

## Basic Image Operations

### Create New Images

``` c++
// create an empty matrix of size (100, 200)
Mat emptyMatrix = Mat(100, 200, CV_8UC3, Scalar(0, 0, 0));
// fill with white pixels
emptyMatrix.setTo(Scalar(255,255,255));
// create an empty matrix of the same size as another matrix
Mat emptyCopy = Mat(emptyMatrix.size(), emptyMatrix.type(), Scalar(0, 0, 0))

```

### Cropping an Image

``` c++
// Crop out a rectangle
// x coordinates = 170 - 320
// y coordinates = 40 - 200
Mat cropped = img(Range(40, 200), Range(170, 320));
```

### Copying a Region to Another

``` c++
img.copyTo(copiedImage(Range(40, 40+height), Range(10, 10 + width)));
```

### Resizing an Image: `cv::resize`

**Function Syntax** 

```
void cv::resize (   InputArray  src,
OutputArray     dst,
Size    dsize,
double  fx = 0,
double  fy = 0,
int     interpolation = INTER_LINEAR 
)
```

**Parameters**

- **`src`** - input image
- **`dst`** - output resized image
- **`dsize`** - output image size
- **`fx`** - scale factor along the horizontal axis;
- **`fy`** - scale factor along the vertical axis; Either dsize or both fx and fy must be non-zero.
- **`interpolation`** - interpolation method ( Bilinear / Bicubic etc ).

Check interpolation flags [here](https://docs.opencv.org/4.1.0/da/d54/group__imgproc__transform.html#ga5bb5a1fea74ea38e1a5445ca803ff121)

There are two ways of using the resize function.

1. Specify width and height of output image explicitly

   > Use the dsize argument to specify the output size in the form (width,height).

   ``` c++
   resize(img, res, Size(resizedWidth, resizedHeight), INTER_LINEAR);
   ```

   

2. Specify the scaling factors for resizing ( for both width and height )

   > Use fx and fy arguments to specify the scaling factor for horizontal and vertical axis respectively. It should be a float.
   >
   > The output size is calculated as: `Size(round(fx*src.cols), round(fy*src.rows))`

   ``` c++
   resize(image, scaledDown, Size(), scaleDownX, scaleDownY, INTER_LINEAR);
   ```

### Creating Image Masks

Create naive mask

``` c++
Mat mask1 = Mat::zeros(image.size(), image.type());
```

Create a mask using pixel intensity or color

#### Function Syntax

It finds the pixels which lie in between the specified range. It produces a binary output image in which the white pixels corresspond to those pixels in the input image which fall in the specified range. The pixel values which fall outside the specified range are black `(0)`

```c++
void cv::inRange    (   InputArray  src,
InputArray  lowerb,
InputArray  upperb,
OutputArray     dst 
)
```

**Parameters**

- **`src`** - first input array.
- **`lowerb`** - inclusive lower boundary array or a scalar.
- **`upperb`** - inclusive upper boundary array or a scalar.
- **`dst`** - output array of the same size as src and CV_8U type.

It produces a binary image ( pixels are either black or white ).

## Mathematical Operations on Images

### Datatype Conversion

``` c++
double scalingFactor = 1/255.0;
double shift = 0;

//Converting from unsigned char to float(32bit)
image.convertTo(image, CV_32FC3, scalingFactor, shift);
//Converting from float to unsigned char
image.convertTo(image, CV_8UC3, 1.0/scalingFactor, -shift/scalingFactor);
```

### Contrast Enhancement

Many definitions of contrast exist in literature. In simple terms, it is the difference in intensity between the brightest and darkest regions of an image. Higher the difference, higher is the contrast. The maximum contrast of an image is also known as **Dynamic Range**. In an image with good contrast, objects are easily discernible.

One of the easiest ways to improve contrast of an image is Intensity Scaling.

In this approach, a scale factor ( $\alpha$ ) is multiplied with intensity values of all the pixels. Given below is the code snippet to do the same. Intensity scaling is represented by the following equation

$$I_o=αI$$

``` c++
double contrastPercentage = 50.0;

Mat image32F = image.clone();
Mat highCont_1;
Mat highCont_2;

// Convert to CV_64F without mapping to [0,1].
image32F.convertTo(image32F, CV_32F);

// Multiply with scaling factor to increase contrast
highCont_1 = image32F * (1+contrastPercentage/100.0);

// Map the float image to [0,1].
image32F  = image32F/255.0;
highCont_2 = image32F * (1+contrastPercentage/100.0);
```

### Brightness Enhancement

Brightness is a measure of light falling on the scene. In RGB color space, it can be thought of as the arithmetic mean of the R, G and B color values. To make an image brighter, the intensity values should be increased by some offset ( β� ) and vice-versa.

If $I$ is the input image, and $Io$ is the output image, brightness enhanced image is given by the equation

$$Io=I+β$$

``` cpp
int brightnessOffset = 100;

Mat bright_32F;
Mat brightHighChannels_32F[3];

// Incorrect way.
Mat tempBright = image_32F.clone();
// Add brightness offset to the image directly.
tempBright = tempBright + brightnessOffset;

// Correct way.
// Split the channels.
split(image_32F, brightHighChannels_32F);
// Add brightness offset to each channels.
for (int i=0; i < 3; i++)
    {
        add(brightHighChannels_32F[i], brightnessOffset/255.0, brightHighChannels_32F[i]);
    }
merge(brightHighChannels_32F, 3, bright_32F);
```

### Performing normalization 

Note that the colors appear washed. This is because after performing addition, some pixel intensities has values greater than 1. Meaning the image is not in correct range of [0,1], which means all the values that are above 1 will be mapped to 255. Making the image appear washed. We can tone the image by normalizing it to the correct range.

We need to divide the matrix by the maximum value to normalize the image. It can be obtained by the function **`minMaxLoc`** as shown below.

``` cpp
// Add the offset for increasing brightness to the 32 bit image.
Mat bright_normalized_32F;
Mat brightHighChannels_norm_32F[3];
split(image_32F, brightHighChannels_norm_32F);

for (int i=0; i < 3; i++)
    {
        add(brightHighChannels_norm_32F[i], brightnessOffset/255.0, brightHighChannels_norm_32F[i]);
    }
merge(brightHighChannels_norm_32F, 3, bright_normalized_32F);

// Get maximum pixel intensity.
double minVal, maxVal;
minMaxLoc(bright_normalized_32F, &minVal, &maxVal);
cout << "Maximum pixel intensity : " << maxVal;
bright_normalized_32F = bright_normalized_32F/maxVal;
```

