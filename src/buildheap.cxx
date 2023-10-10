#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;

int main(int argc, char** argv) {
  nlohmann::json jsonObject1, jsonObject2;
  string currentOperation;
  ifstream file;
  file.open(argv[1]);
  if (file.is_open()) {
    file >> jsonObject1;
  }
  file.close();
  int numOperations = jsonObject1["metadata"]["numOperations"];
  int maxSize = jsonObject1["metadata"]["maxHeapSize"];
  PriorityQueue Heap(maxSize);
  for (auto itr = jsonObject1.begin(); itr.key() != "metadata"; ++itr) {
    string currentOperation = jsonObject1[itr.key()]["operation"];
    if (currentOperation == "insert") {
      Key currentKey = jsonObject1[itr.key()]["key"];
      Heap.insert(currentKey);
    }
    else if (currentOperation == "removeMin") {
      Heap.removeMin();
    }
  }
  jsonObject2 = Heap.JSON();
  jsonObject2["metadata"]["numOperations"] = numOperations;
  jsonObject2["metadata"]["maxHeapSize"] = maxSize;
  cout << jsonObject2.dump(2) << endl;
}
