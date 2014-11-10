#include <iostream>
#include "datasetReader.h"


/**
 * @brief
 * MAIN FUNCTION
 * @return int
 */
int main()
{
    std::cout << "Hello World!" << std::endl;


    //SAMPLE USAGE
    cvc::KittiDataset cvd;
    cvd.loadDataset();
    for(int i=0;i<cvd.max_files_train;i++)
    {
        std::vector<std::string> file_pair = cvd.loadFiles(false);
        std::cout<<file_pair[0]<<"\n"<<file_pair[1]<<std::endl<<std::endl;
    }
    //END OF SAMPLE USAGE



    return 0;
}
