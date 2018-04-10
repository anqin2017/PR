#include "Core_Func.h"

Mat PR::colorMatch(const Mat & src, Mat & match, const Color r, const bool adaptive_minsv)
{
	//if use adative_sv
	const float max_sv = 255;
	const float min_refsv = 64;
	const float minabs_sv = 95; //95;

	// H range of blue 
	const int min_blue = 100;  // 100
	const int max_blue = 140;  // 140

    // H range of yellow
	const int min_yellow = 15;  // 15
	const int max_yellow = 40;  // 40

    // H range of white
	const int min_white = 0;   // 0
	const int max_white = 30;  // 30

	Mat src_hsv;
	// convert to hsv
	cvtColor(src, src_hsv, CV_BGR2HSV);
	// split image to channels
	vector <Mat> hsvSplit;
	split(src_hsv, hsvSplit);
	// equalizehist to improve image 
	equalizeHist(hsvSplit[2], hsvSplit[2]);
	// merge the image again
	merge(hsvSplit, src_hsv);

	// match to find the color
	int min_h = 0;
	int max_h = 0;
	switch (r)
	{
	case BLUE:
		min_h = min_blue;
		max_h = max_blue;
		break;
	case YELLOW:
		min_h = min_yellow;
		max_h = max_yellow;
		break;
	case WHITE:
		min_h = min_white;
		max_h = max_white;
		break;
	default:
		// Color::UNKNOWN
		break;
	}
	float diff_h = float((max_h - min_h) / 2);
	float avg_h = min_h + diff_h;

	int channels = src_hsv.channels();
	int nRows = src_hsv.rows;
	//consider the mutichannel image
	int nCols = src_hsv.cols * src_hsv.channels();
	if (src_hsv.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i, j;
	uchar* p;
	float s_all = 0;
	float v_all = 0;
	float count = 0;
	for (i = 0; i < nRows; ++i) {
		p = src_hsv.ptr<uchar>(i);
		for (j = 0; j < nCols; j += 3) {
			int H = int(p[j]);      // 0-180
			int S = int(p[j + 1]);  // 0-255
			int V = int(p[j + 2]);  // 0-255

			s_all += S;
			v_all += V;
			count++;

			bool colorMatched = false;

			if (H > min_h && H < max_h) {
				float Hdiff = 0;
				if (H > avg_h)
					Hdiff = H - avg_h;
				else
					Hdiff = avg_h - H;

				float Hdiff_p = float(Hdiff) / diff_h;

				float min_sv = 0;
				if (true == adaptive_minsv)
					min_sv =
					min_refsv -
					min_refsv / 2 *
					(1- Hdiff_p);  // inref_sv - minref_sv / 2 * (1 - Hdiff_p)
				else
					min_sv = minabs_sv;  // add

				if ((S > min_sv && S < max_sv) && (V > min_sv && V < max_sv))
					colorMatched = true;
			}

			if (colorMatched == true) {
				p[j] = 0;
				p[j + 1] = 0;
				p[j + 2] = 255;
			}
			else {
				p[j] = 0;
				p[j + 1] = 0;
				p[j + 2] = 0;
			}
		}
	}

	// cout << "avg_s:" << s_all / count << endl;
	// cout << "avg_v:" << v_all / count << endl;

	// get the final binary

	Mat src_grey;
	std::vector<cv::Mat> hsvSplit_done;
	split(src_hsv, hsvSplit_done);
	src_grey = hsvSplit_done[2];

	match = src_grey;
	return src_grey;;
}
