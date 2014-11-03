#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <algorithm>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "includes/dirent.h"
static const std::string slash = "\\";
#else
#include <dirent.h>
static const std::string slash = "/"; /**< TODO */
#endif


namespace cvc
{
using namespace std;



/**
 * @brief
 *  class directoryReader is a generic class
 *  which contains all utility functions for
 *  daset reading
 */
class directoryReader
{
private:

public:
    DIR *directory;
    struct dirent *directory_entry;
    string folder;
    string extension;
    vector<string> files;

    /**
     * @brief
     * Initializing the object
     */
    directoryReader()
    {
        //Change with whatever you like-Default Value
        this->folder= ("/home/prassanna/Development/Datasets/KITTI_SEMANTIC/Training_00/RGB");

        this->extension = ".png";
        directory = opendir(this->folder.c_str());
    }

    /**
     * @brief Constructor
     *
     * @param location is the location of the folder
     * @param extension is the extension of the files to be stored.
     */
    directoryReader(string &location, string extension)
    {
       initPath(location,extension);
    }

    /**
     * @brief Changes directory name and extension
     *
     * @param location is the location of the folder
     * @param extension is the extension of the files to be stored.
     */
    void initPath(string &location, string extension)
    {
        this->extension = extension;
        this->folder = location;
        directory = opendir(location.c_str());
    }

    /**
     * @brief lists files in a directory
     *
     * @return vector<string>files is the list of files in that directory
     */
    vector<string> listFiles()
    {
        this->files.clear();
        if(directory!=NULL)
        {
            while( (directory_entry = readdir (directory))!=NULL)
            {
                string file_name = directory_entry->d_name;

                if(checkExtension(file_name, this->extension))
                    files.push_back(folder + slash + directory_entry->d_name);
            }

        }

        return files;
    }

    /**
     * @brief
     *
     * @param file_name filename of a file
     * @param extension desired extension that the filename should have
     * @return bool (true/false) if extension is matched
     */
    bool checkExtension(std::string &file_name, std::string extension)
    {
        unsigned location_of_last_dot = file_name.rfind(".");
        if(location_of_last_dot!=std::string::npos)
        {
            string ext = file_name.substr(location_of_last_dot);
            if(ext.compare(extension) == 0)
                return true;
            else
                return false;
        }

        return false;
    }

};

/**
 * @brief
 * Uses directory Reader for general Dataset purposes
 */
class generalDataset
{
public:
    string location_labels_train =""; /**< TODO */
    string location_images_train =""; /**< TODO */
    string location_labels_test = ""; /**< TODO */
    string location_images_test = ""; /**< TODO */
    string extension = ""; /**< TODO */

    vector<string> files_labels_test; /**< TODO */
    vector<string> files_images_test; /**< TODO */
    vector<string> files_labels_train; /**< TODO */
    vector<string> files_images_train; /**< TODO */

    directoryReader dateset_iterator; /**< TODO */

    int index_train; /**< TODO */
    int index_test; /**< TODO */

    int max_files_train; /**< TODO */
    int max_files_test; /**< TODO */

    /**
     * @brief
     *
     */
    generalDataset(){}

    /**
     * @brief
     * loads all four parts of a dataset -> (Test,Train) x (Images, Labels)
     */
    void loadDataset()
    {
        this->dateset_iterator.initPath(location_labels_train, extension);
        this->files_labels_train = this->dateset_iterator.listFiles();

        this->dateset_iterator.initPath(location_images_train, extension);
        this->files_images_train = this->dateset_iterator.listFiles();

        this->dateset_iterator.initPath(location_labels_test, extension);
        this->files_labels_test = this->dateset_iterator.listFiles();

        this->dateset_iterator.initPath(location_images_test, extension);
        this->files_images_test = this->dateset_iterator.listFiles();

        this->index_train=0;
        this->index_test = 0;
        this->max_files_train = std::max(files_labels_train.size(), files_images_train.size());
        this->max_files_test= std::max(files_labels_test.size(), files_images_test.size());
    }

    /**
     * @brief
     *
     * @param isTrain pass true if you want the training subset, false for testing
     * @return vector<string>image_label_pair which are two strings-> (image filename, label filename)
     */
    vector<string> loadFiles(bool isTrain)
    {
        vector<string> image_label_pair;
        if(isTrain)
        {
            image_label_pair.push_back(this->files_images_train[this->index_train]);
            image_label_pair.push_back(this->files_labels_train[this->index_train]);
            this->index_train++;
        }
        else
        {
            image_label_pair.push_back(this->files_images_test[this->index_test]);
            image_label_pair.push_back(this->files_labels_test[this->index_test]);
            this->index_test++;
        }

        return image_label_pair;
    }


};

/**
 * @brief
 * Generic dataset adapted for Camvid
 */
class CamVidDataset : public generalDataset
{
public:
    /**
     * @brief
     * Only have to change the variable names pointing to directories.
     * Everything else is taken care by generalDataset
     */
    CamVidDataset()
    {
       location_labels_train ="/home/prassanna/Development/Datasets/CamVid_new/Train/Annotations";
       location_images_train ="/home/prassanna/Development/Datasets/CamVid_new/Train/Images";
       location_labels_test = "/home/prassanna/Development/Datasets/CamVid_new/Test/Annotations";
       location_images_test = "/home/prassanna/Development/Datasets/CamVid_new/Test/Images";
       extension = ".png";

    }
};

/**
 * @brief
 * custom dataset which you can fill in just like camvid
 */
class customDataset : public generalDataset
{
public:

    customDataset()
    {
        //Replace this with anything you like
       location_labels_train ="/home/prassanna/Development/Datasets/CamVid_new/Train/Annotations";
       location_images_train ="/home/prassanna/Development/Datasets/CamVid_new/Train/Images";
       location_labels_test = "/home/prassanna/Development/Datasets/CamVid_new/Test/Annotations";
       location_images_test = "/home/prassanna/Development/Datasets/CamVid_new/Test/Images";
       extension = ".png";

    }
};
}



/**
 * @brief
 * MAIN FUNCTION
 * @return int
 */
int main()
{
    std::cout << "Hello World!" << std::endl;


    //SAMPLE USAGE
    cvc::CamVidDataset cvd;
    cvd.loadDataset();
    for(int i=0;i<cvd.max_files_train;i++)
    {
        std::vector<std::string> file_pair = cvd.loadFiles(false);
        std::cout<<file_pair[0]<<"\n"<<file_pair[1]<<std::endl<<std::endl;
    }
    //END OF SAMPLE USAGE



    return 0;
}
