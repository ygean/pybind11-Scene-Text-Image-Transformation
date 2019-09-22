#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"

namespace py = pybind11;

namespace MLSTransformer {
	py::array_t<uint8_t> Distort(py::array_t<uint8_t>& image, const int segment);

	py::array_t<uint8_t> Stretch(py::array_t<uint8_t>& image, const int segment);

	py::array_t<uint8_t> Perspective(py::array_t<uint8_t>& image);
}

