// #include <iostream>
// #include <thread>

// void Loop1(){
//     while (true) {
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//         std::cout << "************** 111111 *********** \n" << std::endl;
//     }
// }
// void Loop2(){
//     while (true) {
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//         std::cout << "############### 2222222 ############### \n" << std::endl;
//     }
// }
// int main() {

//    std::thread t1(Loop1);
//    std::thread t2(Loop2);

//     t1.join();
//     t2.join();

//     return 0;
// }