// This file automatically generated by create_export_module.py
#include "../NumpyEigenConverter.hpp"


void import_11_14_int()
{
	// Without this import, the converter will segfault
	import_array();
	NumpyEigenConverter<Eigen::Matrix< int, 11, 14 > >::register_converter();
}
