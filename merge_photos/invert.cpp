#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <vector>

#define WIDTH 640
#define HEIGHT 951

void read_image_file_to_vector(std::string file_name, std::vector<uint8_t> *data) {
	std::fstream image_file_stream (file_name, std::ios::in | std::ios::binary);
	char bin_val;
	
	while ( image_file_stream.read( &bin_val, 1) ) {
		data->push_back(bin_val);
	}

	image_file_stream.close();
}

//***************************************************************************************************************
// merge_photos:
// 	Input: two equal-sized 8-bit intensity images
// 	Output: nothing returned, modifies the data_merged vector data in place to end up with the merged image
// 	Method: the resulting image will be the average of each corresponding pixel value
//***************************************************************************************************************
void merge_photos( const std::vector<uint8_t> *data_1, const std::vector<uint8_t> *data_2, std::vector<uint8_t> *data_merged) {
// 	for (int i = 0; i < data_1->size(); i++) {
// 		data_merged->at(i) = data_1->at(i) + data_2->at(i) / 2;
// 	}
	
// 	auto it_1 = data_1->begin();
// 	auto it_2 = data_2->begin();
// 	
// 	while ( it_1 != data_1->end() ) {
// 		data_merged->push_back ( (*it_1 * *it_2) / 2 );
// 		it_1++;
// 		it_2++;
// 	}

	for (auto it_1 = data_1->begin(), it_2=data_2->begin(); it_1 != data_1->end(); it_1++, it_2++) {
		data_merged->push_back( ( *it_1 + *it_2 ) / 2 );
	}
}

void invert (std::vector<uint8_t> *data) {
	for (uint8_t &pixel: *data) {
		pixel != 0 ? pixel = 255 % pixel : pixel = 255;
	}
}

void write_data_vector_to_file( std::string file_name, std::vector<uint8_t> *data ) {	
	std::fstream image_file_stream (file_name, std::ios::out | std::ios::binary);
	char* bin_val = new char [WIDTH * HEIGHT];
	std::copy( data->begin(), data->end(), bin_val );
	image_file_stream.write( bin_val, data->size() );
	image_file_stream.close();

	delete [] bin_val;
}

int main(int argc, const char** argv) {
	std::vector<uint8_t> data_1;
	std::vector<uint8_t> data_2;
	std::vector<uint8_t> data_merged;	
	std::string input_image_file_name_1 = argv[1];
	//std::string input_image_file_name_2 = argv[2];
	std::string output_image_file_name;
	read_image_file_to_vector( input_image_file_name_1, &data_1 );
	//read_image_file_to_vector( input_image_file_name_2, &data_2 );
	std::stringstream ss;
	//int intensity = atoi(argv[3]);
	//int num_iterations = atoi(argv[4]);
	
//	average_with_constant_intensity(&data_1, intensity, num_iterations);
//	ss << "image_averaged_with_" << intensity << "_" << num_iterations << "_times.dat";
//	ss >> output_image_file_name;
//	write_data_vector_to_file (output_image_file_name, &data_1);
//	std::cout << "about to merge the photos" << std::endl;
//	merge_photos(&data_1, &data_2, &data_merged);	
//	write_data_vector_to_file ("merged_photo.dat", &data_merged);
	invert(&data_1);
	write_data_vector_to_file ("inverted.data", &data_1);
}
