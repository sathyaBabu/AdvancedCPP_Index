

// 17_NameSpaceINineVersioning

#include <utility>
#include<memory>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

   namespace Wifi_App_Versioning
   {
      
      namespace version_1 {
          void transmitPacket(){
              cout << endl << "Transsmiting via xyz protocall ver 1  : " << endl ;
          }
      }
      namespace version_2 {
//          [[deprecated("Use transmitPacket() version_3  instead.")]]
          void transmitPacket(){
              cout << endl << "Transsmiting via xyz protocall Updated ver 2  : " << endl ;
          }
      }
   
   inline namespace version_3 {
       void transmitPacket(){
           cout << endl << "Transsmiting via xyz protocall Bug fixed  ver 3  : " << endl ;
       }
       void transmitPacketViaVoIP(){
           cout << endl << "Transsmiting via VoIP protocall Latest APi in  ver 3 : " << endl;
       }
   }
} // closing name space



int main(void) {
    
    Wifi_App_Versioning::transmitPacket();
    Wifi_App_Versioning::version_2:: transmitPacket();
    Wifi_App_Versioning::transmitPacketViaVoIP();
    
   
     
}
/*
 Transsmiting via xyz protocall Bug fixed  ver 3  :

 Transsmiting via xyz protocall Updated ver 2  :

 Transsmiting via VoIP protocall Latest APi in  ver 3 :
 Program ended with exit code: 0
 */
