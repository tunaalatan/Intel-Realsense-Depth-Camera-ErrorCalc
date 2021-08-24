#include <iostream>
#include <cmath>
#include <cstdio>
#include <stdint.h>
#include <vector>

using namespace std;

class rawImage{
    public:
        string name;
        int distance;
        string path;
        vector<int> rawArray;

        rawImage(string filename){
            name = filename;
            path = "C:\\Users\\alatan\\Downloads\\DepthHistogram\\FinalImages\\" + name;
            distance = stoi(name.substr(0, 2)) * 10;
            if(name.substr(0,3) == "100"){
                distance = 1000;
            }
            
            FILE* file;
            short raw_array[240][424];

            file = fopen(path.c_str(), "rb");
            if(!feof(file)){
                fread(raw_array, 2, 424*240, file);
                for (int i = 0; i < 240; i++){
                    for(int j = 0; j < 424; j++){
                    }
                }
            }
            else{
                cout << "Cannot find directory: " << path;
            }
            for(int i = 0; i < 240; i++){
                for (int j = 0; j < 424; j++){
                    rawArray.push_back(raw_array[i][j]);
                }
            }
            rawArray = rawArray;
        }
        double errorClac(){
            int totalZeros = 0;
            double res, totalError, totalSum;

            for(int i = 0; i < 240 * 424; i++){
                   if(rawArray[i] == 0){
                       totalZeros += 1;
                       continue;
                   }
                   else{
                       totalSum += abs(rawArray[i] - distance);
                   } 
            }
            totalError = totalSum/(424 * 240 - totalZeros);
            res = totalError * 100 / distance;
            return res;
        }
};

int main(){
    double ans;
    vector<string> files {"25.Hali_Depth.raw", "25.Duvar_Depth.raw", "50.Duvar_Depth.raw", "50.Hali_Depth.raw", "100.Hali_Depth.raw", "100.Duvar_Depth.raw"};
    
    for (int i = 0; i < files.size(); i++){
        rawImage raw = rawImage(files[i]);
        ans = raw.errorClac();
        cout << files[i] << "  " << ans << endl;   
    
    }
}
