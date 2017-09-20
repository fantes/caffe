// This program reads in pairs label names and optionally ids and display names
// and store them in LabelMap proto buffer.
// Usage:
//   create_label_map [FLAGS] MAPFILE OUTFILE
// where MAPFILE is a list of label names and optionally label ids and
// displaynames, and OUTFILE stores the information in LabelMap proto.
// Example:
//   ./build/tools/create_label_map --delimiter=" " --include_background=true
//   data/VOC2007/map.txt data/VOC2007/labelmap_voc.prototxt
// The format of MAPFILE is like following:
//   class1 [1] [someclass1]
//   ...
// The format of OUTFILE is like following:
//   item {
//     name: "class1"
//     label: 1
//     display_name: "someclass1"
//   }
//   ...

#include <fstream>  // NOLINT(readability/streams)
#include <string>

#include "gflags/gflags.h"
#include "glog/logging.h"

#include "caffe/proto/caffe.pb.h"
#include "caffe/util/io.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "caffe/util/im_transforms.hpp"

using namespace caffe;  // NOLINT(build/namespaces)



int main(int argc, char** argv) {
  ::google::InitGoogleLogging(argv[0]);
  // Print output to stderr (while still logging)
  FLAGS_alsologtostderr = 1;

#ifndef GFLAGS_GFLAGS_H_
  namespace gflags = google;
#endif



  if (argc < 7) {

    return 1;
  }

  cv::Mat img = ReadImageToCVMat(argv[1], true);
  cv::Mat out_img(img.rows, img.cols, img.type());
  BarrelPincussionDistortion(img, &out_img, true,
                                    atof(argv[3]), atof(argv[4]),atof(argv[5]),atof(argv[6]));


  cv::imwrite(argv[2], out_img);
}
