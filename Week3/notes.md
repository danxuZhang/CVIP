# Week 3: Binary Image Processing

## Shareholding

**Note**: OpenCV library functions are almost always faster than self-invented algorithms.

### Function Syntax

`threshold` has the following syntax :

``` cpp
double cv::threshold    (   InputArray  src,
OutputArray     dst,
double  thresh,
double  maxval,
int     type 
)
```

Where,

Input:

* **src** is the input array ot image (multiple-channel, 8-bit or 32-bit floating point).
* **thresh** is the threshold value.
* **maxval** is the maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types.
* **type** is thethresholding type ( THRESH_BINARY, THRESH_BINARY_INV, etc )

Output:

**dst** is the output array or image of the same size and type and the same number of channels as src.

### Threshold Types

#### Binary Threshold

$$ dst(x,y)= maxval\ if\ src(x,y)>threshold\ else\ 0 $$

#### Binary Threshold Inverse

$$ dst(x,y)=0\ if\ src(x, y)>threshold\ else\ maxval $$

#### Truncate

$$ dst(x,y)=threshold\ if\ src(x, y)>threshold\ else\ src(x,y) $$

#### To Zero

$$ dst(x,y)=src(x,y)\ if\ src(x, y)>threshold\ else\ 0 $$

#### To Zero Inverse

$$ dst(x,y)=0\ if\ src(x, y)>threshold\ else\ src(x,y) $$

## Morphological Operations

* **Morphological**: The study of the forms of the things.
* **Dilation**: To expand
* **Erosion**: To shrink

## Dilation

**Dilation** is used to merge or expand white regions which may be close to each other and

### Function Syntax

```cpp
void cv::dilate (   InputArray  src,
OutputArray     dst,
InputArray  kernel,
Point   anchor = Point(-1,-1),
int     iterations = 1,
int     borderType = BORDER_CONSTANT,
const Scalar &  borderValue = morphologyDefaultBorderValue() 
)
```

## Erosion

**Erosion** is used to separate or shrink white regions

### Function Syntax

```cpp
void cv::erode  (   InputArray  src,
OutputArray     dst,
InputArray  kernel,
Point   anchor = Point(-1,-1),
int     iterations = 1,
int     borderType = BORDER_CONSTANT,
const Scalar &  borderValue = morphologyDefaultBorderValue() 
)
```

**Parameters**

* **`src`** input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
* **`dst`** output image of the same size and type as src.
* **`kernel`** structuring element used for dilation; if elemenat=Mat(), a 3 x 3 rectangular structuring element is used.
* **`anchor`** position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
* **`iterations`** number of times dilation is applied.
* **`borderType`** pixel extrapolation method.
* **`borderValue`** border value in case of a constant border

**Note:** In the functions above, the parameter ‘iterations’ is optional and if not mentioned default is taken as 1. In case, we need to run the dilate/erode function n number of times we specify "iterations = n" in the function parameter list.

## Opening and Closing

we can combine erosion and dilation operations to perform some interesting operations on binary images. We can remove small black or white spots from a binary image. For example, we know that erosion removes white region and dilation adds white region. Thus, if we want to **remove small white spots**, we should perform **erosion followed by dilation** so that the smaller white spots are removed, whereas the bigger white blobs are unchanged. Similarly you can **remove black spots using dilation followed by erosion**.

**Opening** refers Erosion followed by Dilation and these operations is used for clearing **white blobs** and

**Closing** refers Dilation followed by Erosion and are used for clearing **black holes**

Opening and Closing operations can be performed by combining erosion and dilation. It can also be done using special OpenCV functions

In OpenCV, the opening and closing operations are implemented using **MorphologyEx** function.

To specify between the opening and closing operation to be performed we specify an argument in the function [**`MorphologyEx`**](https://docs.opencv.org/4.1.0/d4/d86/group__imgproc__filter.html?fbclid=IwAR1GtoDsIv4Fi8o7vrZ8SGb3bb1uiU_Nyt94fc9J2sHKF7FlbDNT1fq-kI0#ga67493776e3ad1a3df63883829375201f) definition. The argument for opening operation and closing operations are [**`MORPH_OPEN`**] and [**`MORPH_CLOSE`**] respectively.

### Function Syntax

#### Opening

```cpp
void morphologyEx(Mat initialImage, Mat imageMorphOpened, MORPH_OPEN, Mat structuringElement)
```

#### Closing

```cpp
void morphologyEx(Mat initialImage, Mat imageMorphClosed, MORPH_CLOSE, Mat structuringElement)
```

**Parameters**

* **`src`** Source image. The number of channels can be arbitrary. The depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
* **`dst`** Destination image of the same size and type as source image.
* **`op`** Type of a morphological operation
* **`kernel`** Structuring element. It can be created using getStructuringElement.
* **`anchor`** Anchor position with the kernel. Negative values mean that the anchor is at the kernel center.
* **`iterations`** Number of times erosion and dilation are applied.
* **`borderType`** Pixel extrapolation method.
* **`borderValue`** Border value in case of a constant border. The default value has a special meaning.

## Connected Components Analysis

**Connected Component Analysis(CCA)** is used for labeling blobs in a binary image.It can also be used to count the number of blobs (connected components) in a binary image.
