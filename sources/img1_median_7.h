#ifndef _IMG1_MEDIAN_7_H_
#define _IMG1_MEDIAN_7_H_

#include "ap_int.h"
#include "hls_stream.h"
typedef ap_uint<16> data_t;

struct word_t{
	ap_uint<16> data;
	ap_int<1> last;
};

typedef hls::stream<word_t> axis_t;

void img1_median_7(
	axis_t &img_out,
	axis_t &img_in
);

#endif //_IMG1_MEDIAN_7_H_
