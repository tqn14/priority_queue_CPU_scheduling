#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "TemplatedDLList.h"

using namespace std; 
using namespace std::chrono;
int main() {
     DLList<int> dll; 
     cout << "--------Test PQ linked list type int-----------\n";
     cout << "Check is empty: \n";
     cout << (dll.is_empty()) << endl; 
     cout << "Check insert input: 8 2 20 0 -15 3 7 8 and make min p queue: \n";
     dll.insert(dll,-8); 
     dll.insert(dll,2); 
     dll.insert(dll,20); 
     dll.insert(dll,0); 
     dll.insert(dll,-15); 
     dll.insert(dll,3); 
     dll.insert(dll,7); 
     dll.insert(dll,8); 
     cout << dll << endl; 
     cout << "Test insert 100: \n"; 
     dll.insert(dll,100);
     cout << dll << endl;
     cout << "Test remove min: \n"; 
     int min = dll.remove_first();
     cout << "min is: " << min << endl;
     cout << dll << endl;
//      DLList<CPUjob> dll; 
//      ifstream fin("SetSize100000.txt"); 
//      fin >> dll; 
//      // ostream os(cout.rdbuf());
//      // os << dll.getObj();
//      ofstream out("SetSize100000list.txt"); 
//      DLListNode<CPUjob> *tmp = dll.first_node(); 
//      while(tmp!=dll.after_last_node()) {
//         CPUjob obj = tmp->getObj(); 
//         int b = obj.getLength(); 
//         while (b >0) 
//         { 
//           out << "Job "<< obj.getID();
//           out << " with length ";
//           out << b;
//           out << " and priority ";
//           out << obj.getPrior();
//           out << " ";
//           out << endl; 
//           b--;
//         }
//         tmp = tmp->getNext();
//     }
//     out << "No more job to run. "<< endl;
//     out.close();
     //ofstream out("SetSize4listout.txt");
//      for (auto a : job) {
//         int b = a.getLength(); 
//         while (b > 0) {
//             out << "Job "; 
//             out << a.getID();
//             out << " with length ";
//             out << b; 
//             out << " and priority "; 
//             out << a.getPrior();
//             b--; 
//             out << endl;
//         }
//     }
    // out << "No more job to run" << endl; 
    // out.close();
     // auto start1 = high_resolution_clock::now();
     // fin >> dll; 
     // auto stop1 = high_resolution_clock::now();
     // auto duration1 = duration_cast<seconds>(stop1-start1);
     // cout << "Input size 100000: \n"; 
     // cout << "------------Before insert-------------\n"; 
     // cout << "Time it takes to input and sort:" << duration1.count() << endl;
     // //cout << dll;
     // auto start2 = high_resolution_clock::now();
     // CPUjob a = CPUjob(112, 8, 15);
     // dll.insert(dll, a);
     // auto stop2 = high_resolution_clock::now();
     // auto duration2 = duration_cast<microseconds>(stop2-start2);
     // ostream os(cout.rdbuf());
     // cout << "------------After insert-------------\n"; 
     // cout << "Time it takes to input new obj into sorted linked list:" << duration2.count() << endl;
     //cout << dll;
     //dll.remove_first();
     //cout << dll;
}