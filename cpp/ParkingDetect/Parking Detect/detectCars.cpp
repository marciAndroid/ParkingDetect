#include "detectCars.h"

double *percentagesToDraw = new double[NUMBER_OF_POINTS]();
bool *canRefresh = new bool[NUMBER_OF_POINTS]();

void calcPercentages(const Mat& thresh, const Mat& diffImage, Mat* spotMasks, double* percentages, int count) {
	if (count != NUMBER_OF_POINTS) {
		cerr << "Unable to read next frame." << endl;
		for (int i = 0; i < count; i++) {
			percentages[i] = 0;
		}
		return;
	}
	int currX = 950;
	int i = 0;
	double *newPercentages = new double[NUMBER_OF_POINTS]();
	while (currX > 60) {
		double percentage = calcNonZeroPixels(thresh, spotMasks[i], true);
		double percentage_of_moving_objects = 2; // calcNonZeroPixels(diffImage, mask = maskRectangles[i], percentage = true);
		newPercentages[i] = percentage;
		if (percentage_of_moving_objects < 5)
			canRefresh[i] = true;
		else
			canRefresh[i] = false;
		currX -= 10;
		i += 1;
	}
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		bool refresh = true;
		if (i > 0 and canRefresh[i - 1] == false)
			refresh = false;
		if (i > 1 and canRefresh[i - 2] == false)
			refresh = false;
		if (i > 2 and canRefresh[i - 3] == false)
			refresh = false;
		if (i > 3 and canRefresh[i - 4] == false)
			refresh = false;

		if (i < NUMBER_OF_POINTS - 1 and canRefresh[i + 1] == false)
			refresh = false;
		if (i < NUMBER_OF_POINTS - 2 and canRefresh[i + 2] == false)
			refresh = false;
		if (i < NUMBER_OF_POINTS - 3 and canRefresh[i + 3] == false)
			refresh = false;
		if (i < NUMBER_OF_POINTS - 4 and canRefresh[i + 4] == false)
			refresh = false;

		if (refresh)
			percentages[i] = newPercentages[i];
	}

}