#include "img1_median_7.h"

void img1_median_7(axis_t &img_out, axis_t &img_in){

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

	unsigned short window [49];
	unsigned short tempo;
	for (short row = 10; row < 235; row++) {
			img_col:for (short col = 10; col < 235; col++) {
				window_col:for (short i = -3; i <= 3; i++) {
					for (short j = -3; j <= 3; j++) {
						window[(i + 3) * 7 + (j + 3)] = img[row + i][col + j];
					}
				}

				sort_row:for (short x = 0; x < 49; x++) {
					for (short z = 0; z < 48 - x; z++) {
						if (window[z] > window[z + 1]) {
							tempo = window[z];
							window[z] = window[z + 1];
							window[z+1] = tempo;
						}
					}
				}
				result[row-10][col-10] = window[3*7+3];
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
