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
