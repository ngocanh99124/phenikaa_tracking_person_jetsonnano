/*
 * VideoTracker.cpp
 */
#include "VideoTracker.h"
#include "opencv2/opencv.hpp"
#include "tracker.h"
#include "FeatureTensor.h"
#include <DarkHelp.hpp>
#include <thread>

using namespace cv;
using namespace std;

std::queue <Mat> lf;
int frame_width, frame_height;

VideoTracker::VideoTracker(const DeepSortParam& tracker_params) : params(tracker_params)
{
	modelDetection = std::shared_ptr<ModelDetection>(new ModelDetection(params.detections(), params.images()));
	
}


void VideoTracker::Video_Read()
{
	VideoCapture cap(params.video_read());//(*/"/home/ngocanh/Downloads/deep_sort/video/11.mp4");
	if (params.VoC == 0)
		cap.set(cv::CAP_PROP_BUFFERSIZE, 5);
	frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
	frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  	float tf;
	  Mat frame;
	while (true)
	{
	try
		{
			tf = cap.read(frame);
			
			if (!tf)
				continue;
				//cap.open(params.video_read(),cv::CAP_GSTREAMER);
			if (frame.empty())
            	continue;
			lf.pop();
			lf.push(frame);
			//video.write(frame);
			//cv::imshow("DeepSortTracking", frame);
			//waitKey(1);
			frame.release();
		}
		catch(const char* err)
		{ 
			cerr << err << endl;
			continue;
		}
	}
}


void VideoTracker::run()
{
	clock_t start = clock();
	clock_t s1, s2;
	double res = 0;
	tracker mytracker(params);
	std::shared_ptr<FeatureTensor> featureTensor(new FeatureTensor(params.metric_model(), params.feature_model()));
	
    DarkHelp darkhelp(params.config(), params.weights(), params.names());
	VideoCapture cap;
	cout << params.VoC << "VoC" << endl;
	if (params.VoC < 2)
		cap.open(params.video_read());
	else
		cap.open(0);
	

	if (params.VoC == 0)
		cap.set(cv::CAP_PROP_BUFFERSIZE, 5);
	frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
	frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  	float tf;
	VideoWriter video(params.video_write()+"/"+params.name + ".avi", VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height));//"/home/ngocanh/Downloads/deep_sort/video/output.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
	bool write_flag = true;
	cout<<"STARTING.....";
	
	DETECTIONS detections;
	Mat frame;
	DETECTION_ROW tmpRow;
	std::vector<RESULT_DATA> result;
	std::stringstream ss;
	DETECTBOX tmp, tmpbox;
	int i = 0;
	while(true) 
	{
		
		s1 = clock();
		//frame = lf.front();
		tf = cap.read(frame);
		if (params.VoC == 1)
		{
			if (frame.empty())
				break;
		}
		
			if (!tf && params.VoC == 0)
				{
					//cap.release();
					cap.open(params.video_read());
					cap.set(cv::CAP_PROP_BUFFERSIZE, 5);
					continue;
				}
			if (frame.empty())
				continue;
		
		if (i%params.getStep() == 0)
		{
			const auto results = darkhelp.predict(frame);
		
			for (const auto & detection : results)
       		{
				if(detection.best_class != 0) continue;
				tmpRow.class_num = detection.best_class;
				tmpRow.confidence = detection.best_probability;
				tmpRow.tlwh = DETECTBOX(detection.rect.x , detection.rect.y , detection.rect.width , detection.rect.height);

				detections.push_back(tmpRow);
			}

            
        }

		
		if(featureTensor->getRectsFeature(frame, detections) == false) 
		{
			this->errorMsg = "Tensorflow get feature failed!";
			return;
		}

		if (i%params.getStep() == 0)
		{	mytracker.predict();
			mytracker.update(detections);
		}
		
		for(Track& track : mytracker.tracks) 
		{
			if(!track.is_confirmed() || track.time_since_update > 1) continue;
			result.push_back(std::make_pair(std::make_pair(track.track_id, track.detection_class), std::make_pair(track.to_tlwh(), track.color)));
		}

		if(params.show_detections())
		{
			for(unsigned int k = 0; k < detections.size(); k++) 
			{
				tmpbox = detections[k].tlwh;
				Rect rect(tmpbox(0), tmpbox(1), tmpbox(2), tmpbox(3));
				rectangle(frame, rect, Scalar(0,0,255), 4);
			}
		}

		
		for(unsigned int k = 0; k < result.size(); k++) 
		{
			tmp = result[k].second.first;
			std::string det_class = result[k].first.second;
			cv::Scalar color = result[k].second.second;
			Rect rect = Rect(tmp(0), tmp(1), tmp(2), tmp(3));
			rectangle(frame, rect, color, 2);
			ss << result[k].first.first << " - " << det_class;
			putText(frame, ss.str(), Point(rect.x, rect.y), cv::FONT_HERSHEY_SIMPLEX, 0.8, color, 2);
			ss.str("");
		}
		s2 = clock();
		res = res + ((double)(s2-s1))/CLOCKS_PER_SEC;
		
		//cv::resize(frame, outImg, cv::Size(), 0.75, 0.75);
		
		if (params.write_video == 1)
			video.write(frame);
			//cout << "write done!";
		
		if (params.show_video == 1)
		{
			cv::imshow("DeepSortTracking", frame);
			waitKey(1);
		}
		frame.release();
		
		i++;
		
		if (res > 10*60)     
			{
				break;
				cout << "end time";
			}
		detections.clear();
		result.clear();
	}//end while;

	ofstream of;
	cout << params.video_write() << endl;
	cout << params.name <<' '<< i/res << endl;
	cout << params.video_write()+"/"+params.name + ".txt";
	of.open(params.video_write()+"/"+params.name + ".txt", ios::out);
	of << i/res;
	
}

std::string VideoTracker::showErrMsg() 
{
	return this->errorMsg;
}
