#include "param.h"
#include <bits/stdc++.h>

void DeepSortParam::read(const std::string& filename) 
{
  std::ifstream file;
  
  try
  {
    file.open(filename);
  }
  catch(...)
  {
    std::cerr << "Cannot open " << filename << std::endl;
    file.close();
    exit(-1);
  }
  
  if(!file.is_open())
  {
    std::cerr << "Error: file " << filename << " not found!" << std::endl;
    exit(-1);
  }
  
  
  std::string line;
  while(std::getline(file, line))
  {
      std::remove_if(line.begin(), line.end(), isspace);
      if(line.empty())
      {
	    continue;
      }
      else if(line.find("[video_read]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        video_read_ = line;
            
	    }
	    catch(...)
	    {
	        std::cerr << "video_read: " << line << std::endl;
	        exit(-1);
	    }
      }
      else if(line.find("[video_write]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        video_write_ = line;
	    }
	    catch(...)
	    {
	        std::cerr << "video_write: " << line << std::endl;
	        exit(-1);
	    }
      }
      else if(line.find("[name]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        name = line;
           
	    }
	    catch(...)
	    {
	        std::cerr << "name: " << line << std::endl;
	        exit(-1);
	    }
      }
      else if(line.find("[config_file<yolov3>]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        config_file = line;
	    }
	    catch(...)
	    {
	        std::cerr << "config_file<yolov3>: " << line << std::endl;
	        exit(-1);
	    }
      }
      else if(line.find("[weights_file]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        weights_file = line;
	    }
	    catch(...)
	    {
	        std::cerr << "Error in converting the weights_file: " << line << std::endl;
	        exit(-1);
	    }
      }
      else if(line.find("[names_file]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        names_file = line;
	    }
	    catch(...)
	    {
	        std::cerr << "Error in converting the names_file: " << line << std::endl;
	        exit(-1);
	    }
      }
      
    //   else if(line.find("[IMAGE_DIRECTORY]") != std::string::npos)
    //   {
	//     std::getline(file, line);
	//     try
	//     {
	//         image_directory = line.c_str();
	//     }
	//     catch(...)
	//     {
	//         std::cerr << "Error in converting the IMAGE_DIRECTORY: " << line << std::endl;
	//         exit(-1);
	//     }
    //   }
      else if(line.find("[METRIC_MODEL]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        metric_model_file = line.c_str();
	    }
	    catch(...)
	    {
	        std::cerr << "Error in converting the METRIC_MODEL: " << line << std::endl;
	        exit(-1);
	    }
      }
      else if(line.find("[FEATURE_MODEL]") != std::string::npos)
      {
	    std::getline(file, line);
	    try
	    {
	        feature_model_file = line.c_str();
	    }
        catch(...)
        {
        std::cerr << "Error in converting the FEATURE_MODEL: " << line << std::endl;
        exit(-1);
        }
      }
      else if(line.find("[step_frame]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            step = atof(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the step_frame: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[ARGS_NN_BUDGET]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            args_nn_budget_value = atof(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the ARGS_NN_BUDGET: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[ARGS_MAX_COSINE_DISTANCE]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            args_max_cosine_distance_value = atof(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the ARGS_MAX_COSINE_DISTANCE: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[DT]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            dt_value = atof(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the DT: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[MAX_IOU_DISTANCE]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            max_iou_distance_value = atof(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the MAX_IOU_DISTANCE: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[MAX_AGE]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            max_age_value = atoi(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the MAX_AGE: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[N_INIT]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            n_init_value = atoi(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the N_INIT: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[SHOW_DETECTIONS]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            show_detection_value = atoi(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the SHOW_DETECTIONS: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[CLASSES]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            std::ifstream class_file;
            try
            {
                class_file.open(line);
            }
            catch(...)
            {
                std::cerr << "Cannot open " << line << std::endl;
                file.close();
                exit(-1);
            }
            
            if(!class_file.is_open())
            {
                std::cerr << "Error: file " << line << " not found!" << std::endl;
                exit(-1);
            }
            
            
            std::string class_line;
            while(std::getline(class_file, class_line))
            {
                detection_classes.push_back(class_line);
            }

            class_file.close();
        }
        catch(...)
        {
            std::cerr << "Error in converting the N_INIT: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[CAM/VIDEO/USB_CAM]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            VoC = atoi(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the SHOW_DETECTIONS: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[Show_Video]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            show_video = atoi(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the SHOW_DETECTIONS: " << line << std::endl;
            exit(-1);
        }
      }
      else if(line.find("[Write_Video]") != std::string::npos)
      {
        std::getline(file, line);
        try
        {
            write_video = atoi(line.c_str());
        }
        catch(...)
        {
            std::cerr << "Error in converting the SHOW_DETECTIONS: " << line << std::endl;
            exit(-1);
        }
      }
  }
 
  file.close();
  
  print();
}
