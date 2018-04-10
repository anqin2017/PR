#pragma once
#include "Plate.h"

namespace PR
{
	class CPlateLocate
	{
	public:
		CPlateLocate();
		~CPlateLocate();

		int PlateLocate(Mat, vector<Mat>&, int = 0);

		int PlateColorLocate(Mat src, vector<CPlate>& candPlates, int index);

		int PlateSobelLocate(Mat src, vector<CPlate>& candPlates, int index);

		int PlateMserLocate(Mat src, vector<CPlate>& candPlates, int index);

	};
}


