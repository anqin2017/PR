#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include "config.h"

using namespace std;
using namespace cv;

namespace PR
{
	class CPlate
	{
	public:
		CPlate();

		~CPlate();

		inline void setPlateMat(Mat param) { m_plateMat = param; }

		inline Mat getPlateMat() const { return m_plateMat; }

		inline  void setChinesePlateMat(Mat param) { m_chinesePlateMat = param; }

		inline Mat getChinesePlateMat(Mat param) { return m_chinesePlateMat; }





	private:
		// plate mat
		Mat  m_plateMat;
		// plate rect
		Mat  m_platePos;
		// chinese plate mat
		Mat m_chinesePlateMat;
		// chinese plate rect
		Mat m_chinesePlateRect;
	};

}

