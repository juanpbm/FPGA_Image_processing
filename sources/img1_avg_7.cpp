#include "img1_avg_7.h"
#include <math.h>

void img1_avg_7(axis_t &img_out, axis_t &img_in){

#pragma HLS INTERFACE axis port=img_in
#pragma HLS INTERFACE axis port=img_out
#pragma HLS stream variable=img_in
#pragma HLS stream variable=img_out
#pragma HLS INTERFACE ap_ctrl_none port=return

	data_t img[245][245];
	data_t result[225][225];

	word_t temp;

#pragma HLS dataflow
	ArraytoM:for (int i = 0; i < 60025; i++) {
#pragma HLS PIPELINE
		temp = img_in.read();
		img[i / 245][i % 245] = temp.data;
	}

	unsigned short sum = 0;
	unsigned short avg = 0;
	for (int row = 10; row < 235; row++) {
		img_col:for (int col = 10; col < 235; col++) {
			sum = 0;
			avg = 0;
			window_row:for (int i = -3; i <= 3; i++) {
				window_col:for (int j = -3; j <= 3; j++) {
					sum += img[row + i][col + j];
				}
			}
			avg = round(sum/(49.0));
			result[row-10][col-10] = avg;
		}
	}

	word_t out;
	MtoArrayRow:for (int row = 0; row < 225; row++) {
		MtoArrayCol:for (int col = 0; col < 225; col++) {
			out.data = result[row][col];
			out.last = row == 224  && col == 224;
			img_out.write(out);
		}
	}

}
