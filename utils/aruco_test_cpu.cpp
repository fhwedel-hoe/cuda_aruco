#include <iostream>
#include <iomanip>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>

int main(int, char **) {
    cv::Mat image;
    cv::VideoCapture video_capture(0);
    video_capture >> image;

    cv::Ptr<cv::aruco::DetectorParameters> detector_params;
    detector_params = cv::aruco::DetectorParameters::create();
    detector_params->cornerRefinementMethod = cv::aruco::CORNER_REFINE_SUBPIX;

    cv::Ptr<cv::aruco::Dictionary> dictionary;
    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_50);

    float detection_time_seconds = 0.0f;
    int detection_time_samples = 0;
    while(video_capture.isOpened() && !image.empty()) {
        auto begin_tick = cv::getTickCount();
        
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners, rejected;
        cv::aruco::detectMarkers(image, dictionary, corners, ids, detector_params, rejected);
        
        auto finish_tick = cv::getTickCount();
        detection_time_seconds += float(finish_tick - begin_tick) / cv::getTickFrequency();
        detection_time_samples++;
        float avg_detection_time_seconds = detection_time_seconds / detection_time_samples;
        std::cout << "\rTime detection=" << std::fixed << std::setw(6) << std::setprecision(2) << 1000 * avg_detection_time_seconds << " milliseconds nmarkers=" << ids.size() << std::flush;
        
        video_capture >> image;
    }
}
