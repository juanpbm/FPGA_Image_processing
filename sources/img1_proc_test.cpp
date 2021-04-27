#include <iostream>
#include <fstream>
//#include "img1_avg_7.h"
//#include "img1_avg_21.h"
//#include "img1_median_7.h"
#include "img1_median_21.h"
using namespace std;

int main() {

    data_t img[245][245];
    data_t gold_img[225][225];
    data_t img_result[225][225];

    ifstream rf;
    rf.open("img1.txt");

    if (rf.is_open()) {

        for (int row = 0; row < 245; row++) {
            for (int col = 0; col < 245; col++) {
                rf >> img[row][col];
            }
        }
        rf.close();
    }
    else {
        cout << "error";
        return -1;
    }

    axis_t input;
    axis_t output;

    word_t in;
    word_t out;

    for (int row = 0; row < 245; row++) {
        for (int col = 0; col < 245; col++) {
        	in.data = img[row][col];
        	in.last = row == 244 && col == 244;
            input.write(in);
        }
    }

    //img1_avg_7(output, input);
    //rf.open("1_avg_7by7.txt");
    //img1_avg_21(output, input);
    //rf.open("1_avg_21by21.txt");
    //img1_median_7(output, input);
    //rf.open("1_median_7by7.txt");
    img1_median_21(output, input);
    rf.open("1_median_21by21.txt");

    for (int i = 0; i < 50625; i++) {
    	out = output.read();
    	img_result[i / 225][i % 225] = out.data;
    	bool last = out.last;
    	if(i == 50624)
			printf("last = %d\n", last);
    }

    if (rf.is_open()) {

        for (int row = 0; row < 225; row++) {
            for (int col = 0; col < 225; col++) {
                rf >> gold_img[row][col];
            }
        }
        rf.close();
    }
    else {
        cout << "error";
        return -1;
    }

    for (int row = 0; row < 225; row++) {
        for (int col = 0; col < 225; col++) {
            if (img_result[row][col] != gold_img[row][col]){
                cout << "!!!!!!!!!!!!Failed at(" << row << "," << col << ")!!!!!!!!!!!!!!!!!!!1" << endl;
                return -1;
            }
        }
    }
    cout << "!!!!!!!!!!!!!!!PASS: The output matches the golden output!!!!!!!!!!!";

    return 0;
}
