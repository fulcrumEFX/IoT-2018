#include <iostream>
#include <string>

int main(){

	std::string input="";

	while(1){
	std::cout << ">";
	std::cin >> input;
	if (input[0]=='#') break;
	std::cout << std::endl << "Anwenderprogramm laeuft" << std::endl << "Was ist " << input << "??" << std::endl;
	}
	return 0;
}
