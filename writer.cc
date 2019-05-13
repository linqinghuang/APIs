#include<iostream>
#include<fstream>

using namespace std;
int main(int argc,char* argv[])
{
	char tempData[100];
	ofstream outfile;
	outfile.open("temp.txt",ios::app);

	cout << "input something" << endl;
	cin.getline(tempData,100);

	outfile << tempData << endl;

	outfile.close();
	ifstream infile;
	infile.open("temp.txt",ios::binary);
	infile >> tempData;
	cout << tempData << endl;
	infile >> tempData;
	cout << tempData << endl;
	infile.close();
	return 0;
}
