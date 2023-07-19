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
