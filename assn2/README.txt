main.cpp: main() 함수를 포함한 c++ source file. 메뉴 입력과 관련된 부분을 담당하며, 사용자의 선택에 따라 적절하게 다른 함수를 호출한다. 

student.hpp: student 정보를 담은 Student class의 declaration과 관련 member methods 및 functions의 declaration을 포함한다. Student objects를 비교하기 위한 operator overloading (==, >, <)과 출력하기 위한 bit shift operator (<<) overloading을 포함한다. 또한, 각 student의 최대 및 최소 나이가 상수로 정의되어 있다. 
student.cpp: student.hpp의 declaration의 definition 및 구현을 포함한다. 

node.hpp: Node class의 선언과 두 개의 Node objects를 비교하기 위한 operator overloading (==)을 포함한다. 또한, 서로 다른 두 개의 Node objects가 주어졌을 때 두 nodes의 자리를 바꾸는 함수 또한 선언 되어 있다. 
node.cpp: node.hpp에서 선언된 functions와 class의 definition 및 구현을 포함한다. 

list.hpp: list 관리에 필요한 상수의 선언 및 student 정보를 저장하는 linked list class List의 선언을 포함한다. 
list.cpp: list.hpp에 선언된 functions과 class의 definition 및 구현을 포함한다. 

io.hpp: 사용자의 입력에 대한 예외를 처리하는 class Format와 double을 적절히 출력하는 operator+ overloading의 선언이 포함되어 있다. 또한, double의 출력에 관한 상수 또한 선언되어 있다. 
io.cpp: io.hpp에 선언된 function과 class의 definition 및 구현을 포함한다. 

exception.hpp: 사용자가 입력을 중단하고 메인 메뉴로 돌아가는 것을 선택했을 때 throw 되는 exception인 InterruptedInputException과 list의 department capacity가 꽉 차 더 이상 새로운 department의 학생을 추가할 수 없는 경우에 raise되는 exception인 MaxDepartmentException의 선언 및 정의가 포함되어 있다. 두 class 모두 추가적인 member 없이 default constructor/destructor로 구성되기에 class 정의까지 header file에 포함되어 있다. 

Makefile: make command를 통해 build할 수 있도록 한다. make all을 통해 object files를 만들고 executable (main.out)로 build할 수 있으며, make clean을 통해 생성된 파일 (*.o, *.out)을 모두 삭제할 수 있다. build의 기본 standard는 c++14로 설정되어 있다. make run을 통해 build와 run을 동시에 할 수 있다. 
