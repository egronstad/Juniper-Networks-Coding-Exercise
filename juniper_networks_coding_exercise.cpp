#include <iostream>
#include <string>

using namespace std;

string ip = "";
int ip_int[4];

int* get_ip(string ip){
    //splitting to sections each number between the ip dots
    for(int i = 0; i<4; i++){
        ip_int[i] = stoi(ip.substr(0, '.'));
        //cout<<ip_int[i]<<" ";
        string z = to_string(ip_int[i]);
        int ln = z.length();
        ip.erase(0, ln+1);
    }
    return ip_int;
}

string ip_bin[1024];

void dec(){
    int bin =0;
    int i=1;
    for(int  s=0; s<4; s++){
        while(ip_int[s] >0 ){
            bin += (ip_int[s]%2)*i;
            ip_int[s] = ip_int[s]/2;
            i*=10;
        }
        ip_bin[s] = to_string(bin);
        //cout << ip_bin[s] << " ";
        bin = 0;
        i=1;
    }
}

int num_shared_bits(string str1, string str2){
    int count = 0;
    int len = min(str1.length(), str2.length());
    for (int i = 0; i < len; i++){
        if (str1[i] != str2[i])
            break;
        count++;
    }
    return (count);
}

string binary[4];

int main(){
    string ip_adds[7] = {"192.168.0.16", "192.168.0.17", "192.168.0.18", "192.168.0.19", "192.168.0.66", "192.168.0.122", "192.168.0.123"};
    int size = sizeof(ip_adds)/sizeof(ip_adds[0]);
    string least = "";
    string most = "";
    for (int k = 0; k < size; k++){
        string str_temp = ip_adds[k];
        get_ip(str_temp);
        dec();
        for (int j=0; j<4; j++){
            while (ip_bin[j].length()<8){
                ip_bin[j]='0'+ip_bin[j];
            }
            binary[k] += ip_bin[j];
            
        }
        if (least == ""){
            least = binary[k];
        }
        if (binary[k] > most){
            most = binary[k];
        }else if (binary[k] < least){
            least = binary[k];
        }
    }
    /*
    cout << "most: " << most << endl;
    cout << "least: " << least << endl;
    */
    cout << "minimum hostmask: /" << num_shared_bits(most, least) << endl;
    return 0;
}