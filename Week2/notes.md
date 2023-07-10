# Video I/O & GUI

# Read and display a Video in OpenCV

Just like we used [**`imread`**](https://docs.opencv.org/4.1.0/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56) to read an image stored on our machine, we will use **`VideoCapture`** to create a [**VideoCapture**](https://docs.opencv.org/4.1.0/d8/dfe/classcv_1_1VideoCapture.html#ac4107fb146a762454a8a87715d9b7c96) object and read from input file (video).

### Function Syntax 

```cpp
cv::VideoCapture::VideoCapture  (   const String &  filename,
int     apiPreference = CAP_ANY 
)
```

**Parameters**

- `filename` it can be:
  - name of video file (eg. video.avi)
  - or image sequence (eg. img_%02d.jpg, which will read samples like img_00.jpg, img_01.jpg, img_02.jpg, ...)
  - or URL of video stream (eg. protocol://host:port/script_name?script_params|auth). Note that each video stream or IP camera feed has its own URL scheme. Please refer to the documentation of source stream to know the right URL.
- **`apiPreference`**: preferred Capture API backends to use. Can be used to enforce a specific reader implementation if multiple are available: e.g. cv::CAP_FFMPEG or cv::CAP_IMAGES or cv::CAP_DSHOW.

## Create a video reader object 

```
VideoCapture cap(args)
```

Three most popular ways of reading videos using the VideoCapture Object are :

1. Using Webcam ( Pass the argument as 0)
2. From a video File ( Specify the filename as argument)
3. Image sequence [image_%03d.jpg]

#### NOTE for Webcam

In most cases, only one camera is connected to the system. So, all we do is pass **`0`** and OpenCV uses the only camera attached to the computer. When more than one camera is connected to the computer, we can select the second camera by passing **`1`**, the third camera by passing **`2`** and so on.



``` cpp
// Read until video is completed
while(cap.isOpened()){

    Mat frame;

    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Write the frame into the file 'outputChaplin.mp4'
    imshow("Frame", frame);

    // Wait for 25 ms before moving on to the next frame
    // This will slow down the video 
    waitKey(25);
}
```

# Write a Video in OpenCV

After we are done with capturing and processing the video frame by frame, the next step we would want to do is to save the video.

For images, it is straightforward. We just need to use **`cv::imwrite()`** and specify an image format(jpg/png). But for videos, some more info is required.

The steps are as follows:

**1.** Create a [**VideoWriter**](https://docs.opencv.org/4.1.0/dd/d9e/classcv_1_1VideoWriter.html#ac3478f6257454209fa99249cc03a5c59) object.

### Function Syntax 

```
cv::VideoWriter::VideoWriter    (   const String &  filename,
int     fourcc,
double  fps,
Size    frameSize,
bool    isColor = true 
)
```

**Parameters**

- **`filename`**: Name of the output video file.
- **`fourcc`**: 4-character code of codec used to compress the frames. For example, VideoWriter::fourcc('P','I','M','1') is a MPEG-1 codec, VideoWriter::fourcc('M','J','P','G') is a motion-jpeg codec etc. List of codes can be obtained at Video Codecs by FOURCC page. FFMPEG backend with MP4 container natively uses other values as fourcc code: see ObjectType, so you may receive a warning message from OpenCV about fourcc code conversion.
- **`fps`**: Framerate of the created video stream.
- **`frameSize`**: Size of the video frames.
- **`isColor`**: If it is not zero, the encoder will expect and encode color frames, otherwise it will work with grayscale frames (the flag is currently supported on Windows only).

**2.** Write frames to the object in a loop

**3.** close and release the object

### FourCC Code

[FourCC](https://en.wikipedia.org/wiki/FourCC) is a 4-byte code used to specify the video codec. The list of available codes can be found at [fourcc.org](http://fourcc.org/). There are many FOURCC codes available, but in this lecture we would work only with MJPG.

#### Note

Only a few of the FourCC codes listed above will work on your system based on the availability of the codecs on your system. Sometimes, even when the specific codec is available, OpenCV may not be able to use it. **MJPG is a safe choice.**

``` cpp
VideoCapture cap(DATA_PATH+"videos/chaplin.mp4");

// Check if camera opened successfully
if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
}

// Default resolutions of the frame are obtained.The default resolutions are system dependent.
int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

// Define the codec and create VideoWriter object.
// The output is stored in 'outputChaplin.mp4' file.
VideoWriter out("../results/outputChaplin.mp4",VideoWriter::fourcc('M','J','P','G'),10, Size(frame_width,frame_height));

// Read until video is completed
while(cap.isOpened()){

    Mat frame;

    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Write the frame into the file 'outputChaplin.mp4'
    out.write(frame);
    imshow("Frame",frame);
    // Wait for 25 ms before moving on to the next frame
    // This will slow down the video 
    waitKey(25);
}

// When everything done, release the VideoCapture and VideoWriter objects
cap.release();
out.release();
```

