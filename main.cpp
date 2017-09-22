
#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int upperLimit = 255;   // Set upper limit for trackbar
int H_MIN_1 = 0;
int H_MAX_1 = 255;
int S_MIN_1 = 0;
int S_MAX_1 = 255;
int V_MIN_1 = 0;
int V_MAX_1 = 255;   // Initialise values for minimum & maximum values of Hue, Saturation & Value
int H_MIN_2 = 0;
int H_MAX_2 = 255;
int S_MIN_2 = 0;
int S_MAX_2 = 255;
int V_MIN_2 = 0;
int V_MAX_2 = 255;

void on_trackbar( int, void* ){
    
    // This function gets called whenever trackbar position is changed
}

void createTrackbars(){
    
    namedWindow("Trackbars",0);   // Create window for trackbars
    
    createTrackbar( "Hue Min 1", "Trackbars", &H_MIN_1, upperLimit, on_trackbar );
    createTrackbar( "Hue Max 1", "Trackbars", &H_MAX_1, upperLimit, on_trackbar );
    createTrackbar( "Saturation Min 1", "Trackbars", &S_MIN_1, upperLimit, on_trackbar );
    createTrackbar( "Saturation Max 1", "Trackbars", &S_MAX_1, upperLimit, on_trackbar );
    createTrackbar( "Value Min 1", "Trackbars", &V_MIN_1, upperLimit, on_trackbar );
    createTrackbar( "Value Max 1", "Trackbars", &V_MAX_1, upperLimit, on_trackbar );
    createTrackbar( "Hue Min 2", "Trackbars", &H_MIN_2, upperLimit, on_trackbar );
    createTrackbar( "Hue Max 2", "Trackbars", &H_MAX_2, upperLimit, on_trackbar );
    createTrackbar( "Saturation Min 2", "Trackbars", &S_MIN_2, upperLimit, on_trackbar );
    createTrackbar( "Saturation Max 2", "Trackbars", &S_MAX_2, upperLimit, on_trackbar );
    createTrackbar( "Value Min 2", "Trackbars", &V_MIN_2, upperLimit, on_trackbar );
    createTrackbar( "Value Max 2", "Trackbars", &V_MAX_2, upperLimit, on_trackbar );
    
    // Create trackbars and insert them into window, 5 parameters are:
    // 1. The title of the trackbar
    // 2. The title of the window
    // 3. The variable that is changing when the trackbar is moved
    // 4. The max value the trackbar can move to
    // 5. The function that is called whenever the trackbar is moved
    
}

int main(int argc, char* argv[]){
    
    Mat cameraFeed;   // Matrix to store each frame of the webcam feed
    Mat HSV;   // Matrix storage for HSV image
    Mat threshold1;   // Matrix storage for binary threshold image 1
    Mat threshold2;   // Matrix storage for binary threshold image 2
    Mat thresholdComb;   // Matrix storage for combination of threshold 1 & 2
    
    VideoCapture capture;   // Video capture object to acquire webcam feed
    
    capture.open(0);   // Open capture object at location zero (default location for webcam)
    
    createTrackbars();   // Call the trackbar function
    
    while(1){
        
        capture.read(cameraFeed);   // Store image to matrix "cameraFeed"
        
        cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);   // Convert image from BGR to HSV colorspace
        
        inRange(HSV,Scalar(H_MIN_1,S_MIN_1,V_MIN_1),Scalar(H_MAX_1,S_MAX_1,V_MAX_1),threshold1);
        // Filter HSV image between values and store filtered image to threshold matrix 1
        
        if(((H_MIN_2 != 0) || (H_MAX_2 != 255)) && (S_MIN_2 == 0) && (S_MAX_2 == 255) && (V_MIN_2 == 0) && (V_MAX_2 == 255)){
        
            inRange(HSV,Scalar(H_MIN_2,S_MIN_1,V_MIN_1),Scalar(H_MAX_2,S_MAX_1,V_MAX_1),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
        
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
        
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << " & " << H_MIN_2 << " - " << H_MAX_2 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << ",\n";
            cout << "\n";
            
            // If the Hue is between a particular range, e.g 0-20 & 50-150 this case will be called
            
        }
        
        if((H_MIN_2 == 0) && (H_MAX_2 == 255) && ((S_MIN_2 != 0) || (S_MAX_2 != 255)) && (V_MIN_2 == 0) && (V_MAX_2 == 255)){
            
            inRange(HSV,Scalar(H_MIN_1,S_MIN_2,V_MIN_1),Scalar(H_MAX_1,S_MAX_2,V_MAX_1),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
            
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
            
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << " & " << S_MIN_2 << " - " << S_MAX_2 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << ",\n";
            cout << "\n";
            
            // If the Saturation is between a particular range, e.g 0-20 & 50-150 this case will be called
            
        }
        
        if((H_MIN_2 == 0) && (H_MAX_2 == 255) && (S_MIN_2 == 0) && (S_MAX_2 == 255) && ((V_MIN_2 != 0) || (V_MAX_2 != 255))){
            
            inRange(HSV,Scalar(H_MIN_1,S_MIN_1,V_MIN_2),Scalar(H_MAX_1,S_MAX_1,V_MAX_2),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
            
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
            
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << " & " << V_MIN_2 << " - " << V_MAX_2 << ",\n";
            cout << "\n";
            
            // If the Value is between a particular range, e.g 0-20 & 50-150 this case will be called
            
        }
        
        if(((H_MIN_2 != 0) || (H_MAX_2 != 255)) && ((S_MIN_2 != 0) || (S_MAX_2 != 255)) && (V_MIN_2 == 0) && (V_MAX_2 == 255)){
            
            inRange(HSV,Scalar(H_MIN_2,S_MIN_2,V_MIN_1),Scalar(H_MAX_2,S_MAX_2,V_MAX_1),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
            
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
            
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << " & " << H_MIN_2 << " - " << H_MAX_2 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << " & " << S_MIN_2 << " - " << S_MAX_2 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << ",\n";
            cout << "\n";
            
            // If the Hue & Saturation are between a particular range, e.g 0-20 & 50-150 for Hue and 20-60 & 130-200 for Saturation this case will be called
            
        }
        
        if(((H_MIN_2 != 0) || (H_MAX_2 != 255)) && (S_MIN_2 == 0) && (S_MAX_2 == 255) && ((V_MIN_2 != 0) || (V_MAX_2 != 255))){
            
            inRange(HSV,Scalar(H_MIN_2,S_MIN_1,V_MIN_2),Scalar(H_MAX_2,S_MAX_1,V_MAX_2),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
            
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
            
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << " & " << H_MIN_2 << " - " << H_MAX_2 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << " & " << V_MIN_2 << " - " << V_MAX_2 << ",\n";
            cout << "\n";
            
            // If the Hue & Value are between a particular range, e.g 0-20 & 50-150 for Hue and 20-60 & 130-200 for Value this case will be called
            
        }
        
        if((H_MIN_2 == 0) && (H_MAX_2 == 255) && ((S_MIN_2 != 0) || (S_MAX_2 != 255)) && ((V_MIN_2 != 0) || (V_MAX_2 != 255))){
            
            inRange(HSV,Scalar(H_MIN_1,S_MIN_2,V_MIN_2),Scalar(H_MAX_1,S_MAX_2,V_MAX_2),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
            
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
            
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << " & " << S_MIN_2 << " - " << S_MAX_2 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << " & " << V_MIN_2 << " - " << V_MAX_2 << ",\n";
            cout << "\n";
            
            // If the Saturation & Value are between a particular range, e.g 0-20 & 50-150 for Saturation and 20-60 & 130-200 for Value this case will be called
            
        }
        
        if(((H_MIN_2 != 0) || (H_MAX_2 != 255)) && ((S_MIN_2 != 0) || (S_MAX_2 != 255)) && ((V_MIN_2 != 0) || (V_MAX_2 != 255))){
            
            inRange(HSV,Scalar(H_MIN_2,S_MIN_2,V_MIN_2),Scalar(H_MAX_2,S_MAX_2,V_MAX_2),threshold2);
            // Filter HSV image between values and store filtered image to threshold matrix2
            
            add(threshold1, threshold2, thresholdComb);
            // adds value of elements from threshold 1 and threshold 2 and stored in thresholdComb
            
            imshow("Thresholded Image",thresholdComb);   // Show total combined threshold image
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << " & " << H_MIN_2 << " - " << H_MAX_2 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << " & " << S_MIN_2 << " - " << S_MAX_2 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << " & " << V_MIN_2 << " - " << V_MAX_2 << ",\n";
            cout << "\n";
            
            // If the Hue, Saturation & Value are all between a particular range, e.g 0-20 & 50-150 for Hue and 15-35 & 70-200 for Saturation and 20-60 & 130-200 for Value this case will be called
            
        }
        
        else if((H_MIN_2 == 0) && (H_MAX_2 == 255) && (S_MIN_2 == 0) && (S_MAX_2 == 255) && (V_MIN_2 == 0) && (V_MAX_2 == 255)){
            
            imshow("Thresholded Image",threshold1);
            
            cout << "Hue: " << H_MIN_1 << " - " << H_MAX_1 << ",\n";
            cout << "Saturation: " << S_MIN_1 << " - " << S_MAX_1 << ",\n";
            cout << "Value: " << V_MIN_1 << " - " << V_MAX_1 << ",\n";
            cout << "\n";
            
            // Else if the Hue, Saturation & Value are all within one range e.g 0-150 for Hue and 150-255 for Saturation and 150-255 for Value then this case will be called
            
        }
        
        waitKey(30);   // Delay 30ms so that screen can refresh. Image will not appear without this waitKey() command
        
    }
    
    return 0;
}


