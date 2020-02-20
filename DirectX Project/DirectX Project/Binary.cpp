//#include "Binary.h"
//
//Binary::Binary(){}
//
//Binary::~Binary(){}
//
//std::ostream& Binary::Serialize(std::ostream& os, int test_1, int test_2)
//{
//	BufferData data(test_1, test_2);
//	data.Write(os);
//	return os;
//}
//
//std::istream& Binary::Deserialize(std::istream& is)
//{
//	BufferData data;
//	int test_1, test_2;
//	data.Read(is, test_1, test_2);
//	std::ofstream myfile;
//	myfile.open("TEST.txt");
//	myfile << std::to_string(test_1) << std::endl;
//	myfile << std::to_string(test_2) << std::endl;
//	myfile.close();
//	return is;
//}