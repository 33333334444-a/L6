#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct TV {
  string manufacturer;
  string model;
  double diagonal;
  int quantity;
  double price;
};

int main() {
  vector<TV> televisions;

  ifstream input("input.txt");
  if (!input) {
    cout << "ERROR";
    return 1;
  }

  string line;

  while (getline(input, line)){
    istringstream stream(line);

    string manufacturer;
    string model;
    string diagonal;
    string quantity;
    string price;

    getline(stream, manufacturer, ';');
    getline(stream, model, ';');
    getline(stream, diagonal, ';');
    getline(stream, quantity, ';');
    getline(stream, price, ';');

    TV television;
    television.manufacturer = manufacturer;
    television.model = model;
    television.diagonal = stod(diagonal);
    television.quantity = stoi(quantity);
    television.price = stod(price);

    televisions.push_back(television);
  }
  ostringstream report;

  string targetManufacturer;
  cout << "Enter manufacturer: ";
  cin >> targetManufacturer;
  vector<TV> targets;
  double totalprice = 0.0;

  if (televisions.empty()) {
    report << "No TVs in file";
    return 0;
  }
  for (const TV& tv : televisions) {
    if (tv.manufacturer == targetManufacturer) {
      report << tv.model << endl;
      totalprice = totalprice + tv.quantity * tv.price;
      targets.push_back(tv);
    }
  }
  if (targets.empty()) {
  report << "No TVs from this manufacturer." << endl;
  }
  
  int maxindex = 0;
  for (int i = 1; i < televisions.size(); ++i) {
    if (televisions[i].diagonal > televisions[maxindex].diagonal) {
      maxindex = i;
    }
  }


  report << "\nMaxdiagonal: " << televisions[maxindex].diagonal << endl;
  report << "Total price: " << totalprice << endl;
  report << "Manufacturer: " << televisions[maxindex].manufacturer << endl;
  report << "Model: " << televisions[maxindex].model << endl;
  report << "Diagonal: " << televisions[maxindex].diagonal << " cm" << endl;
  report << "Quantity: " << televisions[maxindex].quantity << endl;
  report << "Price per unit: " << televisions[maxindex].price << endl;

  cout << report.str();

  ofstream output("output.txt");

  if (!output) {
    cout << "ERROR";
    return 1;
  }

  output << report.str();
}