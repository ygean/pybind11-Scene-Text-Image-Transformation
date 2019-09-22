#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
//#include <boost/python.hpp>
#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"

#include "pybind11_opencv.h"

#include "conversion.h"
#include "imgwarp_mls_rigid.h"
#include "imgwarp_mls_similarity.h"
#include "imgwarp_piecewiseaffine.h"

#include <stdlib.h>
#include <sys/timeb.h>

using namespace cv;
using namespace std;

namespace py = pybind11;

typedef unsigned char uchar_t;

py::array_t<uint8_t> cv_mat_uint8_3c_to_numpy(cv::Mat& input);

namespace MLSTransformer {

	py::array_t<uint8_t> Distort(py::array_t<uint8_t>& image, const int segment) {

		ImgWarp_MLS_Similarity trans1;
		// ImgWarp_MLS_Rigid trans2;
		// ImgWarp_PieceWiseAffine trans3;
		vector<Point_<int> > qsrc;
		vector<Point_<int> > qdst;
		qsrc.clear();
		qdst.clear();

		// numpy to Mat
		cv::Mat img_input = pyarray_to_mat(image, CV_8U);

		int cut = img_input.cols / segment;
		int threshold = cut * 1. / 3;

		struct timeb timeSeed;
		ftime(&timeSeed);
		srand(timeSeed.time * 1000 + timeSeed.millitm);

		qsrc.push_back(Point(0, 0));
		qsrc.push_back(Point(img_input.cols, 0));
		qsrc.push_back(Point(img_input.cols, img_input.rows));
		qsrc.push_back(Point(0, img_input.rows));

		qdst.push_back(Point(rand() % threshold, rand() % threshold));
		qdst.push_back(Point(img_input.cols - rand() % threshold, rand() % threshold));
		qdst.push_back(Point(img_input.cols - rand() % threshold, img_input.rows - rand() % threshold));
		qdst.push_back(Point(rand() % threshold, img_input.rows - rand() % threshold));

		for (int i = 1; i < segment; i++) {
			qsrc.push_back(Point(cut * i, 0));
			qsrc.push_back(Point(cut * i, img_input.rows));
			qdst.push_back(Point(cut * i + rand() % threshold - 0.5 * threshold, rand() % threshold - 0.5 * threshold));
			qdst.push_back(Point(cut * i + rand() % threshold - 0.5 * threshold, img_input.rows + rand() % threshold - 0.5 * threshold));
		}

		cv::Mat result = trans1.setAllAndGenerate(img_input, qsrc, qdst, img_input.cols, img_input.rows);
		// Mat to numpy
		py::array_t<uint8_t> res = cv_mat_uint8_3c_to_numpy(result);
		return res;
	}

	py::array_t<uint8_t> Stretch(py::array_t<uint8_t>& image, const int segment) {

		ImgWarp_MLS_Similarity trans1;
		// ImgWarp_MLS_Rigid trans2;
		// ImgWarp_PieceWiseAffine trans3;
		vector<Point_<int> > qsrc;
		vector<Point_<int> > qdst;
		qsrc.clear();
		qdst.clear();

		// numpy to Mat
		cv::Mat img_input = pyarray_to_mat(image, CV_8U);

		qsrc.push_back(Point(0, 0));
		qsrc.push_back(Point(img_input.cols, 0));
		qsrc.push_back(Point(img_input.cols, img_input.rows));
		qsrc.push_back(Point(0, img_input.rows));

		qdst.push_back(Point(0, 0));
		qdst.push_back(Point(img_input.cols, 0));
		qdst.push_back(Point(img_input.cols, img_input.rows));
		qdst.push_back(Point(0, img_input.rows));

		int cut = img_input.cols / segment;
		int threshold = cut * 4 / 5;

		struct timeb timeSeed;
		ftime(&timeSeed);
		srand(timeSeed.time * 1000 + timeSeed.millitm);
		int move = 0;
		for (int i = 1; i < segment; i++) {
			move = rand() % threshold - 0.5 * threshold;
			qsrc.push_back(Point(cut * i, 0));
			qsrc.push_back(Point(cut * i, img_input.rows));
			qdst.push_back(Point(cut * i + move, 0));
			qdst.push_back(Point(cut * i + move, img_input.rows));
		}

		cv::Mat result = trans1.setAllAndGenerate(img_input, qsrc, qdst, img_input.cols, img_input.rows);
		// Mat to numpy
		py::array_t<uint8_t> res = cv_mat_uint8_3c_to_numpy(result);
		return res;
	}

	py::array_t<uint8_t> Perspective(py::array_t<uint8_t>& image) {

		ImgWarp_MLS_Similarity trans1;
		// ImgWarp_MLS_Rigid trans2;
		// ImgWarp_PieceWiseAffine trans3;
		vector<Point_<int> > qsrc;
		vector<Point_<int> > qdst;
		qsrc.clear();
		qdst.clear();

		// numpy to Mat
		cv::Mat img_input = pyarray_to_mat(image, CV_8U);

		int threshold = img_input.rows * 0.5;

		struct timeb timeSeed;
		ftime(&timeSeed);
		srand(timeSeed.time * 1000 + timeSeed.millitm);

		qsrc.push_back(Point(0, 0));
		qsrc.push_back(Point(img_input.cols, 0));
		qsrc.push_back(Point(img_input.cols, img_input.rows));
		qsrc.push_back(Point(0, img_input.rows));

		qdst.push_back(Point(0, rand() % threshold));
		qdst.push_back(Point(img_input.cols, rand() % threshold));
		qdst.push_back(Point(img_input.cols, img_input.rows - rand() % threshold));
		qdst.push_back(Point(0, img_input.rows - rand() % threshold));

		cv::Mat result = trans1.setAllAndGenerate(img_input, qsrc, qdst, img_input.cols, img_input.rows);
		// Mat to numpy
		py::array_t<uint8_t> res = cv_mat_uint8_3c_to_numpy(result);
		return res;
	}
}

py::array_t<uint8_t> cv_mat_uint8_3c_to_numpy(cv::Mat& input)
{
	py::array_t<uint8_t> dst = py::array_t<uint8_t>({ input.rows,input.cols,3 }, input.data);
	return dst;
}

PYBIND11_MODULE(MLSTransformer, m) {
	m.def("Distort", &MLSTransformer::Distort, "Moving Least Squares transformation using c++.", py::arg("image"), py::arg("segment"));
	m.def("Stretch", &MLSTransformer::Stretch, "Moving Least Squares transformation using c++.", py::arg("image"), py::arg("segment"));
	m.def("Perspective", &MLSTransformer::Perspective, "Moving Least Squares transformation using c++.", py::arg("image"));
}

//PyObject*
//GenerateDistort(PyObject *img, int segment)
//{
//    NDArrayConverter cvt;
//    cv::Mat img_input;
//    img_input = cvt.toMat(img);
//    cv::Mat result = Distort(img_input, segment);
//
//    PyObject* ret = cvt.toNDArray(result);
//
//    return ret;
//}
//
//PyObject*
//GenerateStretch(PyObject *img, int segment)
//{
//    NDArrayConverter cvt;
//    cv::Mat img_input;
//    img_input = cvt.toMat(img);
//    cv::Mat result = Stretch(img_input, segment);
//
//    PyObject* ret = cvt.toNDArray(result);
//
//    return ret;
//}
//
//PyObject*
//GeneratePerspective(PyObject *img)
//{
//    NDArrayConverter cvt;
//    cv::Mat img_input;
//    img_input = cvt.toMat(img);
//    cv::Mat result = Perspective(img_input);
//
//    PyObject* ret = cvt.toNDArray(result);
//
//    return ret;
//}

//static void init()
//{
//    Py_Initialize();
//    import_array();
//}

//BOOST_PYTHON_MODULE(Augment)
//{
//    init();
//    py::def("GenerateDistort", GenerateDistort);
//    py::def("GenerateStretch", GenerateStretch);
//    py::def("GeneratePerspective", GeneratePerspective);
//}
