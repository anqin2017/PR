#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include "Plate.h"

using namespace std;
using namespace cv;

namespace PR
{
	//! find binary image match to color
	//! input rgb, want match color ( blue or yellow)
	//! out grey, 255 is match, 0 is not match

	Mat colorMatch(const Mat& src, Mat& match, const Color r,
		const bool adaptive_minsv);
}

