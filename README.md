# ArUco: Augmented Reality library from the University of Cordoba

ArUco is a minimal C++ library for detection of Augmented Reality markers based on OpenCv exclusively.

It is an educational project to show student how to detect augmented reality markers and it is provided under BSD license.

ORIGINAL CONTACT: Rafael Munoz-Salinas: rmsalinas@uco.es

## INTRODUCTION

The library relies on the use of coded markers. Each marker has an unique code indicated by the black and white colors in it. The libary detect borders, and analyzes into the rectangular regions which of them are likely to be markers. Then, a decoding is performed and if the code is valid, it is considered that the rectangle is a marker.

The codification included into the marker is a slighly modified version of the Hamming Code. It has a total a 25 bits didived in 5 rows of 5 bits each. So, we have 5 words of 5 bits. Each word, contains only 2 bits of real information, the rest is for  and error detection/correction (error correction is yet to be done). As a conclusion, a marker contains 10 bits of real information wich allows 1024 different markers.

## LIBRARY DESCRIPTION:

The ArUco library contents are divided in two main directories. The src directory, which contains the library itself. And the utils directory which contains the applications.

The library main classes are:

* `aruco::Marker`: which represent a marker detected in the image
* `aruco::MarkerDetector`: that is in charge of deteting the markers in a image Detection is done by simple calling the member funcion `ArMarkerDetector::detect()`. Additionally, the classes contain members to create the required matrices for rendering using OpenGL. See aruco_test_gl for details
* `aruco::BoardConfiguration`: A board is an array of markers in a known order. BoardConfiguracion is the class that defines a board by indicating the id of its markers. In addition, it has informacion about the distance between the markers so that extrinsica camera computations can be done.
* `aruco::Board`: This class defines a board detected in a image. The board has the extrinsic camera parameters as public atributes. In addition, it has a method that allows obtain the matrix for getting its position in OpenGL (see aruco_test_board_gl for details).
* `aruco::BoardDetector`: This is the class in charge of detecting a board in a image. You must pass to it the set of markers detected by ArMarkerDetector and the BoardConfiguracion of the board you want to detect. This class will do the rest for you, even calculating the camera extrinsics.

### BOARDS

Aruco allows the possibility to employ board. Boards are markers composed by an array of markers arranged in a known order. The advantages of using boards instead of simple markers are:

* More robusteness. The misdetection of several markers of the board is not a problem as long as a minimum set of them are detected.
* More precision. Since there are a larger number of corners, camera pose estimation becomes more precise.

A Board contains several markers so that they are more robustly detected.  In general, a board is a set of markers. So BoardConfiguration is only a list  of the id of the markers along with the position of their corners.
 
The position of the corners can be specified either in pixels (in a non-specific size) or in meters. The first is the 
typical case in which you generate the image of  board  and the print it. Since you do not know in advance the real 
size of the markers, their corners are specified in pixels, and then, the translation to meters can be made once you 
know the real size. On the other hand, you may want to have the information of your boards in meters in your 
configuration file once you have created it. The BoardConfiguration allows you to do so.

Creating boards in managed by two applications. First, use aruco_create_board to create the image of the board. 
Print it and use your measurer to know the real size of the markers. Then, you can use aruco_board_pix2meters to create 
new configuration file that expresses the board in meters. So, you no longer need to remember the size of your markers.

Since version 1.2, aruco allows to create boards with chessboard configuration. To support the detection of chessboards, we need to apply an erosion in the image when detecting markers.
This is an option that can be disabled in MarkerDetector::enableErosion. By default, it is enabled. However, disabling it can speed up the process up to a 10%. So if you 
do not want to use chessboards, disable it.

### APPLICATIONS

The library comes with several applications that will help you to learn how to use the library:

* `aruco_create_marker`: which creates marker and saves it in a jpg file you can print.
* `aruco_simple`: simple test aplication that detects the markers in an image
* `aruco_test`: this is the main application for detection. It reads images either from the camera of from a video and detect markers. Additionally, if you provide the intrinsics of the camera(obtained by OpenCv calibration) and the size of the marker in meters, the library calculates the marker intrinsics so that you can easily create your AR applications.
* `aruco_test_gl`: shows how to use the library AR applications using OpenGL for rendering
* `aruco_create_board`: application that helps you to create a board
* `aruco_board_pix2meters`: application that helps you to convert a board configuration file from pixels(as provided by aruco_create_board) to meters.
* `aruco_test_board`: application that detects boards
* `aruco_simple_board`: simple application that detects boards in an image
* `aruco_test_board_gl`: application that detects boards and uses OpenGL to draw
 
### HIGHLY RELIABLE MARKERS
After version 1.2.5, ArUco includes a new type of marker codification know as Highly Reliable Markers (hrm). The main benefits are: (i) number of markers and marker size is customizable by the user and (ii) error correction can be applied. 
For more details, see "S. Garrido-Jurado, R. Muñoz-Salinas, F.J. Madrid-Cuevas, M.J. Marín-Jiménez, Automatic generation and detection of highly reliable fiducial markers under occlusion, Pattern Recognition, Volume 47, Issue 6, June 2014"
The 'utils_hrm' folder contains some applications to test these markers

* `aruco_hrm_create_dictionary`: creates customized dictionary of highly reliable markers
* `aruco_hrm_test`: basic application for single marker detection
* `aruco_hrm_create_board`: create a board of hrm markers, it can also create chromatic boards for occlusion map (see paper for more information)
* `aruco_hrm_test_board`: detect board. If use chromatic board it can also generate occlusion mask
    
## COMPILING THE LIBRARY:

REQUIREMENTS: OpenCv >= 3.x.x, cmake >= 3.x  
OPTIONAL:   OpenGL for aruco_test_gl and aruco_test_board_gl

### LINUX:

Go to the aruco library and do

    mkdir build
    cd build
    cmake ..
    make
    make install (optional) 

NOTE ON OPENGL: The library supports eaily the integration with OpenGL. In order to compile with support for OpenGL, you just have  installed in your system the develop packages for GL and glut (or freeglut).

### WINDOWS

Probably possible with MSVC2019's native cmake support. Not tested.

## Testing

For testing the applications, the library provides videos and the corresponding camera parameters of these videos. Into the directories you will find information on how to run the examples.

## Benchmark

Detection times (per frame, averaged):
  * 1280x960:  
    this library @ NVIDIA GeForce GTX 1060 GPU – 13 ms  
    OpenCV default @ i7-3770 CPU – 15 ms  

→ No significant improvement in speed was observed.
